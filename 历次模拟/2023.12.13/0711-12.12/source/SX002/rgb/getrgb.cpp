#include<bits/stdc++.h>
#define ll long long
using namespace std;
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

