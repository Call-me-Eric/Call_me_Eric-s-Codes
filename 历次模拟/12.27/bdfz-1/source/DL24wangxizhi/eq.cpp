#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=710,mod=998244353;
inline void Add(int &x,int y){x=(x+y)%mod;}
inline int qpow(int s,int t)
{
    int res=1,base=s%mod;
    while(t){ if(t&1) res=res*base%mod; base=base*base%mod; t>>=1; }
    return res;
}

int n,Q,id[maxn];
int c[maxn][maxn],a[maxn][maxn];
inline void gauss()
{
    for(int i=1;i<=n;i++) for(int j=1;j<=n+1;j++) a[i][j]=c[i][j];
	
    int now=1;
    for(int i=1;i<=n;i++)
    {
		int maxx=now;
        for(int j=now+1;j<=n;j++) if(a[j][i]>a[maxx][i]) maxx=j;
		if(!a[maxx][i]) continue;
		for(int j=1;j<=n+1;j++) swap(a[now][j],a[maxx][j]);
		for(int j=1;j<=n;j++) if(j!=now)
        {
            int tmp=a[j][i]*qpow(a[now][i],mod-2)%mod;
            for(int k=i+1;k<=n+1;k++) Add(a[j][k],mod-a[now][k]*tmp%mod);
		}
		id[i]=now++;
	} 
	vector<int>v;
	for(int i=1;i<=n;i++) if(!id[i]) v.push_back(i);
	for(int j=0;now<=n && j<v.size();++now,++j) id[v[j]]=now;
	for(int i=1;i<=n;i++)
        if(!a[id[i]][i] && a[id[i]][n+1]>0) return cout<<"No\n",void();
        else if(!a[id[i]][i] && !a[id[i]][n+1]) return cout<<"Many\n",void();
	for(int i=1;i<=n;i++) cout<<a[id[i]][n+1]*qpow(a[id[i]][i],mod-2)%mod<<" ";
    cout<<'\n';
}
inline void solve()
{
    cin>>n>>Q;
    for(int i=1;i<=n;i++) for(int j=1;j<=n+1;j++) cin>>c[i][j];
    gauss();
    for(int i=1,p;i<=Q;i++)
    {
        cin>>p;
        for(int j=1;j<=n+1;j++) cin>>c[p][j];
        gauss();
    }
}
signed main()
{
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(NULL);
    solve();
}