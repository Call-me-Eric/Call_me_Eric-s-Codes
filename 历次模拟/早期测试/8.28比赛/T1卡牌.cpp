#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, k, sumpoint, ans;
const int maxn = 100 + 10;
int v[maxn], t[maxn];
int pointlast[maxn], sumlast[maxn];
bool book[maxn];
void dfs2(int step,int restpoint, int sum,int time,int needpoint,int lastsum){
    if(restpoint == 0){
        ans = max(ans, lastsum + sum);
        return;
    }
    if(step > n)return;
    if(pointlast[step] < restpoint)return;
    if(sumlast[step] + sum + lastsum <= ans)return;
    if(t[step] <= restpoint && !book[step]){
        book[step] = 1;
        dfs2(step + 1,restpoint - t[step],sum + v[step], time, needpoint,lastsum);
        book[step] = 0;
        if(t[step] * 2 <= restpoint && time){
            book[step] = 1;
            dfs2(step + 1,restpoint - 2 * t[step], sum + v[step], time - 1, needpoint,lastsum);
            book[step] = 0;
        }
    }
    dfs2(step + 1,restpoint, sum, time, needpoint,lastsum);
    return;
}
void dfs1(int step, int restpoint, int sum,int time,int needpoint){
    if(restpoint == 0){
        dfs2(1,needpoint,0,time,needpoint,sum);
        return;
    }
    if(step > n)return;
    if(pointlast[step] < restpoint)return;
    if(t[step] <= restpoint && !book[step]){
        book[step] = 1;
        dfs1(step + 1,restpoint - t[step],sum + v[step], time, needpoint);
        book[step] = 0;
        if(t[step] * 2 <= restpoint && time){
            book[step] = 1;
            dfs1(step + 1,restpoint - 2 * t[step], sum + v[step], time - 1, needpoint);
            book[step] = 0;
        }
    }
    dfs1(step + 1,restpoint, sum, time, needpoint);
    return;
}
signed main(){
    n = read(); k = read();
    int minpoint = 40;
    for(int i = 1;i <= n;i++){
        v[i] = read(); t[i] = read();
        sumpoint += t[i];
        minpoint = min(t[i],minpoint);
    }
    for(int i = n;i >= 1;i--){
        pointlast[i] = pointlast[i + 1] + t[i] * 2;
        sumlast[i] = sumlast[i + 1] + max(v[i],0LL);
    }
    for(int i = minpoint;i <= sumpoint;i++){
        dfs1(1,i,0,k,i);
    }
    printf("%lld\n",ans);
    return 0;
}