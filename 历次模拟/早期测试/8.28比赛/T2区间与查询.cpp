#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1e7 + 10;
int n, m, a[maxn], head[maxn], tot[maxn], nextt[maxn];
signed main(){
    int l, r, k;
    n = read(); m = read();
    for(int i = 1;i <= n;i++){
        k = read();
        tot[k]++;
        if(!head[k]){
            a[k] = i;
            head[k] = i;
        }
        else{
            nextt[a[k]] = i;
            a[k] = i;
        }
    }
    for(int i = 1;i <= m;i++){
        l = read(); r = read(); k = read();
        if(l == 1 && r == n){
            printf("%d\n",tot[k]);
        }
        else{
            int cnt = 0;
            for(int j = head[k];j <= r;j = nextt[j]){
                cnt += (j >= l && j <= r);if(nextt[j] == 0)break;
            }
            printf("%d\n",cnt);
        }
    }
    return 0;
}