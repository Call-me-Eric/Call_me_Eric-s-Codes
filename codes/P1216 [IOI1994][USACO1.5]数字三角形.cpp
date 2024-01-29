#include <iostream>
#include <cstdio>
using namespace std;
int f[1001][1001];
int main(){
    int n, maxx = -0x7ffffff;
	int i, j;
    cin >> n;
    for(i=1;i<=n;i++)
        for(j=1;j<=i;j++)
            cin>>f[i][j];
    for(i = 1; i <= n; i++)
	 	for(j = 1; j <= i; j++)
				f[i][j] += max(f[i-1][j-1], f[i-1][j]);
    for(i = 1; i <= n; i++)
    	maxx = max(maxx,f[n][i]);
    cout << maxx << endl;
    return 0;
}
