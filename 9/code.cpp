/* Name: code.cpp
  Creator: Sayan Sinha (sayan.sinha@iitkgp.ac.in)
  Date: October 12, 2017
  Description: Linear time sorting
*/
#include <bits/stdc++.h>
using namespace std;

void generate_gpa(int arr[], int n)
{
	float Pr[] = {0.05,0.2,0.3,0.15};
	for (int i=1;i<4; i++)
		Pr[i] += Pr[i-1];
	for (int i=0;i<n;i++)
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

int partition(int a[], int l, int r) 
{ 
	int pivot, i, j, t; 
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

void qsort(int a[], int l,int r) 
{ 
	int j; 
	if(l < r) 
	{ // divide and conquer 
		j = partition( a, l, r); 
		qsort(a, l, j-1); 
		qsort(a, j+1, r); 
	}
}


void countingsort1(int cg[], int n)
{
	int C[501]={0}, *B;
	B = (int *) malloc(n*sizeof(int));
	for (int i=0; i<n; i++)
		C[cg[i]]++;
	for (int i=1; i<501; i++)
		C[i] += C[i-1];
	for (int i=0;i<n;i++)
		B[(C[cg[i]]--)-1] = cg[i];
	for (int i=0; i<n; i++)
		cg[i] = B[i];
}

void countingsort2(int cg[], int n)
{
	int C[501]={0}, k=0;
	for (int i=0; i<n; i++)
		C[cg[i]]++;
	for (int i=0; i<501; i++)
		if (C[i]-->0)
		{
			cg[k] = i;
			i--; k++;
		}
}

int* copy(int cg[], int n)
{
	int *cgpa = (int *) malloc(n* sizeof(int));
	for (int i=0;i<n;i++)
		cgpa[i] = cg[i];
	return cgpa;
}

int main()
{
	srand(time(NULL));
	int n;
	cin>>n;
	int cg[n];
	generate_gpa(cg, n);
	int *cg2, *cg3;
	cg2 = copy(cg, n);
	cg3 = copy(cg, n);
	qsort(cg, 0, n-1);
	countingsort1(cg2, n);
	countingsort2(cg3, n);
	for (int i=0; i<n; i++)
		cout<<cg[i]<<endl;
}