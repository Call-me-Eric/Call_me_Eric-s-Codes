#include <bits/stdc++.h>
using namespace std;

const int maxn=1e6+10;

int n,K;

inline void check(int x,int y)
{
    if(x<=1 || (n-x*y)%x) return;
    // cerr<<"segcnt:"<<x<<"  everyseg:"<<y<<"  tot:"<<x*y<<endl;
    int block=(n-x*y)/x;
    vector<bool>ans;
    for(int i=1;i<=x;i++)
    {
        for(int j=1;j<=y;j++) ans.push_back(1);
        for(int j=1;j<=block;j++) ans.push_back(0);
    }
    for(auto x:ans) cout<<x;cout<<'\n';
    exit(0);
}

inline void solve()
{
    cin>>n>>K;
    for(int k=K;k>=1;k--)
    {
        for(int i=1;i*i<=k;i++) if(k%i==0)
        {
            check(i,k/i);
            if(i*i!=k) check(k/i,i);
        }
    }
    for(int i=1;i<=n;i++) cout<<"0";cout<<endl;
}

signed main()
{
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(NULL);
    solve();
}