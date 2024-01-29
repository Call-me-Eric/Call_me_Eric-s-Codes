#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x  =(x << 1) + (x <<3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
int n, m;
struct BIT{
	int c[maxn];
	inline int lowbit(int x){return x & (-x);}
	void upd(int x,int add){for(;x <= n;x += lowbit(x))c[x] += add;}
	int qry(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
}tr;
struct query{
	int x, y, id;
	query(int x = 0,int y = 0,int id = 0):x(x),y(y),id(id){}
	friend bool operator < (query a,query b){return a.x != b.x ? a.x < b.x : (a.y != b.y ? a.y < b.y : a.id < b.id);}
}q[maxn];
vector<int> Y;
bool ans[maxn];
bool book[maxn];
signed main(){
	n = read(); m = read();
	for(int i = 1;i <= n;i++){q[i].x = read();Y.push_back(q[i].y = read());q[i].id = 0;}
	for(int i = 1;i <= m;i++){q[i + n].x = read();q[i + n].y = read();q[i + n].id = i;}
	sort(Y.begin(),Y.end());Y.erase(unique(Y.begin(),Y.end()),Y.end());sort(q + 1,q + 1 + m + n);
	int u = 0, lstx = -1;
	for(int i = 1;i <= n + m;i++){
		int y = upper_bound(Y.begin(),Y.end(),q[i].y) - Y.begin();
		if(!q[i].id){
			int dir = u - tr.qry(y), d = q[i].x - q[i].y;
			if(d < dir){
				if(!book[y]){book[y] = 1;tr.upd(y,1);}
			}
			else{if(d > dir && lstx != q[i].x){u++;lstx = q[i].x;}}
		}
		else{
			if(q[i].x == q[i - 1].x && q[i].y == q[i - 1].y && !q[i - 1].id){ans[q[i].id] = 0;continue;}
			if(q[i].x == lstx){ans[q[i].id] = 1;continue;}
			if((!book[y] || Y[y - 1] != q[i].y) && q[i].y + u - tr.qry(y) == q[i].x){ans[q[i].id] = 0;continue;}
			ans[q[i].id] = 1;
		}
	}
	for(int i = 1;i <= m;i++)puts(ans[i] ? "WIN" : "LOSE");
	return 0;
}
/*
10 40

63 30
80 85
49 82
76 86
3 4
90 60
55 69
25 36
25 3
46 63

58 85
68 60
67 89
33 73
93 8
85 4
54 100
63 87
31 31
28 67
40 94
57 91
0 91
9 80
65 3
77 61
64 0
66 58
58 36
81 60
34 41
96 67
8 77
41 39
7 44
77 15
73 49
3 53
57 95
99 60
47 43
19 24
32 17
34 14
81 42
44 44
1 21
59 34
73 22
64 46

88 61
63 46
30 6
66 15
42 36
77 14
36 60
10 27
33 19
42 63
1 58
9 55
94 56
37 96
2 13
94 59
72 83
30 52
33 17
3 29
1 64
3 63
26 11
95 69

*/
