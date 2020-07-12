// 暴力法匹配字符串
// s: 1 2 3 4 5 6
// t: 4 5
// 先定义两个指针 i、j，然后循环判断 s[i] 是否等于 t[j]
// 如果相等则将 i、j 两指针向后移动 1 位
// 如果不相等则将 i 回溯到 i - j + 1 的位置（上次起始位置的后一位），将 j 置为 0（子串重新开始匹配）
// 循环条件是当 s[i] 和 t[j] 都不为空
// 最后判断 t[j] 的值，如果 t[j] 为空，表明子串已经被完整的扫了一遍，返回 i - j 的值代表子串起始位置
// 否则返回 -1 表明没有找到子串
// 时间复杂度 O(n * m)

#include <stdio.h>
#include <string.h>

int BF(const char *str, const char *substr){
    int i = 0, j = 0;
    
    // 想象两个移动的指针可加深理解
    while(str[i] && substr[j]){
        if(str[i] == substr[j]){
            i++, j++;
        }else{
            i = i - j + 1;
            j = 0;
        }
    }
    
    return !substr[j] ? (i - j) : -1;
}

int main(){
    const char *str = "ABCDEF";
    const char *substr = "ADEF";
    
    printf("%d ", BF(str, substr));
    
    return 0;
}
