#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define for1(i, a, b) for(int i = a; i <= b; i++)
using namespace std;
struct str{
	int num;	int score;
}a[50005];
int cmp1(str a1, str a2){
	if(a1.score == a2.score) return a1.num <a2.num;
	else return a1.score > a2.score;
}
int main(){
	int n, m, ans = 0, cnt = 0;
	cin >> n >> m;
	m = m * 1.5;
	//if(m >= n) m = n;	//虽然是废话，保险写上 
	//cout << m;
	for1(i, 1, n)	cin >>a[i].num >>a[i].score;
	sort(a+1,a+n+1,cmp1);
	for1(i, 1, n){
		if(i >m){
			if(a[i].score != a[i-1].score )
				break;
		}
		cnt++;
		ans = a[i].score;
	}
	cout << ans << ' ' <<cnt <<endl;
	for1(i, 1, n){
		if(i >m){
			if(a[i].score != a[i-1].score )
				break;
		}
		cout <<a[i].num <<' ' << a[i].score <<endl;
	}	
	return 0;
}

