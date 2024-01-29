#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, a[maxn];
signed main(){
    n = read(); for(int i = 1;i <= n;i++)a[i] = read();
    sort(a + 1,a + 1 + n,greater<int>());
    for(int i = 1;i <= n;i++){
        if(i + 1 > a[i + 1]){
            int j = 0;for(j = 0;a[i + j + 1] == i;j++);
            if((a[i] - i) & 1 || (j & 1))puts("First");
            else puts("Second");
            break;
        }
    }
    return 0;
}