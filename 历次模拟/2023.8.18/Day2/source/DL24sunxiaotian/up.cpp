#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 5e4 + 0721;
int n, q;
int ans[N];

inline ll read() {
	ll xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9') 
		xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

struct node {
	ll olda, oldb, newa, newb;
	int id;
	friend bool operator<(node x, node y) {
		if (x.newa != y.newa) return x.newa < y.newa;
		else return x.newb < y.newb;
	}
} anc[N], con[N];

int main() {
	freopen("up.in", "r", stdin);
	freopen("up.out", "w", stdout);
	
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) con[i].olda = read(), con[i].oldb = read();
	for (int i = 1; i <= q; ++i) {
		anc[i].olda = read();
		anc[i].oldb = read();
		anc[i].id = i;
		if (anc[i].olda > anc[i].oldb) {
			anc[i].newb = anc[i].oldb;
			anc[i].newa = anc[i].olda % anc[i].oldb;
		} else if (anc[i].olda < anc[i].oldb) {
			anc[i].newa = anc[i].olda;
			anc[i].newb = anc[i].oldb % anc[i].olda;
		} else {
			anc[i].newa = anc[i].olda;
			anc[i].newb = anc[i].oldb;
		}
		if (!anc[i].newa) anc[i].newa = anc[i].newb;
		if (!anc[i].newb) anc[i].newb = anc[i].newa;
	}
	
	sort(anc + 1, anc + 1 + q);
	
	for (int i = 1; i <= n; ++i) {
		int prs = q;
//		cout << i << "\n";
		while (1) {
//			cout << con[i].olda << " " << con[i].oldb << "%: \n";
//			cout << prs << " ";
			if (con[i].olda > con[i].oldb) {
				con[i].newb = con[i].oldb;
				con[i].newa = con[i].olda % con[i].oldb;
				if (!con[i].newa) con[i].newa = con[i].newb;
				
				while (prs && (anc[prs].newa > con[i].newa || (anc[prs].newa == con[i].newa && anc[prs].newb > con[i].newb))) --prs;
				
				while (prs && anc[prs].newa == con[i].newa && anc[prs].newb == con[i].newb) {
//					cout << "anc: " << anc[prs].newa << " " << anc[prs].newb << " " << anc[prs].olda << " " << anc[prs].oldb << "\n";
//					cout << "con: " << con[i].newa << " " << con[i].newb << " " << con[i].olda << " " << con[i].oldb << "\n";
					if (anc[prs].olda <= con[i].olda && anc[prs].oldb == con[i].oldb) ++ans[anc[prs].id];
					--prs;
				}
				
			} else if (con[i].olda < con[i].oldb) {
				con[i].newa = con[i].olda;
				con[i].newb = con[i].oldb % con[i].olda;
				if (!con[i].newb) con[i].newb = con[i].newa;
				
				while (prs && (anc[prs].newa > con[i].newa || (anc[prs].newa == con[i].newa && anc[prs].newb > con[i].newb))) --prs;
				
				while (prs && anc[prs].newa == con[i].newa && anc[prs].newb == con[i].newb) {
//					cout << "anc: " << anc[prs].newa << " " << anc[prs].newb << " " << anc[prs].olda << " " << anc[prs].oldb << "\n";
//					cout << "con: " << con[i].newa << " " << con[i].newb << " " << con[i].olda << " " << con[i].oldb << "\n";
					if (anc[prs].oldb <= con[i].oldb && anc[prs].olda == con[i].olda) ++ans[anc[prs].id];
					--prs;
				}
				
			} else break;
			if (!prs) break;
			con[i].olda = con[i].newa;
			con[i].oldb = con[i].newb;
		}
	}
	
	for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	
	return 0;
}
