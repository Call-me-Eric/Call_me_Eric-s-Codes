#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,q;
const int p=998244353;
int a[705][705],b[705][705];
inline int poww(int x,int y){
    int re=1;
    while(y>0){
        if((y&1)==1) re=1ll*re*x%p;
        x=1ll*x*x%p;
        y>>=1;
    }
    return re;
}
inline void xy(){
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n+1;++j){
            b[i][j]=a[i][j];
        }
    }
    int to=-1;
    for(int i=1;i<=n;++i){
        int sum=0,ver=i;
        for(int j=i;j<=n;++j){
            if(b[j][i]>sum){
                sum=b[j][i];
                ver=j;
            }
        }
        if(sum==0) continue;
        swap(b[i],b[ver]);
        sum=poww(b[i][i],p-2);
        for(int j=n+1;j>=i;--j){
            b[i][j]=1ll*b[i][j]*sum%p;
        }
        for(int j=1;j<=n;++j){
            if(i==j) continue;
            sum=b[j][i];
            for(int k=i;k<=n+1;++k){
                b[j][k]=(b[j][k]+p-1ll*sum*b[i][k]%p)%p;
            }
        } 
    }
    int fla=0;
    for(int i=1;i<=n;++i){
        if(b[i][i]==0){
            if(b[i][n+1]==0&&fla!=-1) fla=1;
            else fla=-1;
        }
    }
    if(fla==1) printf("Many\n");
    else if(fla==-1) printf("No\n");
    else{
        for(int i=1;i<=n;++i){
            printf("%d ",b[i][n+1]);
        }
        printf("\n");
    }
    return;
}
int main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n+1;++j){
            scanf("%d",&a[i][j]);
        }
    }
    xy();
    int x;
    for(int o=1;o<=q;++o){
        scanf("%d",&x);
        for(int i=1;i<=n+1;++i){
            scanf("%d",&a[x][i]);
        }
        xy();
    }
    return 0;
}
/*
*/
