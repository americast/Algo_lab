#include <bits/stdc++.h>
using namespace std;

struct tree
{
	tree *parent;
	int weight;
};

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

tree findroot(tree **arr, int i, int j)
{
	tree *T = &(arr[i][j]);
	while(1)
	{
		if (T->parent == T)
			return *T;
		else
			T = T->parent;
	}
}

tree* findroot(tree *T)
{
	// tree *T = &(arr[i][j]);
	while(1)
	{
		if (T->parent == T)
			return T;
		else
			T = T->parent;
	}
}

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


int main()
{
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

	printlabyrinth(H,V,m,n);
	findroot(arr,1,1);

}