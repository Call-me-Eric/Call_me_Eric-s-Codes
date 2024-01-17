#include<bits/stdc++.h>
using namespace std;
int n,m,du[200010],s,fa[200010],sz[200010],cnt,flg[200010];
long long sm;
int findd(int x){if(!fa[x])return x;fa[x]=findd(fa[x]);return fa[x];}
bool hb(int x,int y){
    int fx=findd(x),fy=findd(y);if(fx==fy){flg[fy]=1;return false;}
    fa[fx]=fy;sz[fy]+=sz[fx];flg[fy]|=flg[fx];return true;
}
int main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)sz[i]=1;
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        du[x]++;du[y]++;if(du[x]>2||du[y]>2)s=1;
        if(du[x]>3||du[y]>3){puts("-1");return 0;}
        if(!hb(x,y)){s=1;cnt+=sz[findd(y)];}
    }
    if(!s){
        for(int i=1;i<=n;i++){
            if(fa[i])continue;
            sm+=1ll*sz[i]*(sz[i]+1)/2;
        }printf("0 %lld\n",sm);
    }
    else{
        for(int i=1;i<=n;i++){
            if(du[i]==3&&(sz[findd(i)]>4||flg[findd(i)])){puts("-1");return 0;}
            else if(du[i]==3)cnt+=3;
        }printf("1 %d\n",cnt);
    }return 0;
}