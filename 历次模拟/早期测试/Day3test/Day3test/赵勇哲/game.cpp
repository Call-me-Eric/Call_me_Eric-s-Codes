#include<bits/stdc++.h>
#define ll long long
#define qmul(a,b,c) (a) * (b) % (c)
using namespace std;
int n, m, T;
multiset<ll> s;
const int maxn = 1e5 + 10,maxm = maxn;
ll a[maxn], b[maxn],p[maxn], gift[maxn], sword[maxm], mx;/*
ll qmul(ll x,ll y,ll mod){
	ll res = 0;
	if(y < 0){x = -x;y = -y;}
	while(x > 0){
		if(x & 1)res = (res + y) % mod;
		y = (y << 1) % mod;
		x >>= 1;
	}
	return (res % mod + mod) % mod;
}*/
void exgcd(ll a,ll b,ll &x,ll &y,ll &gcd){
	if(!b){
		x = 1;
		y = 0;
		gcd = a;
		return;
	}
	else{
		ll tmp, ret;
		exgcd(b,a % b,x,y,gcd);
		tmp = x;
		x = y;
		y = tmp - a / b * y;
		return;
	}
	return;
}
ll EXCRT(){
	ll ans = 0,lcm = 1,A,B,C,x,y,gcd;
	for(int i = 1;i <= n;i++){
		A = qmul(b[i] , lcm , p[i]);
		B = p[i];
		C = (a[i] - qmul(b[i] , ans , p[i]) + p[i]) % p[i];
		exgcd(A,B,x,y,gcd);
		x = (x % B + B) % B;
		if(C % gcd)return -1;
		ans += qmul(qmul((C / gcd) , x , (B / gcd)) , lcm , (lcm *= B / gcd));
		ans %= lcm;
	}
	if(ans < mx)ans += ((mx - ans - 1) / lcm + 1) * lcm;
	return ans;
}
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		mx = -1;
		bool flag = 1;
		scanf("%d%d",&n,&m);
		for(int i = 1;i <= n;i++){
			scanf("%lld",&a[i]);
		}
		for(int i = 1;i <= n;i++){
			scanf("%lld",&p[i]);
			if(p[i] != 1)flag = 0;
		}
		for(int i = 1;i <= n;i++){
			scanf("%lld",&gift[i]);
		}
		for(int i = 1;i <= m;i++){
			scanf("%lld",&sword[i]);
			s.insert(sword[i]);
		}
		for(int i = 1;i <= n;i++){
			set<ll>::iterator pos = s.upper_bound(a[i]);
			if(pos != s.begin())pos--;
			b[i] = *pos;s.erase(pos);s.insert(gift[i]);
			mx = max(mx,(a[i] - 1) / b[i] + 1);
		}
		if(flag){
			printf("%lld\n",mx);
		}
		else{
			printf("%lld\n",EXCRT());
		}
		s.clear();
	}
	return 0;
}


