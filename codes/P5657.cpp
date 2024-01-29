#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
ull n, k;
ull power[70];//ull请放心食用
int main(){
    cin >> n >> k;
    power[0] = 1;
    power[1] = 2;
    for(int i = 1;i <= 69;i++){
        power[i] = 2 * power[i - 1];
    }
    int i = n;
    while(n--){
        ull mid = (power[i] - 1) / 2;
        if(k > mid){
            k = power[i] - 1 - k;
            putchar('1');
        }
        else{
            putchar('0');
        }
        i--;
    }
    return 0;
}