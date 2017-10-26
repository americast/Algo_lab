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
	Tk = (char *) malloc (sizeof(char) * (m*k +1));
	for (int i=0; i<m; i++)
		for (int j=0; j<k; j++)
			Tk[pos++] = T[i];
	// cout<<Tk;
	// cout<<"\nm*k "<<m*k<<" pos= "<<pos<<endl;
	Tk[pos] = '\0';
	return Tk;
}

pair<int,int> exhsubseq(char *S, char *T)
{
	int n = strlen(S), m = strlen(T), begin;
	int k = n/m;
	for (; k >= 0; k--)
	{
		char *Tk = repsymbols(T, k);
		begin = issubseq(S, Tk);
		if (begin > -1)
		{
			break;
		}
	}
	return make_pair(begin,k);
}

int dnc1(char *S, char *T, int s)
{
	int n = strlen(S);
	int m = strlen(T);
	if (n < 2*m)
		if (issubseq(S,T)>-1)
			return 1;
		else
			return 0;
	int table[1000], i1=0, i2=0;
	for (int i = 0; i<s; i++)
		table[i] = 0;
	char S_1[1000], S_2[1000];
	for (int i=0; i<n; i++)
	{
		int here = S[i] - 'a';
		if (table[here] % 2 == 0)
			S_1[i1++] = S[i];
		else
			S_2[i2++] = S[i];
		table[here]++;
	}
	S_1[i1] = '\0';
	S_2[i2] = '\0';
	// cout<<"S1: "<<S_1<<"\nS2: "<<S_2<<endl;
	if (strlen(S_1) == n)
		return exhsubseq(S_1,T).second;
	else if (strlen(S_2) == n)
		return exhsubseq(S_2,T).second;
	int k1 = dnc1(S_1,T,s), k2 = dnc1(S_2,T,s);
	int k = k1 + k2 + 1;
	char *Tk;
	Tk = repsymbols(T, k);
	// Tk[m*k]='\0';
	if (issubseq(S, Tk)>-1)
		return k;
	k--;
	Tk = repsymbols(T,k);
	// Tk[m*k]='\0';
	if (issubseq(S, Tk)>-1)
		return k;
	if (k == 0)
		return 0;
	else
		return --k;
}

void prnsubseq(char *S, char *T, int begin)
{
	int n = strlen(S);
	int m = strlen(T);
	int j=0;
	for (int i =0; i<begin; i++)
		cout<<" ";
	for (int i = begin; i<n; i++)
		if (S[i]==T[j])
			cout<<T[j++];
		else
			cout<<" ";
}

int main()
{
	// char a[] = "abc";
	// repsymbols(a,2);
	// exit(0);
	int s;
	char S[1000], T[1000];
	cin>>s>>S>>T;
	cout<<"+++ Exhaustive search\n\tk = ";
	pair<int,int> now = exhsubseq(S, T);
	int begin = now.first, k = now.second;
	cout<<k<<endl;
	cout<<"\n+++ Divide and Conquer Strategy 1\n\tk = ";
	k = dnc1(S,T,s);
	cout<<k<<endl;
	cout<<"+++ The subsequence is:\n";
	cout<<S<<endl;
	char *Tk = repsymbols(T, k);
	prnsubseq(S,Tk, begin);
	cout<<endl;

}