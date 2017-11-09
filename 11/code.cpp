/* Name: code.cpp
  Creator: Sayan Sinha (sayan.sinha@iitkgp.ac.in)
  Date: November 9, 2017
  Description: Graphs
*/

#include <bits/stdc++.h>
using namespace std;

struct adjlist
{
	int val;
	adjlist *next;
};

adjlist* gengraph(int n_m[2])
{
	int n, m;
	cin>>n>>m;
	adjlist *arr = (adjlist*) malloc(sizeof(adjlist)*n);
	for (int i=0; i<n; i++)
	{
		arr[i].val = -1;
		arr[i].next = NULL;
	}
	for (int i=0; i<m; i++)
	{
		int u,v;
		cin>>u>>v;
		adjlist *ptr = &arr[u];
		adjlist *ptr_old;
		while(ptr!=NULL)
		{
			if (ptr->val < v)
			{
				ptr_old = ptr;
				ptr = ptr->next;
				continue;
			}
			else
				break;
		}
		adjlist *here = (adjlist*) malloc(sizeof(adjlist));
		here->val = v;
		here->next = ptr;
		ptr_old->next = here;
	}
	n_m[0] = n;
	n_m[1] = m;
	return arr;
}

void prngraph(adjlist arr[], int n)
{
	for (int i=0; i<n; i++)
	{
		adjlist *ptr = &arr[i];
		cout<<i<<" ->\t";
		int count=0;
		while(ptr!=NULL)
		{
			if (count++)
				cout<<ptr->val<<"\t";
			ptr = ptr->next;
		}
		cout<<endl;
	}
}

int main()
{
	int n_m[2];
	adjlist *arr = gengraph(n_m);
	int n = n_m[0], m = n_m[1];
	prngraph(arr, n);

}
