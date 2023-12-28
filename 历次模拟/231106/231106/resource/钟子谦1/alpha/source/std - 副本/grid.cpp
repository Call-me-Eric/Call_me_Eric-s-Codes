#include <bits/stdc++.h>
using namespace std;
#define SZ 2333333
int n,q,a[1005][1005];
const int MOD=998244353;
typedef pair<int,int> pii;
typedef long long ll;
#define fi first
#define se second
pii ix[SZ]; int inn=0;
int in[1005][1005];
int u[1005][1005],d[1005][1005],c[1005][1005];
/*
pair<int*,int> es[1000009*8]; int en=0;
void edt(int&x,int y) {
    if(x==y) return;
    es[++en]={&x,x}; x=y;
}*/
int qx[SZ],qy[SZ],qz[SZ];
vector<int> qq[1005][1005];
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
ll ans=0;
struct record {
ll a_;
record() {
    a_=ans;
}
~record() {
    ans=a_;
}
};
void workr(int l,int r) {
    for(int i=r;i>=l;--i) {
        int x=ix[i].fi,y=ix[i].se;
        in[x][y]=2;
        u[x][y]=c[x][y];
        for(int k=0;k<4;++k) {
            int xx=x+dx[k],yy=y+dy[k];
            if(!in[xx][yy]) continue;
            if(a[xx][yy]>a[x][y]) {
                (u[x][y]+=u[xx][yy])%=MOD;
            }
        }
        for(int k=0;k<4;++k) {
            int xx=x+dx[k],yy=y+dy[k];
            if(!in[xx][yy]) continue;
            if(a[xx][yy]<a[x][y]) {
                ans+=(ll)d[xx][yy]*u[x][y]; ans%=MOD;
            }
        }
        (ans+=u[x][y])%=MOD;
    }
}
void workl(int l,int r) {
    for(int i=l;i<=r;++i) {
        int x=ix[i].fi,y=ix[i].se;
        in[x][y]=1;
        d[x][y]=1;//c[x][y];
        for(int k=0;k<4;++k) {
            int xx=x+dx[k],yy=y+dy[k];
            if(!in[xx][yy]) continue;
            if(a[xx][yy]<a[x][y]) {
                (d[x][y]+=d[xx][yy])%=MOD;
            }
        }
        for(int k=0;k<4;++k) {
            int xx=x+dx[k],yy=y+dy[k];
            if(!in[xx][yy]) continue;
            if(a[xx][yy]>a[x][y]) {
                ans+=(ll)u[xx][yy]*d[x][y]; ans%=MOD;
            }
        }
        (ans+=d[x][y]*(ll)c[x][y])%=MOD;
    }
}
void getout(int l,int r) {
    for(int i=r;i>=l;--i) {
        int x=ix[i].fi,y=ix[i].se;
        in[x][y]=0; u[x][y]=d[x][y]=0;
    }
}
ll aans[SZ];
void fz(int l,int r) {
    if(l==r) {
        int x=ix[l].fi,y=ix[l].se;
        if(qq[x][y].empty()) return;
        for(auto q:qq[x][y]) {
            // ll totald=0,totalu=0;
            // for(int k=0;k<4;++k){
            //     int xx=x+dx[k],yy=y+dy[k];
            //     if(!in[xx][yy]) continue;
            //     totald+=d[xx][yy]; totald%=MOD;
            //     totalu+=u[xx][yy]; totalu%=MOD;
            // }
            // cout<<totale<<"?\n";
            aans[q]=((ans+n*n)%MOD+MOD)%MOD;
        }
        // cout<<x<<","<<y<<":"<<ans<<"\n";
        // for(int i=1;i<=n;++i)
        //     for(int j=1;j<=n;++j) {
        //         cout<<i<<","<<j<<":"<<u[i][j]<<","<<d[i][j]<<endl;
        //     }
        return;
    }
    int m=(l+r)>>1;
    {
    auto _=record();
    workr(m+1,r);
    fz(l,m);
    getout(m+1,r);
    }
    {
    auto _=record();
    workl(l,m);
    fz(m+1,r);
    getout(l,m);
    }
}
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
	FO(grid)
    scanf("%d",&n);
    set<int> sz;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            scanf("%d",&a[i][j]),sz.insert(a[i][j]);
    cerr<<sz.size()<<"?\n";
    inn=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j) ix[++inn]=pii(i,j);
    sort(ix+1,ix+1+inn,[&](pii p,pii q) {
        return a[p.fi][p.se]<a[q.fi][q.se];
    });
    for(int _=1;_<=inn;++_) {
        int i=ix[_].fi,j=ix[_].se;
        for(int k=0;k<4;++k) {
            int ii=i+dx[k],jj=j+dy[k];
            if(ii>=1&&ii<=n&&jj>=1&&jj<=n) c[i][j]++;
        }
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i) {
        scanf("%d%d",qx+i,qy+i);
        qq[qx[i]][qy[i]].push_back(i);
    }
    fz(1,inn);
    for(int i=1;i<=q;++i)
        printf("%lld\n",aans[i]);
}
