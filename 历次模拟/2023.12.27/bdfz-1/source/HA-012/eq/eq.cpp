#include<bits/stdc++.h>
#define ll long long
#define uit unsigned int
#define pa pair
#define fir first
#define sec second
#define mkp make_pair
using namespace std;
const int N=710,mod=998244353;
inline int pls(int x,int y){
    return (x+=y)>=mod?x-mod:x;
}
inline int sub(int x,int y){
    return (x-=y)<0?x+mod:x;
}
int ftp(int b,int p){
    int r=1;
    while(p){
        if(p&1) r=1ll*r*b%mod;
        b=1ll*b*b%mod;
        p>>=1;
    }
    return r;
}
int n,Q,A[N][N],B[N],CH[N][N];
namespace task1{
    int f[N][N],g[N],Id[N];
    void gauss(){
        for(int i=1;i<=n;i++){
            g[i]=B[i];
            for(int j=1;j<=n;j++){
                f[i][j]=A[i][j];
                //cout<<f[i][j]<<" ";
            }
            //cout<<endl;
        }
        for(int i=1;i<=n;i++) Id[i]=0;
        int line=1;
        for(int c=1;c<=n;c++){
            int now=line;
            for(int i=line+1;i<=n;i++){
                if(f[i][c]>f[now][c]) now=i;
            }
            if(f[now][c]==0) continue;
            Id[c]=line;
            for(int i=1;i<=n;i++) swap(f[line][i],f[now][i]);swap(g[line],g[now]);
            for(int i=line+1;i<=n;i++){
                int t=1ll*f[i][c]*ftp(f[line][c],mod-2)%mod;
                for(int j=1;j<=n;j++){
                    f[i][j]=sub(f[i][j],1ll*f[line][j]*t%mod);
                }
                g[i]=sub(g[i],1ll*g[line]*t%mod);
            }
            ++line;
        }
        for(int i=1;i<=n;i++) if(Id[i]==0) Id[i]=line,++line;
        for(int i=1;i<=n;i++){
            if(f[Id[i]][i]==0&&g[Id[i]]>0){
                printf("No\n");return ;
            }
        }
        for(int i=1;i<=n;i++){
            if(f[Id[i]][i]==0&&g[Id[i]]==0){
                printf("Many\n");return ;
            }
        }
        for(int i=n;i>=1;i--){
            for(int j=n;j>i;j--){
                int t=f[i][j];
                for(int k=1;k<=n;k++) f[i][k]=sub(f[i][k],1ll*f[j][k]*t%mod);
                g[i]=sub(g[i],1ll*g[j]*t%mod);
            }
            int t=ftp(f[i][i],mod-2);
            for(int j=1;j<=n;j++) f[i][j]=1ll*f[i][j]*t%mod;
            g[i]=1ll*g[i]*t%mod;
        }
        for(int i=1;i<=n;i++) printf("%d ",g[i]);printf("\n");
    }
    void sol(){
        gauss();
        for(int i=1;i<=Q;i++){
            for(int j=1;j<=n;j++) A[CH[i][0]][j]=CH[i][j];
            B[CH[i][0]]=CH[i][n+1];
            gauss();
        }
    }
}
namespace task2{
    namespace S{
        vector<int> mat[N];int Inv[N];
        vector<pa<pa<int,int>,vector<int> > > stk;
        vector<int> oo;
        int nonum=0;
        void clr(){
            for(int i=1;i<=n;i++) mat[i].resize(n+2,0);
        }
        void Ins(vector<int> arr){
        //cout<<arr.size()<<endl;
            bool flag=0;
            for(int i=1;i<=n;i++){
                if(!arr[i]) continue;
                //cout<<i<<' '<<mat[i][i]<<endl;
                if(!mat[i][i]){
                    stk.emplace_back(mkp(mkp(i,Inv[i]),mat[i]));
                    mat[i]=arr;
                    Inv[i]=ftp(mat[i][i],mod-2);
                    flag=1;
                    break;
                }
                int t=1ll*arr[i]*Inv[i]%mod;
                for(int j=1;j<=n+1;j++){
                    arr[j]=sub(arr[j],1ll*t*mat[i][j]%mod);
                }
            }
//            cout<<"----->"<<endl;
//            for(int i=1;i<=n;i++){
//                for(int j=1;j<=n+1;j++) cout<<mat[i][j]<<' ';cout<<Inv[i]<<'\n';
//            }
            if(!flag){
                stk.emplace_back(mkp(mkp(-1,nonum),mat[0]));
                if(arr[n+1]) ++nonum;
            }
        }
        void Del(const int lim){
            while((int)stk.size()>lim){
                if(stk.back().fir.fir==-1){
                    nonum=stk.back().fir.sec;
                }
                else{
                    mat[stk.back().fir.fir]=stk.back().sec;
                    Inv[stk.back().fir.fir]=stk.back().fir.sec;
                }

                stk.pop_back();
            }
        }
    }
    vector<vector<int> > vec[N<<2];
    vector<int> f[N];int Tim[N];
    int g[N][N];
    void GetAns(){
        if(S::nonum>0){
            printf("No\n");return ;
        }
        bool noflag=0,myflag=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n+1;j++) g[i][j]=S::mat[i][j];
            bool flag=0;
            for(int j=1;j<=n;j++){
                if(g[i][j]!=0){
                    flag=1;break;
                }
            }
            if(!flag){
                if(g[i][i]==0&&g[i][n+1]!=0) noflag=1;
                if(g[i][i]==0&&g[i][n+1]==0) myflag=1;
            }
        }
//        cout<<"-----"<<endl;
//        for(int i=1;i<=n;i++){
//            for(int j=1;j<=n+1;j++) cout<<g[i][j]<<' ';cout<<endl;
//        }
        if(noflag){
            printf("No\n");return ;
        }
        if(myflag){
            printf("Many\n");return;
        }
        for(int i=n;i>=1;i--){
            for(int j=i+1;j<=n;j++){
                g[i][n+1]=sub(g[i][n+1],1ll*g[i][j]*g[j][n+1]%mod);
            }
            g[i][n+1]=1ll*g[i][n+1]*ftp(g[i][i],mod-2)%mod;
        }
        for(int i=1;i<=n;i++) printf("%d ",g[i][n+1]);printf("\n");
    }
    void Ins(int p,int l,int r,int L,int R,vector<int> arr){
        if(l>=L&&r<=R){
            vec[p].emplace_back(arr);return ;
        }
        int mid=(l+r)>>1;
        if(L<=mid) Ins(p<<1,l,mid,L,R,arr);
        if(R>mid) Ins(p<<1|1,mid+1,r,L,R,arr);
    }
    void solve(int p,int l,int r){
        //cout<<p<<' '<<l<<' '<<r<<endl;
        int lsttop=(int)S::stk.size();
        //cout<<"now:"<<p<<' '<<l<<' '<<r<<'\n';
        for(auto u:vec[p]){
           // for(int i=1;i<=n+1;i++) cout<<u[i]<<' ';cout<<endl;
            S::Ins(u);
        }
        //cout<<"------------"<<endl;
        //cout<<p<<' '<<l<<' '<<r<<endl;
        if(l==r){
            GetAns();
        }
        else{
            int mid=(l+r)>>1;
            solve(p<<1,l,mid);solve(p<<1|1,mid+1,r);
        }
        S::Del(lsttop);
    }
    void Init(){
        S::clr();
        for(int i=1;i<=n;i++) f[i].resize(n+2,0);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) f[i][j]=A[i][j];f[i][n+1]=B[i];
            Tim[i]=0;
        }
        for(int i=1;i<=Q;i++){
            Ins(1,0,Q,Tim[CH[i][0]],i-1,f[CH[i][0]]);
            Tim[CH[i][0]]=i;
            for(int j=1;j<=n+1;j++) f[CH[i][0]][j]=CH[i][j];
        }
        for(int i=1;i<=n;i++){
            Ins(1,0,Q,Tim[i],Q,f[i]);
        }
    }
    void sol(){
        Init();
        solve(1,0,Q);
    }
}
int main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    scanf("%d%d",&n,&Q);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) scanf("%d",&A[i][j]);
        scanf("%d",&B[i]);
    }
    for(int i=1;i<=Q;i++){
        scanf("%d",&CH[i][0]);
        for(int j=1;j<=n+1;j++){
            scanf("%d",&CH[i][j]);
        }
    }
    if(n==1||Q<=2){
        task1::sol();return 0;
    }
    task2::sol();
    return 0;
}
