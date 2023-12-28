#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=  0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 110;
int n;
int a[maxn];
bool book[maxn];
signed main(){
    n = read();int cnt = 0;
    for(int i = 1;i <= n;i++){a[i] = read();}
    sort(a + 1,a + 1 + n);
    for(int i = 1;i <= n;i++){
        if(!book[i]){
            cnt++;
            for(int j = i;j <= n;j++){
                if(a[j] % a[i] == 0){
                    book[j] = 1;
                }
            }
        }
    }
    printf("%d\n",cnt);
    return 0;
}