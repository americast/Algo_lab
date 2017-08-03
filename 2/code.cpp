#include <bits/stdc++.h>
using namespace std;

void printschedule(int n, int p, int schedules[1000][1000], int times[1000])
{
	for (int i=0;i<p;i++)
	{
		cout<<"No. of jobs in counter "<<i<<" is "<<schedules[i][0]<<": ";
		for (int j=1;j<n+1;j++)
		{
			if (schedules[i][j]==-1)
				break;
			cout<<" "<<schedules[i][j]<<" ("<<times[schedules[i][j]]<<") ";
		}
		cout<<endl;
	}
}

void finishingtime(int *sum_of_time, int p)
{
	int largest=sum_of_time[0];
	for (int i=1;i<p;i++)
		if (sum_of_time[i]>largest)
			largest=sum_of_time[i];
	cout<<"\nBank finishing time: "<<largest<<"\n";
}

void totalwaittime(int n, int p, int schedules[1000][1000], int times[1000])
{
	int wait_time=0;
	for (int i=0;i<p;i++)
	{
		int wait_time_here=0;
		for (int j=1;j<1000;j++)
		{
			if (schedules[i][j]==-1)
				break;
			wait_time_here+=times[schedules[i][j]];
			wait_time+=wait_time_here;
		}
		wait_time-=wait_time_here;
	}
	cout<<"\nTotal waiting time: "<<wait_time<<"\n";
}

int* schedule1(int n, int p, int schedules[1000][1000], int times[1000])
{
	int *sum_of_time;		//p[i]=sum of times
	sum_of_time=new int(p);
	for (int i=0;i<p;i++)
		sum_of_time[i]=0;
	for (int i=0;i<n;i++)
	{
		int lowest_time=sum_of_time[0], lowest_j=0;
		for (int j=1;j<p;j++)
			if (sum_of_time[j]<lowest_time)
				{lowest_time=sum_of_time[j]; lowest_j=j;}
		schedules[lowest_j][0]++;
		schedules[lowest_j][schedules[lowest_j][0]]=i;
		sum_of_time[lowest_j]+=times[i];
	}
	return sum_of_time;
}

int main()
{
	int n,p;
	cout<<"No. of customers: ";
	cin>>n;
	cout<<"No. of counters: ";
	cin>>p;
	int times[1000];
	cout<<"Enter customer times: \n";
	for (int i=0;i<n;i++)
		cin>>times[i];
	int schedules[1000][1000];
	for (int i=0;i<1000;i++)
		for (int j=0;j<1000;j++)
			if (j==0)
				schedules[i][j]=0;
			else 
				schedules[i][j]=-1;

	int *sum_of_time = schedule1(n,p,schedules,times);
	printschedule(n,p,schedules,times);
	finishingtime(sum_of_time, p);
	totalwaittime(n,p,schedules,times);
}