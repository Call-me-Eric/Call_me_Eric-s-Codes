#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch <'0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n, x;
vector<int> vec;bool book[1 << 18];
signed main(){
    n = read(); book[x = read()] = 1;
    for(int i = 1;i < (1 << n);i++){if(!book[i]){vec.push_back(i);book[i] = book[i ^ x] = 1;}}
    if(vec.empty()){puts("0");return 0;}
    for(int i = vec.size() - 1;i;i--){vec[i] ^= vec[i - 1];}
    printf("%d\n", vec.size());for(int i : vec)printf("%d ",i);
    return 0;
}