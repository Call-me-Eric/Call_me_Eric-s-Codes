#include<bits/stdc++.h>
#define ll long long
using namespace std;
int r,g,b,m,q;
int fa[255],siz[255];
struct qwq{
    int x,y;
    int id;
};
vector<qwq> tr,tg,tb;
bool fla;
bitset<65005> ans;
inline int getfa(int x){
    if(x==fa[x]) return x;
    return getfa(fa[x]);
}
inline void dfsb(int now,int be){
    if(now==0){
        fla=1;
        printf("YES\n");
        for(int i=1;i<=m;++i){
            printf("%d",(ans[i]==1));
        }
        return;
    }
    for(int i=be;i<tb.size();++i){
        int x=getfa(tb[i].x),y=getfa(tb[i].y);
        if(x==y) continue;
        if(siz[x]<siz[y]){
            ans[tb[i].id]=1;
            fa[x]=y;
            siz[y]+=siz[x];
            dfsb(now-1,i+1);
            fa[x]=x;
            siz[y]-=siz[x];
            ans[tb[i].id]=0;
        }
        else{
            ans[tb[i].id]=1;
            fa[y]=x;
            siz[x]+=siz[y];
            dfsb(now-1,i+1);
            siz[x]-=siz[y];
            fa[y]=x;
            ans[tb[i].id]=0;
        }
    }
    return;
}
inline void dfsg(int now,int be){
    if(now==0){
        dfsb(b,0);
        return;
    }
    for(int i=be;i<tg.size();++i){
        int x=getfa(tg[i].x),y=getfa(tg[i].y);
        if(x==y) continue;
        if(siz[x]<siz[y]){
            ans[tg[i].id]=1;
            fa[x]=y;
            siz[y]+=siz[x];
            dfsg(now-1,i+1);
            fa[x]=x;
            siz[y]-=siz[x];
            ans[tg[i].id]=0;
        }
        else{
            ans[tg[i].id]=1;
            fa[y]=x;
            siz[x]+=siz[y];
            dfsg(now-1,i+1);
            siz[x]-=siz[y];
            fa[y]=x;
            ans[tg[i].id]=0;
        }
    }
    return;
}
inline void dfsr(int now,int be){
    if(now==0){
        dfsg(g,0);
        return;
    }
    // printf("%d\n",now);
    // for(int i=1;i<=m;++i){
    //     printf("%d",(ans[i]==1));
    // }
    for(int i=be;i<tr.size();++i){
        int x=getfa(tr[i].x),y=getfa(tr[i].y);
        if(x==y) continue;
        if(siz[x]<siz[y]){
            ans[tr[i].id]=1;
            fa[x]=y;
            siz[y]+=siz[x];
            dfsr(now-1,i+1);
            fa[x]=x;
            siz[y]-=siz[x];
            ans[tr[i].id]=0;
        }
        else{
            ans[tr[i].id]=1;
            fa[y]=x;
            siz[x]+=siz[y];
            dfsr(now-1,i+1);
            siz[x]-=siz[y];
            fa[y]=x;
            ans[tr[i].id]=0;
        }
    }
    return;
}
int main(){
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    scanf("%d%d%d%d",&r,&g,&b,&m);
    qwq x;
    char opt;
    for(int i=1;i<=m;++i){
        scanf("%d%d %c",&x.x,&x.y,&opt);
        x.id=i;
        if(opt=='r') tr.push_back(x);
        if(opt=='g') tg.push_back(x);
        if(opt=='b') tb.push_back(x);
    }
    for(int i=1;i<=r+g+b+1;++i){
        fa[i]=i;
        siz[i]=1;
    }
    dfsr(r,0);
    if(fla==0){
        printf("NO");
    }
    return 0;
}

