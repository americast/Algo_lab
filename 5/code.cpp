/* Name: code.cpp
  Creator: Sayan Sinha (sayan.sinha@iitkgp.ac.in)
  Date: August 17, 2017
  Description: Heaps and Priority Queues 
*/

#include <bits/stdc++.h>
using namespace std;

void adjustI1(int *Q1, int *I1, int s)
{
 	for (int i=0;i<s;i++)
 	{
 		int temp=Q1[i];
 		I1[temp]=i;
 	}
}

void minheapify(int *A, int *Q1, int s, int i)
{
    int smallest = i;  	// Initialize smallest as root
    int l = 2*i + 1;  		// left = 2*i + 1
    int r = 2*i + 2;		// right = 2*i + 2
 
    if (l < s && A[Q1[l]] < A[Q1[smallest]])
        smallest = l;
 
    if (r < s && A[Q1[r]] < A[Q1[smallest]])
        smallest = r;

    if (smallest != i)
    {
        int temp = Q1[i];
        Q1[i] = Q1[smallest];
        Q1[smallest] = temp;
        minheapify(A, Q1, s, smallest);
    }
}

/* Name: makeminheap
  Input: *A, *Q1, *I1, s (no of elements)
  Output: <none>
  Description: Make a mean heap out of an arbitrary array. The code does not change the array, but only 
  	changes Q1, the location of every element in the array.
*/
void makeminheap(int *A, int *Q1, int *I1, int s)
{
    for (int i = s / 2 - 1; i >= 0; i--)
 	minheapify(A, Q1, s, i);
    adjustI1(Q1,I1,s);
}

int getmin(int *A, int *Q1)
{
	return A[Q1[0]];
}

void adjustI2(int *Q2, int *I2, int s)
{
 	for (int i=0;i<s;i++)
 	{
 		int temp=Q2[i];
 		I2[temp]=i;
 	}
}

void maxheapify(int arr[], int *Q2, int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;    // left = 2*i + 1
    int r = 2*i + 2;   // right = 2*i + 2
 
    if (l < n && arr[Q2[l]] > arr[Q2[largest]])
        largest = l;
     if (r < n && arr[Q2[r]] > arr[Q2[largest]])
        largest = r;
 
    if (largest != i)
    {
        int temp = Q2[i];
        Q2[i] = Q2[largest];
        Q2[largest] = temp;
        maxheapify(arr, Q2, n, largest);
    }
}

/* Name: makemaxheap
  Input: *A, *Q2, *I2, s (no of elements)
  Output: <none>
  Description: Make a mean heap out of an arbitrary array. The code does not change the array, but only 
  	changes Q2, the location of every element in the array.
*/

void makemaxheap(int *A, int *Q2, int *I2, int s)
{
	for (int i = s / 2 - 1; i >= 0; i--)
		maxheapify(A, Q2, s, i);
		adjustI2(Q2,I2,s);
}

int getmax(int *A, int *Q2)
{
	return A[Q2[0]];
}

/* Name: heapsort
  Input: *A, *H, *Q1, *I1, s (no of elements)
  Output: <none>
  Description: Heap sort A and place the output in H.
*/

void heapsort(int *A, int *H, int *Q1, int *I1, int s)
{
	int j=0;
	for (int i=s-1; i>=0; i--)
	 {
	    	H[j++] = A[Q1[0]];
		A[Q1[0]] = INT_MAX;
		int temp = Q1[0];
		Q1[0]=Q1[i];
		Q1[i] = temp;
	 
		minheapify(A, Q1, s, 0);
		adjustI1(Q1,I1,s);
	 }
}
/* Name: mcquicksort
  Input: *M, *A, n, s (no of elements)
  Output: <none>
  Description: Sort array M such that maximum allocated memory remains s.
*/
void mcquicksort(int *M,int n,int s)
{
	if (n<=1)
		return;
	if (n<s)
		s=n;
	// system("clear");
	int *H = (int *)malloc(sizeof(int)*s);
	int *L = (int *)malloc(sizeof(int)*(n-s));
	int *R = (int *)malloc(sizeof(int)*(n-s));
	int *A = (int *)malloc(sizeof(int)*s);
	int Q1[s],Q2[s],I1[s],I2[s];
	for (int i=0;i<s;i++)
	{
		A[i]=M[i];
		Q1[i] = Q2[i] = i;
	}
	makeminheap(A,Q1,I1,s);
	makemaxheap(A,Q2,I2,s);
	int flag=0;
	int lpos=0, rpos=0;
	for (int i=s;i<n;i++)
	{
		if (M[i]<=getmin(A,Q1))	// if element is less than min
			L[lpos++]=M[i];
		else if (M[i]>=getmax(A,Q2))	// if element is greater than max
			R[rpos++]=M[i];
		else 				// otherwise
		{
			if (flag%2==0)
			{
				L[lpos++]=A[Q1[0]];
				A[Q1[0]] = M[i];
				minheapify(A,Q1,s,0);
				adjustI1(Q1,I1,s);
				makemaxheap(A,Q2,I2,s);
			}
			else
			{
				R[rpos++] = A[Q2[0]];
				A[Q2[0]] = M[i];
				maxheapify(A,Q2,s,0);
				adjustI2(Q2,I2,s);
				makeminheap(A,Q1,I1,s);
			}
			flag++;
		}
	}
	heapsort(A,H,Q1,I1,s);
	free(A);
	int lcopy[lpos], rcopy[rpos];
	for (int i=0;i<lpos;i++)
	{
		lcopy[i]=L[i];
	}
	free(L);
	for (int i=0;i<rpos;i++)
	{
		rcopy[i]=R[i];
	}
	free(R);
	mcquicksort(lcopy,lpos,s);
	mcquicksort(rcopy,rpos,s);
	int i=0;
	for (i=0;i<lpos;i++)
	{
		M[i]=lcopy[i];
	}
	for (int j=0;j<s;j++,i++)
	{
		M[i]=H[j];
	}
	for (int j=0;j<rpos;j++,i++)
	{
		M[i]=rcopy[j];
	}
	// cout<<"\n";
	// cout<<"\nM: ";
	// for (int i=0;i<n;i++)
	// 	cout<<M[i]<<" ";
	free(H);

}

int main()
{
	system("clear");
	cout<<"Enter n: ";
	int n,s;
	cin>>n;
	cout<<"Enter s: ";
	cin>>s;
	int *M = (int *)malloc(sizeof(int)*n);
	for (int i=0;i<n;i++)
		cin>>M[i];
	mcquicksort(M,n,s);
	cout<<"\n\n+++ Array after sorting\n";
	for (int i=0;i<n;i++)
		cout<<M[i]<<"\t";
	cout<<endl;
}