/*
    给定一个序列，求其中子序列的最大和
    例如 1 3 -4 5 6 7
    当子序列为 5 6 7 时和最大
    
    很简单的一维 dp，状态方程为
    dp[i] = max(dp[i-1] + arr[i], arr[i]);
    解释：
    dp[i] 表示第 i 个数的最大子序列和，这个和和第 i-1 个数有关
    取 dp[i-1] + arr[i] 和 arr[i] 中较大者作为 dp[i] 的值
*/
#include <iostream>

using namespace std;

int main(){
    int arr[] = {1, 3, -4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    int dp[size];
    
    dp[0] = arr[0];
    
    int ans = dp[0];
    for(int i=1; i<size; i++){
        dp[i] = max(dp[i-1] + arr[i], arr[i]);
        ans = max(ans, dp[i]);
    }
    
    cout << ans << endl;
    
    return 0;
}
