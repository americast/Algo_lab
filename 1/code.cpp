#include <bits/stdc++.h>

extern void registerme ( const char [] );
extern int evaluate ( unsigned int );
extern void verify ( unsigned int );
using namespace std;

int findpeak()
{
	unsigned int now, powernow=0, dir=1, res=0, powerlast=0,count=0, prevres, prevnow=0, prevprevnow=0;
	while(1)
	{
		prevres=res;
		prevprevnow=prevnow;
		prevnow=now;
		now=powerlast+(dir)*pow(2,powernow);
		res=evaluate(now);
		if(count!=0){
		if (prevres>res && dir==1)
			{cout<<"here\n";cout<<prevres<<"  "<<res<<"  now:"<<now<<endl; dir=-1; powerlast=now; powernow=-1; break;}
		}
		else count++;
		powernow++;
	}
	unsigned int start=prevprevnow, end=now;
	while(1)
	{
		unsigned int mid=(start+end)/2;
		res=evaluate(mid);
		int res_lesshalf=evaluate(mid-1), res_more_half=evaluate(mid+1);
		cout<<res_lesshalf<<" "<<res_more_half<<" mid: "<<mid<<"\n";
		cout<<"start: "<<start<<" end: "<<end<<endl<<endl;
		if (res_lesshalf<res && res_more_half>res)
			start=mid;
		else if (res_lesshalf>res && res_more_half<res)
			end=mid;
		else return mid;
	}
}

int main()
{
	unsigned int n;
	registerme("16CS10048");
	n = findpeak();
	verify(n);
}