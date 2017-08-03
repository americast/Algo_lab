#include <bits/stdc++.h>
using namespace std;

void merge(int a[1000], int token_id[1000], int i1,int j1,int i2,int j2)
{
	int temp[1000], temp2[1000]; //array used for merging
	int i=i1,j=i2,k=0;
	while(i<=j1 && j<=j2) //while elements in both lists
	{
		if(a[i]>=a[j])
		{
			temp[k++]=a[i++];
			temp2[k-1]=token_id[i-1];
		}
		else
		{
			temp[k++]=a[j++];
			temp2[k-1]=token_id[j-1];
		}
	}
	while(i<=j1) //copy remaining elements of the first list
	{
		temp[k++]=a[i++];
		temp2[k-1]=token_id[i-1];
	}
	while(j<=j2) //copy remaining elements of the second list
	{
		temp[k++]=a[j++];
		temp2[k-1]=token_id[j-1];
	}
	for(i=i1,j=0;i<=j2;i++,j++)
	{
		a[i]=temp[j];
		token_id[i]=temp2[j];
	}
//Transfer elements from temp[] back to a[]
}

void mergesort(int a[1000],int token_id[1000], int i,int j)
{
	int mid;
	if(i<j) {
		mid=(i+j)/2;
	/* left recursion */
		mergesort(a,token_id, i,mid);
	/* right recursion */
		mergesort(a,token_id, mid+1,j);
	/* merging of two sorted sub-arrays */
		merge(a,token_id, i,mid,mid+1,j);
	}
}

void printschedule(int n, int p, int schedules[1000][1000], int times[1000], int token_id[1000])
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
		cout<<endl<<endl;
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

int* schedule2(int n, int p, int schedules[1000][1000], int times[1000], int token_id[1000])
{
	// int token_id[n];
	int times2[n];
	for (int i=0;i<n;i++)
		times2[i]=times[i];
	mergesort(times2,token_id,0,n-1);
	for (int i=0;i<n;i++)
		cout<<"Times: "<<times[i]<<"\n";
	for (int i=0;i<n;i++)
		cout<<"Token_ids: "<<token_id[i]<<"\n";
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
		schedules[lowest_j][schedules[lowest_j][0]]=token_id[i];
		cout<<"\n"<<token_id[i]<<"\n";
		sum_of_time[lowest_j]+=times[token_id[i]];
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
	int token_id[1000];
	for (int i=0;i<n;i++)
		token_id[i]=i;

	int *sum_of_time = schedule1(n,p,schedules,times);
	printschedule(n,p,schedules,times, token_id);
	finishingtime(sum_of_time, p);
	totalwaittime(n,p,schedules,times);

	for (int i=0;i<1000;i++)
		for (int j=0;j<1000;j++)
			if (j==0)
				schedules[i][j]=0;
			else 
				schedules[i][j]=-1;

	sum_of_time = schedule2(n,p,schedules,times, token_id);
	printschedule(n,p,schedules,times, token_id);
	finishingtime(sum_of_time, p);
	totalwaittime(n,p,schedules,times);

}