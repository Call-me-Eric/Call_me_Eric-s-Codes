#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
signed main(){
    ull a, b;
    cin >> a >> b;
    if(a < b || (a - b) % 2 != 0)cout << -1 << endl;
    else cout << (a - b) / 2 << " " << a - (a - b) / 2 << endl;
    return 0;
}