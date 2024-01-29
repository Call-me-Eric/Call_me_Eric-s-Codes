#include <bits/stdc++.h>
using namespace std;
int main(){
    int n, l, r;
    cin >> n >> l >> r;
    if((r - l) >= n)
        cout << n -1 << endl;
    else
        cout << r % n << endl;
    return 0;
}