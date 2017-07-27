/* Name: code.cpp
  Creator: Sayan Sinha (sayan.sinha@iitkgp.ac.in)
  Date: July 27, 2017
  Description: Finding peak in an unknown range of numbers
*/

#include <bits/stdc++.h>

extern void registerme ( const char [] );
extern int evaluate ( unsigned int );
extern void verify ( unsigned int );
using namespace std;

/* Name: findpeak()
  Input: <none>
  Output: nth index where the peak is present
  Description: This program uses a divide-and-conquer iteration for
     computing peak in an unknown range. It estimates the range with
     expoenents of 2 after which performs gradient ascent towards the
     peak.
*/
int findpeak()
{
	unsigned int now, powernow=0, res=0, powerlast=0,count=0, prevres, prevnow=0, prevprevnow=0; //temp variables
																								 // for storing 
	while(1)
	{
		prevres=res;
		prevprevnow=prevnow;
		prevnow=now;
		now=powerlast+pow(2,powernow);
		res=evaluate(now);
		if(count!=0){
		if (prevres>res)
			break;
		}
		else count++;
		powernow++;
	}
	unsigned int start=prevprevnow, end=now; //perform search
	int slope=0;
	while(1)
	{
		unsigned int mid=(start+end)/2;
		res=0;
		int res_lesshalf=evaluate(mid-1), res_more_half=evaluate(mid+1);   //evaluate gradient
		// cout<<res_lesshalf<<" "<<res_more_half<<" mid: "<<mid<<"\n";
		// cout<<"start: "<<start<<" end: "<<end<<endl<<endl;
		if (res_lesshalf<res_more_half)
		{
			if (slope==-1)
			{
				res=evaluate(mid);
				if (res>res_lesshalf && res>res_more_half)
					return mid;
			}
			start=mid; slope=1;
		}
		else if (res_lesshalf>res_more_half)
		{
			if (slope==1)
			{
				res=evaluate(mid);
				if (res>res_lesshalf && res>res_more_half)
					return mid;
			}
			end=mid; slope=-1;
		}
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