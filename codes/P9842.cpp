#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e6 + 10,lim = 1e6;
int n, a[maxn], k;
vector<int> vec[maxn];
signed main(){
    n = read(); k = read();
    for(int i = 1;i <= n;i++)vec[a[i] = read() + lim].push_back(i);
    return 0;
}