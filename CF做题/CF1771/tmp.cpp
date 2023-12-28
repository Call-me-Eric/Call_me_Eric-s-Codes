#include<bits/stdc++.h>
using namespace std;
signed main(){
    freopen("test.in","w",stdout);
    printf("1\n2000\n");
    for(int i = 1;i <= 2000;i++)putchar('a');
    puts("");
    for(int i = 1;i < 2000;i++)printf("%d %d\n",i,i + 1);
    return 0;
}