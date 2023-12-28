#include <cstdio>
int arr[100005];
int main()
{
	freopen("ill.in","r",stdin);
	freopen("ill.out","w",stdout);
	int n;
	double ans = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", arr + i);
	for (int i = 1; i < n; i++)
		ans += (double)arr[i] / (arr[i] + arr[0]);
	printf("%.3lf\n", ans + 1);
	return 0;
}
