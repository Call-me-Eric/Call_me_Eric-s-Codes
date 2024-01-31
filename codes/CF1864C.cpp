#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
inline int lowbit(int x){return x & (-x);}
vector<int> opt;
signed main(){
int t = read();
while(t--){
    int n = read();opt.clear();
    while(n > 1){
        int x = lowbit(n);if(n - x < 1)break;
        opt.push_back(n); n = n - x;
    }
    if(n != 1){
        opt.push_back(n);
        for(int i = 30;i + 1;i--){
            if(n > (1 << i)){
                n -= (1 << i);
                opt.push_back(n);
            }
        }
    }

    printf("%d\n",opt.size());
    for(int i : opt)printf("%d ",i);
    puts("");
}
    return 0;
}