#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1200;
int prime[maxn], tot;
bool book[maxn];
int n;
vector<int> vec;
signed main(){
    n = read();
    for(int i = 2;i <= n;i++){
        if(!book[i])prime[++tot] = i;
        for(int j = 1;j <= tot && prime[j] * i <= n;j++){
            book[prime[j] * i] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    for(int i = 1;i <= tot && prime[i] <= n;i++){
        int tmp = prime[i];
        while(tmp <= n){vec.push_back(tmp);tmp *= prime[i];}
    }
    printf("%d\n",vec.size());
    for(int i : vec)printf("%d ",i);
    puts("");
    return 0;
}