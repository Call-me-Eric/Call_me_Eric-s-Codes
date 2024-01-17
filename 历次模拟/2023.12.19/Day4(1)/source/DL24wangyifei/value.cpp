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
const int N=1.5e5+5;
int n,y[N],bel[N],tot,ans;
struct node{int a,b;} a[N];
il bool cmp(node x,node y) 
{
    if(x.a!=y.a) return x.a<y.a;
    else return x.b<y.b;
}
vector<int> t[N];
struct BIT
{
    int tr[N];
    il void modify(int x,int k) {for(;x<=tot;x+=x&(-x)) tr[x]+=k;}
    il void add(int l,int r,int k) {modify(l,k),modify(r+1,-k);} 
    il int query(int x) {int res=0;for(;x;x-=x&(-x)) res+=tr[x];return res;}
}tr;
signed main()
{
    freopen("value.in","r",stdin);
    freopen("value.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++) a[i].a=read(),a[i].b=read();
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) y[++tot]=a[i].b;
    sort(y+1,y+tot+1); tot=unique(y+1,y+tot+1)-y-1;
    for(int i=1;i<=n;i++) bel[i]=lower_bound(y+1,y+tot+1,a[i].b)-y;
    int last=0;
    for(int i=1;i<=n+1;i++)
    {
        int x=i<=n?a[i].a:1e9;
        int res=(n-i+1)*x,mx=0;
        if(x!=a[i-1].a) 
        {
            for(int j=last;j<i;j++) tr.add(1,bel[j],1);
            last=i;
        }
        int l=1,r=upper_bound(y+1,y+tot+1,x)-y-1;
        // cout<<"QAQ "<<r<<endl;
        while(r-l>5)
        {
            int mid1=l+(r-l)/3,mid2=r-(r-l)/3;
            if(y[r]>a[i].a||tr.query(mid2)==0||tr.query(mid1)*y[mid1]>tr.query(mid2)*y[mid2]) r=mid2;
            else l=mid1;
        }
        for(int j=l;j<=r;j++) mx=max(mx,tr.query(j)*y[j]);
        int pos=lower_bound(y+1,y+tot+1,x)-y;
        if(pos<=tot) mx=max(mx,tr.query(pos)*x);
        // cout<<"res "<<i<<" "<<res+mx<<" "<<res<<" "<<mx<<" "<<bel[i]<<endl;
        // cout<<"l r"<<l<<" "<<r<<endl;
        // for(int i=1;i<=tot;i++) cout<<y[i]<<" "<<tr.query(i)<<endl;
        ans=max(ans,res+mx);
    }
    printf("%lld\n",ans);
    return 0;
}
/*
7
13 21
31 15
49 22
28 37
45 9
23 8
2 43

*/