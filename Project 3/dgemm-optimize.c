///*
//reordering 
void dgemm( int m, int n, float *A, float *C )
{
    for( int j = 0; j < m; j++ ){
        for( int k = 0; k < n; k++ ){
            for( int i = 0; i < m; i++){
                 C[i+j*m] += A[i+k*m] * A[j+k*m];
            } 
        }            
    }       
}
//*/
/*
//loop unrolling
void dgemm( int m, int n, float *A, float *C )
{
    int steps = 4;
    int stepsminone = steps - 1;
    int distance = 0;
    for( int i = 0; i < m; i++ ){
        for( int k = 0; k < n; k++ ){
            for( int j = 0; j < m; j += steps){
                distance = m - j;
                if( distance > stepsminone){
                    distance = steps;
                }
                switch(distance){                   
                        
                    case 4:
                        C[i+(j+3)*m] += A[i+k*m] * A[(j+3)+k*m];
                        
                    case 3:
                        C[i+(j+2)*m] += A[i+k*m] * A[(j+2)+k*m];
                        
                    case 2:
                        C[i+(j+1)*m] += A[i+k*m] * A[(j+1)+k*m]; 
                        
                    default:
                        C[i+j*m] += A[i+k*m] * A[j+k*m];
                }
                                   
            }
        } 
    }  
}       
*/
/*
//blocking/tiling
void dgemm( int m, int n, float *A, float *C )
{
    // i and j get m k gets n
    int blocksize = 1;
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
*/
