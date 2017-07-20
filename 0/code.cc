#include<iostream>
#include<math.h>
#include<time.h>
#include<string.h>
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

int exhsearch_iter(int n)
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
        // cout<<str<<endl;
        if (isvalid(str,n)) count++;
    }
    return count;
    // cout<<count<<endl;
}

void exhsearch_rec(char str[19], int &count_global, int n)
{
    int counthere=0;
    for (;counthere<n;counthere++)
      if(str[counthere]=='\0') break;
    if (counthere==n)
    {
      cout<<str<<endl;
      if(isvalid(str,n)) count_global++;
      return;
    }
    char new_str[n+1];
    str[counthere]='a';
    strcpy(new_str,str);
    exhsearch_rec(new_str, count_global, n);
    str[counthere]='b';
    strcpy(new_str,str);
    exhsearch_rec(new_str, count_global, n);
    str[counthere]='c';
    strcpy(new_str,str);
    exhsearch_rec(new_str, count_global, n);
}


int main()
{
    int n;
    clock_t c1, c2;
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
    c1 = clock();
    int count = exhsearch_iter(n);
    c2 = clock();
    cout<<"With iteration: "<<count<<" and time: "<<(double)(c2-c1)/CLOCKS_PER_SEC<<endl;
    int count_global=0;
    char str[n+1];
    str[0]='\0';
    c1 = clock();
    exhsearch_rec(str, count_global, n);
    c2 = clock();
    cout<<"With recursion: "<<count_global<<" and time: "<<(double)(c2-c1)/CLOCKS_PER_SEC<<endl;
}


















