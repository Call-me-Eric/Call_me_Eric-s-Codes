#include "bits/stdc++.h"
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define Fin(file) freopen(file,"r",stdin)
#define Fout(file) freopen(file,"w",stdout)
#define assume(expr) ((!!(expr))||(exit((fprintf(stderr,"Assumption Failed: %s on Line %d\n",#expr,__LINE__),-1)),false))
using namespace std; using ull = unsigned long long;
const int N=6e5+5; typedef long long ll; const ull P=47,A[2]={13,23};
char s[N]; int n,nxt[N],pos[N*2],ch[N][2],fa[N][21],tot,pp[N],val[N]; ull hsh[N][21],pw[N]; 
int get(int u,int c){
    if(!ch[u][c]){
        ch[u][c]=++tot; fa[tot][0]=u; hsh[tot][0]=A[c]; val[tot]=c;
        For(i,1,20) fa[tot][i]=fa[fa[tot][i-1]][i-1],hsh[tot][i]=hsh[tot][i-1]*pw[i-1]+hsh[fa[tot][i-1]][i-1];
    }
    return ch[u][c];
}
bool comp(int x,int y){
    Rev(i,20,0){
        if(hsh[x][i]==hsh[y][i]) x=fa[x][i],y=fa[y][i];
    }
    return val[x]<val[y];
}
string get(int u){
    string res; while(u>1) res.push_back(val[u]+'('),u=fa[u][0];
    return res;
}
signed main(){
	Fin("kacbret.in");
	Fout("kacbret.out");
    cin>>(s+1); n=strlen(s+1);
    pw[0]=P; For(i,1,20) pw[i]=pw[i-1]*pw[i-1];
    memset(pos,-1,sizeof(pos)); pos[0+N]=n+1;
    for(int i=n,t=0;i>=1;i--){
        s[i]==')'?t++:t--;
        if(s[i]=='(') nxt[i]=pos[t+N]; else nxt[i]=-1;
        pos[t+N]=i;
    }
    pp[n+1]=++tot; val[tot]=-1;
    Rev(i,n,1){
        int c=s[i]-'(';
        if(nxt[i]==-1){
            pp[i]=get(pp[i+1],c);
        }
        else{
            int x=get(pp[i+1],c),y=pp[nxt[i]];
            pp[i]=comp(x,y)?x:y;
        }
    }
    cout<<get(pp[1])<<'\n';
    cerr<<"Time = "<<clock()<<" ms"<<endl;
    return 0;
}