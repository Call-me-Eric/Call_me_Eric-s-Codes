#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+2;
int cnt,pri[maxn],ar[maxn];
bool vis[maxn];
int n,k;
void Euler(){
    for(int i=2;i<maxn;i++){
        if(!vis[i])pri[++cnt]=i;
        for(int j=1;j<=cnt&&i*pri[j]<maxn;j++){
            vis[i*pri[j]]=1;
            if(i%pri[j]==0)break;
        }
    }
    return ;
}
int bitcnt(int S){
    int ret=0;
    while(S)S-=(S&-S),ret++;
    return ret;
}
bool ok(int x,int len){
    for(int i=(x+len)%n;;i=(i+len)%n){
        if(!ar[i])return 0;
        if(i==x)break;
    }
    return 1;
}
void del(int len){
    for(int i=0;i<len;i++){
        if(ok(i,len)){
            for(int j=(i+len)%n;;j=(j+len)%n){
                ar[j]=0;
                if(j==i)break;
            }
        }
    }
}
bool check(int S){
    for(int i=0;i<n;i++)ar[i]=(S&(1<<i))?1:0;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            del(i);
            del(n/i);
        }
    }
    for(int i=0;i<n;i++)if(ar[i])return 0;
    return 1;
}
int main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    scanf("%d%d",&n,&k);
    if(k==n){for(int i=1;i<=n;i++)putchar('1');return 0;}
    if(k==1){for(int i=1;i<=n;i++)putchar('0');return 0;}
    Euler();
    if(!vis[n]){for(int i=1;i<=n;i++)putchar('0');return 0;}
    int ans=0;
    for(int S=1;S<(1<<n);S++){
        if(bitcnt(S)>k)continue;
        if(check(S)){
            if(bitcnt(S)>bitcnt(ans))ans=S;
        }
    }
    for(int i=0;i<n;i++)putchar((ans&(1<<i))?'1':'0');
    return 0;
}