#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 5e4 + 10, maxm = 1e2 + 10;
int buc[maxn];
vector<int> vec[maxn];
vector<pair<pair<int,int>,int > > tmp;
int n, a[maxn], m;
signed main(){
	freopen("avidity.in","r",stdin);
	freopen("avidity.out","w",stdout);
	n = read(); m = read();int lst = 0, mx = 0;
	for(int i = 1;i <= n;i++)mx = max(mx,a[i] = read());
	for(int i = 1;i <= mx;i++)vec[i].push_back(-1);
	for(int i = 1;i <= n;i++){buc[a[i]]++;vec[a[i]].push_back(i);}
	for(int i = 1;i <= mx;i++)vec[i].push_back(n + 1);
	sort(a + 1,a + 1 + n);int tot = unique(a + 1,a + 1 + n) - a - 1;
//	cerr << "tot = " << tot << ",mx = " << mx;
//	for(int i = 1;i <= n;i++){cerr << "a[" << i << "] = " << a[i] << endl;}
	if(mx <= tot){
		for(int i = 1;i <= mx;i++)
			if(buc[i]) for(int j = i + 1;j <= mx;j++){
				int x = sqrt(i * i + j * j);
				if(!buc[j] || x * x != i * i + j * j || x > mx || !buc[x])continue;
				tmp.push_back(make_pair(make_pair(i,j),x));
			}
	}
	else{
		for(int i = 1;i <= tot;i++)
			for(int j = i + 1;j <= tot;j++){
				int x = sqrt(a[i] * a[i] + a[j] * a[j]);
				if(x * x != a[i] * a[i] + a[j] * a[j] || x > mx || !buc[x])continue;
				tmp.push_back(make_pair(make_pair(a[i],a[j]),x));
			}
	}
	
//	for(auto i : tmp)printf("%d %d %d\n",i.first.first,i.first.second,i.second);
	for(int test = 1;test <= m;test++){
		int aa = read(), b = read();
		int l = min((aa + lst) % n + 1,(b + lst) % n + 1), r = max((aa + lst) % n + 1,(b + lst) % n + 1);
		lst = 0;
		for(auto i : tmp){
			int x = i.first.first, y = i.first.second, z = i.second;
			lst += ((upper_bound(vec[z].begin(),vec[z].end(),r) - lower_bound(vec[z].begin(),vec[z].end(),l)) * 
					(upper_bound(vec[y].begin(),vec[y].end(),r) - lower_bound(vec[y].begin(),vec[y].end(),l)) *
					(upper_bound(vec[x].begin(),vec[x].end(),r) - lower_bound(vec[x].begin(),vec[x].end(),l)));
		}
		printf("%d\n",lst);
	}
	return 0;
}
