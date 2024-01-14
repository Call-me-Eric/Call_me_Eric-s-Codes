#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){
	int x = 0, f =1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
int n, m, w, h;
struct node{
	int x, y;mutable int val;
	node(int x = 0,int y = 0,int val = 0):x(x),y(y),val(val){}
	friend bool operator < (node a,node b){return a.x < b.x;}
}a[maxn];
set<pair<int,int> > st;
signed main(){
	n = read(); m = read(); w = read(); h = read();
	int sum = 0;
	for(int i = 1;i <= n;i++){
		int x = read(), y = read();
		a[i] = node(-y * h + x * w,y * h + x * w,read());
		sum += a[i].val;
	}
	for(int i = n + 1;i <= m + n;i++){
		int x = read(), y = read();
		a[i] = node(-y * h + x * w,y * h + x * w,-read());
	}
	n += m;sort(a + 1,a + 1 + n);
	for(int i = 1;i <= n;i++){
		if(a[i].val >= 0){st.insert(make_pair(a[i].y,a[i].val));}
		else{
			auto it = st.lower_bound(make_pair(a[i].y,0));
//			puts("111111111");
			while(it != st.end()){
				if(it->second + a[i].val > 0){
					auto tmp = *it;
					sum += a[i].val;tmp.second += a[i].val;break;
					st.erase(it);st.insert(tmp);
				}
				else{
					sum -= it->second;a[i].val += it->second;
					auto p = it;it++;st.erase(p);
				}
			}
		}
	}
	printf("%lld\n",sum);
	return 0;
}
