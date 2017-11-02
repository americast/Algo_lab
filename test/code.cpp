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

// float grprofit_nonrec(float c[], int n)
// {
// 	int left_index = n/2 -1;
// 	int right_index = n/2;
// 	int count = 0;
// 	float sum = 0.0;
// 	while(1)
// 	{
// 		if (left_index<0 || right_index>=n)
// 			break;
// 		if (c[left_index] > c[right_index])
// 			sum+= c[left_index--]*pow(0.9, count++);
// 		else
// 			sum+= c[right_index++]*pow(0.9, count++);
// 	}
// 	while(left_index>=0)
// 		sum+= c[left_index--]*pow(0.9, count++);
// 	while(right_index<n)
// 		sum+= c[right_index++]*pow(0.9, count++);
// 	return sum;
// }

float grprofit(float c[], int n, int i, int j)
{
	int left_index = n/2 - i - 1;
	int right_index = n/2 + j;

	if (left_index<0 && right_index>=n)
		return 0;
	if (left_index<0)
	{
		// cout<<"just right: "<<right_index<<endl;
		return grprofit(c,n,i,j+1) + c[right_index]*pow(0.9,i+j);
	}
	if (right_index>=n)
	{
		// cout<<"just left: "<<left_index<<endl;
		return grprofit(c,n,i+1,j) + c[left_index]*pow(0.9,i+j);
	}
	// cout<<"left index: "<<left_index<<" and right index: "<<right_index<<endl;
	float left = c[left_index];
	float right = c[right_index];
	if (left > right)
		return grprofit(c,n,i+1,j) + left*pow(0.9,i+j);
	else
		return grprofit(c,n,i,j+1) + right*pow(0.9,i+j);
}

float dpprofit(float c[], int n)
{
	float T[n/2 + 2][n/2 + 2];
	for (int i=0; i<= n/2 + 1; i++)
		for (int j=0; j<=n/2 + 1; j++)
			T[i][j] = 0;
	int iter=0;
	for (int i = n/2; i>=0; i--)
		for (int j = n/2; j>=0 ; j--)
		{
			int left_index = n/2 - i - 1;
			int right_index = n/2 + j;
			if (iter++ == 0)
				continue;
			T[i][j] = max(T[i+1][j] + c[left_index]*pow(0.9,i+j), T[i][j+1] + c[right_index]*pow(0.9,i+j));
		}
		return T[0][0];
}

int main()
{
	int n;
	cin>>n;
	float c[n];
	for (int i=0; i<n; i++)
		cin>>c[i];
	cout<<"+++\tExhaustive Search\n";
	cout<<"\tMaximum profit = "<<esprofit(c, n, 0, 0)<<endl<<endl;
	// cout<<grprofit_nonrec(c,n)<<endl<<endl;
	cout<<"+++\tGreedy Strategy\n";
	cout<<"\tMaximum profit = "<<grprofit(c,n,0,0)<<endl<<endl;
	cout<<"+++\tDynamic Programming\n";
	cout<<"\tMaximum profit = "<<dpprofit(c,n)<<endl<<endl;
}