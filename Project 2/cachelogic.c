#include "tips.h"

/* The following two functions are defined in util.c */

/* finds the highest 1 bit, and returns its position, else 0xFFFFFFFF */
unsigned int uint_log2(word w); 

/* return random int from 0..x-1 */
int randomint( int x );

/*
  This function allows the lfu information to be displayed

    assoc_index - the cache unit that contains the block to be modified
    block_index - the index of the block to be modified

  returns a string representation of the lfu information
 */
char* lfu_to_string(int assoc_index, int block_index)
{
  /* Buffer to print lfu information -- increase size as needed. */
  static char buffer[9];
  sprintf(buffer, "%u", cache[assoc_index].block[block_index].accessCount);

  return buffer;
}

/*
  This function allows the lru information to be displayed

    assoc_index - the cache unit that contains the block to be modified
    block_index - the index of the block to be modified

  returns a string representation of the lru information
 */
char* lru_to_string(int assoc_index, int block_index)
{
  /* Buffer to print lru information -- increase size as needed. */
  static char buffer[9];
  sprintf(buffer, "%u", cache[assoc_index].block[block_index].lru.value);

  return buffer;
}

/*
  This function initializes the lfu information

    assoc_index - the cache unit that contains the block to be modified
    block_number - the index of the block to be modified

*/
void init_lfu(int assoc_index, int block_index)
{
  cache[assoc_index].block[block_index].accessCount = 0;
}

/*
  This function initializes the lru information

    assoc_index - the cache unit that contains the block to be modified
    block_number - the index of the block to be modified

*/
void init_lru(int assoc_index, int block_index)
{
  cache[assoc_index].block[block_index].lru.value = 0;
}

/*
  This is the primary function you are filling out,
  You are free to add helper functions if you need them

  @param addr 32-bit byte address
  @param data a pointer to a SINGLE word (32-bits of data)
  @param we   if we == READ, then data used to return
              information back to CPU

              if we == WRITE, then data used to
              update Cache/DRAM
*/
void accessMemory(address addr, word* data, WriteEnable we)
{
  /* Declare variables here */
  unsigned int tagValue, tagLength, indexValue, indexLength, offsetValue, offsetLength, offsetMask, indexMask;
  unsigned int hit, byteAmount, blockAccessed = 0, maxValue = 0;
  address saveAddr = 0;

  /* handle the case of no cache at all - leave this in */
  if(assoc == 0) {
    accessDRAM(addr, (byte*)data, WORD_SIZE, we);
    return;
  }

  /*
  You need to read/write between memory (via the accessDRAM() function) and
  the cache (via the cache[] global structure defined in tips.h)

  Remember to read tips.h for all the global variables that tell you the
  cache parameters

  The same code should handle random, LFU, and LRU policies. Test the policy
  variable (see tips.h) to decide which policy to execute. The LRU policy
  should be written such that no two blocks (when their valid bit is VALID)
  will ever be a candidate for replacement. In the case of a tie in the
  least number of accesses for LFU, you use the LRU information to determine
  which block to replace.

  Your cache should be able to support write-through mode (any writes to
  the cache get immediately copied to main memory also) and write-back mode
  (and writes to the cache only gets copied to main memory when the block
  is kicked out of the cache.

  Also, cache should do allocate-on-write. This means, a write operation
  will bring in an entire block if the block is not already in the cache.

  To properly work with the GUI, the code needs to tell the GUI code
  when to redraw and when to flash things. Descriptions of the animation
  functions can be found in tips.h
  */

  /* Start adding code here */
  offsetLength = uint_log2(block_size);
  indexLength = uint_log2(set_count);   
  tagLength = 32 - (indexLength + offsetLength);
  byteAmount = uint_log2(block_size);

  offsetMask = ((1 << offsetLength) - 1);
  indexMask = ((1 << indexLength) - 1);
  
  offsetValue = addr & offsetMask;
  indexValue = (addr >> offsetLength) & indexMask;
  tagValue = addr >> (offsetLength + indexLength); 

  for(int i = 0; i < assoc; i++){
    if(policy == LRU){
      cache[indexValue].block[i].lru.value++;
    }
    if(cache[indexValue].block[i].tag == tagValue && cache[indexValue].block[i].valid == 1){      
      hit = 1;
      blockAccessed = i;
      break;
    }
  }
  if(hit == 1){
    cache[indexValue].block[blockAccessed].lru.value = 0;
    highlight_offset(indexValue, blockAccessed, offsetValue, HIT);
    if(we == READ){
      memcpy(data, cache[indexValue].block[blockAccessed].data + offsetValue, byteAmount);
    }else{
      memcpy(cache[indexValue].block[blockAccessed].data + offsetValue, data, byteAmount); 
      accessDRAM(addr, cache[indexValue].block[blockAccessed].data, byteAmount, WRITE);  
      if(memory_sync_policy == WRITE_BACK){
        cache[indexValue].block[blockAccessed].dirty = DIRTY;
      }else{
        cache[indexValue].block[blockAccessed].dirty = VIRGIN;
      }
    }
  }else{
    if(policy == LRU){
      for(int i = 0; i < assoc; i++){
        if(cache[indexValue].block[i].lru.value > maxValue){
          blockAccessed = i;
          maxValue = cache[indexValue].block[i].lru.value;          
        }
      }
    }else if(policy == RANDOM){
      blockAccessed = randomint(assoc);
    }

    highlight_block(indexValue, blockAccessed); 
    highlight_offset(indexValue, blockAccessed, offsetValue, MISS);

    if(memory_sync_policy == WRITE_BACK){
      if(cache[indexValue].block[blockAccessed].dirty == DIRTY){
        saveAddr = (cache[indexValue].block[blockAccessed].tag << (offsetLength + indexLength)) | (indexValue << offsetLength);
        accessDRAM(saveAddr, (byte*)cache[indexValue].block[blockAccessed].data, byteAmount, WRITE);
      }
    }
    
    if(we == READ){
      memcpy(data, cache[indexValue].block[blockAccessed].data + offsetValue, byteAmount);
    }else{
      memcpy(cache[indexValue].block[blockAccessed].data + offsetValue, data, byteAmount);
    }
    
    accessDRAM(addr, cache[indexValue].block[blockAccessed].data, byteAmount, READ);
    cache[indexValue].block[blockAccessed].tag = tagValue;
    cache[indexValue].block[blockAccessed].valid = VALID;
    cache[indexValue].block[blockAccessed].lru.value = 0;
  }
}