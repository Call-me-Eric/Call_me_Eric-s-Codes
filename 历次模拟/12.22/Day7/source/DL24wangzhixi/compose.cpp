#include <bits/stdc++.h>
using namespace std;
inline void cmin(int &x,int y){if(y<x)x=y;}
typedef pair<int,int> pii;
const int maxn=1e5+5;

int n,K,Q,m;
pii w[maxn][24];
bitset<(1<<12)+10>f[maxn];
int base[15][maxn];
inline void solve()
{
    cin>>n>>K>>Q,m=K;
    for(int i=0;i<K;i++) for(int j=1,x;j<=n;j++) cin>>x,w[j][i]=pii(x,i);
    for(int j=1;j<=n;j++) sort(w[j],w[j]+K);
    for(int j=1;j<=n;j++) for(int i=0;i<K;i++)
        if(i) base[i][j]=base[i-1][j]|(1<<w[j][i].second);
        else base[i][j]=(1<<w[j][i].second);
    for(int i=0;i<K;i++) for(int s=0;s<(1<<K);s++) f[i][s]=(s>>i&1);
    for(int i=1,opt,x,y;i<=Q;i++)
    {
        cin>>opt>>x>>y,x--;
        if(opt==1) f[m++]=f[x]&f[y-1];
        if(opt==2) f[m++]=f[x]|f[y-1];
        if(opt==3)
        {
            int res=INT_MAX;
            for(int j=0;j<K;j++) if(f[x][base[j][y]]) cmin(res,w[y][j].first);
            cout<<res<<'\n';
        }
    }
}
signed main()
{
    freopen("compose.in","r",stdin);
    freopen("compose.out","w",stdout);
    solve();
}
