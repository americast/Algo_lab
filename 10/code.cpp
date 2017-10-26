/* Name: code.cpp
  Creator: Sayan Sinha (sayan.sinha@iitkgp.ac.in)
  Date: October 26, 2017
  Description: Strings and sequences
*/
#include <bits/stdc++.h>
using namespace std;

/* Name: issubseq
  Input: S, T, n, m
  Output: begin (The position where the subsequence starts)
  Description: To verify if T is a subsequence of S
*/
int issubseq(char *S, char *T)
{
	int n = strlen(S);
	int m = strlen(T);
	int j=0;
	int begin=-1;
	for (int i=0; i<n; i++)
	{
		if (S[i]==T[j])
		{
			// cout<<"\nhere "<<S[i]<<endl;
			if (begin==-1)
				begin = i;
			j++;
		}
		if (j==m)
			return begin;
	}
	return -1;
}

char* repsymbols(char *T, int k)
{
	int m = strlen(T),pos = 0;
	char *Tk;
	Tk = (char *) malloc (sizeof(char) * m * k);
	for (int i=0; i<m; i++)
		for (int j=0; j<k; j++)
			Tk[pos++] = T[i];
	return Tk;
}

void prnsubseq(char *S, char *T)
{
	int n = strlen(S), m = strlen(T), begin;
	for (int k=n/m; k >= 0; k--)
	{
		char *Tk = repsymbols(T, k);
		begin = issubseq(S, Tk);
		if (begin > -1)
		{
			cout<<"k = "<<k<<endl;
			break;
		}
	}
}

int main()
{
	int s;
	char S[1000], T[1000];
	cin>>s>>S>>T;
	prnsubseq(S, T);
}