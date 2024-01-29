#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
typedef long long ll;
ll a[100010];
ll del[100010];
ll s[100010];
ll res[100010];
ll f[100010];
bool book[100010];
long long getf(long long t){
	if(f[t] == t)return t;
	else {
		f[t] = getf(f[t]);
		return f[t];
	}
}
int n;
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%lld",&a[i]);
		f[i] = i;
	}
	for(int i = 1;i <= n;i++){
		scanf("%lld",&del[i]);
	}
	ll maxx = 0;
	stack<ll> stk;
	for(int i = n;i >= 1;i--){
		ll t = del[i];
		ll ans = 0;
		stk.push(maxx);
		ll fl = getf(t - 1);
		ll fr = getf(t + 1);
		if(book[t - 1] && book[t + 1]){
			f[fl] = f[fr] = getf(t);
			ans = s[t] = s[fl] + s[fr] + a[t];
			book[t] = 1;
		}
		else if(!book[t - 1] && book[t + 1]){
			f[fr] = getf(t);
			ans = s[t] = s[fr] + a[t];
			book[t] = 1;
		}
		else if(book[t - 1] && !book[t + 1]){
			f[fl] = getf(t);
			ans = s[t] = s[fl] + a[t];
			book[t] = 1;
		}
		else {
			book[t] = 1;
			s[t] = a[t];
			ans = a[t];
		}
		maxx = maxx > ans ? maxx : ans;
	}
	for(int i = 1;i <= n;i++){
		printf("%lld\n",stk.top());
		stk.pop();
	}
	return 0;
}

