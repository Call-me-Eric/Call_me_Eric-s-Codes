#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e6 + 10;
char ch[maxn];
bool ans[maxn];
int n;

signed main(){
	freopen("soccer.in","r",stdin);
	freopen("soccer.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",ch + 1);
	bool all1 = true, all0 = true;
	for(int i = 1;i <= n && (all1 || all0);i++)
		if(ch[i] == '0')all1 = false;
		else all0 = false;
	if(all0 || all1){
		puts("Yes");
		if(all0){for(int i = 1;i <= n;i++)putchar('R');return 0;}
		if(all1){for(int i = 1;i <= n;i++)putchar('B');return 0;}
	}
	if(ch[1] == '1' || ch[n] == '1'){puts("No");return 0;}
	int cnt = 0, col = 0,i = 1;
	while(ch[i] == '0' && i <= n)i++;
	int r = n;
	while(ch[r] == '0' && r > i)r--;
	cnt = 1;col = 1;i++;
	for(;i <= r;i++){
		if(ch[i] != (col + '0')){
			if(!col){if(cnt == 1){puts("No");return 0;}}
			else{
				for(int j = 0;j <= cnt;j++)ans[i - j] = 1;
				ans[i - cnt - 1] = 0;
			}
			cnt = 1;col = ch[i] - '0';
		}
		else cnt++;
	}
	puts("Yes");
	for(int i = 1;i <= n;i++)putchar(ans[i] ? 'B' : 'R');
	puts("");
	return 0;
}
