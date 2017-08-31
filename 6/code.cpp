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
	int flag;	//-1 for left, 1 for right
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

void printtree(bintree *T, int indent=0)
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

void printlist(bintree *T,int n)
{
	bintree *here = T;
	while(n-->0)
	{
		cout<<here->key<<"\t";
		here = here->R;
	}
	cout<<"\n";
}

bintree* left_rotate_tree(bintree *T)
{
	bintree *right = T->R;
	T->R = T->R->L;
	right->L = T;
	return right;
}

bintree* right_rotate_tree(bintree *T)
{
	bintree *left = T->L;
	T->L = T->L->R;
	left->R = T;
	return left;
}

bintree* tree2list(bintree *T)
{
	bintree *here = T;
	while(1)
	{
		bintree *there = here;
		here = here->L;
		// cout<<"--\n";
		// cout<<"Key here: "<<here->key<<endl;
		if (here->L == NULL && here->R == NULL)
			break;
		if (here->R != NULL)
		{
			while(1)
			{
				here = left_rotate_tree(here);
				if (here->R == NULL)
					break;
			}
		}
		there -> L = here;
		// bintree *there = T;
		// cout<<"Key there: "<<T->L->key<<endl<<(T ==here)<<endl;
		// printtree(T,0);
	}
	here = T;
	while(1)
	{
		bintree *there = here;
		here=here->R;
		if (here->L == NULL && here->R == NULL)
			break;
		if (here->L != NULL)
		{
			while(1)
			{
				here = right_rotate_tree(here);
				if (here->L == NULL)
					break;
			}
		}
		there->R = here;
	}
	here = T;
	cout<<"+++ Flattened tree\n";
	printtree(T);
	while(1)
	{
		bintree *there = here;
		here = here->L;
		here->R = there;
		if (here->L == NULL)
			break;
	}
	bintree *smallest = here;
	here = T;
	while(1)
	{
		bintree *there = here;
		here = here->R;
		here->L = there;
		if (here->R == NULL)
			break;
	}
	// printtree(T,0);
	// cout<<"Key: "<<smallest->key<<endl;
	return smallest;
}

bintree* list2tree(bintree *T, int n)
{
	if (n==1)
	{
		T->L = NULL;
		T->R = NULL;
		return T;
	}
	if (n<=0)
		return NULL;
	int centre = n/2;
	bintree *here = T;
	for (int i=1; i<=centre; i++)
		here = here->R;
	// bintree *there = here;
	cout<<"here: "<<here->key<<"\n";
	here->L = list2tree(T, centre);
	// here = there;
	// cout<<"one r ";
	here->R = list2tree(here->R, n-centre-1);
	cout<<"there: "<<here->key<<"\n";
	return here;
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
	printtree(T);
	T = tree2list(T);
	cout<<"\n+++ Linked list\n";
	printlist(T,n);
	T = list2tree(T,n);
	cout<<endl<<endl;
	cout<<"\n+++ Balanced tree\n";
	printtree(T);
}