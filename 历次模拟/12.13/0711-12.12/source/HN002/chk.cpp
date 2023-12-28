#include<bits/stdc++.h>
using namespace std;
int xz[3],m,fa[260];
char s[62510],ss[10];
int findd(int x){if(!fa[x])return x;fa[x]=findd(fa[x]);return fa[x];}
bool hb(int x,int y){
    int fx=findd(x),fy=findd(y);
    if(fx==fy)return false;
    fa[fx]=fy;return true;
}
int main(){
    freopen("rgb.in","r",stdin);
    FILE *fp=fopen("rgb.out","r");
    scanf("%d%d%d%d",&xz[0],&xz[1],&xz[2],&m);
    fscanf(fp,"%s",s);if(s[0]=='N'){puts("NO");return 1;}
    fscanf(fp,"%s",s+1);
    for(int i=1;i<=m;i++){
        int x,y,z;scanf("%d%d",&x,&y);scanf("%s",ss);
        if(s[i]=='0')continue;
        if(!hb(x,y)){puts("WA");return 1;}
        if(ss[0]=='r')xz[0]--;
        if(ss[0]=='g')xz[1]--;
        if(ss[0]=='b')xz[2]--;
    }
    if(xz[0]!=0){printf("WA0 %d\n",xz[0]);return 1;}
    if(xz[1]!=0){printf("WA1 %d\n",xz[1]);return 1;}
    if(xz[2]!=0){printf("WA2 %d\n",xz[2]);return 1;}
    return 0;
}