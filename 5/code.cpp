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
	cout<<"here also\n";
    int smallest = i;  // Initialize smallest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2
 
    // If left child is larger than root
    if (l < s && A[Q1[l]] < A[Q1[smallest]])
        smallest = l;
 
    // If right child is larger than smallest so far
    if (r < s && A[Q1[r]] < A[Q1[smallest]])
        smallest = r;
 
    // If smallest is not root
    if (smallest != i)
    {
    	cout<<"true\n";
        swap(Q1[i], Q1[smallest]);
        // Recursively heapify the affected sub-tree
        minheapify(A, Q1, s, smallest);
    }
}

void makeminheap(int *A, int *Q1, int *I1, int s)
{
	cout<<"here\n";
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
        maxheapify(arr, Q2, n, largest);
    }
}

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

void heapsort(int *A, int *H, int *Q1, int *I1, int s)
{
	int j=0;
	for (int i=s-1; i>=0; i--)
    {
    	H[j++] = A[Q1[0]];
        // Move current root to end
        swap(Q1[0], Q1[i]);
 
        // call max heapify on the reduced heap
        minheapify(A, Q1, s, 0);
        adjustI1(Q1,I1,s);
    }
}

void mcquicksort(int *M,int *A,int *H,int *L,int *R,int n,int s)
{
	cout<<"starting\n";
	for (int i=0;i<s;i++)
		A[i]=M[i];
	int Q1[s],Q2[s],I1[s],I2[s];
	makeminheap(A,Q1,I1,s);
	cout<<"starting1/5\n";
	makemaxheap(A,Q2,I2,s);
	cout<<"starting2\n";
	cout<<"\n";
	for (int i=0;i<s;i++)
		cout<<A[Q1[i]]<<"  "<<Q1[i]<<" "<<I1[i]<<endl;
	cout<<"Max heap: \n";
	for (int i=0;i<s;i++)
		cout<<A[Q2[i]]<<"  "<<Q2[i]<<" "<<I2[i]<<endl;
	int flag=0;
	int lpos=0, rpos=0;
	cout<<"min: "<<getmin(A,Q1)<<"\n";
	cout<<"max: "<<getmax(A,Q2)<<"\n";
	for (int i=s;i<n;i++)
	{
		cout<<"M[i]: "<<M[i]<<endl;
		if (M[i]<=getmin(A,Q1))
			L[lpos++]=M[i];
		else if (M[i]>=getmax(A,Q2))
			R[rpos++]=M[i];
		else
		{
			if (flag%2==0)
			{
				L[lpos++]=A[Q1[0]];
				A[Q1[0]] = M[i];
				minheapify(A,Q1,s,0);
				adjustI1(Q1,I1,s);
				makemaxheap(A,Q2,I2,s);
				cout<<"L[0]: "<<L[0];
				exit(0);
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
	int i=0;
	for (i=0;i<lpos;i++)
	{
		M[i]=L[i];
	}
	for (int j=0;j<s;j++,i++)
	{
		M[i]=H[j];
	}
	for (int j=0;j<rpos;j++,i++)
	{
		M[i]=R[j];
	}
	if (n-s<=0)
		return;
	int lcopy[n-s], rcopy[n-s];
	for (int i=0;i<lpos;i++)
		lcopy[i]=L[i];
	for (int i=0;i<rpos;i++)
		rcopy[i]=R[i];
	for (int i=0;i<n;i++)
		cout<<M[i]<<" ";
	mcquicksort(lcopy,A,H,L,R,lpos,s);
	mcquicksort(rcopy,A,H,L,R,rpos,s);

}

int main()
{
	system("clear");
	cout<<"Enter n: ";
	int n,s;
	cin>>n;
	cout<<"Enter s: ";
	cin>>s;
	int *M, *A, *H, *L, *R;
	M = (int *)malloc(sizeof(int)*n);
	A = (int *)malloc(sizeof(int)*s);
	H = (int *)malloc(sizeof(int)*s);
	L = (int *)malloc(sizeof(int)*(n-s));
	R = (int *)malloc(sizeof(int)*(n-s));
	// int M[n],A[s],H[s],L[n-s],R[n-s];
	cout<<"n is "<<n<<endl;
	for (int i=0;i<n;i++)
	{	cout<<i;
		cin>>M[i];
		cout<<"took "<<i<<"\n";
	}
	cout<<"n is "<<n<<endl;
	cout<<"start";
	mcquicksort(M,A,H,L,R,n,s);
	for (int i=0;i<n;i++)
		cout<<M[i]<<" ";
}