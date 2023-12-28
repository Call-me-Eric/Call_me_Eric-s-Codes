#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, a[maxn];
int prime[maxn], tot;
bool book[maxn];
map<int,int> mp;
signed main(){
    for(int i = 2;i <= 1e5;i++){
        if(!book[i]){prime[++tot] = i;}
        for(int j = 1;j <= tot && i * prime[j] <= 1e5;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
int T = read();
while(T--){
    n = read();mp.clear();
    for(int i = 1;i <= n;i++){a[i] = read();}
    bool flag = false;
    for(int i = 1;i <= n && !flag;i++){
        int tmp = a[i];
        for(int j = 1;j <= tot && prime[j] <= tmp;j++){
            if(tmp % prime[j] == 0){
                if(mp[prime[j]] == 1){flag = true;break;}
                mp[prime[j]] = 1;
                while(tmp % prime[j] == 0)tmp /= prime[j];
            }
        }
        if(tmp != 1){
            if(mp[tmp]){flag = true;break;}
            mp[tmp] = 1;
        }
    }
    puts(flag ? "YES" : "NO");
}
    return 0;
}