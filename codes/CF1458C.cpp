#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=  0, f=  1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch =getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e3 + 10;
int n, m;
char ch[maxn * 100];
int a[maxn][maxn][3];
int p[3][2];
int ans[maxn][maxn];
void solve(){
	memset(a,0,sizeof(a));
	memset(p,0,sizeof(p));
	memset(ans,0,sizeof(ans));
	n = read(); m = read();
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			a[i][j][0] = i;a[i][j][1] = j;
			a[i][j][2] = read() - 1;
		}
	}
	p[1][0] = 1;p[2][0] = 2;
	scanf("%s",ch + 1);
	for(int i = 1;i <= m;i++){
		switch(ch[i]){
			case 'L':{p[1][1]--;break;}
			case 'R':{p[1][1]++;break;}
			case 'U':{p[0][1]--;break;}
			case 'D':{p[0][1]++;break;}
			case 'I':{swap(p[1][0],p[2][0]);swap(p[1][1],p[2][1]);break;}
			case 'C':{swap(p[0][0],p[2][0]);swap(p[0][1],p[2][1]);break;}
			default:break;
		}
	}
	for(int i = 0;i < 3;i++){
		while(p[i][1] < 0)p[i][1] += n;
		p[i][1] %= n;
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			int tp[3] = {0};
			for(int k = 0;k < 3;k++)
				tp[k] = (a[i][j][p[k][0]] + p[k][1]) % n;
			ans[tp[0]][tp[1]] = tp[2];
		}
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			printf("%d ",ans[i][j] + 1);
		}
		putchar('\n');
	}
}
signed main(){
	int T = read();
	while(T--)solve();
	return 0;
}
