#include <stdio.h>
#include <stdlib.h>

// huffman 结点定义
// 父节点、左右子节点、权值是必须的，根据需求还可以添加其他成员
typedef struct _HTNODE{
    int parent;
    int lch, rch;
    double weight;
}HTNODE, *PHTNODE;

// huffman tree
// 保存一个结点数组和叶子结点个数
typedef struct _HTTREE{
    PHTNODE nodes;
    int size;
}HTTREE, *PHTREE;

void huffman_code(PHTNODE nodes, int cur, int parent);

// 在未使用的节点中选择两个最小的权值
void select(PHTREE tree, int end, int *fri, int *sec){
    double v1, v2;
    v1 = v2 = 1 << 30;
    
    for(int i=1; i<=end; i++){
        // 注意这里 !tree->nodes[i].parent，这一步判断该节点是否是子节点或是否被使用
        if(!tree->nodes[i].parent && tree->nodes[i].weight < v1){
            v1 = tree->nodes[i].weight;
            *fri = i;
        }
    }
    
    for(int i=1; i<=end; i++){
        if(!tree->nodes[i].parent && tree->nodes[i].weight < v2 && *fri != i){
            v2 = tree->nodes[i].weight;
            *sec = i;
        }
    }
}

void init_tree(PHTREE tree, int size){
    tree->size = size;
    // 共有 n 个结点，会进行 n - 1 次合并，而这 n - 1次合并又会产生 n 个结点，所以一共有 2n - 1个结点
    // 为了编码方面我们的节点数组下标是从 1 开始的，所以要分配 2 * n 个空间
    // 所有节点下标范围在 [1, 2n) 之间
    tree->nodes = (PHTNODE)malloc(sizeof(HTNODE) * 2 * size);
    
    // 初始化结点值
    for(int i=1; i<2*size; i++){
        tree->nodes[i].parent = 0;
        tree->nodes[i].lch = tree->nodes[i].rch = 0;
        tree->nodes[i].weight = 0;
    }
    
    // 根据输入的叶子结点个数获取相应的叶子结点权值
    for(int i=1; i<=size; i++){
        double k; // 这里用了 double 类型，可以用于有小数的情况
        scanf("%lf", &k);
        tree->nodes[i].weight = k;
    }
    
    // 从森林中选出两个最小的结点，将他们的权值和为根组合成一个新树，加入到森林，同时将两个
    // 子节点的父节点更新
    for(int i=size+1; i<2*size; i++){
        int fri, sec;
        
        select(tree, i-1, &fri, &sec);
        
        // 父节点的权值为两个子节点的权值和
        tree->nodes[i].weight = tree->nodes[fri].weight + tree->nodes[sec].weight;
        // 左子树小，右子树大
        tree->nodes[i].lch = fri;
        tree->nodes[i].rch = sec;
        // 更新父节点
        tree->nodes[fri].parent = tree->nodes[sec].parent = i;
    }
    
    /*
    for(int i=1; i<2*size; i++){
        HTNODE node = tree->nodes[i];
        printf("parent: %d weight: %5.2f lch: %d rch: %d idx: %d\n",
        node.parent,
        node.weight,
        node.lch,
        node.rch, i);
    }*/
}

void prt_huffman_code(PHTREE tree){
    for(int i=1; i<=tree->size; i++){
        huffman_code(tree->nodes, i, tree->nodes[i].parent);
        puts("");
    }
}

// 递归打印编码
// 这里将左边作为 0，右边作为 1，打印编码就是从叶子结点开始一直回溯到根节点，然后
// 判断子节点是左右节点，如果是左打印 0，否则打印 0
void huffman_code(PHTNODE nodes, int cur, int parent){
    if(parent){
        huffman_code(nodes, parent, nodes[parent].parent);
        printf("%d", cur == nodes[parent].rch);
    }
}

int main(){
    HTTREE tree;
    
    init_tree(&tree, 3);
    prt_huffman_code(&tree);
    
    return 0;
}
