#include <bits/stdc++.h>
using namespace std;

void min_heapify(int arr[], int *Q1, int n, int i)
{
    int smallest = i;  // Initialize smallest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && arr[Q1[l]] < arr[Q1[smallest]])
        smallest = l;
 
    // If right child is larger than smallest so far
    if (r < n && arr[Q1[r]] < arr[Q1[smallest]])
        smallest = r;
 
    // If smallest is not root
    if (smallest != i)
    {
        swap(Q1[i], Q1[smallest]);
        // Recursively heapify the affected sub-tree
        min_heapify(arr, Q1, n, smallest);
    }
}

void make_min_heap(int *A, int *Q1, int *I1, int s)
{
    for (int i = s / 2 - 1; i >= 0; i--)
 	   min_heapify(A, Q1, s, i);
 	for (int i=0;i<s;i++)
 	{
 		int temp=Q1[i];
 		I1[temp]=i;
 	}
}

void max_heapify(int arr[], int *Q2, int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && arr[Q2[l]] > arr[Q2[largest]])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && arr[Q2[r]] > arr[Q2[largest]])
        largest = r;
 
    // If largest is not root
    if (largest != i)
    {
        swap(Q2[i], Q2[largest]);
        // Recursively heapify the affected sub-tree
        max_heapify(arr, Q2, n, largest);
    }
}

void make_max_heap(int *A, int *Q2, int *I2, int s)
{
    for (int i = s / 2 - 1; i >= 0; i--)
 	   max_heapify(A, Q2, s, i);
 	for (int i=0;i<s;i++)
 	{
 		int temp=Q2[i];
 		I2[temp]=i;
 	}
}

void mcquicksort(int s)
{
	int A[s],Q1[s],Q2[s],I1[s],I2[s];
	for (int i=0;i<s;i++)
	{
		cin>>A[i];
		Q1[i]=Q2[i]=i;
	}
	make_min_heap(A,Q1,I1,s);
	make_max_heap(A,Q2,I2,s);
	cout<<"\n";
	for (int i=0;i<s;i++)
		cout<<A[Q1[i]]<<"  "<<Q1[i]<<" "<<I1[i]<<endl;
	cout<<"Max heap: \n";
	for (int i=0;i<s;i++)
		cout<<A[Q2[i]]<<"  "<<Q2[i]<<" "<<I2[i]<<endl;
}

int main()
{
	system("clear");
	cout<<"Enter n: ";
	int n,s;
	cin>>n;
	cout<<"Enter s: ";
	cin>>s;
	mcquicksort(s);
}