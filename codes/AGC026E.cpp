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
const int maxn = 2e5 + 10;
string s, f[maxn];
int n;
int x[maxn], y[maxn], b[maxn];
void main(){
    cin >> n >> s;s = ' ' + s;int u = 0, v = 0;
    for(int i = 1;i <= n * 2;i++){
        if(s[i] == 'a'){u++;b[x[u] = i] = u;}
        else{v++;b[y[v] = i] = v;}
    }
    for(int i = n;i;i--){
        if(x[i] < y[i]){
            for(u = i + 1;u <= n;u++)
                if(min(x[u],y[u]) > y[i])break;
            f[i] = "ab" + f[u];
        }
        else{
            for(u = y[i];y[b[u]] < x[b[u]] && (b[u] <= i || y[b[u]] < x[b[u] - 1]);u++){
                if(b[u] >= i)f[i] += s[u];
            }
            f[i] += f[b[u]];
        }
        f[i] = max(f[i],f[i + 1]);
    }
    cout << f[1] << endl;;
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