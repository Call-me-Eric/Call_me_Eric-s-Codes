#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 5e4 + 10;
int n, m;
int x[maxn], y[maxn];
struct query{
	int x, y, id;
}qu[maxn];
map<pair<int,int> ,int> mp;
map<int, int> mpx, mpy;
vector<pair<int,int> > l[maxn << 1], r[maxn << 1];
int ans[maxn];
bool book[maxn];
signed main(){
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
	n = read(); m = read();
	for(int i = 1;i <= n;i++){
		x[i] = read(); y[i] = read();
	}
		int idx = 0, idy = 0;
		for(int i = 1;i <= m;i++){
			qu[i].x = read(); qu[i].y = read();
			if(mpx.find(qu[i].x) == mpx.end()){mpx[qu[i].x] = ++idx;}
			l[mpx[qu[i].x]].push_back(make_pair(qu[i].y,i));
			
			if(mpy.find(qu[i].y) == mpy.end()){mpy[qu[i].y] = ++idy;}
			r[mpy[qu[i].y]].push_back(make_pair(qu[i].x,i));
		}
//		puts("1111111");
		for(int i = 1;i <= n;i++){
			int tx = x[i], ty = y[i];
			memset(book,0,sizeof(book));
			while(tx != ty && tx > 0 && ty > 0){
//				printf("%lld %lld\n",tx,ty);
				if(tx > ty){
					if(mpy.find(ty) != mpy.end()){
						int pos = mpy[ty];
						for(int j = r[pos].size() - 1;j >= 0;j--){
							ans[r[pos][j].second] += ((r[pos][j].first % ty) == (tx % ty) && r[pos][j].first <= tx && !book[r[pos][j].second]);
							if((r[pos][j].first % ty) == (tx % ty) && r[pos][j].first <= tx){
//								printf("%lld %lld %lld %lld\n",tx,ty,r[pos][j].first, ty);
								book[r[pos][j].second] = 1;
							}
						}
					}
					tx = tx % ty;
				}
				else{
					if(mpx.find(tx) != mpx.end()){
						int pos = mpx[tx];
						for(int j = l[pos].size() - 1;j >= 0;j--){
							ans[l[pos][j].second] += ((l[pos][j].first % tx) == (ty % tx) && l[pos][j].first <= ty && !book[l[pos][j].second]);
							if((l[pos][j].first % tx) == (ty % tx) && l[pos][j].first <= ty){
//								printf("%lld %lld %lld %lld\n",tx,ty,tx,l[pos][j].first);
								book[l[pos][j].second] = 1;
							}
						}
					}
					ty = ty % tx;
				}
			}
		}
		for(int i = 1;i <= m;i++){
			printf("%lld\n",ans[i]);
		}
	return 0;
}

