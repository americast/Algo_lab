#include <bits/stdc++.h>
using namespace std;

float esprofit(float c[], int n, int i, int j)
{
	int left_index = n/2 - i - 1;
	int right_index = n/2 + j;

	if (left_index<0 && right_index>=n)
		return 0;
	if (left_index<0)
	{
		// cout<<"just right: "<<right_index<<endl;
		return esprofit(c,n,i,j+1) + c[right_index]*pow(0.9,i+j);
	}
	if (right_index>=n)
	{
		// cout<<"just left: "<<left_index<<endl;
		return esprofit(c,n,i+1,j) + c[left_index]*pow(0.9,i+j);
	}
	// cout<<"left index: "<<left_index<<" and right index: "<<right_index<<endl;
	float left = c[left_index];
	float right = c[right_index];
	return max(esprofit(c,n,i+1,j) + left*pow(0.9,i+j),esprofit(c,n,i,j+1) + right*pow(0.9,i+j));
}

int main()
{
	int n;
	cin>>n;
	float c[n];
	for (int i=0; i<n; i++)
		cin>>c[i];
	cout<<esprofit(c, n, 0, 0)<<endl;
}