# SAM学习笔记

在开始之前，先给一个画出 `SAM` 的网站：[link](https://yutong.site/sam/)

## SAM是个啥？

- `SAM` 是一个可以接受一个字符串 $S$ 的所有后缀，且最小的 `DFA`。

- `SAM` 是一个 `DAG`，其中节点被称为状态，而变被称为转移。每条边上都有一个字符。
- `SAM` 还应当满足以下性质：
  - 一个 `SAM` 从同一个节点出发，经过的所有（出）边所标记的字符（都是字符集中的字符）各不相同。
  - 一个 `SAM` 有多个终止节点，每次转移到一个终止节点的时候，将经过的边上的字母组合起来，就会形成一个 $S$ 的后缀。
  - 在满足了以上的性质的前提下，`SAM` 最小。

- `SAM` 能够在 $O(n)$ 的时空复杂度记录下所有的信息。
- `SAM` 可以计算每个子串出现的次数和有多少个不同的子串。

## 怎么构建SAM？

这里我们就需要引出一个东西：$endpos(t)$  

**定义1**：设 $t$ 是 $S$ 的一个子串，那么 $endpos(t)$ 就是所有 $t$ 在 $S$ 中子串的结束位置组成的集合。

举个栗子：对于 $S=aabab$ 这个字符串，我们有：
$$
endpos(a)=\{1,2,4\}\\
endpos(aa)=\{2\}\\
endpos(aab)=\{3\}\\
endpos(aaba)=endpos(aba)=endpos(ba)=\{4\}\\
endpos(aabab)=endpos(abab)=endpos(bab)=\{5\}\\
endpos(b)=endpos(ab)=\{3,5\}\\
$$
然后我们发现，有的子串的 $endpos$ 相同，比如说 $b$ 和 $ab$。

**定义2**：我们定义两个子串为一个等价类，当且仅当两个子串的 $endpos$ 相同。

然后我们将每一个可能的 $endpos$ 值都做成一个节点，然后我们会发现，在同一个等价类的子串在 `SAM` 上的终止位置相同。

然后我们给出一些重要结论：

**引理1**：如果 $A,B(|A|\le|B|)$ 都是字符串 $S$ 的子串，两者在同一个等价类（$endpos(A)=endpos(B)$）当且仅当 $A$ 的每次出现都是以 $B$ 的后缀形式出现。

**引理2**：如果 $A,B(|A|\le|B|)$ 都是字符串 $S$ 的子串，那么要不然 $endpos(A)\cap endpos(B)=\emptyset$，要不然 $endpos(A)\subsetneq endpos(B)$。

**引理3**：如果将一个等价类中所有的子串排序，那么有

- 每一个较短的子串都是较长的子串的子串。
- 所有子串的长度连续且会覆盖 $[x,y]$ 中的所有整数。

**定义3**：我们定义 $len(t)$ 表示在等价类 $t$ 中最长的子串 $w$ 的长度 $|w|$。

**定义4**：我们定义后缀链接 $link(t)$ 是满足 $endpos(link(t))\neq endpos(t)$ ，且满足等价类 $link(t)$ 的最长子串是等价类 $t$ 的最长子串的子串 的等价类。不难发现，刚刚的 **引理3** 的第二条可以表示成：覆盖 $[len(link(t))+1,len(t)]$ 中的所有整数。

**引理4**：所有后缀链接构成一颗根节点为起始节点 $t_0$ 的（指向根的）树。

**引理5**：通过 $endpos$ 构造的树和通过 $link$ 构造的树是相同的。

## 构造算法

对于一个节点（等价类 $t$），我们只需要记录以下三个内容：$len(t),link(t),nxt_t[]$。

构造 `SAM` 可以逐个加入字符并维护。

首先构造初始（虚拟）状态 $t_0$，编号为 $0$。我们强制定义 $len(0)=0,link(0)=-1$。

然后考虑怎么增加一个字符 $c$。

- 首先设 $last$ 表示添加字符之前整个字符串的状态（显然最开始 $last=0$）
- 然后创建一个新的状态 $cur$，然后 $len(cur)\gets len(last)+1$。但是 $link(cur)$ 不知道怎么办？
- 我们设 $p\gets last$，然后循环操作找到 $q$：
  - 如果 $p==-1$（即到达虚拟节点），那么令 $q\gets0$ 并退出。
  - 如果 $p$ 有 $c$ 的转移，那么让 $q$ 为 $nxt_{p,c}$ 并退出。
  - 否则让 $nxt_{p,c}=cur$，然后 $p\gets link(p)$。

- 如果 $q=0$ 或者 $len(p)+1=len(q)$，那么令 $link(cur)=q$ 并退出。
- 否则 **复制** 状态 $q$ 到一个新的状态 $clone$，$clone$ 保留 $q$ 除了 $len(q)$ 之外的所有信息。令 $len(clone)=len(p)+1$。
- 然后 $link(cur)\gets clone$，$link(q)\gets clone$。
- 然后从找到的 $p$ 开始，进行循环操作：
  - 如果 $p==-1$ 或者 $nxt_{p,c}\neq q$，那么退出。
  - 否则让 $nxt_{p,c}\gets clone$，然后让 $p\gets link(p)$。
- 无论是哪种情况，最后都应让 $last\gets cur$。

## 时空复杂度

经证明，一个 `SAM` 的点数最多有 $2|S|-1$ 个，转移边最多有 $3n-4$ 条。

构造算法的时间复杂度是 $O(n)$ 的。

~~虽然我不会证QAQ~~

## 模板

知道了算法，赶紧来写一道[模板](https://www.luogu.com.cn/problem/P3804)吧！

个人代码：

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	int x = 0,f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
char ch[maxn];
int n, cf[maxn * 2], a[maxn * 2];
struct SAM{
	int tot, last, rt;
	struct node{
		int link, len, siz;
		unordered_map<char,int> nxt;
	}d[maxn * 2];
	void init(){rt = tot = last = 0;d[rt].link = -1;d[rt].nxt.clear();}
	void insert(char ch){
		int cur = ++tot;d[cur].siz = 1;
		d[cur].len = d[last].len + 1;
		int p = last;
		while(p != -1 && !d[p].nxt[ch]){
			d[p].nxt[ch] = cur;p = d[p].link;
		}
		if(p == -1){d[cur].link = 0;last = cur;return;}
		int q = d[p].nxt[ch];
		if(d[q].len == d[p].len + 1){d[cur].link = q;last = cur;return;}
		int clone = ++tot;
		d[clone] = d[q];d[clone].len = d[p].len + 1;d[clone].siz = 0;
		while(p != -1 && d[p].nxt[ch] == q){d[p].nxt[ch] = clone;p = d[p].link;}
		d[cur].link = d[q].link = clone;
		last = cur;
	}
	ll calc(){
		ll ans = -1;
		for(int i = 0;i <= tot;i++){cf[d[i].len]++;}cf[0] = 0;
		for(int i = 1;i <= n;i++)cf[i] += cf[i - 1];
		for(int i = 0;i <= tot;i++)a[cf[d[i].len]--] = i;
		for(int i = tot;i;i--){
			int p = a[i];
//printf("a[%d] = %d,link = %d,siz = %d\n",i,a[i],d[p].link,d[p].siz);
			d[d[p].link].siz += d[p].siz;
			if(d[p].siz > 1){ans = max(ans,(ll)d[p].siz * d[p].len);}
		}
		return ans;
	}
	void DEBUG(){
		for(int p = 0;p <= tot;p++){
			printf("p = %d:\nlink = %d,siz = %d,len = %d\n",p,d[p].link,d[p].siz,d[p].len);
			for(char j = 'a';j <= 'z';j++){
				if(d[p].nxt[j]){
					printf("%c -> %d\n",j,d[p].nxt[j]);
				}
			}
		}
	}
}sam;
signed main(){
	scanf("%s",ch + 1); n = strlen(ch + 1);
	sam.init();
	for(int i = 1;i <= n;i++){sam.insert(ch[i]);}
	printf("%lld\n",sam.calc());
//	sam.DEBUG();
	return 0;
}
~~~

