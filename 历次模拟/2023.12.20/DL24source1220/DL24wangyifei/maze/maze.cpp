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
const int mod=998244353;
int m,tp,lst;
namespace sub1
{
    const int N=1e5+5;
    struct segtree
    {
        int tr[N<<2];
        il void add(int l,int r,int k) {for(int i=l;i<=r;i++) tr[i]=(tr[i]+k)%mod;}
        il int query(int l,int r) 
        {
            int res=0;
            for(int i=l;i<=r;i++) res+=tr[i];
            return res;
        }
    }seg;
    typedef pair<int,int> pir;
    #define fi first
    #define se second
    pir pos[N];
    int id[1005][1005];
    int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
    il void init(int mx)
    {
        int x=sqrt(mx)+3,y=x;
        pos[1]=pir(x,y),id[x][y]=1; int w=0; 
        for(int i=2;i<=mx;i++)
        {
            x+=dx[w],y+=dy[w];
            pos[i]=pir(x,y),id[x][y]=i; int nw=(w+1)%4;
            if(!id[x+dx[nw]][y+dy[nw]]) w=nw;
        }
    }
    int main()
    {
        init(1e5);
        while(m--)
        {
            int op=read();
            if(op==1)
            {
                int l=read()^(lst*tp),r=read()^(lst*tp),v=read()^(lst*tp);
                seg.add(l,r,v);
            }
            else if(op==2)
            {
                int x=read()^(lst*tp),v=read()^(lst*tp);
                int a=pos[1].fi,b=pos[1].se,c=pos[x].fi,d=pos[x].se;
                if(a>c) swap(a,c); if(b>d) swap(b,d);
                for(int i=a;i<=c;i++)
                    for(int j=b;j<=d;j++) 
                    {
                        // cout<<"qwq"<<id[i][j]<<endl;
                        seg.add(id[i][j],id[i][j],v);
                    }
            }
            else if(op==3)
            {
                int l=read()^(lst*tp),r=read()^(lst*tp);
                lst=seg.query(l,r); printf("%lld\n",lst);
            }
        }
        return 0;
    }
}
namespace sub5
{
    const int N=2e7+5;
    struct segtree
    {
        #define ls(x) tr[(x)].l
        #define rs(x) tr[(x)].r
        #define mid (l+r>>1)
        struct node
        {
            int x,l,r,lz;
            node() {x=l=r=lz=0;}
        }tr[N];
        int tot;
        void modify(int &now,int l,int r,int ml,int mr,int k)
        {
            if(!now) now=++tot;
            (tr[now].x+=(mr-ml+1)*k%mod)%=mod;
            if(l==ml&&r==mr) {(tr[now].lz+=k)%=mod;return;}
            if(mr<=mid) modify(ls(now),l,mid,ml,mr,k);
            else if(ml>mid) modify(rs(now),mid+1,r,ml,mr,k);
            else modify(ls(now),l,mid,ml,mid,k),modify(rs(now),mid+1,r,mid+1,mr,k);
        }
        int query(int now,int l,int r,int ml,int mr)
        {
            if(!now) return 0;
            if(l==ml&&r==mr) return tr[now].x;
            int res=tr[now].lz*(mr-ml+1)%mod;
            if(mr<=mid) return (res+query(ls(now),l,mid,ml,mr))%mod;
            else if(ml>mid) return (res+query(rs(now),mid+1,r,ml,mr))%mod;
            else return (res+query(ls(now),l,mid,ml,mid)+query(rs(now),mid+1,r,mid+1,mr))%mod;
        }
    }seg;
    int main()
    {
        int mx=1e10+5,rt=0;
        while(m--)
        {
            int op=read();
            if(op==1)
            {
                int l=read()^(lst*tp),r=read()^(lst*tp),v=read()^(lst*tp);
                assert(l<=r);
                seg.modify(rt,1,mx,l,r,v);
            }
            else if(op==3)
            {
                int l=read()^(lst*tp),r=read()^(lst*tp);
                assert(l<=r);
                lst=seg.query(rt,1,mx,l,r); printf("%lld\n",lst);
            }
            else assert(false);
        }
        return 0;
    }
}
signed main()
{
    freopen("maze.in","r",stdin);
    freopen("maze.out","w",stdout);
    m=read(),tp=read();
    if(m<=2000&&tp==0) return sub1::main();
    else return sub5::main();
}
/*
9 0
1 9 14 3
3 2 12
2 12 5
3 2 12
3 9 10
2 6 5
3 2 12
1 5 6 4
3 2 12
*/