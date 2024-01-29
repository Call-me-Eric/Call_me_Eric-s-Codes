#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, m;
char ch[maxn];
int a[maxn];
signed main(){
    freopen("bracket.in","r",stdin);
    freopen("bracket.out","w",stdout);
    n = read(); m = read();int opt, l, r;
    scanf("%s",ch + 1);
    for(int i = 1;i <= n;i++){a[i] = ((ch[i] == '(') ? 1 : -1);}
    for(int test = 1;test <= m;test++){
        opt = read(); l = read(); r = read();
        if(opt == 1){
            for(int i = l;i <= r;i++){a[i] = -a[i];}
        }
        else{
            int sum = 0, cnt = 0, ans = 0;
            for(int i = l;i <= r;i++)sum += a[i];
            vector<int> vec;vec.clear();
            vector<int> pos;pos.clear();int lpos = 0;
            for(int i = 1;i <= sum;i++)vec.push_back(-1);
            for(int i = l;i <= r;i++){vec.push_back(a[i]);if(a[i] == 1)pos.push_back(vec.size() - 1);}
            for(int i = 1;i <= -sum;i++){vec.push_back(1);pos.push_back(vec.size() - 1);}
            // for(int i : vec)printf("%d",i);puts("");
            // for(int i : pos)printf("%d ",i);puts("");
            for(int i = 0;i < vec.size();i++){
                cnt += vec[i];lpos += (vec[i] == 1);
                // printf("i = %d, ans = %d, posl = %d\n",i,ans, pos[lpos]);
                if(cnt < 0){
                    ans += pos[lpos] - i;
                    vec[i] = 1;vec[pos[lpos]] = -1;
                    lpos++;cnt = 1;
                }
            }
            if(sum < 0)sum = -sum;
            printf("%d\n",ans + sum);
        }
    }
    return 0;
}