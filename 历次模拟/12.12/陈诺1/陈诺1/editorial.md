# Chess

- 算法 1

我会搜索！状压 $2^n$ 个格子的状态进行 dfs，时间复杂度 $O(n2^n)$，期望得分 $25$。

- 算法 2

我会特殊性质！注意到任何状态经过若干次操作后都可以变为全黑，因此答案即为 $2^{nm}$。

结合算法 1 期望得分 $50$。

- 观察 1

考虑一个格子，如果它被反色过，显然它的颜色会和其四周所有格子的颜色相同。

证明：如果在这次反色之前它们颜色相同，则它们都会被反色，否则只有这个格子被反色。

因此我们可以知道有哪些格子的初始颜色可以与最终颜色不同。

- 算法 3

容易发现该条件同样充分，答案即为 $2^c$，其中 $c$ 为可以反色的方格数。

# Sequence

- 算法 1

我会枚举！时间复杂度 $O(n^n)$，期望得分 $20$。

- 算法 2

我会状压 DP！记 $f_{x,S}$ 为放完 $\leq x$ 的数，将集合 $S$ 的位置放完的序列贡献，期望得分 $40$。

- 算法 3

我会 DP！注意到从前往后放数时，新增的贡献只和最后三个数有关。

因此我们可以设 $f_{x,y,z}$ 为放完前 $x$ 个数，$a_{x-1}=y$，$a_{x-2}=z$ 的序列贡献。

状态数 $O(n^3)$，转移数 $O(n)$，总复杂度 $O(n^4)$，期望得分 $50$。

- 算法 4

我会前缀和！使用前缀和优化算法 3，转移可以优化到 $O(1)$，总复杂度 $O(n^3)$。

期望得分 $60$。

- 算法 5

我会加乘原理！

考虑 $w_i=1$ 的情况，显然每个序列的权值都是 $1$，因此问题等价于统计序列数量。

因此输出 $n^n\bmod 998244353$ 即可，结合算法 4 期望得分 $70$。

- 算法 6

我会写特殊性质！

考虑 $w_i>0$ 的数很少的情况，不难发现 $[w_i+1,w_{i+1}-1]$ 的数都是等效的，相当于将每个数赋权后值域缩小到 $80$，再使用算法 4 即可，结合算法 4,5 期望得分 $80$。

- 算法 7

我会 FFT！

出题人猜到肯定会有 FFT 大师，于是留了一档做法给 $O(n^2\log n)$ 和极大常数的 $O(n^2)$。

- 算法 8

我会减少状态！由于计算答案只和 $\max$ 有关，考虑直接记录取到最大值的位置和最大值本身且暂时不考虑它后面的所有数，状态数降低到 $O(n^2)$。

枚举下一个取到最大值的位置转移即可。

直接做是 $O(n^3)$ 的，使用前缀和优化即可做到 $O(n^2)$。

# Graph

- 算法 1

我会 $k=1$！

每条边都在 $2^{n-2}$ 张子图中，因此答案即为 $2^{n-2}m$，期望得分 $10$。

- 算法 2

我会 $n\leq 12$！

枚举每张导出子图，对于每个 $i$ 求出有 $i$ 个点的导出子图数量，时间复杂度 $O(n^22^n)$。

结合算法 1 期望得分 $20$。

- 算法 3

我会特殊性质！

考虑一个菊花，不选 $1$ 时导出子图边数为 $0$，否则边数即为选择的其余点的数量。

因此恰有 $\binom{n-1}{i}$ 张子图的边数为 $i$，结合算法 1~2 期望得分 $40$。

- 观察 1

我会拆贡献！

将 $\sum |S|^2$ 拆成 $\sum\limits_{i,j\in S}1$。

相当于对于每两/三条边，求出同时含有它们的子图数量，再对每两条边的答案求和。

- 算法 4

我会暴力！

枚举三条边，求出它们的点集的并 $U$，答案记为 $\sum 2^{n-|U|}$。

时间复杂度 $O(m^3)$，结合算法 1~3 期望得分 $50\sim 60$。

- 算法 5

我会分类讨论！

两/三条边的点集并显然不会 $>6$，而 $\leq 6$ 的本质不同情况并没有很多种。

具体地，对于 $k=2$：

- $|U|=2$，两条重复的边。
- $|U|=3$，一条链。
- $|U|=4$，两条没有交集的边，容斥掉上面两种情况即可。

对于 $k=3$：

- $|U|=2$，三条重复的边。
- $|U|=3$，一个三元环。
- $|U|=3$，两条本质不同的边构成一条链。
- $|U|=4$，两条本质不同的边没有交集。
- $|U|=4$，一条链。
- $|U|=4$，一个菊花。
- $|U|=5$，一条长度为 $3$ 的链和与链无交的边。
- $|U|=6$，三条无交的边。

因此问题在一些容斥之后等价于数三元环，时间复杂度 $O(m\sqrt m)$。

# Bracket

- 观察 1

一个括号串能在若干操作后变为合法当且仅当其左右括号数量相等。

- 观察 2

对于一个左括号和右括号数量相等的括号串，我们可以使用如下方法计算答案：

考虑每个前缀，如果其右括号数量多于左括号，则将最后一个右括号通过与非前缀中的数交换变为左括号，依次对每个前缀执行后括号串合法且能取到最小步数。

- 观察 3

注意到在序列前加右括号和在序列后加左括号都使答案不降。

因此一定只会补足某一种括号到两种括号数量相同为止。

- 算法 1

暴力进行补足，然后模拟上述过程。

时间复杂度 $O(n^2m)$，期望得分 $20$。

- 算法 2

考虑在执行该算法后第 $i$ 个左括号的位置是 $\min(a_i,2i-1)$，其中 $a_i$ 为其原序列中位置。

注意到一个左括号只会向左移动，计算这个值即可。

时间复杂度 $O(nm)$，期望得分 $40$。

- 算法 3

对于只有询问的部分，考虑一个区间中所有左括号的贡献。

假设区间左侧已经有 $t$ 个左括号，贡献可以写成 $\sum\min(a_i,2i+2t-1)$。

显然每一项都是关于 $t$ 的一个分段函数。

使用线段树或分块预处理分段函数，结合算法 2 期望得分 $60$。

- 算法 4

考虑分块显然比线段树更容易处理带修改的问题。

对于整块，我们要重构的部分等价于分段函数全部的 $B+1$ 段取值。

使用一些前缀和技巧即可。

时间复杂度 $O((n+m)\sqrt n)$，期望得分 $100$。
