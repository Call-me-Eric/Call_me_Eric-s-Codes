#include<bits/stdc++.h>
#define mp make_pair
using namespace std;
const int M=2e5+5;
vector<int>v[2][M];
long long f[M],s[M];
long long poww(int a,int b)
{
    if(a==0) return 1;
    long long ans=1,x=a;
    while(b)
    {
        if(b&1) ans*=x;
        x*=x;
        b>>=1;
    }
    return ans;
}
int main()
{
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    int n,m,x,y,op=0,cnt=0,ans=0,ff=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y),cnt++;
        v[op][x].push_back(cnt),v[op][y].push_back(cnt);
    }
    f[0]=n;
    for(int i=1;i<=2000;i++)
    {
        f[i]=m,op^=1,cnt=0;
        for(int i=1;i<=n;i++) v[op][i].clear();
        for(int j=1;j<=n;j++)
            for(int k=0;k<v[op^1][j].size();k++)
                for(int kk=k+1;kk<v[op^1][j].size();kk++)
                {
                    x=v[op^1][j][k],y=v[op^1][j][kk];
                    cnt++,v[op][x].push_back(cnt),v[op][y].push_back(cnt);
                }
        n=m,m=cnt;
    }
    for(int i=1;i<=2000;i++) f[i]+=f[i-1];
    while(ans<=2000)
    {
        for(int i=0;i<=2000;i++) s[i]=f[i]/poww(i,ans);
        if(s[2000]==s[1999]) {printf("%d %lld",ans,s[2000]),ff=1;break;}
        ans++;
    }
    if(!ff) printf("-1");
    return 0;
}