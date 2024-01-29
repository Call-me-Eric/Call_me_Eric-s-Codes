#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n;
vector<int> vec, a, b, c;
signed main(){
    ios::sync_with_stdio(false);
    cin >> n;for(int i = 1;i <= n;i++)vec.push_back(i);
    while(1){
        string s;
        a.clear();b.clear();c.clear();
        if(vec.size() == 2){
            cout << "! " << vec[0] << endl;
            cin >> s;
            if(s == ":)"){return 0;}
            cout << "! " << vec[1] << endl;
            cin >> s;return 0;
        }
        if(vec.size() == 1){
            cout << "! " << vec[0] << endl;
            return 0;
        }
        for(int i = 0;i < vec.size() / 3;i++)a.push_back(vec[i]);
        for(int i = vec.size() / 3;i < vec.size() / 3 * 2;i++)b.push_back(vec[i]);
        for(int i = vec.size() / 3 * 2;i < vec.size();i++)c.push_back(vec[i]);
        bool st1 = true, st2 = true, st3 = true;
        cout << "? " << a.size();for(int i : a)cout << " " << i;cout << endl;
        cin >> s;
        if(s == "YES"){
            cout << "? " << b.size();for(int i : b)cout << " " << i;cout << endl;
            cin >> s;
            if(s == "YES")st3 = false;
            else st2 = false;
        }
        else{
            cout << "? " << a.size();for(int i : a)cout << " " << i;cout << endl;
            cin >> s;
            if(s == "YES"){
                cout << "? " << b.size();for(int i : b)cout << " " << i;cout << endl;
                cin >> s;
                if(s == "YES")st3 = false;
                else st2 = false;
            }
            else st1 = false;
        }
        vec.clear();
        if(st1)for(int i : a)vec.push_back(i);
        if(st2)for(int i : b)vec.push_back(i);
        if(st3)for(int i : c)vec.push_back(i);
    }
    return 0;
}