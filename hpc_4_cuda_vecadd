%%cu

#include <bits/stdc++.h>
using namespace std;

__global__ void add(int *X, int *Y, int *Z, int size){

    int tid=blockIdx.x * blockDim.x + threadIdx.x;
    if(tid<size){
        Z[tid]=X[tid]+Y[tid];
    }
}

void initialize(int *arr, int n){
    for(int i=0;i<n;i++){
        arr[i]=rand()%10;
    }
}

void print(int *vec, int size){
    for(int i=0;i<size;i++){
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int *A, *B, *C;
    int N=8;
    int vectorsize=N;
    size_t vectorbytes=vectorsize * sizeof(int);

    A=new int[vectorsize];
    B=new int[vectorsize];
    C=new int[vectorsize];

    initialize(A,vectorsize);
    initialize(B,vectorsize);

    cout<<"print vector A: ";
    print(A,N);
    cout<<"print vector B: ";
    print(B,N);
    
    int *X, *Y, *Z;
    cudaMalloc(&X, vectorbytes);
    cudaMalloc(&Y, vectorbytes);
    cudaMalloc(&Z, vectorbytes);

    cudaMemcpy(X,A,vectorbytes,cudaMemcpyHostToDevice);
    cudaMemcpy(Y,B,vectorbytes,cudaMemcpyHostToDevice);

    int threadsperBlock=256;
    int blocksperGrid= (N + threadsperBlock-1) / threadsperBlock;

    add<<<blocksperGrid,threadsperBlock>>>(X,Y,Z,N);

    cudaMemcpy(C,Z,vectorbytes,cudaMemcpyDeviceToHost);

    cout<<"Addition vector is: "<<endl;
    print(C,N);

    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);



    return 0;


}
