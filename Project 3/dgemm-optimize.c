
//reordering https://cs61.seas.harvard.edu/wiki/images/0/0f/Lec14-Cache_measurement.pdf
void dgemm( int m, int n, float *A, float *C )
{
    for( int k = 0; k < m; k++ ){
        for( int i = 0; i < n; i++ ){
            for( int j = 0; j < m; j++){
                 C[i+j*m] += A[i+k*m] * A[j+k*m];
            } 
        }            
    }       
}

//loop unrolling with duff's device https://riptutorial.com/c/example/28504/loop-unrolling-and-duff-s-device
void dgemm( int m, int n, float *A, float *C )
{
    for( int i = 0; i < m; i++ ){
        for( int k = 0; k < n; k++ ){
            for( int j = 0; j < m; j += 4){
                switch(j % 4) do{
                    case 0:
                        C[i+(j+3)*m] += A[i+k*m] * A[(j+3)+k*m];
                        break;
                    case 3:
                        C[i+(j+2)*m] += A[i+k*m] * A[(j+2)+k*m];
                        break;
                    case 2:
                        C[i+(j+1)*m] += A[i+k*m] * A[(j+1)+k*m];
                        break;
                    case 1:
                        C[i+j*m] += A[i+k*m] * A[j+k*m];
                        break;
                }while((n -= 4) > 0);
            } 
        }            
    }       
}

//blocking/tiling
void dgemm( int m, int n, float *A, float *C )
{
    int blocksize = 64;
    for( int ii = 0; ii < m; ii += blocksize ){
        for( int kk = 0; kk < n; kk += blocksize ){
            for( int jj = 0; jj < m; jj += blocksize ){
                for( int i = ii; i < ii + blocksize; i++ ){
                    for( int k = kk; k < kk + blocksize; k++ ){
                        float tempBlock = A[i+k*m];
                        for( int j = jj; j < jj + blocksize; j++ ){
                            C[i+j*m] += tempBlock * A[j+k*m];
                        }
                    }
                }
                 
            } 
        }            
    }       
}

// SEE instructions
void dgemm( int m, int n, float *A, float *C )
{
  for( int i = 0; i < m; i++ )
    for( int k = 0; k < n; k++ ) 
      for( int j = 0; j < m; j++ ) 
	C[i+j*m] += A[i+k*m] * A[j+k*m];
    
    

}


