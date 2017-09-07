/* Name: code.cpp
  Creator: Sayan Sinha (sayan.sinha@iitkgp.ac.in)
  Date: September 7, 2017
  Description: Disjoint sets
  Assumption: None of the rows or coloumns is 1
*/
#include <bits/stdc++.h>
using namespace std;

struct tree
{
	tree *parent;
	int weight;
};

/* Name: printlabyrinth
  Input: H, V, m, n
  Output: <none>
  Description: Print the labyrinth
*/

void printlabyrinth(int **H, int **V,int m,int n)
{
	for (int i=1;i<=n;i++)
		cout<<"+---";
	cout<<"+\n";
	int m_here=0;
	while(1)
	{
		cout<<"|   ";
		for (int i=0;i<n-1;i++)
			if (V[m_here][i])
				cout<<"|   ";
			else
				cout<<"    ";
		cout<<"|\n";

		if (m_here < m-1)
		{
			for (int i=0;i<n;i++)
			{
				cout<<"+";
				if (H[m_here][i])
					cout<<"---";
				else
					cout<<"   ";
			}
			cout<<"+\n";
		}
		if(++m_here == m)
			break;
	}
	for (int i=1;i<=n;i++)
		cout<<"+---";
	cout<<"+\n";
}

tree** initrooms(int m, int n)
{
	tree **arr;
	arr = new tree *[m];
	for(int i = 0; i <m; i++)
	    arr[i] = new tree[n];

	for (int i=0;i<m;i++)
		for (int j=0;j<n;j++)
		{
			tree *T = (tree*)malloc(sizeof(tree));
			T -> parent = T;
			T -> weight = 1;
			arr[i][j]=*T;
		}
	return arr;
}

/* Name: findroot
  Input: arr, i, j or arr
  Output: tree*
  Description: Overloaded functions to return root when required
*/

tree* findroot(tree **arr, int i, int j)
{
	tree *T = &(arr[i][j]);
	while(1)
	{
		if (T->parent == T)
			return T;
		else
			T = T->parent;
	}
}

tree* findroot(tree *T)
{
	while(1)
	{
		if (T->parent == T)
			return T;
		else
			T = T->parent;
	}
}

/* Name: mergeregions
  Input: x,y
  Output: <none>
  Description: merge regions x and y
*/

void mergeregions(tree *x, tree *y)
{
	tree *root1 = findroot(x);
	tree *root2 = findroot(y);
	if (x->weight < y->weight)
	{
		root1->parent = root2;
		root2-> weight += root1->weight;
	}
	else
	{
		root2->parent = root1;
		root1-> weight += root2->weight;		
	}
}

/* Name: buildlabyrinth
  Input: R, H, V, m, n
  Output: count
  Description: build it and return the no of times wall was removed
*/

int buildlabyrinth(tree **R, int **H, int **V, int m, int n)
{
	int flag = 0, count=0;
	while(1)
	{
		if (count==m*n-1)
			return count;
		if (flag%2)
		{
			int m_here = rand() % (m-1);
			int n_here = rand() % n;
			int here = H[m_here][n_here];
			if (here)
			{
				// tree *t1 = &(R[m_here][n_here]);
				// tree *t2 = &(R[m_here+1][n_here]);
				tree* root1 = findroot(R,m_here,n_here);
				tree* root2 = findroot(R,m_here+1,n_here);
				if (root1!=root2)
				{
					mergeregions(root1,root2);
					H[m_here][n_here] = 0;
					count++;
				}
			}
		}
		else
		{
			int m_here = rand() % m;
			int n_here = rand() % (n-1);
			int here = V[m_here][n_here];
			if (here)
			{
				// tree *t1 = &(R[m_here][n_here]);
				// tree *t2 = &(R[m_here][n_here+1]);
				tree* root1 = findroot(R,m_here,n_here);
				tree* root2 = findroot(R,m_here,n_here+1);
				if (root1!=root2)
				{
					mergeregions(root1,root2);
					V[m_here][n_here]=0;
					count++;
				}
			}
		}
		flag++;
	}
}

int main()
{
	srand (time(NULL));
	int m,n;
	cin>>m>>n;

	tree **arr = initrooms(m,n);

	int **H,**V;
	H = new int *[m-1];
	for(int i = 0; i <m-1; i++)
	    H[i] = new int[n];

	V = new int *[m];
	for(int i = 0; i <m; i++)
	    V[i] = new int[n-1];

	// int H[m-1][n], V[m][n-1];

	for (int i=0;i<m-1;i++)
		for (int j=0;j<n;j++)
			H[i][j]=1;

	for (int i=0;i<m;i++)
		for (int j=0;j<n-1;j++)
			V[i][j]=1;
	cout<<"+++ Initial labyrinth\n";
	printlabyrinth(H,V,m,n);
	int count = buildlabyrinth(arr,H,V,m,n);
	cout<<"+++ Labyrinth created after "<<count<<" wall removals\n";
	cout<<"\n+++ Final labyrinth\n";
	printlabyrinth(H,V,m,n);

}