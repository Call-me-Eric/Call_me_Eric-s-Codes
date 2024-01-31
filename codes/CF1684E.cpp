#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, k;
int a[maxn];
int buc[maxn];
signed main(){
int T = read();
while(T--){
    n = read();int t = k = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    sort(a + 1,a + 1 + n);
    int rp = n, i = 1;
    a[n + 1] = 0x3f3f3f3f;a[0] = -1;
    for(i = 0;i <= rp && k > 0;i++){
        if(a[i + 1] - a[i] <= 1)continue;
        if(a[i + 1] - a[i] - 1 > k)break;
        while(a[i + 1] - a[i] > 1 && rp > i && k > 0){rp--;k--;a[i]++;}
        // if(a[i + 1] - a[i] > 1)break;
    }
    while(a[i + 1] - a[i] <= 1 && i <= n)i++;i++;
    // for(int i = 1;i <= n;i++){printf("a[%d]=%d ",i,a[i]);}
    // printf("\nrp = %d,i = %d\n",rp,i);

    int cnt = 1, l = i, mx = 0;
    if(i > rp){puts("0");continue;}
    memset(buc,0,sizeof(buc));
    for(int i = l;i <= n;i++){
        if(a[i] != a[i + 1]){buc[cnt]++;mx = max(mx,cnt);cnt = 1;}
        else{cnt++;}
    }
    i = 1;
    while(t && i <= mx){
        if(buc[i] <= t / i){t -= buc[i] * i;buc[i] = 0;}
        else{buc[i] -= t / i;t = 0;break;}
        i++;
    }
    cnt = 0;
    for(int i = 1;i <= mx;i++){cnt += buc[i];}
    printf("%d\n",cnt);
}
    return 0;
}