#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
int n, p; 
struct trees{
	int f;
	int tree_size;
	vector<int> c;
}a[401];
int ans = 99999999;
bool book[401];
vector<int> same_dep[401],e[401];
int depth[401],tree_dep;
void getdep(int fa,int root,int dep){
	depth[root] = dep;
	if(dep > tree_dep)tree_dep = dep;
	same_dep[dep].push_back(root);
	if(e[root].size() == 1){
		a[root].f = fa;
		a[root].tree_size = 1;
		return;
	}
	int ans = 0;
	for(int i = 0,len = e[root].size();i < len;i++){
		if(e[root][i] != fa){
			getdep(root,e[root][i],dep + 1);
			a[root].c.push_back(e[root][i]); 
			ans += a[e[root][i]].tree_size;
			a[e[root][i]].f = root;
		}
	}
	a[root].tree_size = ans + 1;
	return;
}
void bookall(int root,int col){
	book[root] = col;
	if(a[root].c.empty())return;
	int j = 0;
	for(int i = 0,len = a[root].c.size();i < len;i++){
		j = a[root].c[i];
		book[j] = col;
		bookall(j,col);
	}
	return;
}
void dfs(int depth,int tot){
	if(depth > tree_dep){//到最后一层 
		if(tot < ans)ans = tot;
		return;
	}
	int j = 0,flag = 0;
	for(int i = 0,len = same_dep[depth].size();i < len;i++){
		j = same_dep[depth][i];
		if(book[j]){
			flag++;
			continue;
		}
		book[j] = 1;
		bookall(j,1);
		dfs(depth + 1,tot - a[j].tree_size);
		book[j] = 0;
		bookall(j,0);
	}
	if(flag == same_dep[depth].size()){//有可能走不到头就回了 
		if(tot < ans)ans = tot;
		return;
	}
}
int main(){
	scanf("%d%d",&n,&p);
	int u = 0,v = 0;
	for(int i = 1;i <= p;i++){
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	getdep(0,1,1);
	dfs(2,a[1].tree_size); 
	printf("%d",ans);
	return 0;
}
/*100 99
2 1
3 2
4 3
5 3
6 3
7 2
8 7
9 7
10 9
11 7
12 2
13 12
14 12
15 12
16 2
17 16
18 17
19 17
20 16
21 2
22 21
23 21
24 21

25 1
26 25
27 26
28 25
29 28
30 25
31 30
32 31
33 31
34 31
35 30
36 35
37 35
38 37
39 37

40 1
41 40
42 41
43 41
44 41
45 41
46 40
47 46
48 40
49 40
50 49
51 40
52 51
53 51
54 40
55 54
56 54

57 1
58 57
59 58
60 58
61 58
62 57
63 62
64 62
65 62
66 57
67 66
68 66
69 66
70 66
71 57
72 71
73 71
74 71
75 74
76 57
77 76
78 76
79 76
80 76

81 1
82 81
83 82
84 83
85 82
86 85
87 81
88 87
89 88
90 88
91 87
92 87
93 92
94 92
95 94
96 92
97 96
98 96
99 92
100 99
ans=55
*/
