/*
01背包版子，《笔记》那个貌似有点问题

70 3
71 100
69 1
1 2
*/

#include <iostream>

using namespace std;


int w[110], c[110];

int dp[110][1010];

int main(){
    int V, N;

    cin >> V >> N;

    for(int i=1; i<=N; i++){
        cin >> w[i] >> c[i];
    }

    for(int i=1; i<=N; i++){
        // 倒着遍历
        for(int v=V; v>=0; v--){
            // 还有空间的时候
            if(v >= w[i]){
                // 最优即为
                // 前一个物品当前空间 和 前一个物品放入该物品后加上当前物品的价值中较大者
                dp[i][v] = max(dp[i-1][v], dp[i-1][v-w[i]] + c[i]);
            }else{
                // 没有空间的话最优解就是前一个物品容量为 v 的最优解
                dp[i][v] = dp[i-1][v];
            }
        }
    }

    cout << dp[N][V] << endl;

    return 0;
}
