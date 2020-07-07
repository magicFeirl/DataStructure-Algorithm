// 最后完全忘了的是输出编码...
// 输出编码的思路是：
// 从叶节点开始往上找父节点，直到到到达根，然后判断是根的左右分支来输出编码，是一个递归的过程
// 这里规定左小右大
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
    问题：
    1. 定义 priority_queue 时单词拼写忘了
    2. 对 priority_queue 的元素比较还不熟
    3. 对优先队列的弹出元素大小判断错误（原先是 size() > 2）
    4. 用 top() 时代码写成了这样：
        fir = pq.top().first;
        sec = pq.top().second;
        pq.pop();
        pq.pop();

        导致结果出问题。这里 frist 是权，second 是下标，实际只会用到 second，而且用了一次 top 后如果
        还想找第二小的元素要先 pop 出队最小元素
    5. 最后忘了把新树 push 到队列中
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
