#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
	return x * f;
}
const int maxm = 100, maxk = 62;
int n, m;
int pos[maxm];
signed main(){
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
	n = read(); m = read();
	for(int i = 1;i <= m;i++){pos[i] = read();}
	sort(pos + 1,pos + 1 + m);
	int ans = 0;
	if(m == 0){
		ans = 1;int x = 1;
		for(int i = maxk;i + 1;i--){
			if(x + (1LL << i) < n){
				ans++;x += (1LL << i);
			}
			else if(x + (1LL << i) == n){
				break;
			}
		}
		ans++;
		printf("%lld\n",ans);
	}
	else if(m == 1){
		int x = pos[m];
		for(int i = maxk;i + 1;i--){
			if(x + (1LL << i) < n){
				ans++;x += (1LL << i);
			}
			else if(x + (1LL << i) == n){
				break;
			}
		}
		ans++;
		for(int i = maxk;i + 1;i--){
			if(x - (1LL << i) > 1){
				ans++;x -= (1LL << i);
			}
			else if(x - (1LL << i) == 1){
				break;
			}
		}
		ans++;
		printf("%lld\n",ans);
	}
	else{
		int x = pos[m];
		for(int i = maxk;i + 1;i--){
			if(x + (1LL << i) < n){
				ans++;x += (1LL << i);
			}
			else if(x + (1LL << i) == n){
				break;
			}
		}
		if(pos[m] != n) ans++;
//		printf("end = %lld\n",ans);
		x = pos[1];
		for(int i = maxk;i + 1;i--){
			if(x - (1LL << i) > 1){
				ans++;x -= (1LL << i);
			}
			else if(x - (1LL << i) == 1){
				break;
			}
		}
		if(pos[1] != 1)ans++;
//		printf("fr = %lld\n",ans);
		for(int i = 1;i <= m - 1;i++){
			x = pos[i];if(pos[i] == pos[i + 1] - 1)continue;
			for(int j = maxk;j + 1;j--){
				if(x + (1LL << j) < pos[i + 1]){
					ans++; x += (1LL << j);
				}
				else if(x + (1LL << j) == pos[i + 1]){
					break;
				}
			}
//			printf("between %lld %lld = %lld\n",i,i + 1,ans);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
