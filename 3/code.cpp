#include <bits/stdc++.h>
using namespace std;

extern int* registerme ( );
extern int makemove1 ( int );
extern int makemove2 ( int );

int* dptable(int n, int k, int *p)
{
	int *T;
	T=(int*)malloc((n+1)*sizeof(int));
	for (int i=0; i<=n; i++)
	{
		if (i<p[0]) T[i]=-1;
		else
		{
			int flag=0;
			for (int j=0;j<k;j++)
			{
				if (i-p[j]<0) break;
				if (T[i-p[j]]==-1)
					{T[i]=j; flag=1;}
			}
			if (flag==0)
				T[i]=-1;
		}
	}
	return T;
}

void playgame1(int *T, int i, int *p, int k)
{
	while(i>0)
	{
		// cout<<"Now "<<i<"\n";
		if (T[i]>=0)
			i=makemove1(T[i]);
		else
		{
			srand(time(NULL));
			int j=rand()%k;
			i=makemove1(j);
		}
	}
}

int main()
{
	int* A, n, k,*p;
	A = registerme();
	n = A[0];
	k = A[1];
	p = A + 2;
	int *T = dptable(n,k,p);
	// cout<<"\n\nT: ";
	// for (int i=0;i<=n;i++)
	// 	cout<<i<<":"<<T[i]<<"\t";
	cout<<endl;

	playgame1(T, n, p,k);
}