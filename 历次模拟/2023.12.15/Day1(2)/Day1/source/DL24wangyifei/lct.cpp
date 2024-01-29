#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
    long long xr=0,F=1; char cr;
    while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
    while(cr>='0'&&cr<='9')
        xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
    return xr*F;
}
#define int long long
const int N=2e5+5;
int n,Q,ans[N];
struct node{int l,r,id;};
vector<node> q[N];
vector<int> e[N];
struct segtree
{
    int tr[N<<2],lz[N<<2];
    #define ls (x<<1)
    #define rs (x<<1|1)
    #define mid (l+r>>1)
    il void pushdown(int x,int l,int r)
    {
        tr[ls]+=(mid-l+1)*lz[x],tr[rs]+=(r-mid)*lz[x];
        lz[ls]+=lz[x],lz[rs]+=lz[x];
        lz[x]=0;
    }
    il void modify(int x,int l,int r,int ml,int mr,int k)
    {
        if(l==ml&&r==mr) {tr[x]+=(r-l+1)*k,lz[x]+=k;return;}
        pushdown(x,l,r);
        if(mr<=mid) modify(ls,l,mid,ml,mr,k);
        else if(ml>mid) modify(rs,mid+1,r,ml,mr,k);
        else modify(ls,l,mid,ml,mid,k),modify(rs,mid+1,r,mid+1,mr,k);
        tr[x]=tr[ls]+tr[rs];
    }
    il int query(int x,int l,int r,int pos)
    {
        if(l==r) return tr[x];
        pushdown(x,l,r);
        if(pos<=mid) return query(ls,l,mid,pos);
        else return query(rs,mid+1,r,pos);
    }
}seg;
il void solve(int r)
{
    vector<int> s;
    for(auto v:e[r]) if(v<r) s.push_back(v);
    seg.modify(1,1,n,1,r,1);
    sort(s.begin(),s.end()),reverse(s.begin(),s.end());
    for(auto x:s) seg.modify(1,1,n,1,x,-1);
    for(auto x:q[r]) ans[x.id]=seg.query(1,1,n,x.l);
    // for(int i=1;i<=r;i++) cout<<seg.query(i)<<" "; cout<<endl;
}
signed main()
{
    freopen("lct.in","r",stdin);
    freopen("lct.out","w",stdout);
    n=read(),Q=read();
    for(int i=1;i<n;i++) 
    {
        int u=read(),v=read();
        e[u].push_back(v),e[v].push_back(u);
    }
    for(int i=1;i<=Q;i++)
    {
        int l=read(),r=read(),id=i;
        q[r].push_back({l,r,id});
    }
    for(int i=1;i<=n;i++) solve(i);
    for(int i=1;i<=Q;i++) printf("%lld\n",ans[i]);
    return 0;
}
/*
4 1
1 4
4 3
3 2
1 3
*/