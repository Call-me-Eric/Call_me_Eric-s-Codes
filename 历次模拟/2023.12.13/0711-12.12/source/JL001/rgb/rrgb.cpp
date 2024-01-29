//每次瞎删边，然后判断充要条件？
//县看看充要条件对不对。
#include<iostream>
#include<algorithm>
#include<vector>
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
}u[4],us;
struct edg{
    int x,y,c;
}e[1010];

int lw[1010];

int mp[1010];
int r,g,b,m;
int cw[1010];
int main(){
    mp['r']=1,mp['g']=2,mp['b']=3;
    cin>>r>>g>>b>>m;
    n=r+g+b+1;
    for(int i=0;i<=3;i++) u[i].init();
    for(int i=1;i<=m;i++){
        int x,y;string s;cin>>x>>y>>s;
        int id=mp[s[0]];
        cw[id]+=u[id].merge(x,y);
        e[i]=edg{x,y,id};
    }
    for(int c=1;c<=3;c++){
        us.init();
        for(int i=1;i<=m;i++){
            if(e[i].c!=c){
                us.merge(e[i].x,e[i].y);
            }
        }
        int parts=0;
        for(int i=1;i<=n;i++){
            if(us.f[i]==i) parts++;
        }
        lw[c]=parts-1;
    }
    if(cw[1]>=r&&cw[2]>=g&&cw[3]>=b){
        // cerr<<"HONHONH"<<" "<<lw[1]<<endl;
        if(lw[1]<=r&&lw[2]<=g&&lw[3]<=b){

        cout<<"YES\n";exit(0);
        }
    }
    cout<<"NO\n";
    
}