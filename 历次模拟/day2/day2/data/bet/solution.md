首先 $a_i$ 的 sg 值就是 $a_i\bmod (x+1)$。

考虑我们所求 $ans_j=[\oplus_{i=1}^n (a_i\bmod (j+1))>0]$。考虑怎么求 $\oplus_{i=1}^n (a_i\bmod(j+1))$。

考虑分别求每一位，求 $2^k$ 次方时，就相当于询问有哪些 $(a_i\bmod(j+1))\bmod 2^{k+1}\ge 2^k$，我们统计 $c_i$ 为 $i$ 的出现次数，那么枚举 $\lfloor\frac{a_i}{j+1}\rfloor$，相当于一段 $c_i$ 的区间和，共有 $\frac{n}{j+1}$ 段，前缀预处理即可。

复杂度 $O(n\log^2n)$。