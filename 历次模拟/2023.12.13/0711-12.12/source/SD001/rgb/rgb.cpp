#include<bits/stdc++.h>
using namespace std;
const int N=255;
const int M=N*N/2;
const int inf=1000000000;
struct edge{
    int u,v,w,use,id;
    string op;
}e[N*3],tmp[M];
bool operator <(edge A,edge B) {return A.w<B.w;}
int R,G,B,m,cntr,cntg,cntb,n;
int fa[N],val[M],ans[M];
int get_fa(int x) {return (fa[x]==x)?x:fa[x]=get_fa(fa[x]);}
int merge(int x,int y){
    x=get_fa(x);y=get_fa(y);
    if(x==y) return 0;
    fa[x]=y;
    return 1;
}
void mst1(int mid) {
    for(int i=1;i<=m;++i) {
          if(e[i].op=="b") {
              e[i].w=val[i]+mid;
               }
               e[i].use=0;
          }
        for(int i=1;i<=n;++i) fa[i]=i;
        cntr=cntg=cntb=0;
        sort(e+1,e+1+m);
        for(int i=1;i<=m;++i) {
            if(merge(e[i].u,e[i].v)) {
                e[i].use=1;
                if(e[i].op=="r") {cntr++;}
                if(e[i].op=="g") {cntg++;}
                if(e[i].op=="b") {cntb++;}
            }
    }
    return ;
}
void mst2(int mid) {
    for(int i=1;i<=m;++i) {
        if(e[i].op=="g") {
            e[i].w=val[i]+mid;
        }
        if(e[i].op!="b") {//!!
            e[i].use=0;
        }
    }
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i) if(e[i].use) merge(e[i].u,e[i].v);
    cntr=cntg=0;
    sort(e+1,e+1+m);
    for(int i=1;i<=m;++i) {
        if(e[i].op=="b") continue;
        if(merge(e[i].u,e[i].v)) {
            e[i].use=1;
            if(e[i].op=="r") cntr++;
            if(e[i].op=="g") cntg++;
        }
    }
    return ;
}
int main() {
    srand(time(0));
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    ios::sync_with_stdio(false);
    int tot;
    cin>>R>>G>>B>>tot;
    m=0;
    n=R+G+B+1;
    /*for(int i=1;i<=m;++i) {
        cin>>e[i].u>>e[i].v;
        cin>>e[i].op;
        e[i].id=i;
    }*/
    for(int i=1;i<=tot;++i) {
        cin>>tmp[i].u>>tmp[i].v;
        cin>>tmp[i].op;
        tmp[i].id=i;
    }
    //r
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=tot;++i) {
        if(tmp[i].op=="r"&&merge(tmp[i].u,tmp[i].v)) {
            e[++m]=tmp[i];
        }
    }
    //g
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=tot;++i) {
        if(tmp[i].op=="g"&&merge(tmp[i].u,tmp[i].v)) {
            e[++m]=tmp[i];
        }
    }
    //b
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=tot;++i) {
        if(tmp[i].op=="b"&&merge(tmp[i].u,tmp[i].v)) {
            e[++m]=tmp[i];
        }
    }

    //wqs+random
    int times=300;
    while(times--) {
        for(int i=1;i<=m;++i) e[i].w=val[i]=rand();
        int l=-inf,r=inf;
        while(l<r) {

            int mid=(1ll*l+r+inf+inf)/2-inf;//!
            mst1(mid);
            if(cntb<=B) r=mid;
            else l=mid+1;
        }
        mst1(l);
        if(cntb!=B) continue;
        l=-inf;r=inf;
        while(l<r) {
            int mid=(1ll*l+r+inf+inf)/2-inf;
            mst2(mid);
            if(cntg<=G) r=mid;
            else l=mid+1;
        }
        mst2(l);
        if(cntg==G) {
            cout<<"YES\n";
            for(int i=1;i<=m;++i) //cout<<e[i].use;
            ans[e[i].id]=e[i].use;
            for(int i=1;i<=tot;++i) cout<<ans[i];
            return 0;
        }
    }
    cout<<"NO";
    return 0;
}