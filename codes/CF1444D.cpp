#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e3 + 10;

bitset<maxn * maxn> f[maxn];

bool work(int n,int *arr,bool *book){
	int sum = 0;
	for(int i = 1;i <= n;i++)sum += arr[i];
	if((sum & 1))return false;
	f[0].set(0);
	for(int i = 1;i <= n;i++)
		f[i] = f[i - 1] | (f[i - 1] << arr[i]);
	if(!f[n][sum / 2])return false;
	int x = sum / 2;
	for(int i = n;i;i--){
		if(x >= arr[i] && f[i - 1][x - arr[i]]){
			book[i] = 1;x -= arr[i];
		}
		else if(f[i - 1][x]){book[i] = 0;}
		else return false;
	}
	return !x;
}

int n, m;
int a[maxn], b[maxn];
bool book1[maxn], book2[maxn];

void solve(){
	n = read();for(int i = 1;i <= n;i++){a[i] = read();book1[i] = 0;}
	bool check = work(n,a,book1);//printf("check = %d\n",check);
	m = read();for(int i = 1;i <= m;i++){b[i] = read();book2[i] = 0;}
	check &= work(m,b,book2);check &= (n == m);//printf("check=%d\n",check);
	if(!check){puts("No");return;}
	vector<int> v1, v2, v3, v4;
	v1.clear(); v2.clear(); v3.clear(); v4.clear();
	for(int i = 1;i <= n;i++){
		if(book1[i])v1.push_back(a[i]);
		else v2.push_back(a[i]);
	}
	for(int i = 1;i <= m;i++){
		if(book2[i])v3.push_back(b[i]);
		else v4.push_back(b[i]);
	}
	if(v1.size() > v2.size())swap(v1,v2);
	if(v3.size() < v4.size())swap(v3,v4);
	sort(v1.begin(),v1.end(),greater<int>());sort(v2.begin(),v2.end(),greater<int>());
	sort(v3.begin(),v3.end());sort(v4.begin(),v4.end());
//	printf("%d %d %d %d\n",v1.size(),v2.size(),v3.size(),v4.size());
	for(int i : v2){v1.push_back(-i);}
	for(int i : v4){v3.push_back(-i);}
	int x = 0, y = 0;
	vector<pair<int,int> > ans;
	for(int i = 0;i < (int)v1.size();i++){
		x += v1[i];
		ans.push_back(make_pair(x, y));
		y += v3[i];
		ans.push_back(make_pair(x, y));
	}
	puts("Yes");
	for(auto i : ans){printf("%d %d\n",i.first,i.second);}
	return;
}

signed main(){
	int T = read();
	while(T--){solve();}
	return 0;
}
/*
2
10
123 81 70 107 100 70 117 128 113 91
10
126 92 58 113 81 126 115 80 107 102

10
90 87 80 113 110 69 154 95 88 114
10
110 108 95 108 143 38 49 111 138 100

*/
