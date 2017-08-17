#include <bits/stdc++.h>
using namespace std;

struct tnode
{
	int key;
	tnode *L, *R;
};

typedef tnode *bintree;

bintree buildtree ( int n )
{
	bintree T;
	int n1, n2;
	if (n <= 0) return NULL;
	T = (bintree)malloc(sizeof(tnode));
	int key_here; cin>>key_here;
	T -> key = key_here;
	if (n == 1)
		T -> L = T -> R = NULL;
	else
	{
		int num_to_left; cin>>num_to_left;
		n1 = num_to_left % n; n2 = (n - 1) - n1;
		T -> L = buildtree(n1);
		T -> R = buildtree(n2);
	}
	return T;
}

int lefttilt(bintree T)
{
	if (T==NULL)
		return -1;
	int left_height = lefttilt(T->L);
	int right_height = lefttilt(T->R);
	if (left_height<right_height)
	{
		bintree lt = T->L;
		T->L=T->R;
		T->R=lt;
		return right_height+1;
	}
	return left_height+1;
}

void printtree(bintree T, int indent)
{
	for (int i=0;i<indent;i++)
		cout<<"\t";
	cout<<"+-- ";
	if (T==NULL) 
	{
		cout<<"NULL\n";
		return;
	}
	cout<<T->key<<"\n";
	printtree(T->L, indent+1);
	printtree(T->R, indent+1);
}

int main()
{
	int n;
	cin>>n;
	bintree T = buildtree(n);
	cout<<"+++ Initial tree\n";
	printtree(T,0);
	int h = lefttilt(T);
	cout<<"+++ Tree after left-tilting\n";
	printtree(T,0);
	cout<<"+++ The height of the tree is "<<h<<"\n";
}