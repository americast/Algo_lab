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
}