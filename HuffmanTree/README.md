# 哈夫曼树（最优二叉树）

> 提前复习数据结构课的知识

哈夫曼树的建立有四个步骤，总结成口诀就是（[来源：王卓老师的数据结构视频](https://www.bilibili.com/video/av35817244))：

1. 建立森林全是根
2. 选择两小新树
3. 删除两小添新人
4. 重复 2、3 剩单根

简单的解释：

1. 首先输入 N 个值作为根建立的森林
2. 在森林中选择两个权值最小的根（注意这里只是选根，有没有子树无所谓，到时候会合并）
3. 删除这两个根（通常是把 parent 标记为非 0 值以在第 2 步中标记删除），将他们作为左右子树且将他们的权值的和作为新树的根，加入到森林
4. 重复 2、3 步知道森林中只有一个数

思想：

根据权值分配叶子节点的位置，权值越大/小离根的位置也就越近，否则就越远。