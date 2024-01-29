#include<bits/stdc++.h>
using namespace std;
long long n,m,a[7001],z[7001],ans=10000000000;
inline void dfs(int k,long long zhi)
{
    if(k==n)
    {
        ans=min(ans,zhi);
        return;
    }
    if(zhi>=ans)
    return;
    for(int i=0;i<m;i++)
    {
        if(z[i]+a[k]<=ans){
        z[i]+=a[k];
        dfs(k+1,max(zhi,z[i]));
        z[i]-=a[k];
        }
    }
}
bool qwe(int a,int b)
{
    return a>b;
}
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    sort(a,a+n,qwe);
    dfs(0,0);
    cout<<ans;
}
