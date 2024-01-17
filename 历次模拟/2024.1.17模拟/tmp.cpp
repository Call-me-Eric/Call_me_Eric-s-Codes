#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
bool stmemory;
bool book[maxn];
int prime[maxn], tot;
bool edmemory;
signed main(){
    cerr << (&edmemory - &stmemory) / 1024.0 / 1024.0 << "Mib cost." << endl;
    freopen("xor.in","w",stdout);srand(time(0));
    int n = 14;
    for(int i = 2;i <= n;i++){
        if(!book[i]){prime[++tot] = i;}
        for(int j = 1;j <= tot && prime[j] * i <= n;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    // printf("%d\n",tot);
    // for(int i = 1;i <= n;i++){if(!book[i])printf("%d\n",i);}
    printf("%d\n",n);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            int x = 6;
            printf("%d%c",(rand() % (1 << (x - 1))) * ((i > n / 2) ? (1 << (12 - x)) : (1))," \n"[j == n]);
        }
    }
    return 0;
}