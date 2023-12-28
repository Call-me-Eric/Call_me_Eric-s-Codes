#include <bits/stdc++.h>
using namespace std;
int t,l,r,jie[20];
vector<int> now;
bool vis[10000005];
void dfs(int st,int num,int _1,int _89,int _46,int _49){
    if(num)now.push_back(num);
    if(st==10)return;
    if(!_1&&!_46)dfs(st+1,num*10+1,1,_89,0,_49);
    if(!_1&&!_89&&_49<2)dfs(st+1,num*10+9,_1,_89,_46,_49);
    dfs(st+1,num*10+4,_1,_89,1,(_49?2:1));
    dfs(st+1,num*10+6,_1,_89,1,_49);
    dfs(st+1,num*10+8,_1,1,_46,(_49?2:0));
    if(num)dfs(st+1,num*10,_1,_89,_46,(_49?2:0));
}
bool qfs(int st,int x,int chs){
    if(!st){
        if(chs<2)return 1;
        if(chs<=1e7)return vis[chs];
        bool kt=0;
        for(int i=2;i*i<=chs;i++){
            if(chs%i==0){
                kt=1;
                break;
            }
        };
        return kt;
    }
    if(!qfs(st-1,x,chs*10+x/jie[st-1]%10))return 0;
    return qfs(st-1,x,chs);
}
bool chk(int x){
    int d=0,y=x;
    while(y)d++,y/=10;
    return qfs(d,x,0);
}
vector<int> nxt;
int pri[1000005];
void init(){
    int cnt=0;
    for(int i=2;i<=1e7;i++){
        if(!vis[i])pri[++cnt]=i;
        for(int j=1;pri[j]*i<=1e7;j++){
            vis[pri[j]*i]=1;
            if(i%pri[j]==0)break;
        }
    }
    dfs(1,0,0,0,0,0);jie[0]=1;
    for(int i=1;i<=12;i++)jie[i]=jie[i-1]*10;
    for(int u:now){
        if(chk(u))nxt.push_back(u);
    }
    sort(nxt.begin(),nxt.end());
}
signed main(){
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    cin>>t;init();
    while(t--){
        cin>>l>>r;
        r=upper_bound(nxt.begin(),nxt.end(),r)-nxt.begin()-1;
        l=lower_bound(nxt.begin(),nxt.end(),l)-nxt.begin();
        printf("%d\n",r-l+1);
    }
    return 0;
}