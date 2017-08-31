#include <bits/stdc++.h>
using namespace std;

struct bintree
{
	int key;
	bintree *L, *R;
};

// typedef tnode *bintree;

void buildtree (bintree *T, int n, int net_n)
{
	int num;
	cin>>num;
	bintree *prev, *root=T;
	int flag=-1;	//-1 for left, 1 for right
	while(1)
	{
		prev = T;
		if (num < T->key)
		{
			T = T->L;
			flag=-1;
		}
		else 
		{
			T = T->R;
			flag=1;
		}
		if (T==NULL)
			break;
	}
	bintree *now = (bintree*)malloc(sizeof(bintree));
	now->key = num;
	now->L = now->R = NULL;
	if (flag==-1)
		prev->L = now;
	else
		prev->R = now;
	if (++net_n<n)
		buildtree(root,n,net_n);
}

void printtree(bintree *T, int indent)
{
	if (T==NULL)
		return;
	bintree *root = T;
	printtree(T->L, indent+1);
	T = root;
	for (int i=0;i<indent;i++)
		cout<<"\t";
	// cout<<"+-- ";
	cout<<T->key<<"\n";
	printtree(T->R, indent+1);
}


int main()
{
	int n, num;
	cin>>n;
	bintree *T = (bintree*)malloc(sizeof(bintree));
	cin>>num;
	T->key = num;
	T->L = T->R = NULL;
	buildtree(T,n,1);
	cout<<"+++ Initial tree\n";
	printtree(T,0);
}