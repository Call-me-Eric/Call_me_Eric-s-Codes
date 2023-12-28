#include<bits/stdc++.h>
using namespace std;
const int maxn = 10000010;
const int maxm = 3200;
unsigned k1,k2;
unsigned long long xorShift128Plus() {
    unsigned long long k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= k3 << 23;
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}
int n,m;
int a[maxn];
int sa[maxn];
int block,cnt;
int len[maxm];
int lid[maxm],rid[maxm];
int sm[maxm];
int lbest[maxm][maxm];
int rbest[maxm][maxm];
int lbig[maxm][maxm];
int rbig[maxm][maxm];
int dp[maxm][maxm];
int ldp[maxm][maxm];
int rdp[maxm][maxm];
int bl(int x){
    return (x-1)/block+1;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        sa[i]=a[i]+sa[i-1];
    }
   cin>>m>>k1>>k2;
    block=sqrt(n);
    for(int i=1;i<=n;i++){
        int bli=bl(i);
        cnt=bli;
        if(lid[bli]==0) lid[bli]=i;
        rid[bli]=i;
        sm[bli]+=a[i];
        len[bli]++;
    }
    for(int i=1;i<=cnt;i++){
        for(int j=lid[i];j<=rid[i];j++){
            int x=j-lid[i]+1;
            lbest[i][x]=a[j]+(lbest[i][x-1]>0?lbest[i][x-1]:0);
        }
        for(int j=lid[i];j<=rid[i];j++){
            int x=j-lid[i]+1;
            lbest[i][x]=max(lbest[i][x],lbest[i][x-1]);
        }
        for(int j=rid[i];j>=lid[i];j--){
            int x=j-lid[i]+1;
            rbest[i][x]=a[j]+(rbest[i][x+1]>0?rbest[i][x+1]:0);
        }
        for(int j=rid[i];j>=lid[i];j--){
            int x=j-lid[i]+1;
            rbest[i][x]=max(rbest[i][x],rbest[i][x+1]);
        }
        int tmp=0;
        for(int j=lid[i];j<=rid[i];j++){
            int x=j-lid[i]+1;
            tmp+=a[j];
            lbig[i][x]=max(tmp,lbig[i][x-1]);
        }
        tmp=0;
        for(int j=rid[i];j>=lid[i];j--){
            tmp+=a[j];
            int x=j-lid[i]+1;
            rbig[i][x]=max(tmp,rbig[i][x+1]);
        }
    }
    for(int i=1;i<=cnt;i++){
        dp[i][i]=lbest[i][len[i]];
    }
    for(int i=1;i<cnt;i++){
        dp[i][i+1]=max({dp[i][i],dp[i+1][i+1],rbig[i][1]+lbig[i+1][len[i+1]]});
    }
    for(int tlen=3;tlen<=cnt;tlen++){
        for(int i=1;i<=cnt;i++){
            int j=i+tlen-1;
            if(j>cnt) break;
            dp[i][j]=max({dp[i][j-1],dp[i+1][j],rbig[i][1]+lbig[j][len[j]]+sa[rid[j-1]]-sa[rid[i]]});
        }
    }
    for(int i=1;i<=cnt;i++){
        int mx=0,sum=0;
        for(int j=i;j<=cnt;j++){
            mx=max(mx,sum+lbig[j][len[j]]);
            ldp[i][j]=mx;
            sum+=sm[j];
        }
    }
    for(int i=cnt;i>=1;i--){
        int mx=0,sum=0;
        for(int j=i;j>=1;j--){
            mx=max(mx,sum+rbig[j][1]);
            rdp[j][i]=mx;
            sum+=sm[j];
        }
    }
    int ans=0;
   // scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int tl=xorShift128Plus()%n+1;
        int tr=xorShift128Plus()%n+1;
        if(tl>tr) swap(tl,tr);
        int tans=0;
        int btl=bl(tl);
        int btr=bl(tr);
        int xl=tl-lid[btl]+1;
        int xr=tr-lid[btr]+1;
        if(btl==btr){
            int now=0;
            for(int j=tl;j<=tr;j++){
                if(now<0) now=a[j];
                else now+=a[j];
                tans=max(tans,now);
            }
            ans^=tans;
        }
        else if(btl==btr-1){
            tans=max({rbest[btl][xl],lbest[btr][xr],rbig[btl][xl]+lbig[btr][xr]});
            ans^=tans;
        }
        else{
            tans=max(rbest[btl][xl],lbest[btr][xr]);
            tans=max(tans,dp[btl+1][btr-1]);
            tans=max(tans,rbig[btl][xl]+lbig[btr][xr]+sa[rid[btr-1]]-sa[rid[btl]]);
            tans=max(tans,rbig[btl][xl]+ldp[btl+1][btr-1]);
            tans=max(tans,rdp[btl+1][btr-1]+lbig[btr][xr]);
            ans^=tans;
        }
    }
    cout<<ans<<endl;
    return 0;
}