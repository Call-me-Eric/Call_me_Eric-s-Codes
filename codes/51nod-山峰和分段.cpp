#include<bits/stdc++.h>
using namespace std;
const int maxn = 50000 + 5;
int a[maxn];
int n;
int sum[maxn];
bool book[maxn];
int maxx = -114514;
int main(){
    int last = 0;
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
    }
    for(int i = 2;i < n;i++){
        if(i > 1 && i < n && a[i] > a[i - 1] && a[i] > a[i + 1]){
            book[i] = 1;
            if(i - last > maxx)maxx = i - last;
            last = i;
        }
        if(book[i] == 1)sum[i] = sum[i - 1] + 1;
        else sum[i] = sum[i - 1];
    }
    if(n - last > maxx)maxx = n - last;
    bool flag = 1;
    for(int i = maxx / 2;i <= maxx;i++){
        flag = 1;
        for(int j = 1;j <= n / i;j++){
            if(sum[i * j] - sum[i * (j - 1)] < 1){
                flag = 0;
                break;
            }
        }
        if(flag == 1){
            printf("%d\n",n / i);
            break;
        }
    }
    return 0;
}