#include <bits/stdc++.h>
#define N 999999
using namespace std;
using namespace std::chrono;

void swap(long *a, long *b)
{
    long temp = *a;
    *a = *b;
    *b = temp;
}

//Normal partition method
long partition(long arr[], long p, long q)
{
    long pivot = arr[q];
    long i = p;
    for (long j = p; j < q; j++)
    {
        if (arr[j] <= pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[q]);
    return i;
}

// Randomized pivot selection
long randPartition(long arr[], long p, long q)
{
    srand(time(NULL));
    long r = p + rand() % (q - p);
    swap(&arr[r], &arr[q]);
    long pivot = arr[q];
    long i = p;
    for (long j = p; j < q; j++)
    {
        if (arr[j] <= pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[q]);
    return i;
}

//Quicksort
void QuickSort(long arr[], long low, long high)
{
    if (low < high)
    {
    long p = partition(arr, low, high);
    QuickSort(arr, low, p - 1);
    QuickSort(arr, p + 1, high);
    }
}

//RandQuicksort
void randQuickSort(long arr[], long low, long high)
{
    if (low <high)
    {
    long p = randPartition(arr, low, high);
    randQuickSort(arr, low, p - 1);
    randQuickSort(arr, p + 1, high);
    }
}

int main()
{
    //long a[N], b[N];
    long* a=new long[N];
    long* b=new long[N];

    long n, k;
    cin >> n;
    for (long i = 1; i <= n; i++)
        {
            //cin >> a[i];
            a[i-1]=i;
            b[i-1]=i;
        }
    //copy(a, a + n, b);
    //Normal Quicksort
    
    auto start1 = high_resolution_clock::now();
    QuickSort(b, 0, n - 1);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);
  
    //Randomized Quicksort
    auto start2 = high_resolution_clock::now();
    randQuickSort(b, 0, n - 1);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);

    cout << "Time taken by Normal Quicksort: " << duration1.count() << " ms" << endl;
    cout << "Time taken by Randomized Quicksort: " << duration2.count() << " ms" << endl;
   /*
    cout << "After Sorting \n";
    for (int i = 0; i < n; i++)
        cout << b[i] << " ";
    cout << endl;
    */
    delete[] a;
    delete[] b;
    return 0;
}
