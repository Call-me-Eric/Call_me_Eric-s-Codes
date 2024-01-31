#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define file(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define inf 0x3f3f3f3f
#define endl "\n"
#define mk make_pair
using namespace std;
const int N = 2e5+10;
struct node{
	bitset<40>code;
	int son;
	int col;
}ip[N],x; 
int n,tot=1;
struct tree{
	int ls,rs;
	int col;
}t[N<<6];
int cover,need,cnt,top;
node ans[N];
bool f;
int white[N<<4],black[N<<4];
inline void insert(node IP){
	int p = 1;
	for(int i = 1;i <= IP.son;i ++){
		if(t[p].col != 0 && t[p].col != IP.col){
			f = 1;
			return ;
		}
		if(IP.code[i]){
			if(t[p].rs == -1) t[p].rs = ++tot;
			p = t[p].rs;
		}else{
			if(t[p].ls == -1) t[p].ls = ++tot;
			p = t[p].ls;
		}
	}
	if(t[p].col != 0 && t[p].col != IP.col){
		f = 1;
		return ;
	}
	t[p].col = IP.col;
}
inline void solve(int u){
	white[u] = (t[u].col==1),black[u] = (t[u].col==-1);
	if(t[u].ls != -1){
		solve(t[u].ls);
		if(white[t[u].ls] == 1)white[u] = 1;
		black[u] += black[t[u].ls];
	}
	if(t[u].rs != -1){
		solve(t[u].rs);
		if(white[t[u].rs] == 1)white[u] = 1;
		black[u] += black[t[u].rs];
	}
}
inline void Find_Ans(int u,node p,int dep,int tp){
//	cout << u << " ls: " << t[u].ls << " rs: " << t[u].rs << endl;
	if(dep)p.code[dep] = tp;
	if(white[u]){
		if(t[u].col == -1){
			f = 1;
			return ;
		}
		if(t[u].ls != -1)Find_Ans(t[u].ls,p,dep+1,0);
		if(t[u].rs != -1)Find_Ans(t[u].rs,p,dep+1,1);
	}else{
		p.son = dep;
		ans[++ cnt] = p;
		cover += black[u];
		return ;
	}
}
bool operator < (node A,node B){
	if(A.son == B.son){
		if(A.col == B.col){
			for(int i = 1;i <= 32;i ++)if(A.code[i] != B.code[i])return A.code[i] < B.code[i];
		}
		return A.col < B.col;
	}
	return A.son < B.son;
}
map<node,int>vis;
int main(){
	cin >> n;
	for(int i = 1;i < N<<4;i ++)t[i].ls = t[i].rs = -1;
	for(int i = 1;i <= n;i ++){
		string s;cin >> s;node temp;
		temp.col = (s[0]=='+'?1:-1);
		int res = 0,st = 1,nw;bool fl = 0;
		for(int j = 1;j < s.size();j ++){
			if(s[j] == '.'){
				nw = st*8;
				while(res){
					temp.code[nw --] = res&1;
					res >>= 1;
				}
				res = 0;
				st ++;
			}
			if(isdigit(s[j]))res = res * 10 + s[j]-48;
			if(s[j] == '/'){
				nw = st*8;
				while(res){
					temp.code[nw --] = res&1;
					res >>= 1;
				}
				res = 0;
				st ++;
				res = 0,fl = 1;	
			}
		}
		if(fl)temp.son = res;
		else{
			nw = st*8;
			while(res){
				temp.code[nw --] = res&1;
				res >>= 1;
			}
			temp.son = 32;
		}
		if(vis[temp])continue;
		vis[temp] = 1;
		ip[++top] = temp;
		if(temp.col == -1)need ++;
	}
	n = top;
	sort(ip+1,ip+1+n);
	for(int i = 1;i <= n;i ++){
		insert(ip[i]);
		if(f==1)return cout<<-1<<endl,0;
	}
	solve(1);
	Find_Ans(1,x,0,0);
	if(need > cover || f == 1)return cout << -1 << endl,0;
	cout << cnt << endl;
	for(int i = cnt;i;i--){
		node tmp = ans[i];
		int st = 1;
		for(int j = 1;j <= 4;j ++){
			int res = 0;
			for(int i = st;i <= st + 7;i ++)res = (res<<1) + tmp.code[i];
			st += 8;
			cout << res;
			if(j!=4)cout<<'.';
		}
			cout << '/' << tmp.son;
		cout << endl;
	}
	return 0;
}
