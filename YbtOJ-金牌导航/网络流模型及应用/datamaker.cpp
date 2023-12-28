#include<bits/stdc++.h>
using namespace std;
bool book[100][100][4];
signed main(){
    srand(time(0));
    mt19937 rnd(rand());
    int n = 50, m = 50;
    printf("%d %d\n",n,m);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            int sed = rnd() % 15;
            if(0 <= sed && sed <= 3){
                int chk = true;
                if(sed == 0){
                    if(book[i][j][0]){chk = false;}
                    else{
                        book[i][j][0] = 1;
                        for(int k = i + 1;k <= n;k++){book[k][j][0] = 1;}
                        for(int k = j + 1;k <= m;k++){book[i][k][2] = 1;}
                    }
                }
                if(sed == 1){
                    if(book[i][j][1])chk = false;
                    else{
                        for(int k = i;k <= n;k++)book[k][j][0] = book[k][j][1] = book[k][j][2] = book[k][j][3] = 1;
                        for(int k = j + 1;k <= m;k++)book[i][k][2] = 1;
                    }
                }
                if(sed == 2){
                    if(book[i][j][2])chk = false;
                    else{
                        for(int k = j + 1;k <= m;k++){book[i][k][2] = 1;}
                    }
                }
                if(sed == 3){
                    if(book[i][j][3])chk = false;
                    for(int k = i + 1;k <= n;k++){book[k][j][0] = 1;}
                    for(int k = j + 1;k <= m;k++)book[i][k][0] = book[i][k][1] = book[i][k][2] = book[i][k][3] = 1;
                }
                printf("%d ",chk * (-sed - 1));
            }
            if(4 <= sed && sed <= 6){
                printf("%d ",0);
            }
            if(7 <= sed && sed <= 14){
                printf("%d ",rnd() % 1000);
            }
        }
        puts("");
    }
    return 0;
}