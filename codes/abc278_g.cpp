#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x  =(x << 1) + (x <<3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 5e3 + 10;
int n, l, r;
int sg[maxn];
bool book[maxn];
set<pair<int,int> > st;
void split(int a,int b){
	for(auto it = st.begin();it != st.end();it++){
		if(it->first <= a && b <= it->second){
			int u = it->first, v = it->second;
			st.erase(it);
			if(u <= a - 1)st.insert(make_pair(u, a - 1));
			if(b + 1 <= v)st.insert(make_pair(b + 1, v));
			return;
		}
	}
}
pair<int,int> getseg(){//find a seg to let the SG gets 0
	int nsg = 0;	
	for(auto i : st){nsg ^= sg[i.second - i.first + 1];}
	for(auto it = st.begin();it != st.end();it++){
		auto i = *it;
		int x = nsg ^ sg[i.second - i.first + 1];
		for(int j = i.first;j + l - 1 <= i.second;j++){
			if((x ^ sg[j - i.first] ^ sg[i.second - j - l + 1]) == 0){
				return make_pair(j,j + l - 1);
			}
		}
	}
}
signed main(){
	cin >> n >> l >> r;
	if(l != r || (n & 1) == (l & 1)){
		cout << "First" << endl;
		int x = ((n & 1) == (l & 1)) ? l : (l + 1);
		cout << n / 2 - x / 2 + 1 << ' ' << x << endl;
		while(1){
			int a, b; cin >> a >> b;
			if(a == 0 && b == 0)return 0;
			cout << n - a - b + 2 << ' ' << b << endl;
		}
	}
	for(int i = l;i <= n;i++){
		for(int j = 0;j <= n;j++)book[j] = 0;
		for(int j = 0;j + l <= i;j++){book[sg[j] ^ sg[i - j - l]] = 1;}
		int x = 0;while(book[x])x++;
		sg[i] = x;
	}
	int a, b;
	st.insert(make_pair(1, n));
	if(sg[n]){
		cout << "First" << endl;
	}
	else{
		cout << "Second" << endl;
		cin >> a >> b;b = a + b - 1;
		split(a, b);
	}
	while(1){
		auto x = getseg();
		cout << x.first << ' ' << x.second - x.first + 1 << endl;
		split(x.first,x.second);
		cin >> a >> b;
		if(a == 0 && b == 0)return 0;
		b = a + b - 1;
		split(a, b);
	}
	return 0;
}
