#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f  = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch= getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int mod = (1 << 14);
vector<int> vec1, vec2;
bool book[mod];
signed main(){
    for(int i = 1;i <= 100;i++)vec1.push_back(i);
    for(int i = 1;i <= 100;i++)vec2.push_back(i << 7);
    cout << "?"; for(int i : vec1){cout << ' ' << i;}cout << endl;
    int tmp1;cin >> tmp1;
    cout << "?"; for(int i : vec2){cout << ' ' << i;}cout << endl;
    int tmp2;cin >> tmp2;
    int x = 0, y = 0;bool flag = 0;
    for(int i : vec1){
        if(flag)break;
        for(int j : vec2)
            if((i ^ j) == (tmp1 ^ tmp2)){
                flag = 1;x = i,y = j;break;
            }
    }
    cout << "! " << (tmp1 ^ x) << endl;
    return 0;
}