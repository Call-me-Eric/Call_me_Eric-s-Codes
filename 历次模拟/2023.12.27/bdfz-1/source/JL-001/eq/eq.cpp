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
int mat[1510][710];
int done[1500],id[1500];
int b[710][710],c[1510],pre[1510];
int cur[710],p[1510];
int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%mod;
        a=a*a%mod;b>>=1;
    }return ret;
}
void ins(int p){
    memcpy(cur,mat[p],sizeof(cur));
    rep(i,1,n+1){
        if(!cur[i]) continue;
        if(!b[i][i]){
            c[i]=p;
            // rep(j,i,n+1) b[i][j]=cur[j];
            memcpy(b[i],cur,sizeof(cur));
            return ;
        }
        if(done[p]>done[c[i]]){
            swap(p,c[i]);
            rep(j,i,n+1) swap(cur[j],b[i][j]);
        }
        int inv=qpow(b[i][i],mod-2)*cur[i]%mod;
        rep(j,i,n+1) (cur[j]-=b[i][j]*inv)%=mod;
    }
}
int32_t main(){
    freopen("eq.in","r",stdin);freopen("eq.out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n>>q;
    rep(i,1,n){
        rep(j,1,n+1) cin>>mat[i][j];
        id[i]=i;
    }
    rep(i,n+1,n+q){
        int z;cin>>z;p[i]=z;
        rep(j,1,n+1) cin>>mat[i][j];
        done[id[z]]=i-1;pre[i]=id[z];
        id[z]=i;
    }
    rep(i,1,n+q) if(!done[i]) done[i]=n+q;
    // cerr<<"??? "<<pre[n+1]<<endl;
    rep(u,1,n+q){
        if(u>n){
            rep(i,1,n+1){
                if(c[i]==pre[u]){
                    c[i]=0;memset(b[i],0,sizeof(b[i]));
                    break;
                }
            }
        }
        ins(u);
        static int x[710],y[710];
        if(u>=n){
            // if(u==n+664-1||u==n+663-1){
            //     cerr<<">> "<<u<<" "<<pre[u]<<" "<<pre[u-1]<<" "<<p[u]<<endl;
            //     rep(i,1,2){
            //         cerr<<c[i]<<" : ";
            //         rep(j,1,3) cerr<<b[i][j]<<" ";cerr<<endl;
            //     }
            //     cerr<<"===========\n";
            // }
            memset(x,0,sizeof(x));
            if(b[n+1][n+1]){
                cout<<"No\n";
                continue;
            }
            int fl=0;
            rep(i,1,n) if(!c[i]) {fl=1;break;}
            if(fl){
                cout<<"Many\n";
                continue;
            }
            rep(i,1,n) y[i]=b[i][n+1];
            for(int i=n;i>=1;i--){
                x[i]=y[i]*qpow(b[i][i],mod-2)%mod;
                rep(j,1,i){
                    (y[j]-=x[i]*b[j][i])%=mod;
                }
            }
            rep(i,1,n) cout<<(x[i]%mod+mod)%mod<<" ";
            cout<<"\n";
        }
        // if(u==n+1){

        //     // rep(i,1,n+1){
        //     //     cout<<c[i]<<":";
        //     //     rep(j,1,n+1)cout<<b[i][j]<<" ";cout<<endl;
        //     // }cout<<"============\n";
        //     // rep(i,1,n) cout<<y[i]<<" ";cout<<endl;
        //     // rep(i,1,n+1){
        //     //     int res=0;
        //     //     rep(j,1,n) (res+=b[i][j]*x[j])%=mod; 
        //     //     cerr<<(res+mod)%mod<<" "<<(b[i][n+1]+mod)%mod<<endl;
        //     // }
        //     // return 0;
        // }
    }
}