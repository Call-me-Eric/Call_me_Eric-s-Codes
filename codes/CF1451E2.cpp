#include<bits/stdc++.h>
using namespace std;
int a[1 << 16];
int c[1 << 16];
int buc[1 << 16];
int n;
signed main(){
    cin >> n;int x = 0, y = 0;
    for(int i = 2;i <= n;i++){
        cout << "XOR 1 " << i << endl;
        cin >> c[i];
        if(!buc[c[i]]){buc[c[i]] = i;}
        else {x = buc[c[i]];y = i;}
    }
    if(buc[0]){x = 1;y = buc[0];}
    if(x != 0 && y != 0){
        cout << "AND " << x << " " << y << endl;
        cin >> a[x];a[1] = c[x] ^ a[x];
        for(int i = 2;i <= n;i++){a[i] = c[i] ^ a[1];}
        cout << '!';for(int i = 1;i <= n;i++)cout << ' ' << a[i];cout << endl;
        return 0;
    }
    else{
        int tmp1 = 0, tmp2 = 0;
        cout << "AND 1 " << buc[1] << endl;
        cin >> tmp1;
        cout << "AND 1 " << buc[n - 2] << endl;
        cin >> tmp2;
        a[1] = ((tmp1 >> 1) << 1) | (tmp2 & 1);
        for(int i = 2;i <= n;i++){a[i] = c[i] ^ a[1];}
        cout << '!';for(int i = 1;i <= n;i++)cout << ' ' << a[i];cout << endl;
    }
    return 0;
}