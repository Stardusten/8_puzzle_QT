# 8_puzzle_QT

大一课设，八数码问题，GUI 中`BFS`、`A_star`、`DFS`、`IDDFS`、`IDA_star` 每种算法只展示了一个版本，实际上还有很多略作改动的版本

1. 所有判重均使用自己实现的 `bitmap`

2. 尝试使用 `Cantor Expansion` 和 *压位为 long* 两种编码方式（性能差不多）

3. 尝试使用 *错位数*、*全体曼哈顿距离（含 0）*、*全体曼哈顿距离（不含 0）* 三种启发函数

4. 尝试使用 `priority-queue + bitmap` `fhq_treap + bitmap` `double-STL-map` 三种方式实现 *A_star* 算法

5. 尝试改变 f(x)=Ag(x)+Bh(x) 中 A、B 的系数，并观察其对搜索过程的影响

6. 使用 QT5 制作了简单的图形界面，能画出 `BFS` 和 `A_star` 搜索过程的状态树（深度大于 5 时过于密集，效果不好）
