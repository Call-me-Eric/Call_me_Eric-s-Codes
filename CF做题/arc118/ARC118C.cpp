#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=  0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e4 + 10;
int n;
int prime[maxn], tot, a[maxn];
bool book[maxn];
signed main(){
    n = read();
    for(int i = 2;i < maxn;i++){
        if(!book[i])prime[++tot] = i;
        for(int j = 1;j <= tot && prime[j] * i < maxn;j++){
            book[prime[j] * i] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    memset(book,0,sizeof(book));
    int tmp = 1,pim = 1, point = 1;
    while(point < n){
        pim++;tmp *= prime[pim];
        int cnt = 2 * prime[pim], i = 0;
        while(cnt * (i + 1) <= 1e4 && point < n){
            i++;
            if(book[cnt * i])continue;
            book[cnt * i] = 1; 
            a[point++] = i * cnt;
        }
    }
    a[n] = tmp * (pim == 2 ? prime[pim + 1] : 1);
    a[n - 1] = (pim == 2 ? (prime[pim + 1] * 2) : a[n - 1]);
    for(int i = 1;i <= n;i++)printf("%d ",a[i]);
    return 0;
}