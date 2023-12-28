## <center>Bet</center>

### 题目描述

YYX 是个无忧无虑的女孩子。

这天，YYX 在空地上发现了一个长度为 $n$ 的正整数数组，她觉得这个数组很有意思！所以她找到了 Dr. Wu，希望和他在这个数组上做游戏。

具体的，YYX 和 Dr. Wu 事先指定了一个正整数 $x$，并在数组上轮流操作，YYX 先手：当一个玩家操作时，她将选择数组中一个大于 $0$ 的元素 $a_i$ 并选择一个 $[1,\min(a_i,x)]\cap \mathrm {Z}$ 中的数 $j$，令 $a_i$ 减去 $j$，不能操作者负。

现在，YYX 找到了你，希望你对于每个 $1\le x\le n$，求出若两个人都使用最优策略，是先手必胜还是后手必胜。 

### 输入格式（bet.in）

第一行一个正整数 $n$ 表示数组长度。

第二行一个长度为 $n$ 的正整数序列 $a_i$，表示 YYX 发现的数组。

### 输出格式（bet.out）

输出 $n$ 行，若 $x=i$ 时先手必胜，则第 $i$ 行输出一行 `First`，否则输出一行 `Second`。

### 输入输出样例

#### 输入1

```
4
1 2 3 4
```

#### 输出1

```
Second
First
Second
First
```

#### 输入2

```
5
1 2 3 2 2
```

#### 输出2

```
Second
First
Second
Second
Second
```

#### 样例输入/输出 3

见下发文件中的 `ex_bet3.in/ex_bet3.ans`。

### 数据范围

对于全部的数据，$1\le n\le 5\times 10^5,1\le a_i\le n$。

$\text{subtask1 10pts}$，$n\le 8$。

$\text{subtask2 20pts}$，$n\le 200$。

$\text{subtask3 30pts}$，$n\le 2000$。

$\text{subtask4 40pts}$，无特殊限制。