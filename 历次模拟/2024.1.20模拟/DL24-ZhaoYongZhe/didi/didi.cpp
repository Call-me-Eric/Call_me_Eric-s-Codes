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
void write(int x){if(x % 10)write(x / 10);putchar((x / 10) ^ 48);}
const int maxn = 2e6 + 10;
bool book[maxn];
int st[maxn];
int n, k;
void printans(){
    for(int i = 1;i <= n;i++){
        write(st[i]);putchar(' ');
    }
    putchar('\n');
}
void dfs(int u,int step){
    if(step == n + 1){
        printans();
        exit(0);
    }
    if(u + k <= n && !book[u + k]){
        book[u + k] = 1;st[step] = u + k;
        dfs(u + k,step + 1);
        book[u + k] = 0;st[step] = 0;
    }
    if(u + k + 1 <= n && !book[u + k + 1]){
        book[u + k + 1] = 1;st[step] = u + k + 1;
        dfs(u + k + 1,step + 1);
        book[u + k + 1] = 0;st[step] = 0;
    }
    if(u - k - 1 >= 1 && !book[u - k - 1]){
        book[u - k - 1] = 1;st[step] = u - k - 1;
        dfs(u - k - 1,step + 1);
        book[u - k - 1] = 0;st[step] = 0;
    }
    if(u - k >= 1 && !book[u - k]){
        book[u - k] = 1;st[step] = u - k;
        dfs(u - k,step + 1);
        book[u - k] = 0;st[step] = 0;
    }
}
void main(){
    n = read(); k = read();
    if(k == 1){
        for(int i = 1;i <= n;i++)st[i] = i;
        printans();
        return;
    }
    for(int i = 1;i <= n;i++){
        st[1] = i;book[i] = 1;
        dfs(i,2);
        st[1] = 0;book[i] = 0;
    }
    puts("-1");
    return;
}
};
bool edmemory;
signed main(){
    freopen("didi.in","r",stdin);
    freopen("didi.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}