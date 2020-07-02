#include <stdio.h>
#include <stdlib.h>

// huffman ��㶨��
// ���ڵ㡢�����ӽڵ㡢Ȩֵ�Ǳ���ģ��������󻹿������������Ա
typedef struct _HTNODE{
    int parent;
    int lch, rch;
    double weight;
}HTNODE, *PHTNODE;

// huffman tree
// ����һ����������Ҷ�ӽ�����
typedef struct _HTTREE{
    PHTNODE nodes;
    int size;
}HTTREE, *PHTREE;

void huffman_code(PHTNODE nodes, int cur, int parent);

// ��δʹ�õĽڵ���ѡ��������С��Ȩֵ
void select(PHTREE tree, int end, int *fri, int *sec){
    double v1, v2;
    v1 = v2 = 1 << 30;
    
    for(int i=1; i<=end; i++){
        // ע������ !tree->nodes[i].parent����һ���жϸýڵ��Ƿ����ӽڵ���Ƿ�ʹ��
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
    // ���� n ����㣬����� n - 1 �κϲ������� n - 1�κϲ��ֻ���� n ����㣬����һ���� 2n - 1�����
    // Ϊ�˱��뷽�����ǵĽڵ������±��Ǵ� 1 ��ʼ�ģ�����Ҫ���� 2 * n ���ռ�
    // ���нڵ��±귶Χ�� [1, 2n) ֮��
    tree->nodes = (PHTNODE)malloc(sizeof(HTNODE) * 2 * size);
    
    // ��ʼ�����ֵ
    for(int i=1; i<2*size; i++){
        tree->nodes[i].parent = 0;
        tree->nodes[i].lch = tree->nodes[i].rch = 0;
        tree->nodes[i].weight = 0;
    }
    
    // ���������Ҷ�ӽ�������ȡ��Ӧ��Ҷ�ӽ��Ȩֵ
    for(int i=1; i<=size; i++){
        double k; // �������� double ���ͣ�����������С�������
        scanf("%lf", &k);
        tree->nodes[i].weight = k;
    }
    
    // ��ɭ����ѡ��������С�Ľ�㣬�����ǵ�Ȩֵ��Ϊ����ϳ�һ�����������뵽ɭ�֣�ͬʱ������
    // �ӽڵ�ĸ��ڵ����
    for(int i=size+1; i<2*size; i++){
        int fri, sec;
        
        select(tree, i-1, &fri, &sec);
        
        // ���ڵ��ȨֵΪ�����ӽڵ��Ȩֵ��
        tree->nodes[i].weight = tree->nodes[fri].weight + tree->nodes[sec].weight;
        // ������С����������
        tree->nodes[i].lch = fri;
        tree->nodes[i].rch = sec;
        // ���¸��ڵ�
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

// �ݹ��ӡ����
// ���ｫ�����Ϊ 0���ұ���Ϊ 1����ӡ������Ǵ�Ҷ�ӽ�㿪ʼһֱ���ݵ����ڵ㣬Ȼ��
// �ж��ӽڵ������ҽڵ㣬��������ӡ 0�������ӡ 0
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
