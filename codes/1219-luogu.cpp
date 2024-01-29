#include<cstring>
#include<cstdio>
using namespace std;
int ans[100][10], t[9];
int k = 1, f = 1, a[101], b[101], c[101];
bool flag = false;
int n;
void dfs(int step){//step 是第几行 
	if(step == n + 1){for(int i = 1;i <= n;i++)ans[k][i] = t[i];k++;return;}
	for(int i = 1;i <= n;i++){
		if(a[i] || b[step + i] || c[step - i + 14])continue;
		a[i] = b[step + i] = c[step - i + 14] = true;
		t[f++] = i;
		dfs(step + 1);
		t[--f] = 0;
		a[i] = b[step + i] = c[step - i + 14] = false;
	}
}
int main(){	
	scanf("%d",&n);
	int m;
	f = k = 1;
	dfs(1);
	for(m = 1;m <= 3;m++){for(int i = 1;i <= n;i++)printf("%d ",ans[m][i]);putchar('\n');}
	printf("%d",k - 1);
	return 0;
}
