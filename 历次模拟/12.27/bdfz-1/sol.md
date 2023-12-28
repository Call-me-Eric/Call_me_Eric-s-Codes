# 线图 题解

首先按照连通块分开讨论

如果度数最大 $\leq 2$，要不是环要不是链，环每次不变，链每次会少一个。

如果度数最大 $\geq 5$，则 $L(G)$ 中存在 $K_5$，而可以发现，对于 $K_n$，选择一个边，与它相邻有 $2n-4$ 条其它边，所以 $K_{1,2n-4}\subseteq L(K_n)$，进而 $K_{2n-4}\subseteq L(L(K_n))$，所以一旦 $n\geq 5$，$L^k(K_n)$ 的点数就会指数级增长，这个情况下就不存在 $s$ 使得收敛。

如果度数最大 $=4$，可以发现 $K_5\subseteq L^3(K_4)$，故同理。

如果度数最大 $=3$，且图不是 $K_{1,3}$，那么选了一个度为 $3$ 的节点，其邻居一定有一个度 $\geq 2$ 的节点。取这三条边以及那个邻居的另一条边，得到图 $P\subseteq G$，其中 $P$ 是边集为 $\{(1,2),(1,3),(1,4),(2,5)\}$ 的图。可以发现 $K_4\subseteq  L^4(P)$，所以也和上面同理。

最后 $L(K_{1,3})=K_3$，所以和一个三元环相同。



<div STYLE="page-break-after: always;"></div>

# 方程组 题解

考虑一个 $a$ 时刻消失的方程组 $\boldsymbol v_1\cdot\boldsymbol x=k_1$，和一个 $b$ 时刻消失的方程组 $\boldsymbol v_2\cdot\boldsymbol x=k_2$

如果某一时刻这两个方程组都生效，且假设 $a\leq b$，那么实际上把这第一个方程替换为  $(\boldsymbol v_1+p\boldsymbol v_2)\cdot\boldsymbol x=k_1+pk_2$ 之后解集不变。

于是直接按照出现时间把所有方程依次加入到类似线性基的结构里面，每次把消失时间早的换出去就好。

如果最后出现了 $0=k$ 这样的方程就无解。如果线性基不是满的就多解，否则 $O(n^2)$ 消一下上三角矩阵即可

总复杂度 $O((n+q)n^2)$



<div STYLE="page-break-after: always;"></div>

# 风扇 题解

实际上就是判断 $n$ 次单位根有没有大小为 $k$ 的子集和为 $0$，如果有则构造。

结论实际上是当且仅当 $k,n-k$ 都能表示为 $n$ 的素因子的非负整数系数的线性组合时存在子集和为 $0$，构造方案见 [On Vanishing Sums of Distinct Roots of Unity DOI:10.1515/INTEG.2010.031](http://www.kurims.kyoto-u.ac.jp/EMIS/journals/INTEGERS/papers/k31/k31.pdf)，论文很简洁，直接对着看就好

~~不过关于必要性引用的那个引理我也看不懂，接受它是对的就好了~~

复杂度瓶颈在于背包，也就是 $O(n\omega(n))$

## bonus: checker 的实现

实际上判断 $n$ 次单位根的线性组合是否为 $0$，只需要看系数构成的多项式能不能被 $n$ 次分圆多项式整除就好，checker 使用了几个随机选取的素模数进行多项式除法计算，应该除非对着卡应该判断的都挺准的。

另外还使用实数判了一下那个和是不是真的 $<\varepsilon$，保守估计 $\varepsilon<100n\varepsilon_{\text{mach}}$，感觉应该判不出错！