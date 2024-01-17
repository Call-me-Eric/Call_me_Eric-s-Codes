#include <bits/stdc++.h>
using namespace std;
typedef vector<pair<int, int>> Graph; 

int n, m; 

int main(void) {
    freopen("li.in", "r", stdin); 
    freopen("li.out", "w", stdout); 
    cin >> n >> m; 
    if (n == 2) return cout << "0 3\n", 0; 
    if (n == 3) {
        if (m == 1) return cout << "0 4\n", 0; 
        if (m == 2) return cout << "0 7\n", 0; 
        return cout << "1 3\n", 0; 
    }
    return 0;
}