#include <bits/stdc++.h>
using namespace std;

struct node
{
	int i;
	int u;
	int v;
	node* next;
};

int exhsearch (int L, int n, int A[], int i=0, int u=0, int v=0)
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

bool ispresent (node* H[], int s, int i, int u, int v)
{
	int index = (7*i + 3*u + 5*v) % s;
	node *now = H[index];
	while(1)
	{
		if (now == NULL)
			return false;
		if (now->i == i && now->u == u && now->v == v)
			return true;
		now = now->next;
	}
}

int hashsearch (int L, int n, int A[], node* H[], int i=0, int u=0, int v=0)
{
	int s = n*L;
	node *here = (node*) malloc (sizeof(node));
	here->i = i;
	here->u = u;
	here->v = v;
	int index = (7*i + 3*u + 5*v) % s;
	here->next = H[index];
	H[index] = here;
	if (i==n || (u+A[i] > L && v+A[i] > L))
		return i;
	int toreturn_left = -1, toreturn_right = -1;
	if (u+A[i] <= L)
		if (ispresent(H,s,i+1,u+A[i],v))
			toreturn_left = i+1;
		else
			toreturn_left = hashsearch(L,n,A,H,i+1,u+A[i],v);
	if (v+A[i] <= L)
		if (ispresent(H,s,i+1,u,v+A[i]))
			return i+1;
		else
			toreturn_right = hashsearch(L,n,A,H,i+1,u,v+A[i]);
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
	cout<<"+++\tExhaustive search\n\tk = "<<k<<"\n\tSearch time = "<<runtime<<" sec"<<endl;
	int s=n*L;
	node* H[s];
	for (int i=0; i<s; i++)
		H[i] = NULL;

	c1 = clock();
	k = hashsearch(L,n,A,H);
	c2 = clock();
	runtime = (double)(c2 - c1) / (double)CLOCKS_PER_SEC;
	cout<<"+++\tHash-based search\n\tHash table of size "<<s<<" initialized\n\tk = "<<k<<"\n\tSearch time = "<<runtime<<" sec"<<endl;
}