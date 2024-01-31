#include<bits/stdc++.h>
using namespace std;
int a, ta, b, tb, x, y;
signed main(){
    scanf("%d%d",&a,&ta);
    scanf("%d%d",&b,&tb);
    scanf("%d:%d",&x,&y);
    int tmp = (x - 5) * 60 + y;
    int i = 0,cnt = 0;
    while(i < tmp + ta && i <= 18 * 60 + 59){
        if(i + tb > tmp)cnt++;i += b;
    }
    printf("%d\n",cnt);
    return 0;
}