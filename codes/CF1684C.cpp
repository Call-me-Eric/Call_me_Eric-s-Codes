#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
vector<int> vec[maxn], srt[maxn];
int n, m;
void solve(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++){
        vec[i].clear();vec[i].push_back(-114514);
        for(int j = 1;j <= m;j++)vec[i].push_back(read());
        srt[i] = vec[i];
        sort(srt[i].begin(),srt[i].end());
    }
    int pos0 = -1, pos1 = -1;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(srt[i][j] != vec[i][j]){
                if(pos0 == -1){pos0 = j;continue;}
                if(pos1 == -1){pos1 = j;break;}
            }
        }
        if(pos0 != -1 && pos1 != -1)break;
    }
    for(int i = 1;i <= n;i++){
        swap(vec[i][pos0],vec[i][pos1]);
        for(int j = 1;j <= m;j++)
            if(vec[i][j] != srt[i][j]){puts("-1");return;}
    }
    if(pos0 == -1 && pos1 == -1)pos0 = pos1 = 1;
    printf("%d %d\n",pos0, pos1);
}
signed main(){
    int T = read();
    while(T--)solve();
    return 0;
}