# 8_puzzle_QT

大一课设，八数码问题，GUI 中只展示了 `BFS`、`A_star`、`DFS`、`IDDFS`、`IDA_star` 五种算法，实际上还有很多略作改动的版本

1. 所有判重均使用自己实现的 `bitmap`

2. 尝试使用 `Cantor Expansion` 和 *压位为 long* 两种编码方式（性能差不多）

3. 尝试使用 *错位数*、*全体曼哈顿距离（含 0）*、*全体曼哈顿距离（不含 0）* 三种启发函数

4. 尝试使用 `priority-queue + bitmap` `fhq_treap + bitmap` `double-STL-map` 三种方式实现 *A_star* 算法

5. 尝试改变 $f(x)=Ag(x)+Bh(x)$ 中 $A$、$B$ 的系数观察搜索过程
