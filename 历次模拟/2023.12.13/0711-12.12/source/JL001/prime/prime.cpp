#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
using namespace std;
const int mod=998244353;
#define int long long
int a[101000],b[101010];

void dec1(int *s,int l){
    s[l]--;
    for(int i=l;i>=1;i--){
        if(s[i]<0) s[i]+=10,s[i-1]--;
        else break;
    }
}
int pr[101];
/*
00 
*/
struct vec{
    int a[300];
};
struct mat{
    int a[300][300];
}imp[11],trs,pw[20];
mat operator+(const mat &a,const mat &b){
    mat c=a;
    for(int i=0;i<289;i++){
        for(int j=0;j<289;j++){
            (c.a[i][j]+=b.a[i][j])%=mod;
        }
    }return c;
}
mat operator*(const mat &a,const mat &b){
    mat c;memset(&c,0,sizeof(c));
    for(int k=0;k<289;k++){
        for(int i=0;i<289;i++){
            for(int j=0;j<289;j++){
                (c.a[i][j]+=a.a[i][k]*b.a[k][j])%=mod;
            }
        }
    }return c;
}
vec operator*(const vec &a,const mat &b){
    vec c;memset(&c,0,sizeof(c));
    for(int k=0;k<289;k++){
        for(int j=0;j<289;j++){
            (c.a[j]+=a.a[k]*b.a[k][j])%=mod;
        }
    }return c;
}
int id(int x,int y){
    if(x==-1&&y==-1) return 0;
    if(x==-1&&y==0) return 1;
    if(x==0&&y==-1) return 2;
    if(x==1&&y==-1) return 3;
    if(x==2&&y==-1) return 4;
    if(x==1&&y==0) return 5;
    if(x==0&&y==0) return 6;
    return 114514;
}
bool cp(int x){
    if(x==1||x==0)return 0;
    for(int i=2;i*i<=x;i++){
        if(x%i==0) return 0;
    }return 1;
}
int tr[1010][20];
int solve(int *s,int l){
    if(l==1&&s[1]==0) return 0;
    vec cur;
    memset(&cur,0,sizeof(cur));
    cur.a[1]=1;
    int ans=0;
    for(int i=1;i<=l;i++){
        mat T;memset(&T,0,sizeof(T));
        for(int c=0;c<s[i];c++){
            if(pr[c]) continue;
            T=T+imp[c];
        }
        vec tmp=cur;
        tmp=tmp*T;
        tmp=tmp*pw[l-i];
        for(int j=0;j<289;j++) ans+=tmp.a[j];
        ans%=mod;
        if(pr[s[i]]) break;
        cur=cur*imp[s[i]];
    }
    // int tot=0;
    // for(int i=1;i<=4242;i++){
    //     vec cur;
    //     memset(&cur,0,sizeof(cur));
    //     cur.a[1]=1;
    //     int a=i/1000,b=i/100%10,c=i/10%10,d=i%10;
    //     cur=cur*imp[a]*imp[b]*imp[c]*imp[d];
    //     // int cur=1;
    //     // cur=tr[cur][a];
    //     // cur=tr[cur][b];
    //     // cur=tr[cur][c];
    //     // cur=tr[cur][d];
    //     int s=0;
    //     for(int i=0;i<289;i++) s+=cur.a[i];
    //     if(s) tot++;
    // }
    // cerr<<tot<<endl;
    return ans-1;
}
char L[101010],R[101010];
void solve(){
    int len;
    cin>>(L+1);len=strlen(L+1);
    for(int i=1;i<=len;i++) a[i]=L[i]-'0';
    dec1(a,len);
    int ans=0;
    ans-=solve(a,len);
    cin>>(R+1);len=strlen(R+1);
    for(int i=1;i<=len;i++) a[i]=R[i]-'0';
    ans+=solve(a,len);
    cout<<(ans+mod)%mod<<"\n";
}
int ch[1010][20],w[1010],tot;
int ins(string s,int x){
    int u=0;
    for(int i=0;i<s.length();i++){
        if(!ch[u][s[i]-'0']) ch[u][s[i]-'0']=++tot;
        u=ch[u][s[i]-'0'];
    }
    w[u]=x;
    return u;
}
int PR[10101];
map<vector<int>,int>vis;
pair<int,vector<int>>TRS(vector<int>a,int p){
    int fl=0;
    for(int z:a){
        if(PR[w[z]*10+p]){
            return make_pair(0,a);
        }
        if(z==10) fl=1;
    }
    vector<int>add;
    if(fl==1){
        return make_pair(1,a);
    }
    for(int z:a){
        if(ch[z][p]) add.push_back(ch[z][p]);
    }
    for(int z:add) a.push_back(z);
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    return make_pair(1,a);
}
// vector<int>tr[1010];

int32_t main(){
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    pr[2]=pr[3]=pr[5]=pr[7]=1;
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    for(int i=1;i<=10000;i++) PR[i]=cp(i);
    ins("40",40);
    ins("44",44);
    ins("49",49);
    ins("99",99);
    ins("88",88);
    ins("81",81);
    cerr<<ins("1",1)<<endl;;
    ins("4",4);
    ins("6",6);
    ins("8",8);
    ins("900",900);
    queue<vector<int>>q;
    int tot=0;
    q.push(vector<int>{0});vis[vector<int>{0}]=++tot;
    // cerr<<"OK"<<endl;
    // for(int i=0;i<=9;i++) cerr<<ch[0][i]<<" ";cerr<<endl;
    while(!q.empty()){
        auto z=q.front();q.pop();
        // cerr<<"? : ";
        for(int i=0;i<=9;i++){
            if(!pr[i]){
                auto [w,u]=TRS(z,i);
                if(w==0) continue;
        // for(int x:u) cerr<<x<<" ";cerr<<endl;
                if(!vis.count(u)) vis[u]=++tot,q.push(u);
                tr[vis[z]][i]=(vis[u]);
            }
        }
    }
    cerr<<vis.size()<<" "<<tot<<endl;

    // exit(0);
    /*
    Remember
    */
    for(int i=1;i<=tot;i++){
        for(int j=0;j<=9;j++){
            if(tr[i][j])
                imp[j].a[i][tr[i][j]]=1;
        }
    }
    for(int j=0;j<=9;j++) trs=trs+imp[j];
    for(int i=0;i<289;i++){
        pw[0].a[i][i]=1;
    }
    for(int i=1;i<=18;i++) pw[i]=pw[i-1]*trs;
    int T;cin>>T;
    while(T--) solve();
}