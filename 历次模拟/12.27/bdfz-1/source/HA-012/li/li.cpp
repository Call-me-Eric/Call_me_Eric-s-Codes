#include<bits/stdc++.h>
#define ll long long
#define uit unsigned int
using namespace std;
const int N=2e5+10;
int n,m,uni[N],U[N],V[N],edgenum[N],sz[N],d[N];bool vis[N];
int Get(int x){
    return x==uni[x]?x:(uni[x]=Get(uni[x]));
}
bool Merge(int x,int y){
    int fx=Get(x),fy=Get(y);
    if(fx==fy){
        ++edgenum[fx];
        return 0;
    }
    uni[fx]=fy;
    sz[fy]+=sz[fx];edgenum[fy]+=edgenum[fx]+1;
    return 1;
}
int main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        uni[i]=i;sz[i]=1;edgenum[i]=0;
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&U[i],&V[i]);
        ++d[U[i]];++d[V[i]];
        Merge(U[i],V[i]);
    }
    for(int i=1;i<=n;i++){
        if(d[i]>3){
            printf("-1\n");exit(0);
        }
        if(d[i]==3) vis[Get(i)]|=1;
    }
    ll ans1=0,ans2=0;
    for(int i=1;i<=n;i++){
        if(Get(i)==i&&edgenum[i]>sz[i]){
            printf("-1\n");exit(0);
        }
    }
    for(int i=1;i<=n;i++){
        if(Get(i)!=i) continue;
        if(vis[i]){
            if(sz[i]>4){
                printf("-1\n");exit(0);
            }
            edgenum[i]=sz[i];
        }
        if(sz[i]==edgenum[i]+1){
            if(ans1==0) ans2+=1ll*(1+sz[i])*sz[i]/2;
        }
        else{
            if(ans1==0) ans2=0,ans1=1;
            ans2+=sz[i];
        }
    }
    printf("%lld %lld\n",ans1,ans2);
    return 0;
}
