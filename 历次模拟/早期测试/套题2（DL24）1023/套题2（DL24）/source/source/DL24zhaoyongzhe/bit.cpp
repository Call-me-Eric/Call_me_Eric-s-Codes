#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, op;
const int maxn = 1e5 + 10;
int a[maxn];
signed main(){
    freopen("bit.in","r",stdin);
    freopen("bit.out","w",stdout);
    n = read(); op = read();
    for(int i = 1;i <= n;i++){
        a[i] = read();
    }
    int maxx = -1, cnt = 0;
    for(int i = 1;i <= n;i++){
        for(int j = i + 1;j <= n;j++){
            int sum = a[i];
            if(op == 1){
                sum = sum & a[j];
                if(sum > maxx){
                    cnt = 1;
                    maxx = sum;
                }
                else if(sum == maxx){
                    cnt++;
                }
            }
            else if(op == 2){
                sum = sum ^ a[j];
                if(sum > maxx){
                    cnt = 1;
                    maxx = sum;
                }
                else if(sum == maxx){
                    cnt++;
                }
            }
            else {
                sum = sum | a[j];
                if(sum > maxx){
                    cnt = 1;
                    maxx = sum;
                }
                else if(sum == maxx){
                    cnt++;
                }
            }
        }
    }
    printf("%d %d\n",maxx,cnt);
    return 0;
}