/*
    做题时发现自己忘了怎么求组合，复习一下。
    2020年7月12日13:48:36
*/
#include <iostream>
#include <vector>

using namespace std;


/*
* 输出长度为 m 的组合
* @param nums 要进行组合的数组
* @param res  暂存结果的 vector
* @param step 暂存步数的变量，传入 0
* @param m    要进行组合的长度
* @param n    组合数组的大小
*/
void backtrack(int nums[], vector<int> res, int step, int m, int n){
    if(m > n){
        return ;
    }
    
    // 输出
    if(res.size() == m){
        for(int i=0; i<res.size(); i++){
            cout << res[i] << " ";
        }
        cout << endl;
        return;
    }
    
    // 回溯版子
    for(int i=step; i<n; i++){
        res.push_back(nums[i]);
        // 这里 step 为 i + 1，即当前数已经放入组合，下次使用下一个数
        backtrack(nums, res, i+1, m, n);
        res.pop_back();
    }
}

int main(){
    int nums[] = {1, 2, 3},
    size = sizeof(nums) / sizeof(nums[0]);
    
    vector<int> res;
    
    backtrack(nums, res, 0, 3, size);
    
    return 0;
}
