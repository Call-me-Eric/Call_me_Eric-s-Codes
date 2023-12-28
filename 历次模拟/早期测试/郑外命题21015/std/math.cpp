#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
const int maxn = 1e8;
const int mod = 1e9;
 
ll limit;
 
int isprime(ll x)
{
  if(x<=1)return 0;
  for(ll i = 2;i * i <= x; i++) {
    if(x % i == 0) {
      return 0;
    }
  }
  return 1;
}
 
ll ans = 0;
std::vector<ll> v;
void dfs(ll id,ll now,ll upper)
{
 if(v[id] > upper || id == v.size()) {
    for(ll x = now ; x <= limit ; x *= 2LL) {
      for(ll y = 1 ; x*y <= limit ; y *= 3LL) {
        for(ll z = 1 ; x*y*z <= limit; z *= 5LL) {
           ans += (int)(x*y*z); //a little bug , need to change ll into interger
        }
      }
    }
    return;
  }
  dfs(id + 1, now, upper);
  dfs(id + 1, now * v[id], upper / v[id]);
}
int main(int argc, char const *argv[]) {
 
cin>>limit;
  for(ll x = 1; x <= limit;  x *= 2LL) {
    for(ll y = 1; x*y <= limit; y *= 3LL) {
      for(ll z = 1 ; x*y*z <= limit; z *= 5LL) {
        if(isprime(x*y*z + 1)) {
          v.push_back(1LL*(x*y*z + 1));
        }
      }
    }
  }
  sort(v.begin(),v.end());
 
  dfs(3LL,1LL,limit);
  ans = ans % (1LL<<32);
  std::cout << ans << '\n';
 
  return 0;
}