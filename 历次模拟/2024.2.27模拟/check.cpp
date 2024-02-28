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
int check(){
    int sum = 0;
    for(int i = 0;i < n;i++){
        int tmp = 0;
        for(int j = 0;j < k;j++){
            tmp += c[(i + j) % n];
        }
        if(tmp & 1)sum++;
        else sum--;
    }
    return sum;
}
void main(){
    freopen("base.in","r",stdin);
    n = read(); k = read();
    freopen("base.out","r",stdin);
    ch = getchar();
    while(!isdigit(ch) && ch != '-')ch = getchar();
    if(ch == '-'){cerr << "No Answer!,n = " << n << ", k = " << k << "\n";exit(0);}
    int i = 0;
    while(isdigit(ch))c[i++] = ch - '0',ch = getchar();i--;
    if(i >= n){cerr << "Too many Values!\n";exit(1);}
    int x = check();
    if(x == 0){cerr << "Accepted!\n";}
    else{cerr << "Wrong Answer,sum = " << x << " \n";exit(1);}
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    return 0;
}