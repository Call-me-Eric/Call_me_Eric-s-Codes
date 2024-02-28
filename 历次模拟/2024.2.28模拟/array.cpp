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
const int maxn = 2e6 + 10;
int n, m, t;

int a[maxn], fa[maxn];
set<int> T,T1;
int cntpoint;

void MERGE(int k,vector<int> vec){
    if(k == 0 || k == 1)return;
    cntpoint++;int x = cntpoint, val = 0;
    
}
void GET(int u,int v){}
int QUERY(int u){}
void main(){
    cntpoint = n = read(); m = read(); t = read();
    int opt, k, u, v, lastans = 0;
    for(int i = 1;i <= n;i++)a[i] = 2,T.insert(i),fa[i] = i;
    for(int test = 1;test <= m;test++){
        char ch = getchar();while(!isupper(ch))ch = getchar();
        if(ch == 'M'){opt = 1;}if(ch == 'G'){opt = 2;}if(ch == 'Q'){opt = 3;}
        while(isupper(ch))ch = getchar();
        if(opt == 1){vector<int> vec;for(int i = read();i;i--)vec.push_back((read() - 1 + t * lastans) % n + 1);}
        if(opt == 2){u = (read() - 1 + t * lastans) % n + 1; v = read();}
        if(opt == 3){u = (read() - 1 + t * lastans) % n + 1;printf("%d\n",lastans = QUERY(u));}
    }
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