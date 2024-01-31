#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int a[maxn], b[maxn], n;
int atka,atkb;
priority_queue<int,vector<int>,less<int> > que;
void main(){
    n = read();atka = read(); atkb = read();
    for(int i = 1;i <= n;i++){
        int x = read();
        a[i] = ((x - 1) % atkb + 1 + atka - 1) / atka;
        b[i] = (x + atkb - 1) / atkb;
    }
    int s = 0;
    for(int i = 1;i <= n;i++){
        s += (b[i] - a[i] - 1); que.push(a[i] + 1);
        while(s < -1 && !que.empty()){s += que.top();que.pop();}
    }
    printf("%d\n",que.size());
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