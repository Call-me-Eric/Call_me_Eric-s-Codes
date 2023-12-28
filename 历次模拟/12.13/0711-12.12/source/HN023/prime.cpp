#include<bits/stdc++.h>
using namespace std;
int T;
int pre[100005];
int F[10];
bool vis[100005];
vector<int> prime;
void EulerPrime(int N){
    for(int i=2;i<=N;i++){
        if(!vis[i]){
            prime.push_back(i);
        }
        for(int j=0;j<prime.size();j++){
            int p=prime[j];
            if(i*p>N){
                break;
            }
            vis[i*p]=true;
            if(i%p==0){
                break;
            }
        }
    }
    return;
}
bool check(int x){
    for(int i=1;i<10;i++){
        F[i]=0;
    }
    int cnt=0;
    while(x){
        F[++cnt]=x%10;
        x/=10;
    }
    int st=1,ed=cnt;
    while(st<ed)swap(F[st++],F[ed--]);
    for(int i=1;i<(1<<cnt);i++){
        int tmp=0;
        for(int j=0;j<cnt;j++){
            if((i>>j)&1){
                tmp=tmp*10+F[j+1];
            }
        }
        if(!vis[tmp]){
            return false;
        }
    }
    return true;
}
int main(){
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    vis[0]=true;
    vis[1]=true;
    EulerPrime(100000);
    for(int i=1;i<=100000;i++){
        pre[i]=pre[i-1]+check(i);
    }
    scanf("%d",&T);
    while(T--){
        int lt,rt;
        scanf("%d%d",&lt,&rt);
        printf("%d\n",pre[rt]-pre[lt-1]);
    }
    return 0;
}
/*
*/