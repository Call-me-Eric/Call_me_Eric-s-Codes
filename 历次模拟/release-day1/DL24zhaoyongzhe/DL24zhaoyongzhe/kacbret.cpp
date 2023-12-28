#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
int n, cnt;
string ch;
bool book[maxn];
string ans;
void dfs(int l){
	string tmp = "";for(int i = 1;i <= n;i++)if(!book[i])tmp = tmp + ch[i - 1];
	ans = min(ans,tmp);cnt++;
	if(l <= 0)return;
	if(cnt >= 1e7){cout << ans << endl;exit(0);}
//	cerr << "tmp = " << tmp << " l = " << l << endl;
	for(int i = l;i >= 1;i--)
		if(!book[i] && ch[i - 1] == ')')
		for(int j = i - 1;j >= 1;j--){
			if(ch[j - 1] == '(' && !book[j]){
				book[i] = book[j] = 1;
				dfs(j - 1);
				book[i] = book[j] = 0;
			}
		}
//	dfs(l + 1);
}
signed main(){
	freopen("kacbret.in","r",stdin);
	freopen("kacbret.out","w",stdout);
	cin >> ch;ans = ch;n = ch.length();
	dfs(n);cout << ans;
	return 0;
}
