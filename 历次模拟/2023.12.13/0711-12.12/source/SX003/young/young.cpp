#include<bits/stdc++.h>
using namespace std;
int a[45],b[45],k,ans=0;
int pan(int n,int m)
{
    int ans=0;
    for(int i=1;i<=max(n,m);i++)
        ans+=abs(a[i]-b[i]);
    return ans;
}
void dfs(int n,int m,int x)
{
    if(x>k)
    {
        if(n!=m) return;
        for(int i=1;i<=n;i++)
            if(a[i]!=b[i]) return;
        ans++;return;
    }
    if(pan(n,m)>k-x+1) return;
    for(int i=1;i<=n+1;i++)
    {
        if((a[i-1]>=a[i]-1||i==1)&&a[i]-1>=a[i+1])
        {
            a[i]--;
            if(i==n&&a[i]==0) dfs(n-1,m,x+1);
            else dfs(n,m,x+1);
            a[i]++;
        }
        if((a[i-1]>=a[i]+1||i==1)&&a[i]+1>=a[i+1])
        {
            a[i]++;
            if(i==n+1&&a[i]==1) dfs(n+1,m,x+1);
            else dfs(n,m,x+1);
            a[i]--;
        }
    }
}
int main()
{
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    int n,m,q;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%d",&k),ans=0;
        dfs(n,m,1),printf("%d\n",ans);
    }
    return 0;
}