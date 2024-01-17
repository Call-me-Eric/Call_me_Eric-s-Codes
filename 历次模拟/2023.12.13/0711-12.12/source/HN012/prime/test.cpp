#include <bits/stdc++.h>

using namespace std;

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;
using db=double;
using vi=vector<int>;
using pii=pair<int,int>;

template<typename T>
T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f|=(c=='-'),c=getchar();
	while(isdigit(c)) x=x*10+(c-'0'),c=getchar();
	return f?-x:x;
}

#define rdi read<int>
#define rdi64 read<i64>
#define fi first
#define se second
#define pb push_back

const int MOD=998244353;

inline bool isprime(i64 x){
	if(x==1) return false;
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return false;
	return true;
}

inline bool issubs(i64 x,i64 y){
	while(x&&y){
		if(x%10==y%10) y/=10;
		x/=10;
	}
	return y?0:1;
}

const i64 MX=1e10;

bitset<MX> bs;
void init(){
	bs[1]=1;
	for(i64 i=2;i<MX;i++){
		if(bs[i]) continue;
		for(i64 j=i;j<=(MX-1)/i;j++) bs[i*j]=1;
	}

	vector<i64> v;
	for(i64 i=1;i<MX;i++){
		if(bs[i]) continue;
		bool fl=1;
		for(auto j:v)
			if(issubs(i,j)) {fl=0;break;}
		if(fl) v.pb(i);
	}
	for(auto x:v)
		cout<<x<<'\n';
}

int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	init();
	return 0;
}
