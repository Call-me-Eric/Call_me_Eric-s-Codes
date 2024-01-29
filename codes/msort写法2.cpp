//mosrt 
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
#define N  10005
int a[N], b[N];

void msort(int l,int r){
	if(l == r) return ;
	int m = (l + r) / 2;
	msort(l, m), msort(m + 1, r);
	for(int i = l, j = m + 1, k = l; k <= r; ++k)
		if(i <= m &&(a[i] <= a[j] || j > r))
			b[k] = a[i++];
		else
			b[k] = a[j++];
	for(int i = l; i <= r; i++)
		a[i] = b[i];
}
int main(){
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	msort(1, n);
	for (int i = 1; i <= n; i++)
		cout << a[i] << ' ';
}
