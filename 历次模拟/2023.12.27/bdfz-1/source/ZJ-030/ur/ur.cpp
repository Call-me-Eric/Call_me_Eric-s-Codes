#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(j);i<=(k);i++)
#define per(i,j,k) for (int i=(j);i>=(k);i--)
#define pb push_back
#define ll long long
#define pdd pair<double,double>
#define fi first
#define se second
#define pcnt __builtin_popcount
#define mkp make_pair
const double eps=1e-10;
int n,k;
const int N=2e6+5;
pdd a[N][2];
bool cmp(pdd x,pdd y)
{
    if (fabs(x.fi-y.fi)+fabs(x.se-y.se)<eps) return 0;
    return x<y;
}
map<pdd,int,decltype(cmp)*>q(cmp);
const double pi=acos(-1);
double w;
void dfs(int u,int v,pdd s,int t,int tp)
{
    if (u>t)
    {
        a[v][tp]=s;
        return;
    }
    dfs(u+1,v,s,t,tp);
    dfs(u+1,v|(1<<(t-u)),mkp(s.fi+sin(w*u),s.se+cos(w*u)),t,tp);
}
void print(int S,int l)
{
    per(i,l,0) 
    {
        if (S&(1<<i)) cout << 1;
        else cout << 0;
    }
}
pdd F(pdd x)
{
    return mkp(-x.fi,-x.se);
}
int p[N],cnt;
void work(int x)
{
    for (int i=2;i*i<=x;i++)
    {
        while (x%i==0)
        {
            p[++cnt]=i;
            x/=i;
        }
    }
    if (x>1) p[++cnt]=x;
}

int main()
{
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    if (n<=36)
    {
        w=2*pi/n;
        int mid=(n-1)/2;
        dfs(0,0,mkp(0.0,0.0),mid,0);
        dfs(mid+1,0,mkp(0.0,0.0),n-1,1);
        rep(i,0,(1<<(mid+1))-1) 
        {
            if (q.find(a[i][0])==q.end()) q[a[i][0]]=i;
            else if (pcnt(q[a[i][0]])<pcnt(i)) q[a[i][0]]=i;
        }
        int ans=0,ansx=0,ansy=0;
        rep(i,0,(1<<(n-mid-1))-1)
        {
            if (q.find(F(a[i][1]))==q.end()) continue;
            if (pcnt(i)+pcnt(q[F(a[i][1])])>k) continue;
            if (ans>=pcnt(i)+pcnt(q[F(a[i][1])])) continue;
            ans=pcnt(i)+pcnt(q[F(a[i][1])]);
            ansx=q[F(a[i][1])],ansy=i;
        }
        print(ansx,mid),print(ansy,n-mid-2);  
        return 0; 
    }
    if (k<=1)
    {
        rep(i,1,n) cout << 0;
        return 0;
    }
    if (k==n)
    {
        rep(i,1,n) cout << 1;
        return 0;
    }
    work(n);
    bool flag=1;
    rep(i,1,cnt) if (p[i]!=p[1]) flag=0;
    if (flag)
    {
        int d=n/p[1];
        int ans=k/p[1];
        rep(i,1,p[1]) 
        {
            rep(j,1,ans) cout << 1;
            rep(j,ans+1,d) cout << 0;
        }
        return 0;
    }
    else if (cnt==2)
    {
        int ans1=k/p[1],ans2=k/p[2];
        if (ans1*(p[1])<ans2*(p[2])) swap(p[1],p[2]),swap(ans1,ans2);
        rep(i,1,p[1])
        {
            rep(j,1,ans1) cout << 1;
            rep(j,ans1+1,n/p[1]) cout << 0;
        }
        return 0;
    }
    return 0;
}