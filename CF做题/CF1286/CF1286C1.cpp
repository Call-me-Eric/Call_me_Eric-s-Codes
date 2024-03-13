#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 100 + 10;
int n;
string ans;
namespace Subtask1{
multiset<string> st;
int cnt[maxn][27];
string solve(int n){
    cout << "? " << 2 << " " << n << endl;
    for(int i = 1;i <= (n - 1) * n / 2;i++){
        string s;cin >> s; sort(s.begin(),s.end());
        st.insert(s);
    }
    cout << "? " << 1 << " " << n << endl;
    for(int i = 1;i <= n * (n + 1) / 2;i++){
        string s;cin >> s; sort(s.begin(),s.end());
        auto it = st.find(s);
        if(it == st.end()){
            for(int i = 0;i < s.length();i++)
                cnt[s.length()][s[i] - 'a']++;
        }
        else st.erase(it);
    }
    string res = "";
    for(int len = 1;len <= n;len++){
        char ch = '-';
        for(int i = 0;i < 26;i++)
            if(cnt[len][i] != cnt[len - 1][i]){
                ch = i + 'a';break;
            }
        res.push_back(ch);
    }
    return res;
}
};
void main(){
    ios::sync_with_stdio(false);
    cin >> n;
    if(n <= 3){
        for(int i = 1;i <= n;i++){
            cout << "? " << i << " " << i << endl;
            char ch;cin >> ch;
            ans.push_back(ch);
        }
        cout << "! " << ans << endl;
        return;
    }
    ans = Subtask1::solve(n);
    cout << "! " << ans << endl;
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}