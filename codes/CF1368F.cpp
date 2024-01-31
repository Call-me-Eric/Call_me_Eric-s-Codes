#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
int n;
bool a[maxn];
signed main(){
    cin >> n;int k = sqrt(n);
for(int tt = 1;tt <= n + 2;tt++){
    int cnt = 0;vector<int> opt;opt.clear();
    for(int i = 1;i <= n && cnt < k;i++){
        if(i % k == 0 || i == n)continue;
        if(!a[i]){opt.push_back(i);cnt++;a[i] = 1;}
    }
    cout << opt.size();for(int i : opt)cout << " " << i;cout << endl;
    int x;cin >> x;x--;
    for(int i = 1;i <= k;i++){int y = x + i;if(y > n)y -= n;a[y] = 0;}
}
    cout << 0 << endl;
    return 0;
}