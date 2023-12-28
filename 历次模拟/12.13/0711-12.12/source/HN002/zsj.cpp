#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(random_device{}());
int n=250,m,xz[3],gl,fa[260];
int ljjz[260][260];
struct bbbb{
    int x,y,z,id;
}b[62510];
bool gz(bbbb x,bbbb y){return x.id<y.id;}
int findd(int x){if(!fa[x])return x;fa[x]=findd(fa[x]);return fa[x];}
bool hb(int x,int y){
    int fx=findd(x),fy=findd(y);
    if(fx==fy)return false;
    fa[fx]=fy;return true;
}
int main(){
    freopen("rgb.in","w",stdout);
    gl=rnd()%10;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++)ljjz[i][j]=-1;
    }
    for(int i=2;i<=n;i++){
        int f=(rnd()%(i-1))+1;ljjz[i][f]=rnd()%3;
        m++;b[m].x=i;b[m].y=f;b[m].z=ljjz[i][f];b[m].id=rnd();
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(rnd()%10<gl||ljjz[i][j]!=-1)continue;
            ljjz[i][j]=rnd()%3;m++;b[m].x=i;b[m].y=j;b[m].z=ljjz[i][j];b[m].id=rnd();
        }
    }
    sort(b+1,b+m+1,gz);
    for(int i=1;i<=m;i++){
        if(hb(b[i].x,b[i].y))xz[b[i].z]++;
    }
    for(int i=1;i<=m;i++)b[i].id=rnd();
    sort(b+1,b+m+1,gz);
    printf("%d %d %d %d\n",xz[0],xz[1],xz[2],m);
    for(int i=1;i<=m;i++){
        printf("%d %d ",b[i].x,b[i].y);
        if(b[i].z==0)puts("r");
        if(b[i].z==1)puts("g");
        if(b[i].z==2)puts("b");
    }return 0;
}