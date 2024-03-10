#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f =1 ;char ch = getchar();
	while(ch < '0'||ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
	return x * f;
}
const int maxn = 1e3 + 10;
int n;
int ch[maxn],tmp[maxn << 1];
struct node{int suf, id;friend bool operator < (node a,node b){return a.suf	< b.suf;}}a[maxn];
int r[maxn << 1], rnk[maxn];
bool getans = false;
bool check(){
	int tim = 1,tim2 = 1;
//	puts("try");
//	for(int i = 1;i <= n;i++){putchar('a' + ch[i] - 1);}
//	putchar('\n');
	for(int i = 1;i < n;i++)tim2 *= 10;
	for(int i = n;i;i--){
		a[i].id = i - 1;
		a[i].suf = a[i + 1].suf + tim * ch[i];tim *= 10;
	}
	for(int i = n;i;i--){
		a[i].suf *= tim2;
		tim2 /= 10;
	}
//	for(int i = 1;i <= n;i++){printf("%d ",a[i].suf);}
//	puts("");
	sort(a + 1,a + 1 + n);memset(tmp,0,sizeof(tmp));
	for(int i = 1;i <= n;i++){
		if(rnk[i] != a[i].id)return false;
		tmp[i * 2 - 2] = -1;tmp[i * 2 - 1] = ch[i];
	}
	tmp[n * 2] = -1;
//	for(int i = 0;i <= n * 2;i++)printf("%d ",tmp[i]);
//	puts("");
	for(int i = 1;i < n * 2;i++){
		int j = 1;
		while(i - j >= 0 && i + j <= n * 2 && tmp[i - j] == tmp[i + j])j++;
		if(r[i] != j - 1)return false;
	}
//	puts("success");
	return true;
}
void dfs(int x){
	if(x == n + 1){
		if(check()){getans = true;}
		return;
	}
	if(getans)return;
	for(int i = 1;i <= n;i++){
		ch[x] = i;
		dfs(x + 1);
		if(getans)return;
	}
}

signed main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
int T = read();
while(T--){
	n = read();
	for(int i = 1;i <= n;i++)rnk[i] = read();
	for(int i = 1;i < n * 2;i++)r[i] = read();
	getans = false;
	dfs(1);
	if(!getans)puts("-1");
	else{
		for(int i = 1;i <= n;i++){putchar('a' + ch[i] - 1);}
		putchar('\n');
	}
}
	return 0;
}
