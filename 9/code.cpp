/* Name: code.cpp
  Creator: Sayan Sinha (sayan.sinha@iitkgp.ac.in)
  Date: October 12, 2017
  Description: Linear time sorting
*/
#include <bits/stdc++.h>
using namespace std;

void generate_gpa(int arr[], int n)
{
	float Pr[] = {0.05,0.2,0.3,0.15};
	for (int i=1;i<4; i++)
		Pr[i] += Pr[i-1];
	for (int i=1;i<=n;i++)
	{
		float y = (float)rand()/RAND_MAX;
		// Decision tree begins
		if (y > Pr[2])
			if (y > Pr[3])
				arr[i] = rand()%100 + 401;
			else
				arr[i] = rand()%100 + 301;
		else
			if (y > Pr[1])
				arr[i] = rand()%100 + 201;
			else
				if (y < Pr[0])
					arr[i] = rand()%101;
				else
					arr[i] = rand()%100 +101;
		// cout<<i<<": "<<arr[i]<<", y:"<<y<<"\n";
	}
}

int main()
{
	srand(time(NULL));
	int n;
	cin>>n;
	int cg[n];
	generate_gpa(cg, n);
}