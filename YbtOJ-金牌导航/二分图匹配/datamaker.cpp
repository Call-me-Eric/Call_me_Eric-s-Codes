#include<bits/stdc++.h>
using namespace std;
signed main(){
    int n = 1000, m = 10;srand(time(0));
    printf("%d %d\n", m, n);int srd = rand();
    for(int i = 1;i <= n;i++){
        bool book = false;
        for(int j = 1;j <= m;j++){
            srd += rand();srd %= 3;
            if(srd < 2)putchar('0' + srd);
            else{
                if(book)putchar('0' + rand() % 2);
                else putchar('*'),book = 1;
            }
        }
        puts("");
    }
    puts("0 0");
    return 0;
}