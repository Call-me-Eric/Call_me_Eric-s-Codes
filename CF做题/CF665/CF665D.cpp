#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10;
int a[maxn], n;
bool book[maxn * maxn * 4];
int prime[maxn * maxn], tot;
vector<int> ans1,ans2,ans3;
signed main(){
    for(int i = 2;i <= 3e6;i++){
        if(!book[i])prime[++tot] = i;
        for(int j = 1;j <= tot && i * prime[j] <= 3e6;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    n = read();
    for(int i = 1;i <= n;i++){a[i] = read();if(a[i] == 1)ans1.push_back(1);}
    bool book2 = false, book1 = false;
    ans3.push_back(a[1]);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n && !book2;j++)
            if(!book[a[i] + a[j]] && !book2 && i != j){
                ans2.push_back(a[i]);ans2.push_back(a[j]);
                book2 = true;break;
            }
        if(ans1.size() && !book[a[i] + 1] && !book1 && a[i] != 1){
            book1 = true;ans1.push_back(a[i]);
        }
    }
    if(ans2.size() >= ans1.size() && ans2.size() >= ans3.size()){
        printf("%d\n",ans2.size());for(int i : ans2)printf("%d ",i);
    }
    else if(ans1.size() >= ans2.size() && ans1.size() >= ans3.size() && ans1[0] == 1){
        printf("%d\n",ans1.size());for(int i : ans1)printf("%d ",i);
    }
    else{
        printf("%d\n",ans3.size());for(int i : ans3)printf("%d ",i);
    }
    return 0;
}