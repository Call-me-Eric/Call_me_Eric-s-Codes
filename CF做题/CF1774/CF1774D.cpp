#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
vector<int> vec[maxn];
int cnt[maxn];
vector<int> need, rest;
vector<pair<pair<int,int>,int> > opt;
signed main(){
int T = read();
while(T--){
    n = read(); m = read();
    int sum = 0;
    for(int i = 1;i <= n;i++){
        vec[i].clear();cnt[i] = 0;
        for(int j = 0;j < m;j++){
            vec[i].push_back(read());
            cnt[i] += vec[i][j];
        }
        sum += cnt[i];
    }
    if(sum % n){puts("-1");continue;}
    opt.clear();int res = sum / n;rest.clear();need.clear();

// printf("res=%d,,sum=%d\n",res,sum);

    for(int i = 1;i <= n;i++){
        // printf("cnt[%d]=%d\n",i,cnt[i]);
        if(cnt[i] > res){rest.push_back(i);}
        if(cnt[i] < res){need.push_back(i);}
    }
    while(!rest.empty()){
        int i = rest.back();rest.pop_back();
        while(!need.empty()){
            int j = need.back();need.pop_back();
            for(int k = 0;k < m && cnt[i] > res;k++){
                // printf("i=%d,j=%d,k=%d,ik=%d,jk=%d\n",i,j,k,vec[i][k],vec[j][k]);
                if((vec[i][k] == 1) && (vec[j][k] == 0)){
                    opt.push_back(make_pair(make_pair(i,j),k));
                    cnt[i]--;cnt[j]++;vec[i][k] = 0;vec[j][k] = 1;
                    if(cnt[i] == res || cnt[j] == res)break;
                }
            }
            if(cnt[j] < res){need.push_back(j);break;}
        }
    }
    printf("%d\n",opt.size());
    for(auto i : opt){
        printf("%d %d %d\n",i.first.first,i.first.second,i.second + 1);
    }
}
    return 0;
}