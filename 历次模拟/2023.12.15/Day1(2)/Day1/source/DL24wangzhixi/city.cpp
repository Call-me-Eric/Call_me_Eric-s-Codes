#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+10,mod=22222223;
inline void Add(int &x,int y){x=(x+y)%mod;}
int inv[maxn],fac[maxn];
inline int binom(int x,int y){return x<0||y<0||x<y?0:fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline int qpow(int s,int t)
{
    int res=1,base=s%mod;
    while(t){if(t&1)res=res*base%mod;base=base*base%mod;t>>=1;}
    return res;
}
int n,m,a[maxn],b[maxn];
vector<int>lsh;
inline void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],lsh.push_back(a[i]);
    for(int i=1;i<=m;i++) cin>>b[i],lsh.push_back(b[i]);
    sort(lsh.begin(),lsh.end(),greater<int>());
    lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
    sort(a+1,a+n+1,greater<int>()),sort(b+1,b+m+1,greater<int>());
    int ans=1,la=1,lb=1,posa=0,posb=0;
    for(auto s:lsh)
    {
        int A=0,B=0,C=posa,D=posb,res=0;
        while(posa<n && a[posa+1]>=s) posa++,A++;
        while(posb<m && b[posb+1]>=s) posb++,B++;
        for(int j=0;j<=A;j++)
        {
            int base1=qpow(s,j)*(qpow(s+1,A+C-j)-qpow(s,A+C-j)%mod);
            int base2=qpow(s,j)*qpow(s+1,A-j)%mod;
            int val=binom(A,j)*qpow(base1,B)%mod*qpow(base2,D)%mod;
            Add(res,(j&1)?(mod-val):val);
        }
        ans=ans*res%mod;
    }
    if(a[1]!=b[1]) cout<<"No solution!\n";
    else cout<<ans<<endl;
}
signed main()
{
    freopen("city.in","r",stdin);
    freopen("city.out","w",stdout);
    inv[0]=inv[1]=fac[0]=fac[1]=1;
    for(int i=2;i<maxn;i++) fac[i]=fac[i-1]*i%mod,inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for(int i=2;i<maxn;i++) inv[i]=inv[i-1]*inv[i]%mod;
    ios::sync_with_stdio(false);cin.tie(NULL);
    solve();   
}
