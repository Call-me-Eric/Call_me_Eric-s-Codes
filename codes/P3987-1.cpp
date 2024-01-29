// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define L (o<<1)
#define R (o<<1|1)
using namespace std;
const int maxn=500010;
int n,m,a[maxn],op,l,r,x;
vector<int>g[maxn];
const int ddd=40000010;
struct FHQ
{
    int rt[maxn],cnt,lc[ddd],rc[ddd],siz[ddd],val[ddd];
    void print(int o)
    {
        if(!o)return;
        print(lc[o]);
        printf("%d ",val[o]);
        print(rc[o]);
    }
    void maintain(int o){siz[o]=siz[lc[o]]+siz[rc[o]]+1;}
    int build(int l,int r,int*p)
    {
        if(l>r)return 0;
        int mid=(l+r)>>1,v=p[mid],ret=newnode(v);
        lc[ret]=build(l,mid-1,p);
        rc[ret]=build(mid+1,r,p);
        maintain(ret);
        return ret;
    }
    int merge(int x,int y)
    {
        if(x==0||y==0)return x+y;
        maintain(x);maintain(y);
        if(rand()<rand())
        {
            rc[x]=merge(rc[x],y);
            maintain(x);return x;
        }
        else
        {
            lc[y]=merge(x,lc[y]);
            maintain(y);return y;
        }
    }
    void split_val(int o,int k,int&x,int&y)
    {
        if(!o){x=y=0;return;}
        if(val[o]<=k)x=o,split_val(rc[o],k,rc[o],y);
        else y=o,split_val(lc[o],k,x,lc[o]);
        maintain(o);
    }
    void split_siz(int o,int k,int&x,int&y)
    {
        if(!o){x=y=0;return;}
        if(siz[lc[o]]>=k)y=o,split_siz(lc[o],k,x,lc[o]);
        else x=o,split_siz(rc[o],k-siz[lc[o]]-1,rc[o],y);
        maintain(o);
    }
    int newnode(int v)
    {
        cnt++;
        lc[cnt]=rc[cnt]=0;
        val[cnt]=v;
        siz[cnt]=1;
        return cnt;
    }
}st;
typedef long long ll;
/*
struct segtree
{
    ll sum[maxn];
    void build(int o,int l,int r)
    {
        if(l==r){sum[o]=a[l];return;}
        int mid=(l+r)>>1;
        build(L,l,mid);
        build(R,mid+1,r);
        sum[o]=sum[L]+sum[R];
    }
    void update(int o,int l,int r,int x,int v)
    {
        if(l==r){sum[o]=v;return;}
        int mid=(l+r)>>1;
        if(x<=mid)update(L,l,mid,x,v);
        if(x>=mid+1)update(R,mid+1,r,x,v);
        sum[o]=sum[L]+sum[R];
    }
    ll query(int o,int l,int r,int ql,int qr)
    {
        if(r<ql||l>qr)return 0;
        if(ql<=l&&r<=qr)return sum[o];
        int mid=(l+r)>>1;
        return query(L,l,mid,ql,qr)+query(R,mid+1,r,ql,qr);
    }
}sg;
*/
#define lowbit(x) (x&(-x))
struct bit
{
    ll sum[maxn];
    void upd(int o,int v){for(int i=o;i<=n;i+=lowbit(i))sum[i]+=v;}
    ll query(int o){ll ret=0;for(int i=o;i;i-=lowbit(i))ret+=sum[i];return ret;}
}sg;
int cur,q[maxn];
void dfs(int x,int v)
{
    if(!x)return;
    if(st.lc[x])dfs(st.lc[x],v);
    if(a[st.val[x]]%v==0)sg.upd(st.val[x],-a[st.val[x]]),a[st.val[x]]/=v,sg.upd(st.val[x],a[st.val[x]]);
    if(a[st.val[x]]%v==0)q[++cur]=st.val[x];
    if(st.rc[x])dfs(st.rc[x],v);
}
void del(int x,int l,int r)
{
    int a,b,c;
    st.split_val(st.rt[x],r,b,c);
    st.split_val(b,l-1,a,b);
    cur=0;int t=0;dfs(b,x);
    t=st.build(1,cur,q);
    st.rt[x]=st.merge(a,st.merge(t,c));
}
inline int read()
{
    int ret=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')ret=((ret+(ret<<2))<<1)+ch-'0',ch=getchar();
    return ret;
}
inline void write(ll x)
{
    if(x<10){putchar('0'+x);return;}
    write(x/10);putchar('0'+(x%10));
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)sg.upd(i,a[i]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j*j<=a[i];j++)if(a[i]%j==0)
        {
            g[j].push_back(i);
            //st.rt[j]=st.merge(st.rt[j],st.newnode(i));
            if(j*j!=a[i])g[a[i]/j].push_back(i);
            //st.rt[a[i]/j]=st.merge(st.rt[a[i]/j],st.newnode(i));
        }
    }
    for(int i=1;i<=500000;i++)
    {
        cur=0;
        for(vector<int>::iterator it=g[i].begin();it!=g[i].end();it++)q[++cur]=*it;
        st.rt[i]=st.build(1,cur,q);
    }
    while(m--)
    {
        op=read();l=read();r=read();
        if(op==2)write(sg.query(r)-sg.query(l-1)),putchar('\n');
        else
        {
            x=read(); 
            if(x>1)del(x,l,r);
            //printf("sg:");sg.print(1,1,n);printf("\n");
        }
    }
    return 0;
}
