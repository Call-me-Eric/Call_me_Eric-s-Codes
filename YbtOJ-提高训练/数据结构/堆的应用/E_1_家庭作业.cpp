#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 2e5 + 10;
struct node{
    int a, b, d;
    node(int a = 0,int b = 0,int d = 0){
        this->a = a;
        this->b = b;
        this->d = d;
    }
}a[maxn];
bool operator < (node a,node b){
    return a.d < b.d;
}
signed main(){
    n = read();
    for(int i = 1;i <= n;i++)a[i] = node(read(),read(),read());
    return 0;
}