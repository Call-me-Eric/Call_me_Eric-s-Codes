#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define rint int
#define endl '\n'
#define uint unsigned long long
int read(){
    int x=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c))x=x*10+c-48,c=getchar();
    return x*f;
}const int N=50,p=998244353;

int n,m,k;uint wei[N];
int a[N],b[N];
map<uint,int> mp[22];
int dfs(int x=1,uint h=0)
{
    if(mp[x].find(h)!=mp[x].end()) return mp[x][h];
    if(x==k+1)
    {
        for(rint i=1;i<=m+1;i++) if(a[i]!=b[i]) return mp[x][h]=0;
        return mp[x][h]=1;
    }
    int sum=0;
    for(rint i=1;a[i-1];i++) if(a[i-1]>a[i]) a[i]++,sum+=dfs(x+1,h+wei[i]),sum=sum>=p?sum-p:sum,a[i]--;
    for(rint i=1;a[i];i++) if(a[i]>a[i+1]) a[i]--,sum+=dfs(x+1,h-wei[i]),sum=sum>=p?sum-p:sum,a[i]++;
    return mp[x][h]=sum;
}

signed main()
{
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    
    n=read(),a[0]=p;
    for(rint i=1;i<=n;i++) a[i]=read();
    m=read();
    for(rint i=1;i<=m;i++) b[i]=read();
    read(),k=read();
    wei[n+k]=1;for(rint i=n+k;i;i--) wei[i-1]=wei[i]*131;
    cout<<dfs()<<endl;
    return 0;
}