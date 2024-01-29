#include<cstdio>
#include<cmath>
using namespace std;
int n, m, pos[51], t;
long long ans;
char s[51];
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++){
		scanf("%d",&pos[i]);
	}
	scanf("%s",s + 1);
	for(int i = 1;i < m;i++){
		t = abs(pos[i] - pos[i + 1]) - 1;
		t = t & 1;
		if(s[i] == s[i + 1] && t){
			ans++;
		}
		else if(s[i] != s[i + 1] && !t)ans++;
	}
	printf("%lld",ans);
	return 0;
}
