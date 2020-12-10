# 8_puzzle_QT

大一课设，八数码问题

1. 自己实现 `bitmap` 用于判重

2. 尝试使用 *康拓展开* 和 *压位为 long* 两种编码方式（性能差不多）

3. 尝试使用 *错位数*、*全体曼哈顿距离（含 0）*、*全体曼哈顿距离（不含 0）* 三种启发函数

4. 尝试使用 `priority-queue + bitmap` `fhq_treap + bitmap` `double-STL-map` 三种方式实现 *A_star* 算法

5. 尝试改变 f(x)=Ag(x)+Bh(x) 中 A、B 的系数，并观察其对搜索过程的影响（GUI 中有专门的分析工具）

6. 使用 QT5 制作了简单的图形界面，能画出五种算法搜索过程的解答树（深度大于 5 时过于密集，效果不好）

7. GUI 中`BFS`、`A_star`、`DFS`、`IDDFS`、`IDA_star` 每种算法只展示了一种实现，更多实现可在 Others 中找到
