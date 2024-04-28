#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

vector<int> sequentialBubbleSort(vector<int> a, int n)
{
    for (int i = 0; i < n; i++)
    {
#pragma omp parallel num_threads(n)
        {
            int id = omp_get_thread_num();
            if (i % 2)
            {
                if (id % 2)
                {
#pragma omp critical
                    {
                        if (id + 1 < n)
                        {
                            if (a[id] >= a[id + 1])
                            {
                                swap(a[id], a[id + 1]);
                            }
                        }
                    }
                }
            }
            else
            {
                if (id % 2 == 0)
                {
#pragma omp critical
                    {
                        if (id + 1 < n)
                        {
                            if (a[id] >= a[id + 1])
                            {
                                swap(a[id], a[id + 1]);
                            }
                        }
                    }
                }
            }
        }
    }
    return a;
}

vector<int> bubbleSort(vector<int> a, int n)
{
    for (int i = 0; i < n; i++)
    {
#pragma omp parallel num_threads(n)
        {
            int id = omp_get_thread_num();
            if (i % 2)
            {
                if (id % 2)
                {
#pragma omp critical
                    {
                        if (id + 1 < n)
                        {
                            if (a[id] >= a[id + 1])
                            {
                                swap(a[id], a[id + 1]);
                            }
                        }
                    }
                }
            }
            else
            {
                if (id % 2 == 0)
                {
#pragma omp critical
                    {
                        if (id + 1 < n)
                        {
                            if (a[id] >= a[id + 1])
                            {
                                swap(a[id], a[id + 1]);
                            }
                        }
                    }
                }
            }
        }
    }
    return a;
}

void merge(vector<int> &a, int low, int high)
{
    int mid = (low + high) / 2;
    vector<int> left, right;
    for (int i = low; i <= mid; i++)
    {
        left.push_back(a[i]);
    }
    for (int i = mid + 1; i <= high; i++)
    {
        right.push_back(a[i]);
    }
    int i = 0, j = 0, curr = low;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
        {
            a[curr] = left[i];
            i++;
        }
        else
        {
            a[curr] = right[j];
            j++;
        }
        curr++;
    }
    while (i < left.size())
    {
        a[curr] = left[i];
        i++;
        curr++;
    }
    while (j < right.size())
    {
        a[curr] = right[j];
        j++;
        curr++;
    }
}
void mergeSort(vector<int> &a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            mergeSort(a, low, mid);
#pragma omp section
            mergeSort(a, mid + 1, high);
        }
        merge(a, low, high);
    }
}
int main()
{
    int n;
    cout << "Enter number of elements in array:";
    cin >> n;
    vector<int> a(n);
    cout << "Enter elements of the array:" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    // mergeSort(a,0,n-1);
    // vector<int> ans = bubbleSort(a, n);
    double start = omp_get_wtime();
    vector<int> ans = bubbleSort(a, n);
    double end = omp_get_wtime();
    // cout << end - start << "\n";
    
    cout <<"Time for parallel bubble sort:"<< (end-start) << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    start = omp_get_wtime();
    
    vector<int> sol = sequentialBubbleSort(a, n);
    
    end = omp_get_wtime();
    // cout end - start << "\n";
    
    cout << "Time for sequential bubble sort:" <<(end-start) << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << sol[i] << " ";
    }
    cout << endl;

    
    start = omp_get_wtime();
    
    mergeSort(a,0,n-1);
    
    end = omp_get_wtime();
    // cout end - start << "\n";
    
    cout << "Time for parallel merge sort:" <<(end-start) << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    
    return 0;
}