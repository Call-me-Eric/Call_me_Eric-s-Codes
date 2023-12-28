#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int T, n, k;
const int maxn = 1e5 + 10;
int book[maxn];
signed main(){
    freopen("array.in","r",stdin);
    freopen("array.out","w",stdout);
    T = read();
    while(T--){
        n = read(); k = read();
        memset(book,0,sizeof(book));
        int l = 1, index = 1;
        while(!book[n]){
            int sum = 0, t = l;
            for(int i = l;i < l + k;i++){
                if(book[t]){i--;}
                else{book[t] = index;index++;sum += t;}
                t++;
            }
            book[sum] = index;index++;
            l = l + k;
            while(book[l])l++;
        }
        printf("%d\n",book[n]);
    }
    return 0;
}