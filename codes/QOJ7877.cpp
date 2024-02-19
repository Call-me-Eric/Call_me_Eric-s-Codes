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
int readbase62(){
    int x = 0;char ch = getchar();
    while(!isdigit(ch) && !islower(ch) && !isupper(ch))ch = getchar();
    while(isdigit(ch) || islower(ch) || isupper(ch)){
        x = x * 62;
        if(isupper(ch)){x += ch - 'A' + 36;}
        if(islower(ch)){x += ch - 'a' + 10;}
        if(isdigit(ch)){x += ch - '0' +  0;}
        ch = getchar();
    }
    return x;
}
const int maxn = 2e6 + 10;
typedef unsigned long long ull;
int n, a[maxn];
ull hsh[2][maxn], pw[2][maxn], base[2] = {1145141ull,1919810ull};
ull gethash(int l,int r,int opt){return (hsh[opt][r] - hsh[opt][l - 1] * pw[opt][r - l + 1]);}
bool check(int l,int k){
    if(2 * k + 1 > l)return 0;
    return gethash(1,l - 2 * k,0) + gethash(2 * k + 1,l,0) == 2ull * gethash(k + 1,l - k,0)
        && gethash(1,l - 2 * k,1) + gethash(2 * k + 1,l,1) == 2ull * gethash(k + 1,l - k,1);
}
bool ans[maxn];
void main(){
    n = read();for(int i = 1;i <= n;i++)a[i] = readbase62();
    pw[0][0] = pw[1][0] = 1;
    for(int i = 1;i <= n;i++){
        pw[0][i] = pw[0][i - 1] * base[0];pw[1][i] = pw[1][i - 1] * base[1];
        hsh[0][i] = hsh[0][i - 1] * base[0] + 1ull * a[i];
        hsh[1][i] = hsh[1][i - 1] * base[1] + 1ull * a[i];
    }
    int i = 1;
    for(int k = 1;k * 2 + 1 <= n;k++){
        i = max(i,2 * k + 1);
        while(i <= n && check(i,k)){ans[i++] = '1';}
    }
    for(int i = 1;i <= n;i++)putchar('0' + ans[i]);
    putchar('\n');
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}