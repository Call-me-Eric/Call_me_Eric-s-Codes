#include<bits/stdc++.h>
#define lowbit(x) (x) & (-(x))
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = (1 << 12) + 10;
int a[maxn],c[maxn * 4][maxn * 4];
void update(int x,int y,int k){
    for(int i = x;i <= n;i += lowbit(i)){
        for(int j = y;j <= n;j += lowbit(j)){
            c[i][j] += k;
        }
    }
}
int sum(int x,int y){
    int ans = 0;
    for(int i = x;i;i -= lowbit(i)){
        for(int j = y;j;j -= lowbit(j)){
            ans += c[i][j];
        }
    }
    return ans;
}
signed main(){
    n = read(); m = read();
    int op, x1, x2, y1, y2;
    for(int i = 1;i <= m;i++){
        op = read();
        if(op == 1){
            x1 = read(); y1 = read(); y2 = read();
            update(x1,y1,y2);
        }
        else{
            x1 = read();y1 = read();x2 = read();y2 = read();
            printf("%d\n",sum(x2,y2) - sum(x1,y2) - sum(x2,y1) + sum(x1,x2));
        }
    }
    return 0;
}
