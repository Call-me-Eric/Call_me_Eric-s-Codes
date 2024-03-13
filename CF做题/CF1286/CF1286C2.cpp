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
    if(n == 1){
        cout << "? " << 1 << " " << 1 << endl;
        string s;cin >> s;
        return s;
    }
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
            for(int j = 0;j < s.length();j++)
                cnt[s.length()][s[j] - 'a']++;
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
int cnt[maxn][27];
int sum[27];
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
    ans = Subtask1::solve((n + 1) / 2);
    cout << "? " << 1 << " " << n << endl;
    for(int i = 1;i <= (n + 1) * n / 2;i++){
        string s;cin >> s;
        for(int j = 0;j < s.length();j++)
            cnt[s.length()][s[j] - 'a']++;
    }
    ans.resize(n);
    if(n & 1){sum[ans[n / 2] - 'a']++;}
    for(int i = n - (n + 1) / 2  - 1;i + 1;i--){
        // cerr << "i = " << i << "n - i = " << n - i << endl;
        sum[ans[i] - 'a']++;
        for(int j = 0;j < 26;j++)
            if(cnt[i + 1][j] - cnt[i][j] - sum[j] == 1){
                ans[n - i - 1] = j + 'a';break;
            }
        sum[ans[n - i - 1] - 'a']++;
    }
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