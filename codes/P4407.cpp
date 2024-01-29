#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int maxn = 2e4 + 10;

ull Base = 31, pw[31];
ull l[31], r[31];

int n, m;
char ch[31];
map<ull,int> mp[31];
map<ull,int> dif[31];
map<ull,int> chg[31][31];

signed main(){
    scanf("%d%d",&n,&m);pw[0] = 1;
    for(int i = 1;i <= 20;i++)pw[i] = pw[i - 1] * Base;
    for(int i = 1;i <= n;i++){
        scanf("%s",ch + 1);
        int len = strlen(ch + 1);
        for(int j = 1;j <= len + 2;j++)l[j] = r[j] = 0;
        for(int j = 1;j <= len;j++)l[j] = l[j - 1] * Base + ch[j] - 'a' + 1ull;
        for(int j = len;j;j--)r[j] = r[j + 1] + (ch[j] - 'a' + 1ull) * pw[len - j];
        vector<ull> vec;vec.clear();
        mp[len][l[len]]++;
        for(int j = 1;j <= len;j++){
            vec.push_back(l[j - 1] * pw[len - j] + r[j + 1]);
            chg[len][j][l[j - 1] * pw[len - j] + r[j + 1]]++;
        }
        sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());
        for(ull j : vec)dif[len - 1][j]++;
    }
    for(int i = 1;i <= m;i++){
        scanf("%s",ch + 1);
        int len = strlen(ch + 1);
        for(int j = 1;j <= len + 2;j++)l[j] = r[j] = 0;
        for(int j = 1;j <= len;j++)l[j] = l[j - 1] * Base + ch[j] - 'a' + 1;
        for(int j = len;j;j--)r[j] = r[j + 1] + (ch[j] - 'a' + 1) * pw[len - j];

        if(mp[len][l[len]]){puts("-1");continue;}
        int cnt = dif[len][l[len]];
        // printf("1 : cnt = %d\n",cnt);
        vector<ull> vec;vec.clear();
        for(int j = 1;j <= len;j++){
            vec.push_back(l[j - 1] * pw[len - j] + r[j + 1]);
            cnt += chg[len][j][l[j - 1] * pw[len - j] + r[j + 1]];
        }
        // printf("2 : cnt = %d\n",cnt);
        sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());
        for(ull j : vec)cnt += mp[len - 1][j];
        printf("%d\n",cnt);
    }
    return 0;
}