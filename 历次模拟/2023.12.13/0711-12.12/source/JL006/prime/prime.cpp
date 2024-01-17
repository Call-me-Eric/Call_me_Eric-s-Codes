#include<bits/stdc++.h>
#define MOD 998244353
using namespace std;
int dp[2][2][25];
void add(int &a,int b){
    a+=b;
    if(a>=MOD)a-=MOD;
}
vector<int>ban = {2,3,5,7,11,991,881,449,666649,6469,499,6949,4969,9649,946669,409,9049,66666049,9949,9001,41,61,19,89,60649};
vector<string>tmp;
struct chash{
    size_t operator()(const vector<int> &v)const{
        size_t h = 0;
        for(auto x:v)h = 107u*h+x;
        return h;
    }
};
unordered_map<vector<int>,int,chash>mp[2];
int cal(const char *lim,int len){
    vector<int>s(ban.size()+1,0);
    int x=0;
    mp[x].clear();
    mp[x][s]=1;
    for(int i=0;i<len;i++,x^=1){
        mp[x^1].clear();
        for(auto [k,v]:mp[x]){
            for(int j=0;j<=(k.back()?9:(lim[i]-'0'));j++){
                vector<int> cur = k;
                bool flag=1;
                for(int l=0;l<ban.size();l++){
                    if(j == tmp[l][cur[l]]-'0')cur[l]++;
                    flag&=cur[l]!=tmp[l].size();
                }
                if(!flag)continue;
                cur.back() |= j < lim[i]-'0';
                add(mp[x^1][cur],v);
            }
        }
    }
    int ans=0;
    for(auto [k,v]:mp[x])add(ans,v);
    return ans;
}
int T;
string l,r;
string dec(string s){
    for(int i = s.length()-1;i>=0;i--){
        if(s[i]!='0'){
            s[i]--;
            for(int j=i+1;j<s.length();j++)s[j]++;
            return s;
        }
    }
}
int main(){
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    for(auto x:ban)tmp.push_back(to_string(x));
    cin>>T;
    while(T--){
        cin>>l>>r;
        l = dec(l);
        cout<<(cal(r.c_str(),r.length())-cal(l.c_str(),l.length())+MOD)%MOD<<'\n';
    }
    return 0;
}