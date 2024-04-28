%%cu

#include <bits/stdc++.h>
using namespace std;

__global__ void mul(int *X, int *Y, int *Z, int size){
    int row=blockIdx.y * blockDim.y + threadIdx.y;
    int col=blockIdx.x * blockDim.x + threadIdx.x;
    if(row<size && col<size){
        int sum=0;
        for(int i=0;i<size;i++){
          sum+=X[row*size+i]*Y[i*size+col];

        }
        Z[row*size+col]=sum;
    }
}

void initialize(int *arr, int n){
    for(int i=0;i<n*n;i++){
          arr[i]=rand()%10;
    }   
}

void print(int *mat, int size){
    for(int row=0;row<size;row++){
        for(int col=0;col<size;col++){
            cout<<mat[row * size + col]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main(){
    int *A, *B, *C;
    int N=2;
    int matsize=N*N;
    int blockSize =  16;
    size_t matbytes=matsize * sizeof(int);


    A=new int[matsize];
    B=new int[matsize];
    C=new int[matsize];

    initialize(A,N);
    initialize(B,N);

    cout<<"print matrix A: ";
    print(A,N);
    cout<<"print matrix B: ";
    print(B,N);
    
    int *X, *Y, *Z;
    cudaMalloc(&X, matbytes);
    cudaMalloc(&Y, matbytes);
    cudaMalloc(&Z, matbytes);

    cudaMemcpy(X,A,matbytes,cudaMemcpyHostToDevice);
    cudaMemcpy(Y,B,matbytes,cudaMemcpyHostToDevice);

    int THREADS=2;
    int BLOCKS= N / THREADS;

    dim3 threads(THREADS,THREADS);
    dim3 blocks(BLOCKS,BLOCKS);


    mul<<<blocks,threads>>>(X,Y,Z,N);

    cudaMemcpy(C,Z,matbytes,cudaMemcpyDeviceToHost);

    cout<<"Multiplication matrix is: "<<endl;
    print(C,N);

    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);



    return 0;


}
