#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 4e5 + 10;
int n, m;
struct node{
	int x, y, val;
	node(int x = 0,int y =  0,int val = 0):x(x),y(y),val(val){}
	friend bool operator < (node a,node b){return a.x != b.x ? a.x < b.x : a.y > b.y;}
}a[maxn];
int w, h;
set<pair<int,int> > st;
void main(){
	n = read(); m = read();w = read(); h = read();;int sum = 0;
	for(int i = 1;i <= n;i++){
		int u = read(), v = read(),val = read();
		a[i] = node(u * h + v * w,u * h - v * w,val);sum += val;
	}
	for(int i = 1;i <= m;i++){
		int u = read(), v = read(),val = read();
		a[i + n] = node(u * h + v * w,u * h - v * w,-val);
	}
	n += m;sort(a + 1,a + 1 + n);
	for(int i = 1;i <= n;i++){
		if(a[i].val >= 0)st.insert(make_pair(a[i].y,a[i].val));
		else{
			auto it = st.lower_bound(make_pair(a[i].y,0));
			while(a[i].val < 0){
				// puts("1111243342423143124312");
				if(it == st.end())break;
				auto tmp = *it;it = st.erase(it);
				int d = min(tmp.second,-a[i].val);
				a[i].val += d;sum -= d;tmp.second -= d;
				if(tmp.second)st.insert(tmp);
			}
		}
	}
	printf("%lld\n",sum);
	return;
}
};
bool edmemory;
signed main(){
	auto stclock = clock();
	Call_me_Eric::main();
	auto edclock = clock();
	cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
	cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
	return 0;
}