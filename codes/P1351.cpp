#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
const int N = 200000 + 10;
struct edge{
    int to,nexte;
}e[N * 2];
int head[N];
int n;
long long w[N];
int tot = 0;
long long maxw,sumw;
void add(int u,int v){
    tot++;
    e[tot].nexte = head[u];
    e[tot].to = v;
    head[u] = tot;
}
int main(){
    scanf("%d",&n);
    int u,v;
    for(int i = 1;i <= n;i++){
        head[i] = -1;
    }
    for(int i = 1;i < n;i++){
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    for(int i = 1;i <= n;i++)scanf("%lld",&w[i]);
    for(int i = 1;i <= n;i++){
        int k = head[i], t = e[i].to;
        long long sumv = 0,sumt = 0, maxv = -1,maxi = -1;
        while(k != -1){
            t = e[k].to;
            maxv = max(maxv ,w[t] * maxi);
            maxi = max(maxi,w[t]);
            sumv += w[t] * sumt % 10007;
            sumt += w[t];
            k = e[k].nexte;
        }
        sumw += sumv % 10007;
        maxw = max(maxw,maxv);
    }
    printf("%d %d",maxw,sumw * 2 % 10007);
    return 0;
}