#include<iostream>
#include<math.h>
#include<time.h>
#include<stdlib.h>
using namespace std;


int isvalid(char A[19],int n)
{
    int count=0;
    for (int i=0;i<=n-3;i++)
    {
        if(A[i]=='a' && A[i+1]=='b' && A[i+2]=='c')
          count++;
        if (count>1)
          return 0;
    }
    if (count==1) return 1;
    else return 0;
}

int exhsearch(int n)
{
    char str[n+1];
    for (int i=0;i<n;i++)
      str[i]='a';
    str[n]='\0';
    int count=0;
    for (int i=1; i<=pow(3,n);i++)
    {
        for (int j=n-1;j>=0;j--)
        {
            str[j]++;
            if (str[j]=='d')
                str[j]='a';
            else break;
        }
        //cout<<str<<endl;
        if (isvalid(str,n)) count++;
    }
    return count;
    // cout<<count<<endl;
}

void exhsearch_rec(char str[19], int n, int *ccc)
{
    int counthere=0;
    for (;counthere<n;counthere++)
      if(str[counthere]=='\0') break;
    if (counthere==n)
    {
      // cout<<str<<endl;
      if(isvalid(str,n)) *ccc+=1;
      return;
    }
    char new_str[n+1];
    str[counthere]='a';
    str[counthere+1]='\0';
    exhsearch_rec(str, n, ccc);
    str[counthere]='b';
    str[counthere+1]='\0';
    exhsearch_rec(str, n, ccc);
    str[counthere]='c';
    str[counthere+1]='\0';
    exhsearch_rec(str, n, ccc);
}


int main()
{
    int n;
    while(1)
    {
        cout<<"How many letters? ";
        cin>>n;
        if (n>18)
          cout<<"Enter values less than 18.\n";
        else if (n<0)
            cout<<"Invalid input.\n";
        else
            break;
    }
    clock_t c1, c2;
    c1=clock();
    int count = exhsearch(n);
    c2=clock();
    cout<<"With iteration: "<<count<<" and time: "<<(double)(c2 - c1) / (double)CLOCKS_PER_SEC<<endl;
    char *str;
    int *ccc= new int;
    str=(char *) malloc(19*sizeof(char));
    str[0]='\0';
    c1=clock();
    exhsearch_rec(str,n, ccc);
    c2=clock();
    cout<<"With recursion: "<<*ccc<<" and time: "<<(double)(c2 - c1) / (double)CLOCKS_PER_SEC<<endl;
}


















