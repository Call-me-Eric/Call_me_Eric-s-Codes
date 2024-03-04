#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
stack<int> stk;
queue<int> que;
priority_queue<int> pr;
int n;
bool book1 = true, book2 = true, book3 = true;
signed main(){
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	n = read();int opt, u;
	for(int i = 1;i <= n;i++){
		opt = read(); u = read();
		if(opt == 1){
			pr.push(u);stk.push(u); que.push(u);
		}
		else{
			if(stk.top() != u){book1 = false;}
			if(que.front() != u){book2 = false;}
			if(pr.top() != u){book3 = false;}
			stk.pop(); que.pop(); pr.pop();
		}
	}
	puts(book1 ? "YES" : "NO");
	puts(book2 ? "YES" : "NO");
	puts(book3 ? "YES" : "NO");
	return 0;
}

