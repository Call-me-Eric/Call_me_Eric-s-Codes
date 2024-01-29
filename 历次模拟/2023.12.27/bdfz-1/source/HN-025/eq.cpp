#include<bits/stdc++.h>
using namespace std;
const int N=705,P=2055,M=998244353;
using ll=long long;
int qp(ll a,int x=M-2){
    int res=1;for(;x;x>>=1,a=a*a%M)
        if(x&1)res=a*res%M;return res;
}
int n,m,d[N<<1][N],lt[N],ld[N];
vector<int>lk[P];
ll _c1,_c2;
struct dat{
    int a[N][N],p[N],m;
    void apd(int *c){
        int i,j;ll k;p[++m]=0;
        for(i=0;i<=n;++i)a[m][i]=c[i];
        for(i=1;i<m;++i)
            if(p[i]&&a[m][p[i]]){
                for(j=0,k=a[m][p[i]];j<=n;++j)
                    (a[m][j]-=k*a[i][j]%M)<0&&(a[m][j]+=M),++_c1;
            }
        for(i=1;i<=n;++i)
            if(a[m][i]){
                for(p[m]=i,k=qp(a[m][i]),i=0;i<=n;++i)
                    a[m][i]=k*a[m][i]%M;
                for(i=1;i<m;++i)
                    if(a[i][p[m]])
                        for(j=0,k=a[i][p[m]];j<=n;++j)
                            (a[i][j]-=k*a[m][j]%M)<0&&(a[i][j]+=M),++_c2;
                break;
            }
    }
    void Ret(){
        int i;
        for(i=1;i<=m;++i)
            if(!p[i]&&a[i][0]){puts("No");return;}
        for(i=1;i<=m;++i)
            if(!p[i]){puts("Many");return;}
        for(i=1;i<=n;++i)a[0][p[i]]=a[i][0];
        for(i=1;i<=n;++i)
            printf("%d%c",a[0][i]," \n"[i==n]);
    }
}st[35];
int tp;
#define ls x<<1
#define rs x<<1|1
void ins(int x,int l,int r,int L,int R,int p){
    if(L<=l&&r<=R)lk[x].push_back(p);
    else{
        int md=l+r>>1;
        if(L<=md)ins(ls,l,md,L,R,p);
        if(md<R)ins(rs,md+1,r,L,R,p);
    }
}
void sol(int x,int l,int r){
    for(int p:lk[x])st[tp].apd(d[p]);
    if(l==r)st[tp].Ret();
    else{
        int md=l+r>>1;
        st[tp+1]=st[tp],++tp;
        sol(ls,l,md);
        st[tp+1]=st[tp],++tp;
        sol(rs,md+1,r);
    }--tp;
}
int main(){
    ios::sync_with_stdio(false);
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    int i,j,k,l,r,x,y;
    cin>>n>>m;
    for(i=1;i<=n;++i){
        for(j=1;j<=n;++j)cin>>d[i][j];
        cin>>d[i][0],ld[i]=i;
    }
    for(i=1;i<=m;++i){
        cin>>x;
        for(j=1;j<=n;++j)cin>>d[n+i][j];
        cin>>d[n+i][0];
        ins(1,0,m,lt[x],i-1,ld[x]);
        ld[x]=n+i,lt[x]=i;
    }
    for(i=1;i<=n;++i)ins(1,0,m,lt[i],m,ld[i]);
    tp=1,sol(1,0,m);
    return 0;
}