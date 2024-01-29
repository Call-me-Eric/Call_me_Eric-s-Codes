#include <iostream>
#include <string>
using namespace std;
int main(){
    string k, c;
    cin >> k >> c;
    for (int i = 0;i < c.length();i++) {
        int t = (k[i % k.length()] & 31) - 1;
        c[i] = (c[i] & 31) - t > 0 /* «∑Ò‘ΩΩÁ*/? c[i] - t : c[i] - t + 26;
    }
    cout << c << endl;
    return 0;
}
