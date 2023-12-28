#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

const int maxn=705;
const int mdn=998244353;

int n,q;
int a[maxn*2][maxn];
int id[maxn],st[maxn*2],et[maxn*2];

int x[maxn][maxn],ts[maxn];
int ans[maxn];

int qpw(int bse,int ex=mdn-2){
    int ret=1;
    for(;ex;ex>>=1){
        if(ex&1)ret=ret*(unsigned long long)bse%mdn;
        bse=bse*(unsigned long long)bse%mdn;
    }
    return ret;
}
int main(){
    #ifndef dengyaotriangle
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    #endif
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)cin>>a[i][j];
    for(int i=1;i<=n;i++)id[i]=i,st[i]=0;
    for(int i=1;i<=n+q;i++)et[i]=q;
    for(int i=1;i<=q;i++){
        int z;cin>>z;
        et[id[z]]=i-1;
        int cur=n+i;
        id[z]=cur;st[cur]=i;
        for(int i=1;i<=n+1;i++)cin>>a[cur][i];
    }
    ts[n+1]=-1;
    for(int i=0;i<=q;i++){
        for(int j=1;j<=n;j++)if(x[j][j]&&ts[j]<i){
            fill(x[j]+j,x[j]+n+2,0);
        }
        for(int j=1;j<=n+q;j++)if(st[j]==i){
            //cerr<<i<<' '<<j<<' '<<et[j]<<endl;
            bool ok=0;
            for(int k=1;k<=n;k++){
                if(a[j][k]){
                    int inv=qpw(a[j][k]);
                    for(int l=k;l<=n+1;l++)a[j][l]=a[j][l]*(unsigned long long)inv%mdn;
                    if(!x[k][k]){
                        copy(a[j]+k,a[j]+n+2,x[k]+k);
                        ts[k]=et[j];
                        ok=1;
                        break;
                    }else{
                        if(ts[k]<et[j])swap_ranges(a[j]+k,a[j]+n+2,x[k]+k),swap(ts[k],et[j]);
                        for(int l=k;l<=n+1;l++){
                            a[j][l]-=x[k][l];
                            a[j][l]+=(a[j][l]<0?mdn:0);
                        }
                    }
                }
            }
            if(!ok){
                if(a[j][n+1])ts[n+1]=max(ts[n+1],et[j]);
            }
        }
        if(ts[n+1]>=i){
            cout<<"No\n";
        }else{
            bool ok=1;
            for(int i=1;i<=n;i++)if(x[i][i]==0)ok=0;
            if(!ok){
                cout<<"Many\n";
            }else{
                for(int i=n;i>=1;i--){
                    ans[i]=x[i][n+1];
                    for(int j=i+1;j<=n;j++){
                        ans[i]=(ans[i]+(mdn-x[i][j])*(long long)ans[j])%mdn;
                    }
                }
                for(int i=1;i<=n;i++)cout<<ans[i]<<" \n"[i==n];
            }
        }
    }
    return 0;
}