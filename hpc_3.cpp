#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int sequentialSum(vector<int> &a,int n){
   
    int sum1=0;
    for(int i=0;i<n;i++){
        sum1+=a[i];
    }
    
    return sum1;
}

int sequentialMin(vector<int> &a,int n){
    int mn=INT_MAX;
    for(int i=0;i<n;i++){
        mn=min(mn,a[i]);
    }
    return mn;
}

int sequentialMax(vector<int> &a,int n){
    int mx=INT_MIN;
    for(int i=0;i<n;i++){
        mx=max(mx,a[i]);
    }
    return mx;
}
int sum(vector<int> &a,int n){
    int ans=0;
    #pragma omp parallel 
    {
        int sum1=0;
        #pragma omp for 
        for(int i=0;i<n;i++){
            sum1+=a[i];
        }
        ans+=sum1;
    }
    return ans;
}
int rec_min(vector<int> &a,int l,int r){
    if(l==r){
        return a[l];
    }
    int lmin,rmin;
    #pragma omp parallel sections
    {
        
        #pragma omp section
        {
            int mid = (l+r)/2;
            lmin=rec_min(a,l,mid);
        }
        #pragma omp section
        {
            int mid = (l+r)/2;
            rmin=rec_min(a,mid+1,r);
        }
    }
    return min(lmin,rmin);
}

int rec_max(vector<int> &a,int l,int r){
    if(l==r){
        return a[l];
    }
    int lmax,rmax;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int mid = (l+r)/2;
            lmax=rec_max(a,l,mid);
        }
        #pragma omp section
        {
            int mid = (l+r)/2;
            rmax=rec_max(a,mid+1,r);
        }
    }
    return max(lmax,rmax);
}

int main(){
    int n;
    cout<<"Enter number of elements in an array:"<<endl;
    cin>>n;
    vector<int> a(n);
    cout<<"Enter elements in a vector:"<<endl;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    double start = omp_get_wtime();
    cout<<"Sum is:"<<sum(a,n)<<endl;
    double end = omp_get_wtime();
    cout<<"Time taken by parallel Sum function: "<<(end-start)<<endl;

    start = omp_get_wtime();
    cout<<"Minimum is:"<<rec_min(a,0,n-1)<<endl;
    end = omp_get_wtime();
    cout<<"Time taken by parallel Min function: "<<(end-start)<<endl;

    start = omp_get_wtime();
    cout<<"Maximum is:"<<rec_max(a,0,n-1)<<endl;
    end = omp_get_wtime();
    cout<<"Time taken by parallel Max function: "<<(end-start)<<endl;

    start = omp_get_wtime();
    cout<<"Sum is:"<<sequentialSum(a,n)<<endl;
    end = omp_get_wtime();
    cout<<"Time taken by Sequential Sum function: "<<(end-start)<<endl;

    start = omp_get_wtime();
    cout<<"Minimum is:"<<sequentialMin(a,n)<<endl;
    end = omp_get_wtime();
    cout<<"Time taken by Sequential Min function: "<<(end-start)<<endl;

    start = omp_get_wtime();
    cout<<"Sum is:"<<sequentialMax(a,n)<<endl;
    end = omp_get_wtime();
    cout<<"Time taken by Sequential Max function: "<<(end-start)<<endl;
   
    
}