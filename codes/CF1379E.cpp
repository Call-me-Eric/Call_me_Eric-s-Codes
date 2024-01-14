#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e5 + 10;
int n, k;
int fa[maxn];
void build(int u,int root){
	if(u > n)return;
	int ls = ((u - root) << 1) + root, rs = ((u - root) << 1 | 1) + root;
	if(ls <= n)fa[ls] = u;build(ls,root);
	if(rs <= n)fa[rs] = u;build(rs,root);
}
int cnt;
void build(int u){
	if(cnt == k)return;cnt++;
	fa[u + 1] = fa[u + 2] = u;
	build(u + 2);
}
void printans(int getans = 1){
	if(!getans){puts("NO");}
	else{puts("YES");for(int i = 1;i <= n;i++)printf("%d%c",fa[i]," \n"[i == n]);}
	exit(0);
}

signed main(){
	n = read(); k = read();
	if(!(n & 1)){puts("NO");return 0;}
	if(k == 0){
		if((1 << (int)log2(n + 1)) != n + 1){printans(0);}
		build(1,0);printans();
	}
	if(2 * k + 3 > n){printans(0);}
	build(1);int rest = n - 2 * k - 3;
	build(2 * k + 1,2 * k);
	if((1 << (int)log2(rest + 4)) == rest + 4){printans();}
	if((n - 4) > 6 && k > 1){
		fa[3] = 0;fa[1] = fa[2] = 4;
		printans();
	}
	if(1 << (int)(log2(rest + 6)) != rest + 6){
		fa[3] = 0;fa[1] = fa[2] = (n + 1 - k) / 2 + 2 * k;
		printans();
	}
	printans(0);
	return 0;
}
