#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("bill.in","w",stdout);
    srand(time(0));
    printf("10000\n");
    int sum = 1;
    for(int i = 1;i <= 10000;i++){
        int tmp = rand() % 100000000;
        printf("%d %d\n",tmp,rand() % (100000000 - tmp) + tmp);
    }
    return 0;
}