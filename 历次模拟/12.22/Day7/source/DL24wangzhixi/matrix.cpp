#include <bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
int n,Q;
struct matrix
{
    int N,M,c[maxn][maxn];
    matrix(){ memset(c,0x00,sizeof(c)); }
    matrix(int gn,int gm){ N=gn,M=gm,memset(c,0x00,sizeof(c)); }
};
struct Vector
{
    int N,M,c[maxn];
    Vector(){ memset(c,0x00,sizeof(c)); }
    Vector(int gn,int gm){ N=gn,M=gm,memset(c,0x00,sizeof(c)); }
    inline void print(){ for(int j=0;j<M;j++) cout<<c[j]; cout<<'\n'; }
};
inline matrix operator * (const matrix&A,const matrix&B)
{
    matrix res(A.N,B.M);
    for(int i=0;i<res.N;i++)
        for(int k=0;k<A.M;k++)
            for(int j=0;j<res.M;j++)
                res.c[i][j]^=(A.c[i][k]&B.c[k][j]);
    return res;
}
inline Vector operator * (const Vector&A,const matrix&B)
{
    Vector res(A.N,B.M);
    for(int k=0;k<A.M;k++)
        for(int j=0;j<res.M;j++)
            res.c[j]^=(A.c[k]&B.c[k][j]);
    return res;
}
matrix base[33],mat;
Vector ans,vec;
inline void solve()
{
    cin>>n,mat.N=mat.M=n,vec.N=1,vec.M=n;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) { char ch; cin>>ch; mat.c[j][i]=(ch=='1'); }
    for(int i=0;i<n;i++) { char ch; cin>>ch; vec.c[i]=(ch=='1'); }
    base[0]=mat; for(int i=1;i<31;i++) base[i]=base[i-1]*base[i-1];
    cin>>Q;
    for(int i=1,x;i<=Q;i++)
    {
        cin>>x;
        if(!x){ vec.print(); continue; }
        ans=vec;
        for(int j=0;j<=__lg(x);j++)
            if(x&(1<<j)) ans=ans*base[j];
        ans.print();
    }
}
signed main()
{
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(NULL);
    solve();
}
