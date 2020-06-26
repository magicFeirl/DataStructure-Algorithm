# BST

老早学 CPP6 就接触过 BST，不过那时连链表都没玩明白。后来链表会了，BST 的删除算法还是没搞明白。最后终于找到了一篇自己能看懂的博客把删除算法整明白了。

又是一串流水账式发言。现在啃（摸）《算法4》学到 2-3 树和红黑树，止步不前，不知道自己到底能不能搞懂，随缘。

删除算法：

```c
// 删
// 参考：https://blog.csdn.net/isea533/article/details/80345507
void delete_node(PTREE tree, TREE_DATA val){
    // 先找到要删除的结点
    PNODE node = find_node(tree->root, val); 
    
    if(!node){
        return ;
    }
    
    // 如果要删除的结点有两个子节点
    // 碰到这种情况我们需要转换成只有一个子节点的情况，而后继节点最多只可能有一个节点，所以可以考虑用
    // 后继节点的值代替当前节点的值同时将当前节点指向后继节点
    if(node->right && node->left){
        // 从要删除的节点的右节点开始找最小结点，只在有两个子节点时才会用到
        // 先前这里写成 node 了，但如果这样写的话返回的结点可能会比自身还要小（左节点总是比父节点小）
        // 这里我们的任务是找到要删除的节点的后继（比该节点大的最小结点），所以如果写成 node 的话就是错的
        // 0 1 2 3 => 0 的后继就是 1
        PNODE min_node = find_min(node->right);
        node->val = min_node->val; // 把结点值替换为后继的值（删除了当前的结点值）
        node = min_node; // 把当前节点指向后继，这一步在有两个子节点的情况下很重要
    }
    
    // 不管后继节点有没有子节点，先找
    PNODE child_node = node->left;
    
    if(node->right){
        child_node = node->right;
    }
    
    // 如果后继有子节点，那么把后继的子节点的父节点改为后继节点的父节点，因为稍后我们就会删除后继节点
    if(child_node){
        child_node->parent = node->parent;
    }

    // 如果后继节点没有父节点，也就是根节点的情况，那么把树的根节点更新为子节点（不管有没有）
    if(!node->parent){
        tree->root = child_node;
    // 否则判断后继是左孩子还是右孩子，将父节点的子节点根据相应关系更新
    }else if(node->parent->left == node){ 
        node->parent->left = child_node;
    }else{
        node->parent->right = child_node;
    }
    
    free(node); // 删除当前节点，避免内存泄漏
    tree->size--; // 树的大小减一
}
```

