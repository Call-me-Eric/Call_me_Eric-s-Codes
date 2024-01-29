#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(j);i<=(k);i++)
#define per(i,j,k) for (int i=(j);i>=(k);i--)
#define pb push_back
#define ll long long
#define pdd pair<double,double>
#define pii pair<int,int>
#define fi first
#define se second
#define pcnt __builtin_popcount
#define mkp make_pair
const ll mod=998244353;
int n,q;
const int N=707;
ll ksm(ll x,ll y)
{
    ll res=1;
    while (y)
    {
        if (y&1) res=res*x%mod;
        x=x*x%mod,y>>=1;
    }
    return res;
}
struct matrix
{
    ll a[N][N];
    int ans;
    void init()
    {
        rep(i,1,n) rep(j,1,n) a[i][j]=0;
        ans=0;
    }
    void print()
    {
        rep(i,1,n) 
        {
            rep(j,1,n+1) cout << a[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
    void insert(ll *tmp)
    {
        static ll b[N];
        rep(i,1,n+1) b[i]=tmp[i];
        rep(i,1,n)
        {
            if (b[i]==0) continue;
            if (a[i][i]==0) 
            {
                rep(j,1,n+1) a[i][j]=b[j];
                return;
            }
            ll x=ksm(b[i],mod-2)*a[i][i]%mod;
            rep(j,i,n+1) b[j]=(b[j]*x+mod-a[i][j])%mod;
        }
        if (b[n+1]!=0) ans=1;
        // print();
    }
    bool check()
    {
        rep(i,1,n) if (a[i][i]==0) return 0;
        return 1;
    }
}st[12];
int cnt;
ll b[N*2][N];
vector<int>g[N*4];
void update(int u,int L,int R,int l,int r,int y)
{
    if (l<=L&&R<=r)
    {
        g[u].pb(y);
        return;
    }
    int mid=(L+R)>>1;
    if (l<=mid) update(u*2,L,mid,l,r,y);
    if (mid<r) update(u*2+1,mid+1,R,l,r,y);
}
int f[N],t[N];
ll ans[N];
void solve(int u,int d,int l,int r)
{
    st[d]=st[d-1];
    for (int i:g[u]) st[d].insert(b[i]);
    if (l==r)
    {
        if (st[d].check()==0)
        {
            if (st[d].ans==1) cout << "No\n";
            else cout << "Many\n";
        }
        else
        {
            per(i,n,1)
            {
                ans[i]=ksm(st[d].a[i][i],mod-2)*st[d].a[i][n+1]%mod;
                rep(j,1,i-1) (st[d].a[j][n+1]+=mod-st[d].a[j][i]*ans[i]%mod)%=mod;
            }
            rep(i,1,n) cout << ans[i] << " ";
            cout << "\n";
        }
        return;
    }
    int mid=(l+r)>>1;
    solve(u*2,d+1,l,mid);
    solve(u*2+1,d+1,mid+1,r);
}

int main()
{
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    rep(i,1,n) rep(j,1,n+1) cin >> b[i][j];
    rep(i,1,n) f[i]=i;
    rep(i,1,q)
    {
        int id;
        cin >> id;
        update(1,0,q,t[id],i-1,f[id]);
        f[id]=n+i,t[id]=i;
        rep(j,1,n+1) cin >> b[n+i][j];
    }
    rep(i,1,n) update(1,0,q,t[i],q,f[i]);
    st[0].init();
    solve(1,1,0,q);
    return 0;
}