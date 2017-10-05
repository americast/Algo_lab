#include <bits/stdc++.h>
using namespace std;

int exhsearch (int L, int n, int A[],int i=0, int u=0, int v=0)
{
	if (i==n || (u+A[i] > L && v+A[i] > L))
		return i;
	int toreturn_left = -1, toreturn_right = -1;
	if (u+A[i] <= L)
		toreturn_left = exhsearch(L,n,A,i+1,u+A[i],v);
	if (v+A[i] <= L)
		toreturn_right = exhsearch(L,n,A,i+1,u,v+A[i]);
	if (toreturn_left > toreturn_right)
		return toreturn_left;
	else
		return toreturn_right;
}

int main()
{
	int L,n;
	cin>>L>>n;
	int A[n];
	for (int i=0;i<n;i++)
		cin>>A[i];
	clock_t c1, c2;
	double runtime;
	c1 = clock();
	int k = exhsearch(L,n,A);
	c2 = clock();
	runtime = (double)(c2 - c1) / (double)CLOCKS_PER_SEC;
	cout<<"+++ Exhaustive search\n\tk = "<<k<<"\n\tSearch time = "<<runtime<<" sec"<<endl;
}