#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x  =(x << 1) + (x <<3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 5e5 + 10;
int sg[maxn];
bool book[maxn];
int n;
char ch[maxn];
int table[40] = {
	1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 9, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4, 8
};
int SG(int x){
	x -= 2;if(x < 0)return 0;
	switch(x){
		case 13:return 0;
		case 15:return 2;
		case 16:return 2;
		case 30:return 2;
		case 33:return 0;
		case 50:return 2;
		default:return table[x % 34];
	}
}
void init(){
	for(int i = 2;i <= n;i++){
		for(int j = 0;j <= n;j++)book[j] = 0;
		for(int j = 0;j <= i - 2;j++){book[sg[j] ^ sg[i - 2 - j]] = 1;}
		int x = 0;while(book[x])x++;
		sg[i] = x;
	}
	for(int i = 0;i <= n;i++){
		if(SG(i) != sg[i]){
			printf("wrong on line %d,sg = %d, SG = %d\n",i,sg[i],SG(i));
		}
	}
}
void solve(){
	n = read();scanf("%s",ch + 1);
	int R = 0, B = 0;
	for(int i = 1;i <= n;i++){
		R += (ch[i] == 'R');
		B += (ch[i] == 'B');
	}
	if(R != B){puts(R > B ? "Alice" : "Bob");return;}
	int ans = 0, j = 1;
	for(int i = 1;i <= n;i = j){
		j = i + 1;
		while(j <= n && ch[j] != ch[j - 1])j++;
		ans ^= SG(j - i);
	}
	puts(ans ? "Alice" : "Bob");
}
signed main(){
	int T = read();
	while(T--){solve();}
	return 0;
}
/*
0 0
1 1 2 0 3 1 1 0 3 3 2 2 4 0 5 2 2 3 3 0 1 1 3 0 2 1 1 0 4 5 2 7 4 0
1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 2 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8
1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8
1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8
1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8
1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8
1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8
1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8
1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1
*/
