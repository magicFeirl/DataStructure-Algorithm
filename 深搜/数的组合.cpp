/*
    ����ʱ�����Լ�������ô����ϣ���ϰһ�¡�
    2020��7��12��13:48:36
*/
#include <iostream>
#include <vector>

using namespace std;


/*
* �������Ϊ m �����
* @param nums Ҫ������ϵ�����
* @param res  �ݴ����� vector
* @param step �ݴ沽���ı��������� 0
* @param m    Ҫ������ϵĳ���
* @param n    �������Ĵ�С
*/
void backtrack(int nums[], vector<int> res, int step, int m, int n){
    if(m > n){
        return ;
    }
    
    // ���
    if(res.size() == m){
        for(int i=0; i<res.size(); i++){
            cout << res[i] << " ";
        }
        cout << endl;
        return;
    }
    
    // ���ݰ���
    for(int i=step; i<n; i++){
        res.push_back(nums[i]);
        // ���� step Ϊ i + 1������ǰ���Ѿ�������ϣ��´�ʹ����һ����
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
