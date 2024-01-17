#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int n, a[maxn], b[maxn];
signed main(){
    freopen("bet.in","r",stdin);
    freopen("bet.out","w",stdout);
    n = read(); for(int i = 1;i <= n;i++)b[i] = read();
    sort(b + 1,b + 1 + n);
    // for(int i = 1;i <= n;i++)cerr << "b[" << i << "] = " << b[i] << endl;
    int tot = 0;
    for(int i = 1;i <= n;i++){
        if(b[i] != b[i - 1]){a[++tot] = b[i];}
        else{b[i] = b[i - 1] = -1;tot--;}
    }
    // for(int i = 1;i <= tot;i++)cerr << "a[" << i << "] = " << a[i] << endl;
    int l = 1, pre = 0;
    for(int x = 1;x <= n;x++){
        while(a[l] < x + 1)pre ^= a[l++];
        int res = pre;
        for(int i = l;i <= tot;i++){res ^= (a[i] % (x + 1));}
        puts(res ? "First" : "Second");
    }
    return 0;
}