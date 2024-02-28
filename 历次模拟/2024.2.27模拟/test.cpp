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
const int maxn = 1e7 + 10;
bitset<maxn> c;
char ch;
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
void main(){
    srand(time(0));mt19937 rnd(rand());
    int test = 0;
    while(1){
        test++;cerr << "test " << test << ":";
        system("./datamaker");
        system("./base");
        if(system("./check"))getchar();
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