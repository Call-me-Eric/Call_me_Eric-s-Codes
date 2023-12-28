#include<bits/stdc++.h>
using namespace std;
const int M=1e6+5;
bool v[M];
int tot=0,prime[M];
void pre()
{
    for(int i=2;i<=M-5;i++)
    {
        if(!v[i]) tot++,prime[tot]=i;
        for(int j=1;j<=tot&&i*prime[j]<=M-5;j++)
        {
            v[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}
int main()
{
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k),pre();
    if(n==k)
    {
        for(int i=1;i<=n;i++) printf("1");
        return 0;
    }
    if(k<=1)
    {
        for(int i=1;i<=n;i++) printf("0");
        return 0;
    }
    if(v[n])
    {
        if(k<n) for(int i=1;i<=n;i++) printf("0");
        else for(int i=1;i<=n;i++) printf("1");
        return 0;
    }
    return 0;
}