/* Name: code.cpp
  Creator: Sayan Sinha (sayan.sinha@iitkgp.ac.in)
  Date: October 12, 2017
  Description: Linear time sorting
*/
#include <bits/stdc++.h>
using namespace std;

void generate_gpa(int arr[], long long n)
{
	float Pr[] = {0.05,0.2,0.3,0.15};
	for (int i=1;i<4; i++)
		Pr[i] += Pr[i-1];
	for (long long i=0;i<n;i++)
	{
		float y = (float)rand()/RAND_MAX;
		// Decision tree begins
		if (y > Pr[2])
			if (y > Pr[3])
				arr[i] = rand()%100 + 401;
			else
				arr[i] = rand()%100 + 301;
		else
			if (y > Pr[1])
				arr[i] = rand()%100 + 201;
			else
				if (y < Pr[0])
					arr[i] = rand()%101;
				else
					arr[i] = rand()%100 +101;
		// cout<<i<<": "<<arr[i]<<", y:"<<y<<"\n";
	}
}

long long partition(int a[], long long l, long long r) 
{ 
	long long pivot, i, j, t; 
	pivot = a[l]; 
	i = l; 
	j = r+1; 
	while(1) 
	{ 
		do 
		{
			++i; 
		} while(a[i]<=pivot && i<=r); 
		do
		{
			--j; 
		} while( a[j] > pivot ); 
		if( i>= j ) 
			break; 
		t= a[i]; 
		a[i] = a[j]; 
		a[j] = t; 
	} 
	t = a[l]; 
	a[l] = a[j]; 
	a[j] = t; 
	return j; 
} 

/* Name: quicksort
  Input: array, left, right
  Output: <none>
  Description: Quick sort
*/
void qsort(int a[], long long l,long long r) 
{ 
	long long j; 
	if(l < r) 
	{
		// divide and conquer 
		j = partition( a, l, r); 
		qsort(a, l, j-1); 
		qsort(a, j+1, r); 
	}
}

/* Name: countingsort1
  Input: cg, n
  Output: <none>
  Description: Stable counting sort
*/
void countingsort1(int cg[], long long n)
{
	int C[501]={0}, *B;
	B = (int *) malloc(n*sizeof(int));
	for (long long i=0; i<n; i++)
		C[cg[i]]++;
	for (int i=1; i<501; i++)
		C[i] += C[i-1];
	for (long long i=0;i<n;i++)
		B[(C[cg[i]]--)-1] = cg[i];
	for (long long i=0; i<n; i++)
		cg[i] = B[i];
}

/* Name: countingsort2
  Input: cg, n
  Output: <none>
  Description: Ubstable counting sort
*/
void countingsort2(int cg[], long long n)
{
	int C[501]={0}, k=0;
	for (long i=0; i<n; i++)
		C[cg[i]]++;
	for (int i=0; i<501; i++)
		if (C[i]-->0)
		{
			cg[k] = i;
			i--; k++;
		}
}

/* Name: copy
  Input: cg, n
  Output: <none>
  Description: copy an array elements into another array
*/
int* copy(int cg[], long long n)
{
	int *cgpa = (int *) malloc(n* sizeof(int));
	for (long long i=0;i<n;i++)
		cgpa[i] = cg[i];
	return cgpa;
}

int main()
{
	srand(time(NULL));
	long long n;
	cin>>n;
	cout<<"\nn = "<<n;
	int cg[n];
	clock_t c1, c2;
	c1 = clock();
	generate_gpa(cg, n);
	c2 = clock();
	cout<<"\n+++ Array generation time\t=\t"<<(double)(c2 - c1) / (double)CLOCKS_PER_SEC<<" sec";
	int *cg2, *cg3;
	cg2 = copy(cg, n);
	cg3 = copy(cg, n);
	c1 = clock();
	qsort(cg, 0, n-1);
	c2 = clock();
	cout<<"\n+++ Quick sort time\t\t=\t"<<(double)(c2 - c1) / (double)CLOCKS_PER_SEC<<" sec";
	c1 = clock();
	countingsort1(cg2, n);
	c2 = clock();
	cout<<"\n+++ Counting sort 1 time\t=\t"<<(double)(c2 - c1) / (double)CLOCKS_PER_SEC<<" sec";
	c1 = clock();
	countingsort2(cg3, n);
	c2 = clock();
	cout<<"\n+++ Counting sort 2 time\t=\t"<<(double)(c2 - c1) / (double)CLOCKS_PER_SEC<<" sec"<<endl;
	// cout<<"\n"<<n<<endl;
// 	for (int i=0;i<n;i++)
// 		cout<<cg[i]<<"  ";
}