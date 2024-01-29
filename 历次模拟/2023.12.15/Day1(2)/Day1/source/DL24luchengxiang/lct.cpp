#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define endl '\n'
#define gc cin.get
#define pc cout.put
const int N=2e5+5;
const int M=1e8+5;
const int inf=0x3f3f3f3f;
const int mod=1e8+7;
inl int read(){
    int x=0,f=1;char c=gc();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=gc();}
    return x*f;
}
inl void write(int x){
    if(x<0){pc('-');x=-x;}
    if(x>9)write(x/10);
    pc(x%10+'0');
}
inl void writei(int x){write(x);pc(' ');}
inl void writel(int x){write(x);pc('\n');}
int n,m,len,bl[N],pre[N],t[N],ans[N];
int head[N],nxt[N],to[N],cnt;
inl void add(int u,int v){
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
struct qus{
    int l,r,id,ans;
    friend bool operator<(qus a,qus b){return bl[a.l]^bl[b.l]?bl[a.l]<bl[b.l]:bl[a.l]&1?a.r<b.r:a.r>b.r;}
}q[N];
struct node{
    int l,r,id,op;
};
vector<node>v[N];
signed main(){
    freopen("lct.in","r",stdin);
    freopen("lct.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    n=read();m=read();len=sqrt(n);
    for(int i=1;i<=n;i++)bl[i]=(i-1)/len+1;
    for(int i=1;i<=n-1;i++){
        int u=read(),v=read();
        add(u,v);add(v,u);
    }
    for(int x=1;x<=n;x++){
        for(int i=head[x];i;i=nxt[i]){
            int y=to[i];
            t[y]++;
        }
        pre[x]=t[x];
    }
    memset(t,0,sizeof t);
    for(int i=1;i<=m;i++)
        q[i]={read(),read(),i,0};
    sort(q+1,q+m+1);
    for(int i=1,l=1,r=0;i<=m;i++){
        if(r<q[i].r)v[l-1].emplace_back((node){r+1,q[i].r,i,-1});
        while(r<q[i].r)q[i].ans+=pre[++r];
        if(l>q[i].l)v[r].emplace_back((node){q[i].l,l-1,i,1});
        while(l>q[i].l)q[i].ans-=pre[--l];
        if(r>q[i].r)v[l-1].emplace_back((node){q[i].r+1,r,i,1});
        while(r>q[i].r)q[i].ans-=pre[r--];
        if(l<q[i].l)v[r].emplace_back((node){l,q[i].l-1,i,-1});
        while(l<q[i].l)q[i].ans+=pre[l++];
    }
    for(int x=1;x<=n;x++){
        for(int i=head[x];i;i=nxt[i]){
            int y=to[i];
            t[y]++;
        }
        for(auto i:v[x]){
            int l=i.l,r=i.r,id=i.id,op=i.op;
            for(int j=l;j<=r;j++){
                int ret=t[j];
                q[id].ans+=op*ret;
            }
        }
    }
    for(int i=1;i<=m;i++)q[i].ans+=q[i-1].ans;
    for(int i=1;i<=m;i++)ans[q[i].id]=q[i].r-q[i].l+1-q[i].ans;
    for(int i=1;i<=m;i++)cout<<ans[i]<<endl;
    return 0;
}