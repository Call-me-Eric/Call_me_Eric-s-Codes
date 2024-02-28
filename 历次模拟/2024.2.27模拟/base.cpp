#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n, k;
namespace BF{
const int maxn = 1e5 + 10;
int c[maxn];
bool check(){
    int sum = 0;
    for(int i = 0;i < n;i++){
        int tmp = 0;
        for(int j = 0;j < k;j++){
            tmp += c[(i + j) % n];
        }
        if(tmp & 1)sum++;
        else sum--;
    }
    return sum == 0;
}
int cnt;
void dfs(int u){
    if(u == n){
        if(check()){
            for(int i = 0;i < n;i++){
                putchar('0' + c[i]);
            }
            puts("");
            exit(0);
            cnt++;
        }
        return;
    }
    c[u] = 0;dfs(u + 1);
    c[u] = 1;dfs(u + 1);
}
};
namespace Subtaskn{
void solve(){
    int m = n / 2;
    int block = m / k;
    if(block * k == m){
        for(int i = 1;i <= m;i += k){
            for(int j = 0;j < k - 1;j++)putchar('0');
            putchar('1');
        }
        for(int i = m + 1;i <= n;i++)putchar('0');
        puts("");return;
    }
    int tmp = m - block * k;
    if((tmp & 1) == 0){
        tmp >>= 1;int cnt = 0;block++;
        for(int i = 1;i <= block;i++){
            for(int j = 0;j < k - 1;j++)putchar('0');
            putchar('1');cnt += k;
        }
        for(int i = 1;i < tmp;i++)putchar('0'),cnt++;putchar('1');cnt++;
        for(int i = cnt + 1;i <= n;i++)putchar('0');
        puts("");
    }
    else{
        block--;int res = m - block * k, cnt = 0;
        if(res & 1){puts("-30");return;}
        res >>= 1;block++;
        for(int i = 1;i <= block;i++){
            for(int j = 0;j < k - 1;j++)putchar('0');
            putchar('1');cnt += k;
        }
        for(int i = 1;i < res;i++)putchar('0'),cnt++;putchar('1');cnt++;
        for(int i = cnt + 1;i <= n;i++)putchar('0');
        puts("");
    }
}
};
void main(){
    n = read();k = read();
    if(k > n / 2)k = n - k;
    if(n & 1 || k == 0){puts("-30");return;}
    if(k == 1){
        for(int i = 1;i <= n / 2;i++)putchar('1');
        for(int i = n / 2 + 1;i <= n;i++)putchar('0');
        return;
    }
    if(n <= 20 && k <= 20){BF::dfs(0);puts("-30");return;}
    else Subtaskn::solve();
    return;
}
};
bool edmemory;
signed main(){
    freopen("base.in","r",stdin);
    freopen("base.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    // cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    // cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}