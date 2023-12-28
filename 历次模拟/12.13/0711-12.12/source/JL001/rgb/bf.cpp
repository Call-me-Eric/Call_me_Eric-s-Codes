//每次瞎删边，然后判断充要条件？
//县看看充要条件对不对。
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n;
const int N=500;
struct edge{
    int x,y,c;
}e[1010];
int mp[1010];
int r,g,b,m;
int cw[10];
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
}u;
int main(){
    mp['r']=1,mp['g']=2,mp['b']=3;
    cin>>r>>g>>b>>m;
    n=r+g+b+1;
    for(int i=1;i<=m;i++){
        int x,y;string s;cin>>x>>y>>s;
        int id=mp[s[0]];
        e[i]=edge{x,y,id};
    }
    for(int s=0;s<(1<<m);s++){
        if(__builtin_popcount(s)!=n-1) continue;
        u.init();
        bool fl=0;
        memset(cw,0,sizeof(cw));
        for(int i=0;i<m;i++){
            if((s>>i)&1) {
                cw[e[i+1].c]++;
                // if(s==19)
                // cerr<<"?? "<<e[i+1].x<<" "<<e[i+1].y<<endl;
                if(u.merge(e[i+1].x,e[i+1].y)!=1) {fl=1;break;}
            }
        }
        if(fl) continue;
        if(cw[1]>=r&&cw[2]>=g&&cw[3]>=b){
            // cerr<<"? "<<s<<endl;
            cout<<"YES\n";exit(0);
        }
    }
    cout<<"NO\n";
}