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
const int N=3e5+15;
int mod,T,LL[N],RR[N];
struct BIT
{
    int n; uint tr[N];
    void clear() {for(int i=0;i<=n;i++) tr[i]=0;}
    il void add(int x,uint k) {for(;x<=n;x+=x&(-x)) tr[x]+=k;}
    il uint query(int x) {uint res=0;for(;x;x-=x&(-x)) res+=tr[x];return res;}
    il uint ask(int l,int r) {return query(r)-query(l-1);}
}tr;
namespace baoli
{
    il void add(int &x,int y) {x+=y;if(x>=mod) x-=mod;}
    struct matrix
    {
        int f[2][2];
        matrix() {memset(f,0,sizeof(f));}
        void init() {f[0][0]=f[1][1]=1;}
        friend matrix operator *(const matrix &a,const matrix &b) 
        {
            matrix res;
            for(int i=0;i<2;i++) for(int k=0;k<2;k++)
                for(int j=0;j<2;j++) add(res.f[i][j],a.f[i][k]*b.f[k][j]%mod);
            return res;
        }
    }A,B;
    matrix qpow(matrix n,int k)
    {
        matrix res; res.init();
        for(;k;n=n*n,k>>=1) if(k&1) res=res*n;
        return res;
    }
    int sum[N],a[N],b[N];
    il uint solve(int L,int R)
    {
        matrix qwq=A*qpow(B,L-1); a[1]=qwq.f[0][0];
        for(int i=2;i<=R-L+1;i++) a[i]=(a[i-1]*1103515245%mod+1013904223)%mod;
        for(int i=0;i<=R-L+2;i++) sum[i]=0;
        for(int i=1;i<=R-L+1;i++) 
        {
            if(a[i]&1) sum[i]=1;
            else if(a[i]%4==0) sum[i]=-2;
            else sum[i]=0;
            sum[i]+=sum[i-1],b[i+1]=sum[i];
        }
        b[1]=0,sort(b+1,b+R-L+2+1);
        for(int i=0;i<=R-L+1;i++) sum[i]=lower_bound(b+1,b+R-L+2+1,sum[i])-b;
        tr.n=R-L+2,tr.clear(); tr.add(sum[0],1);
        uint res=0;
        for(int i=1;i<=R-L+1;i++) res+=tr.query(sum[i]-1),tr.add(sum[i],1);
        return res;
    }
    int main()
    {
        A.f[0][0]=134775813%mod,A.f[0][1]=1;
        B.f[0][0]=1103515245%mod,B.f[1][0]=1013904223%mod,B.f[1][1]=1;
        for(int i=1;i<=T;i++) printf("%u\n",solve(LL[i],RR[i]));
        return 0;
    }
}
namespace sub4
{
    int a[N],sum[N],b[N],len;
    struct node{int l,r,id;} q[N];
    il bool cmp(node x,node y)
    {
        if(x.l/len==y.l/len) return (x.l/len)&1?x.r<y.r:x.r>y.r;
        else return x.l<y.l;
    } 
    uint ans[N];
    int main()
    {
        int mx=3e5;
        a[1]=134775813%mod;
        for(int i=2;i<=mx;i++) a[i]=(a[i-1]*1103515245%mod+1013904223)%mod;
        for(int i=0;i<=mx+2;i++) sum[i]=0;
        for(int i=1;i<=mx;i++) 
        {
            if(a[i]&1) sum[i]=1;
            else if(a[i]%4==0) sum[i]=-2;
            else sum[i]=0;
            sum[i]+=sum[i-1],b[i+1]=sum[i];
        }
        b[1]=0,sort(b+1,b+mx+1+1);
        for(int i=0;i<=mx;i++) sum[i]=lower_bound(b+1,b+mx+1+1,sum[i])-b;
        // for(int i=0;i<=20;i++) cout<<i<<" "<<sum[i]<<endl;
        for(int i=1;i<=T;i++) q[i]={LL[i],RR[i],i};
        len=sqrt(mx);
        sort(q+1,q+T+1,cmp);
        int L=1,R=0; uint now=0; tr.n=mx+1;
        for(int i=1;i<=T;i++)
        {
            int l=q[i].l-1,r=q[i].r;
            while(R<r) 
            {
                R++,now+=tr.query(sum[R]-1),tr.add(sum[R],1);
            }
            while(L>l)
                L--,now+=tr.ask(sum[L]+1,mx+1),tr.add(sum[L],1);
            while(R>r)
                tr.add(sum[R],-1),now-=tr.query(sum[R]-1),R--;
            while(L<l)
                tr.add(sum[L],-1),now-=tr.ask(sum[L]+1,mx+1),L++;
            ans[q[i].id]=now;
        }
        for(int i=1;i<=T;i++) printf("%u\n",ans[i]);
        return 0;
    }
}
signed main()
{
    freopen("dark.in","r",stdin);
    freopen("dark.out","w",stdout);
    mod=read(),T=read();
    int mx=0;
    for(int i=1;i<=T;i++)
    {
        LL[i]=read(),RR[i]=read();
        mx=max(mx,RR[i]-LL[i]+1);
    }
    if(T<=2000&&mx<=2000) return baoli::main();
    else return sub4::main();
    return 0;
}
/*
200119 3
12 18
223 256
1428 2952
*/