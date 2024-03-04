#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> P;
#define MAXK 1000010
#define endl '\n'

inline int rd() {
  int x = 0;
  bool f = 0;
  char c = getchar();
  for (; !isdigit(c); c = getchar()) f |= (c == '-');
  for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return f ? -x : x;
}

int t,k,buc[MAXK];
vector<P>vec;
void solve(int ans=2e9,int cnt=0){
    k=rd();
    for(int i=1,siz;i<=k;i++){
        siz=rd();
        for(int j=1,x;j<=siz;j++){
            x=rd();
            vec.push_back(P(x,i));
        }
    }
    sort(vec.begin(), vec.end());
    for(int i=0,j=0;i<vec.size();i++){
        cnt += (++buc[vec[i].second]==1);
        for(;j<i&&buc[vec[j].second]>1;j++)
            buc[vec[j].second]--;
        if(cnt==k)ans = min(ans, vec[i].first-vec[j].first);
    }
    cout<<ans<<endl;
    return;
}

int main(){
	freopen("eliminate.in", "r", stdin);
	freopen("eliminate.out", "w", stdout);
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    solve();
    return 0;
} 
