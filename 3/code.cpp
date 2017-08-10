/* Name: code.cpp
  Creator: Sayan Sinha (sayan.sinha@iitkgp.ac.in)
  Date: August 10, 2017
  Description: Dynamic programming
*/

#include <bits/stdc++.h>
using namespace std;

extern int* registerme ( );
extern int makemove1 ( int );
extern int makemove2 ( int );

/* Name: dptable
  Input: n, k, p array
  Output: T array
  Description: Generate table using DP
*/

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
		if (T[i]>=0)
			i=makemove1(T[i]);
		else
		{
			int j=rand()%k;
			i=makemove1(j);
		}
	}
}

/* Name: playgame2
  Input: k, p array
  Output: <none>
  Description: Same value repeated for every start_value+end+value
*/

void playgame2(int i, int *p, int k)
{
	int start_val=p[0], end_val=start_val+k-1;
	while(i>0)
	{
		int rem=(i%(start_val+end_val))-1;
		if (rem<0) rem=end_val+start_val-1;
		if (rem<start_val)
		{
			int j=rand()%k;
			i=makemove2(j);
		}
		else
		{
			if (rem>=end_val)
				i=makemove2(k-1);
			else
			{
				i=makemove2(rem-start_val);
			}
		}
	}

}


int main()
{
	srand(time(NULL));
	int* A, n, k,*p;
	A = registerme();
	n = A[0];
	k = A[1];
	p = A + 2;
	int *T = dptable(n,k,p);
	cout<<endl;

	playgame1(T, n, p,k);
	playgame2(n,p,k);
}