// 没搞懂红黑树，来写下最简单的 BST
// 2020年6月26日14:15:27

// 看了下以前参考别人博客的代码，发现自己写错了。。。
// 2020年6月26日15:43:36 不过现在已经改过来了。
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int TREE_DATA;

typedef struct _NODE{
    TREE_DATA val;
    struct _NODE *left;
    struct _NODE *right;
    struct _NODE *parent;
}NODE, *PNODE;

typedef void (*TVE_FUNC)(PNODE);

typedef struct _TREE{
    int size;
    
    PNODE root;
}TREE, *PTREE;

void init_tree(PTREE tree){
    tree->size = 0;
    tree->root = NULL;
}

static PNODE create_node(TREE_DATA val){
    PNODE node = (PNODE)malloc(sizeof(NODE));
    
    if(!node){
        return NULL;
    }
    
    node->val = val;
    node->right = node->left = node->parent = NULL;
    
    return node;
}
// 增
int insert(PTREE tree, TREE_DATA val){
    PNODE node = create_node(val);
    
    if(!node){
        return 0;
    }
    
    if(!tree->root){
        tree->root = node;
    }else{
        PNODE curr_node = tree->root;
        while(curr_node){
            TREE_DATA curr_val = curr_node->val;
            
            if(curr_val > val){
                if(!curr_node->left){
                    curr_node->left = node;
                    curr_node->left->parent = curr_node;
                }else{
                    curr_node = curr_node->left;
                }
            }else if(curr_val < val){
                if(!curr_node->right){
                    curr_node->right = node;
                    curr_node->right->parent = curr_node;
                }else{
                    curr_node = curr_node->right;
                }
            }else{
                return 0;
            }
        }
    }
    
    tree->size++;
    
    return 1;
}

// 查
PNODE find_node(PNODE node, TREE_DATA val){
    while(node){
        TREE_DATA curr_val = node->val;

        if(curr_val > val){
            node = node->left;
        }else if(curr_val < val){
            node = node->right;
        }else{
            return node;
        }
    }
    
    return NULL;
}

// 找到最小结点
PNODE find_min(PNODE node){
    // 先前这里写的是 node，错误在于如果当前节点只有一个右节点或没有子节点的话会导致返回的左节点为 NULL
    // 而实际上这种情况下最下的结点应该是自身
    while(node->left){ 
        node = node->left;
    }
    
    return node;
}

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

void preorder(PNODE node, TVE_FUNC func){
    if(node){
        func(node);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

void inorder(PNODE node, TVE_FUNC func){
    if(node){
        inorder(node->left, func);
        func(node);
        inorder(node->right, func);
    }
}

void prt_node_val(PNODE node){
    printf("%d ", node->val);
}

int main(){
    TREE tree;
    TREE_DATA data[] = {1, 0, 3, 5, 6, 10, 9, 8, 7, 13},
     size = sizeof(data) / sizeof(data[0]);
    
    init_tree(&tree);
    
    for(int i=0; i<size; i++){
        insert(&tree, data[i]);
    }
    
    //delete_node(&tree, 10);
    //delete_node(&tree, 11);
    delete_node(&tree, 3);
    //delete_node(&tree, 1);
    preorder(tree.root, prt_node_val);
    printf("\n");
    inorder(tree.root, prt_node_val);
    printf("\n");
    printf("find value 6: %p", find_node(tree.root, 6));
    printf("\n");
    
    return 0;
}
