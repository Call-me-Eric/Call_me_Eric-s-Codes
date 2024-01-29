#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 26, maxk = 2.5e6 + 1;
bitset<maxk> b[maxn][maxn * 2];
int n, a[maxn * 2];
bool book[maxn * 2];
int ans[maxn][3];
void main(){
	n = read();
	for(int i = 1;i <= n * 2;i++){a[i] = read();}
	sort(a + 1,a + 1 + n * 2);
	b[0][2].reset();b[0][2].set(0);int sum = 0;book[1] = book[2] = 1;
	for(int i = 3;i <= n * 2;i++){
		sum += a[i];
		for(int j = n - 1;j;j--)
			b[j][i] = b[j][i - 1] | (b[j - 1][i - 1] << a[i]);
		b[0][i].set(0);
	}
	int u = 0x3f3f3f3f, pos = n * 2, j = n - 1;
	for(int i = 0;i <= sum;i++)
		if(b[n - 1][n * 2][i]){u = min(u,max(i,sum - i));}
	cerr << "u = " << u  << endl;
	ans[1][1] = a[1];ans[n][2] = a[2];
	while(j){
		if(b[j][pos - 1][u]) pos--;
		else{
			ans[j + 1][1] = a[pos];book[pos] = 1;
			u -= a[pos];j--;pos--;
		}
	}
	j = n - 1;for(int i = 3;i <= n * 2;i++){if(!book[i])ans[j--][2] = a[i];}
	for(int i = 1;i <= 2;i++){
		for(j = 1;j <= n;j++){
			printf("%d ",ans[j][i]);
		}
		puts("");
	}
	return;
} 
};
bool edmemory;
signed main(){
	auto stclock = clock();
	Call_me_Eric::main();
	auto edclock = clock();
	cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
	cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
	return 0;
}