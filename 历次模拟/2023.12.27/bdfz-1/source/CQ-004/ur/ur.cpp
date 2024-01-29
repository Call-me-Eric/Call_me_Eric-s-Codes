#include<bits/stdc++.h>
using namespace std;
int n,k,p;
int main()
{
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    scanf("%d%d",&n,&k);
    p=n;
    for(int i=2;i<n;i++)
    {
        if(n%i==0&&k/i*i>k/p*p)
        {
            p=i;
        }
    }
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<n/p;j++)
        {
            printf("%d",j<k/p);
        }
    }
    return 0;
}