#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0'&& ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e4 + 10;
int n, a[maxn];
vector<pair<pair<int,int>,int> >opt;
signed main(){
int T = read();
while(T--){
    n = read(); opt.clear(); int sum = 0;
    for(int i = 1;i <= n;i++)sum += (a[i] = read());
    if(sum % n){puts("-1");continue;}
    for(int i = 2;i <= n;i++){
        if(a[i] % i){
            int x = i - a[i] % i;
            opt.push_back(make_pair(make_pair(1,i),x));
            a[i] += x;a[1] -= x;
        }
        int x = a[i] / i;a[1] += a[i];
        opt.push_back(make_pair(make_pair(i,1),x));
    }
    for(int i = 2;i <= n;i++)
        opt.push_back(make_pair(make_pair(1,i),sum / n));
    printf("%d\n",opt.size());
    for(auto i : opt)printf("%d %d %d\n",i.first.first,i.first.second,i.second);
}
    return 0;
}