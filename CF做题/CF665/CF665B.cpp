#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 200;
int n, m, k;
vector<int> vec;
signed main(){
    n = read(); m = read(); k = read();
    for(int i = 1;i <= k;i++){vec.push_back(read());}
    int ans = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            int x = read(), t = 0;
            for(t = 0;t < vec.size();t++){if(vec[t] == x)break;}
            vec.erase(vec.begin() + t);
            vec.insert(vec.begin(),x);
            ans += t + 1;
        }
    }
    printf("%d\n",ans);
    return 0;
}