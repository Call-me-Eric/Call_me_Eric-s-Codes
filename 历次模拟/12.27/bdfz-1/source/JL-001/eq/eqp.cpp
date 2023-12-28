/*
    All tragedy erased,I see only wonders.
*/
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,l,r) for(int i=l;i<=r;i++)
int n,q;
const int mod=998244353;
#define int long long
int mat[1510][71];
int done[1500],id[1500];
int b[71][71],c[1510],pre[1510];
int cur[710],p[1510];
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%mod;
        a=a*a%mod;b>>=1;
    }return ret;
}
void ins(int *tmp){
    rep(i,0,n+1) cur[i]=tmp[i];
    // memcpy(cur,tmp,sizeof(cur));
    rep(i,1,n+1){
        if(!cur[i]) continue;
        if(!b[i][i]){
            // cerr<<"!!!!!?>"<<i<<endl;
            rep(j,0,n+1) b[i][j]=cur[j];
            // memcpy(b[i],cur,sizeof(cur));
            return ;
        }
        int inv=qpow(b[i][i],mod-2)*cur[i]%mod;
        rep(j,i,n+1) (cur[j]-=b[i][j]*inv)%=mod;
    }
}
void guass(){
    static int tik=0;tik++;
    memset(b,0,sizeof(b));
    rep(i,1,n)ins(mat[i]);
    if(b[n+1][n+1]){
        cout<<"No\n";return ;
    }
   
    // if(tik==664){
    //     cerr<<"==========\n";
    //     rep(i,1,n){
    //         rep(j,1,n+1) cerr<<b[i][j]<<" ";cerr<<endl;
    //     }cerr<<"=========\n";
    //     rep(i,1,n){
    //         rep(j,1,n+1) cerr<<mat[i][j]<<" ";cerr<<endl;
    //     }cerr<<"=========\n";
    // }
    rep(i,1,n){
        if(!b[i][i]) {
            cout<<"Many\n";return ;
        }
    }
    static int x[710],y[710];
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    rep(i,1,n) y[i]=b[i][n+1];
    for(int i=n;i>=1;i--){
        x[i]=y[i]*qpow(b[i][i],mod-2)%mod;
        rep(j,1,i){
            (y[j]-=x[i]*b[j][i])%=mod;
        }
    }
    rep(i,1,n) cout<<(x[i]%mod+mod)%mod<<" ";cout<<'\n';
}
int32_t main(){
    // freopen("eq.in","r",stdin);freopen("eq.out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cerr<<"DSONE"<<endl;
    cin>>n>>q;
    rep(i,1,n){
        rep(j,1,n+1) cin>>mat[i][j];
        id[i]=i;
    }
    rep(i,n+1,n+q){
        int z;cin>>z;p[i]=z;
        rep(j,1,n+1) cin>>mat[i][j];
    }
    guass();
    rep(u,n+1,n+q){
        // cerr<<"?? "<<u<<endl;
        // memcpy(mat[p[u]],mat[u],sizeof(mat[p[u]]));
        rep(i,0,n+1) mat[p[u]][i]=mat[u][i];
        if(u==n+664-1){
            // rep(i,1,2){
            //     rep(j,1,n+1) cerr<<mat[i][j]<<" ";cerr<<endl;
            // }
            // cout<<">";
        }
        guass();
        
    }
}