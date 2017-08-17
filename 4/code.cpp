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

void updatekeys(bintree T, int *arr, int curr, int h)
{
	if (T==NULL) return;
	if (curr<2*h)
		arr[curr]=T->key;
	else
	{
		for (int i=0;i<h-1;i++)
			arr[i]=arr[i+1];
		arr[h-1]=T->key;
	}
	int mod=T->key % h;
	if (mod>curr)
		T->key=arr[0];
	else
	{
		if (curr==2*h)
			T->key = arr[curr-mod-1];
		else
			T->key = arr[curr-mod];
	}		
	curr++;
	updatekeys(T->L,arr,curr,h);
	updatekeys(T->R,arr,curr,h);
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
	cout<<"\n+++ Tree after left-tilting\n";
	printtree(T,0);
	cout<<"\n+++ The height of the tree is "<<h<<"\n";
	int *arr, curr=0;
	arr=(int*) malloc(sizeof(int)*2*h);
	updatekeys(T,arr,curr,h);
	cout<<"\n+++ Tree after key update\n";
	printtree(T,0);
}