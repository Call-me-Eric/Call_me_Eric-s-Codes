//每次瞎删边，然后判断充要条件？
//县看看充要条件对不对。
#include<iostream>
#include<algorithm>
#include<vector>
#include<cassert>
#include<cstring>
using namespace std;
int n;
const int N=500;
struct unio{
int f[N];
int g(int x){
    if(x==f[x]) return x;
    return f[x]=g(f[x]);
}
bool merge(int x,int y){
    if(g(x)!=g(y)){
        f[g(x)]=g(y);
        return 1;
    }return 0;
}
void init(){
    for(int i=1;i<=n;i++) f[i]=i;
}
}u[4],us,cs[4],ut;
struct edg{
    int x,y,c,id;
}e[500*500],tmp[500*500],o[500*500];
int lw[10],mp[300],cw[11];
int r,g,b,m;
int ban[N];
bool chk(edg *e,int m,int r,int g,int b){
    memset(cw,0,sizeof(cw));
    memset(lw,0,sizeof(lw));
    for(int i=0;i<=3;i++) u[i].init();
    for(int i=1;i<=m;i++) {
        cw[e[i].c]+=u[e[i].c].merge(e[i].x,e[i].y);
    }
    for(int c=1;c<=3;c++){
        us.init();
        for(int i=1;i<=m;i++){
            if(e[i].c!=c)us.merge(e[i].x,e[i].y);
        }
        int parts=0;
        for(int i=1;i<=n;i++)if(us.f[i]==i&&ban[i]==0) parts++;
        lw[c]=parts-1;
    }
    if(cw[1]>=r&&cw[2]>=g&&cw[3]>=b)
        if(lw[1]<=r&&lw[2]<=g&&lw[3]<=b) {
            // cerr<<"WTF?? "<<lw[3]<<endl;
            return 1;
        }
    return 0;
}
int usd[500*500];
int main(){
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    mp['r']=1,mp['g']=2,mp['b']=3;
    cin>>r>>g>>b>>m;
    int LIM=m,R=r,G=g,B=b;
    n=r+g+b+1;
    int tot=0;
    for(int i=0;i<=3;i++) cs[i].init();
    for(int i=1;i<=m;i++){
        int x,y;string s;cin>>x>>y>>s;
        int id=mp[s[0]];
        if(cs[id].merge(x,y))
            e[++tot]=edg{x,y,id,i};
        o[i]=edg{x,y,id,i};
    // cerr<<tot<<" "<<id<<" "<<s[0]<<endl;
    }
    // cerr>>

    if(!chk(e,tot,r,g,b)) cout<<"NO\n",exit(0);
    int add=0;
    m=tot;
    while(add!=n-1){
        int num=0;
        bool fd=0;
        edg idd;
        for(int i=1;i<=m;i++){
            int cr=r,cg=g,cb=b,lim=0;
            if(e[i].c==1) cr--;
            else if(e[i].c==2) cg--;
            else cb--;
            ban[e[i].y]=1;
            for(int j=1;j<=m;j++){
                tmp[++lim]=e[j];
                if(tmp[lim].x==e[i].y) tmp[lim].x=e[i].x;
                if(tmp[lim].y==e[i].y) tmp[lim].y=e[i].x;
                if(tmp[lim].x==tmp[lim].y) lim--;
                // else{
                    // if(i==1) cerr<<j<<" "<<lim<<" "<<tmp[lim].x<<" "<<tmp[lim].y<<" "<<tmp[lim].c<<endl;
                // }
            }
            
            // cerr<<i<<" : ";for(int j=1;j<=lim;j++) cerr<<"("<<tmp[j].x<<","
            // <<tmp[j].y<<","<<tmp[j].c<<") ";cerr<<endl;
            if(chk(tmp,lim,cr,cg,cb)){
                usd[e[i].id]=1;
                // cerr<<"! "<<i<<endl;
        // for(int j=1;j<=m;j++) cerr<<e[j].x<<","<<e[j].y<<","<<e[j].c<<"  ";cerr<<endl;
                m=lim;fd=1;idd=e[i];
                // cerr<<"? "<<i<<endl;
                g=cg,r=cr,b=cb;
                for(int j=1;j<=m;j++) e[j]=tmp[j];
                break; 
            }
            ban[e[i].y]=0;
        }
        add++;
        // cerr<<"?? "<<add<<" ("<<idd.x<<" "<<idd.y<<" "<<idd.c<<") "<<" "<<r<<" "<<g<<" "<<b<<" "<<fd<<endl;
        // for(int j=1;j<=m;j++) cerr<<e[j].x<<","<<e[j].y<<","<<e[j].c<<"  ";cerr<<endl;
        assert(fd==1);
    }
    cout<<"Yes\n";
    static int cws[10];
    for(int i=1;i<=LIM;i++) cout<<usd[i];
    for(int i=1;i<=LIM;i++) cws[o[i].c]+=usd[i];
    assert(R==cws[1]);
    assert(G==cws[2]);
    assert(B==cws[3]);
    ut.init();
    for(int i=1;i<=LIM;i++) if(usd[i]) assert(ut.merge(o[i].x,o[i].y));
}