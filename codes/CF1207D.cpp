#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f  = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch= getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10, mod = 998244353;
int n;
struct node{
    int first, second;
    node(int f = 0,int s = 0):first(f),second(s){}
}a[maxn];
int typ, pw[maxn];
bool cmp(node a,node b){
    if(typ == 1){return a.first < b.first;}
    if(typ == 2){return a.second < b.second;}
    if(typ == 3){return a.first != b.first ? a.first < b.first : a.second < b.second;}
}

int calc(int type){
    typ = type; sort(a + 1,a + 1 + n,cmp);
    int len = 1, times = 1;
    // printf("type = %lld\n",type);
    // for(int i = 1;i <= n;i++)printf("%lld %lld\n",a[i].first,a[i].second);
    for(int i = 1;i <= n && times != 0;i++){
        switch(type){
            case 1:{
                if(a[i].first == a[i - 1].first){len++;}
                else {times = times * pw[len] % mod;len = 1;}
                break;
            }
            case 2:{
                if(a[i].second == a[i - 1].second){len++;}
                else {times = times * pw[len] % mod;len = 1;}
                break;
            }
            case 3:{
                if(a[i].second < a[i - 1].second){times = 0;}
                if(a[i].first == a[i - 1].first && a[i].second == a[i - 1].second){len++;}
                else {times = times * pw[len] % mod;len = 1;}
                break;
            }
            default:break;
        }
    }
    return times * pw[len] % mod;
}

signed main(){
    n = read(); int u, v, ans = 1;pw[0] = 1;
    for(int i = 1;i <= n;i++){
        pw[i] = pw[i - 1] * i % mod;
        u = read(); v = read();
        a[i] = node(u, v);
    }
    int tmp = (pw[n] - calc(1) - calc(2) + calc(3) + mod) % mod;
    while(tmp < 0)tmp += mod;
    printf("%lld\n",tmp);
    return 0;
}