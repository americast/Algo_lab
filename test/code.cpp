/* Name: code.cpp
  Creator: Sayan Sinha (sayan.sinha@iitkgp.ac.in)
  Date: November 2, 2017
  Description: Lab test (even)
*/
#include <bits/stdc++.h>
using namespace std;

/* Name: esprofit
  Input: c, n, i, j
  Output: maximum profit
  Description: Exhaustively search for maximum profit taking into consideration all possible
    combinations. Uses recursion.
*/
double esprofit(double c[], int n, int i, int j)
{
    int left_index = n/2 - i - 1;
    int right_index = n/2 + j;

    if (left_index<0 && right_index>=n)
        return 0;
    if (left_index<0)
        return esprofit(c,n,i,j+1) + c[right_index]*pow(0.9,i+j);
    if (right_index>=n)
        return esprofit(c,n,i+1,j) + c[left_index]*pow(0.9,i+j);
    double left = c[left_index];
    double right = c[right_index];
    return max(esprofit(c,n,i+1,j) + left*pow(0.9,i+j),esprofit(c,n,i,j+1) + right*pow(0.9,i+j));
}


/* Name: grprofit
  Input: c, n, i, j
  Output: maximum profit
  Description: Greedily search for maximum profit taking into consideration only the
    best choice at an instant. Uses recursion.
*/
double grprofit(double c[], int n, int i, int j)
{
    int left_index = n/2 - i - 1;
    int right_index = n/2 + j;

    if (left_index<0 && right_index>=n)
        return 0;
    if (left_index<0)
        return grprofit(c,n,i,j+1) + c[right_index]*pow(0.9,i+j);
    if (right_index>=n)
        return grprofit(c,n,i+1,j) + c[left_index]*pow(0.9,i+j);
    double left = c[left_index];
    double right = c[right_index];
    if (left > right)
        return grprofit(c,n,i+1,j) + left*pow(0.9,i+j);
    else
        return grprofit(c,n,i,j+1) + right*pow(0.9,i+j);
}

/* Name: grprofit_nonrec
  Input: c, n, i, j
  Output: maximum profit
  Description: Greedily search for maximum profit taking into consideration only the
    best choice at an instant. Uses iteration. Created this for cross-checking since
    output is not the same as given in the paper.
*/
double grprofit_nonrec(double c[], int n)
{
    int left_index = n/2 -1;
    int right_index = n/2;
    int count = 0;
    double sum = 0.0;
    while(1)
    {
        if (left_index<0 || right_index>=n)
            break;
        if (c[left_index] > c[right_index])
            sum+= c[left_index--]*pow(0.9, count++);
        else
            sum+= c[right_index++]*pow(0.9, count++);
    }
    while(left_index>=0)
        sum+= c[left_index--]*pow(0.9, count++);
    while(right_index<n)
        sum+= c[right_index++]*pow(0.9, count++);
    return sum;
}

/* Name: dppprofit
  Input: c, n
  Output: T[0][0]
  Description: Maximise profit using dynamic programming. First take maximum possible
    values of both i and j. Fill T[i][j] as 0 as no further exploration is possible.
    Henceforth, keep decreasing the value of i or j and fill T[i][j] with the maximum
    value between the cases where i is 1 more added to the cost of the left most item
    on the current day, and, where j is 1 more added to the cost of the right most
    item on the current day. This goes on till T[0][0] is reached which is the answer.
    Enough padding has been applied to T so that no special cases need to be made for
    determination of T[i][j] at the boundaries. No recursion has been used.
*/
double dpprofit(double c[], int n)
{
    double T[n/2 + 3][n/2 + 3];     // Dimension is larger than required by constant
                                    //  value to avoid special cases at the
                                    //  boundaries
    for (int i=0; i<= n/2 + 2; i++)
        for (int j=0; j<=n/2 + 2; j++)
            T[i][j] = 0;
    int iter=0, i, j, flag = 0;
    if (n%2)
        flag++;
    for (i = n/2; i>=0; i--)
        for (j = n/2 + flag; j>=0 ; j--)
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
    double c[n];
    for (int i=0; i<n; i++)
        cin>>c[i];
    cout<<"+++\tExhaustive Search\n";
    cout<<"\tMaximum profit = "<<setprecision(8)<<esprofit(c, n, 0, 0)<<endl<<endl;
    cout<<"+++\tGreedy Strategy\n";
    // cout<<"\tMaximum profit = "<<setprecision(8)<<grprofit_nonrec(c,n)<<endl<<endl;
    cout<<"\tMaximum profit = "<<setprecision(8)<<grprofit(c,n,0,0)<<endl<<endl;
    cout<<"+++\tDynamic Programming\n";
    cout<<"\tMaximum profit = "<<setprecision(8)<<dpprofit(c,n)<<endl<<endl;
}