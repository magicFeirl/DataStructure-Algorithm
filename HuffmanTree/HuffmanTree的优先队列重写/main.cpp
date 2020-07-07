// �����ȫ���˵����������...
// ��������˼·�ǣ�
// ��Ҷ�ڵ㿪ʼ�����Ҹ��ڵ㣬ֱ�����������Ȼ���ж��Ǹ������ҷ�֧��������룬��һ���ݹ�Ĺ���
// ����涨��С�Ҵ�
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct Tree {
    double weight;
    int parent;
    int lch, rch;
};

void huffman_code(Tree *tree, int cur, int parent);

/*
    ���⣺
    1. ���� priority_queue ʱ����ƴд����
    2. �� priority_queue ��Ԫ�رȽϻ�����
    3. �����ȶ��еĵ���Ԫ�ش�С�жϴ���ԭ���� size() > 2��
    4. �� top() ʱ����д����������
        fir = pq.top().first;
        sec = pq.top().second;
        pq.pop();
        pq.pop();

        ���½�������⡣���� frist ��Ȩ��second ���±꣬ʵ��ֻ���õ� second����������һ�� top �����
        �����ҵڶ�С��Ԫ��Ҫ�� pop ������СԪ��
    5. ������˰����� push ��������
*/
void create_tree(Tree *tree, int size){
    priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > pq;
    
    for(int i=1; i<2*size; i++){
        tree[i].lch = tree[i].rch = 0;
        tree[i].parent = 0;
        tree[i].weight = -1;
    }
    
    for(int i=1; i<size+1; i++){
        scanf("%lf", &tree[i].weight);
        pq.push(make_pair(tree[i].weight, i));
    }
    
    for(int i=size+1; i<2*size; i++){
        int fir, sec;
        if(pq.size() >= 2){
            fir = pq.top().second;
            pq.pop();
            sec = pq.top().second;
            pq.pop();
            
            tree[i].lch = fir;
            tree[i].rch = sec;
            tree[i].weight = tree[fir].weight + tree[sec].weight;
            tree[fir].parent = tree[sec].parent = i;
            pq.push(make_pair(tree[i].weight, i));
        }
    }
    
    for(int i=1; i<size+1; i++){
        huffman_code(tree, i, tree[i].parent);
        puts("");
    }
    
    /*
        printf("lch: %d rch: %d parent: %d weight: %f\n",
        tree[i].lch,
        tree[i].rch,
        tree[i].parent,
        tree[i].weight);
    */
}

void huffman_code(Tree *tree, int cur, int parent){
    if(parent){
        huffman_code(tree, parent, tree[parent].parent);
        printf("%d", tree[parent].rch==cur);
    }
}

int main(){
    int size = 3;
    Tree tree[2*3];
    
    create_tree(tree, size);
    
    return 0;
}
