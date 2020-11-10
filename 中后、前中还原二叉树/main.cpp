#include <iostream>

using namespace std;

typedef void (*TVE_FUNC)(int);

int tree[] = {-1, 1, 2, 3, 4, 5, -1, 6};
int tree_size = sizeof(tree) / sizeof(tree[0]);

int pre_seq[]  = {1, 2, 4, 5, 3, -1, 6};
int in_seq[]   = {4, 2, 5, 1, -1, 3, 6};
int post_seq[] = {4, 5, 2, -1, 6, 3, 1};
int seq_size = sizeof(pre_seq) / sizeof(pre_seq[0]);

void preorder(int root){
    if(root < tree_size){
        cout << tree[root] << " ";
        preorder(root * 2);
        preorder(root * 2 + 1);
    }
}

void inorder(int root){
    if(root < tree_size){
        inorder(root * 2);
        cout << tree[root] << " ";
        inorder(root * 2 + 1);
    }
}

void postorder(int root){
    if(root < tree_size){
        postorder(root * 2);
        postorder(root * 2 + 1);
        cout << tree[root] << " ";
    }
}

void print_order_seq(){
    TVE_FUNC funcs[] = {preorder, inorder, postorder};
    
    for(int i=0; i<3; i++){
        funcs[i](1);
        cout << endl;
    }
}

void rebuild_by_pre_in(int pre_l, int pre_r, int in_l, int in_r){
    if(pre_l > pre_r){
        return ;
    }
    
    cout << pre_seq[pre_l] << " ";
    
    int k = in_l;
    for(; k<=in_r; k++){
        if(pre_seq[pre_l] == in_seq[k]){
            break;
        }
    }

    int num_left = k - in_l;
    
    rebuild_by_pre_in(pre_l + 1, pre_l + num_left, in_l, k - 1);
    rebuild_by_pre_in(pre_l + num_left + 1, pre_r, k + 1, in_r);
}

void rebuild_by_post_in(int post_l, int post_r, int in_l, int in_r){
    if(post_l > post_r){
        return ;
    }
    
    cout << post_seq[post_r] << " ";
    
    int k = in_l;
    for(; k<=in_r; k++){
        if(post_seq[post_r] == in_seq[k]){
            break;
        }
    }
    
    int num_left = k - in_l;
    
    rebuild_by_post_in(post_l, post_l + num_left - 1, in_l, k - 1);
    rebuild_by_post_in(post_l + num_left, post_r - 1, k + 1, in_r);
}

void rebuild(){
    rebuild_by_pre_in(0, seq_size - 1, 0, seq_size - 1);
    cout << endl;
    rebuild_by_post_in(0, seq_size - 1, 0, seq_size - 1);
    cout << endl;
}

int main(){
    print_order_seq();
    rebuild();
    
    return 0;
}
