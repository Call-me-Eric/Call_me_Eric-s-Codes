#include<bits/stdc++.h>
using namespace std;
int xz[3],n,m,fa[260],vis[62510];
char s[10];
struct bbbb{
    int x,y,zh,id;
}b[62510];
int findd(int x){if(!fa[x])return x;fa[x]=findd(fa[x]);return fa[x];}
bool hb(int x,int y){
    int fx=findd(x),fy=findd(y);
    if(fx==fy)return false;
    fa[fx]=fy;return true;
}
bool chk(int zy,int op){
    int cnt=0;for(int i=0;i<3;i++)if((zy>>i)&1)cnt+=xz[i];
    for(int i=1;i<=n;i++)fa[i]=0;
    for(int i=1;i<=m;i++){
        if(!((zy>>b[i].zh)&1))continue;
        if(op&&(!vis[b[i].id]))continue;
        if(hb(b[i].x,b[i].y)){cnt--;if(!op)vis[b[i].id]=1;}
    }if(cnt>0)return false;
    return true;
}
bool chkk(int op){
    for(int i=1;i<8;i++){
        if(!chk(i,op))return false;
    }return true;
}
int main(){
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    scanf("%d%d%d%d",&xz[0],&xz[1],&xz[2],&m);n=xz[0]+xz[1]+xz[2]+1;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&b[i].x,&b[i].y);b[i].id=i;
        scanf("%s",s);if(s[0]=='r')b[i].zh=0;else if(s[0]=='g')b[i].zh=1;else b[i].zh=2;
    }
    if(!chkk(0)){puts("NO");return 0;}
    int mm=0;
    for(int i=1;i<=m;i++){
        if(vis[b[i].id]){mm++;b[mm]=b[i];}
    }swap(m,mm);
    for(int i=1;i<=m;i++){
        vis[b[i].id]=0;
        if(!chkk(1))vis[b[i].id]=1;
    }puts("YES");
    for(int i=1;i<=mm;i++)printf("%d",vis[i]);
    return 0;
}