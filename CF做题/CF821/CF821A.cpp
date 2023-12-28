#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 100;
int n;
int a[maxn][maxn];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            a[i][j] = read();
    for(int i = 1;i <= n;i++)
    for(int j = 1;j <= n;j++)
        if(a[i][j] != 1){
            bool check = false;
            for(int s = 1;s <= n && !check;s++)
            for(int t = 1;t <= n;t++){
                if(a[i][s] + a[t][j] == a[i][j]){
                    check = true;break;
                }
            }
            if(!check){puts("No");return 0;}
        }
    puts("YEs");
    return 0;
}