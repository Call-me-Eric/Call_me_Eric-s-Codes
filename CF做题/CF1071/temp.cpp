#include<bits/stdc++.h>
using namespace std;
const int maxn =  1e6 + 10;
int prime[maxn], tot;
bool book[maxn];

signed main(){
    // for(int i = 2;i <= 1e6;i++){
    //     if(!book[i])prime[++tot] = i;
    //     for(int j = 1;j <= tot && i * prime[j] <= 1e6;j++){
    //         book[i * prime[j]] = 1;
    //         if(i % prime[j] == 0)break;
    //     }
    // }
    int cnt = 0;
    for(int i = 0,pi = 1;i <= 20;i++,pi *= 2)
    for(int j = 0,pj = 1;j <= 12 && pi * pj <= 1e6 && j <= i;j++,pj *= 3)
    for(int k = 0,pk = 1;k <= 8 && pi * pj * pk <= 1e6 && k <= j;k++,pk *= 5)
    for(int q = 0,pq = 1;q <= 4 && pi * pj * pk * pq<= 1e6 && q <= k;q++,pq *= 7)
    for(int w = 0,pw = 1;w <= 4 && pi * pj * pk * pq * pw<= 1e6 && w <= q;w++,pw *= 11)
    for(int e = 0,pe = 1;e <= 4 && pi * pj * pk * pq * pw * pe<= 1e6 && e <= w;e++,pe *= 13)
    for(int r = 0,pr = 1;r <= 4 && pi * pj * pk * pq * pw * pe * pr<= 1e6 && r <= e;r++,pr *= 17){
        cnt++;
        int x = 0;
        x = r * 1e7  + e * 1e6  + w * 1e5 + q * 1e4 + k * 1e3 + j * 1e2 + i;
        
    }
    return 0;
}