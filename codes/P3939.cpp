#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f  =-1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, m;
int a[maxn];
vector<int> vec[maxn];
signed main(){
    n = read(); m = read();for(int i = 1;i <= n;i++)vec[a[i] = read()].push_back(i);
    int opt, l, r, c;
    for(int i = 1;i <= m;i++){
        opt = read();l = read();
        if(opt == 2){
            if(a[l] == a[l + 1])continue;
            int pos1 = lower_bound(vec[a[l]].begin(),vec[a[l]].end(),l) - vec[a[l]].begin();
            int pos2 = lower_bound(vec[a[l + 1]].begin(),vec[a[l + 1]].end(),l + 1) - vec[a[l + 1]].begin();
            vec[a[l]][pos1] = l + 1;
            vec[a[l + 1]][pos2] = l;
            swap(a[l],a[l + 1]);
        }
        else{
            r = read(); c = read();
            int pos1 = upper_bound(vec[c].begin(),vec[c].end(),r) - vec[c].begin() - 1;
            int pos2 = lower_bound(vec[c].begin(),vec[c].end(),l) - vec[c].begin();
            // if(!pos2)pos2 = 1;
            if(pos2 > pos1)puts("0");
            else printf("%d\n",pos1 - pos2 + 1);
            // printf("DEBUG:%d %d\n",pos1,pos2);
        }
    }
    return 0;
}