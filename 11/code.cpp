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
	for (int i=0; i<n; i++)
	{
		arr[i].val = i;
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
		int count=0;
		while(ptr!=NULL)
		{
			if (count++)
				cout<<ptr->val<<"\t";
			else
				cout<<ptr->val<<" ->\t";
			ptr = ptr->next;
		}
		cout<<endl;
	}
}

bool present_in_stack(int v, stack<adjlist> stack)
{
	for (int i=0; i<stack.size(); i++)
		if (stack.top().val == v)
		{
			stack.pop();
			return true;
		}
	return false;
}

stack<adjlist> DFS(adjlist *u, stack<adjlist> stack, adjlist arr[], int n, int visit[], int low[], int stack_flag[], int is_present[], int serial[])
{
	adjlist *v = u->next;
	stack.push(*u);
	// cout<<"\nPushed: "<<u->val<<endl;
	visit[u->val] = 1;
	serial[u->val]++;
	low[u->val] = serial[u->val];
	while(v != NULL)
	{
		if (visit[v->val] == -1)
		{
			stack = DFS(&arr[v->val], stack, arr, n, visit, low, stack_flag, is_present, serial);
			low[u->val] = min(low[u->val], low[v->val]);
		}
		else if(present_in_stack(v->val, stack))
		{
			low[u->val] = min(low[u->val], serial[v->val]);
		}
		v = v->next;
	}
	int count=1;

	while (serial[u->val] == low[u->val] && stack.size()!=0)
	{

		// cout<<"\n--- Subgroup "<<count++<<": ";
		v = &stack.top();
		
		cout<<v->val<<" ";

		while(v->val!=u->val && stack.size()!=0)
		{
		    visit[v->val] = -1;
		    stack.pop();
		    v = &stack.top();
		    cout<<v->val<<" ";
		}
		visit[v->val]=-1;
		
		cout<<endl;

		if (v->val == u->val)
			break;
	}
	return stack;
}

void findsubgroups(adjlist arr[], int n)
{
	int visit[n];
	int serial[n];
	int low[n];
	int stack_flag[n];
	int is_present[n];
	for (int i=0; i<n; i++)
	{
		visit[i] = -1;
		serial[i] = -1;
		low[i] = i;
		stack_flag[i] = 0;
		is_present[i] = 0;
	}
	stack<adjlist> stack;
	adjlist *u = &arr[0];
	DFS(u, stack, arr, n, visit, low, stack_flag, is_present, serial);
}

int main()
{
	int n_m[2];
	adjlist *arr = gengraph(n_m);
	int n = n_m[0], m = n_m[1];
	prngraph(arr, n);
	findsubgroups(arr, n);

}
