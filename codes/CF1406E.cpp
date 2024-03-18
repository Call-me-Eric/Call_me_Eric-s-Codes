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
const int maxn = 1e5 + 10;
vector<int> prime;
bool book[maxn];
int n;
void main(){
    n = read();
    for(int i = 2;i <= n;i++){
        if(!book[i]){prime.push_back(i);}
        for(int j : prime){
            if(j * i > n)break;
            book[j * i] = 1;
            if(i % j == 0)break;
        }
    }
    int ans = 1;
    auto askA = [](int x){printf("A %d\n",x);fflush(stdout);return read();};
    auto askB = [](int x){printf("B %d\n",x);fflush(stdout);return read();};
    auto answer = [](int x){printf("C %d\n",x);fflush(stdout);return;};
    for(int i = 0;i < min((int)prime.size(),66);i++){
        askB(prime[i]);int u = 1, tmp = prime[i];
        while(askA(tmp)){tmp *= prime[i];if(tmp > n)break;}
        ans *= tmp / prime[i];
    }
    if(ans != 1){
        for(int i = 66;i < prime.size();i++){
            if(askA(prime[i]) != 1){answer(ans * prime[i]);return;}
        }
    }
    else{
        int tot = askA(1), cnt = 0;
        for(int i = 66;i < prime.size();i++){
            askB(prime[i]);cnt++;
            if(cnt == 100 || i == prime.size() - 1){
                int t = askA(1);
                if(t == tot - cnt){tot = t;cnt = 0;}
                else for(int j = i - cnt + 1;j <= i;j++){
                    if(askA(prime[j]) == 1){answer(ans * prime[j]);return;}
                }
            }
        }
    }
    answer(ans);
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