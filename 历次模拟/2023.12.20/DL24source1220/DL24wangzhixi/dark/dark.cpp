#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=1e5+10;
int mod,Q;
int s[maxn],sum[maxn];
inline bool check(int l,int r)
{
    return sum[r]-sum[l-1]>(r-l+1)*3;
}
inline void solve()
{
    cin>>mod>>Q;
    s[1]=134775813%mod;
    for(int i=2;i<maxn;i++) s[i]=(1103515245*s[i-1]%mod+1013904223)%mod;
    for(int i=1;i<500;i++)
    {
        sum[i]=sum[i-1];
        if(s[i]&1) sum[i]+=4;
        else if(s[i]%4==0) sum[i]++;
        else sum[i]+=3;
    }

    for(int i=1,L,R;i<=Q;i++)
    {
        cin>>L>>R;
        int ans=0;

        for(int l=L;l<=R;l++)
            for(int r=l;r<=R;r++)
                ans+=check(l,r);
        cout<<ans<<'\n'; 
    }
}
signed main()
{
    freopen("dark.in","r",stdin);
    freopen("dark.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(NULL);
    solve();
}