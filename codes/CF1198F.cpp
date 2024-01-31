#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) +  (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n;
bool book[maxn];
struct node{
    int val, id;
    node(int val = 0,int id = 0):val(val),id(id){}
}a[maxn];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){a[i] = node(read(),i);}
for(long long st = clock();clock() - st < CLOCKS_PER_SEC * 0.45;){
    random_shuffle(a + 1,a + 1 + n);
    memset(book,0,sizeof(book));
    int g1 = a[1].val, g2 = 0;book[a[1].id] = 1;
    for(int i = 2;i <= n;i++){
        if(__gcd(g1,a[i].val) < g1){
            book[a[i].id] = 1;
            g1 = __gcd(g1,a[i].val);
        }
        else g2 = __gcd(g2,a[i].val);
    }
    if(g1 == 1 && g2 == 1){
        puts("YES");
        for(int i = 1;i <= n;i++)
            putchar('1' + book[i]),putchar(' ');
        puts("");return 0;
    }
}
    puts("NO");
    return 0;
}