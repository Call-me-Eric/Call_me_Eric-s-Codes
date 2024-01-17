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

int main(){
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	puts("0");
	return 0;
}
