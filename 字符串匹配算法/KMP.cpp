#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>


void prefix_table(const char pattern[], int prefix[], int n){
    int len = 0; // len 表示 下表为 i 时当前的最长公共前后缀为多长
    int i = 1; // 从第二个字母开始和前面的字母进行比较
    prefix[len] = 0; // 第一个字母没有前后缀所以前缀表中的值为 0
    
    while(i < n){ // 当模式串没用完时
        // 如果模式串的第 i 个字母和第 len 个字母相同，公共串长度会增加 1
        if(pattern[i] == pattern[len]){ 
            // printf("%d\n", prefix[i]);
            prefix[i++] = ++len;
        }else{
            // 否则就把当前最长公共前后缀指向前缀表的第 len - 1 位（当前位不参加运算）
            if(len > 0){
                len = prefix[len - 1];
            }else{ // 表明没有最长公共前后缀
                prefix[i] = len; // len == 0
                i++; // 跳过这个字符
            }
        }
    }
    
    // 把前缀数组整体后移一位，同时将其中的第一个元素值置为 -1
    for(i=n-1; i>0; i--){
        prefix[i] = prefix[i-1];
    }
    
    prefix[0] = -1;
}

int KMP(const char *str, const char *substr, int next[], int n){
    int lenstr = strlen(str);
    int lensubstr = strlen(substr);
    int i = 0, j = 0;
    // 暴力法的改进版
    while(i < lenstr && j < lensubstr){
        if(j == -1 || str[i] == substr[j]){
            i++, j++;
        }else{
            j = next[j]; // 跳过 next[j] 个公共前后缀（这一部分在失配前就已经匹配过）
        }
    }
    
    return j == lensubstr ? (i - j) : -1;
}

int BF(const char *str, const char *substr){
    int lenstr = strlen(str);
    int lensubstr = strlen(substr);
    int i = 0, j = 0;
    
    while(i < lenstr && j < lensubstr){
        if(str[i] == substr[j]){
            i++, j++;
        }else{
            i = i - j + 1, j = 0;
        }
    }
    
    return j == lensubstr ? (i - j) : -1;
}

char * gen_str(int len){
    char *str = (char *)malloc(len * sizeof(char) + 1);
    for(int i=0; i<len; i++){
        str[i] = ('a' + rand() % ('z' - 'a'));
    }
    
    str[len] = '\0';
    
    return str;
}

const int N = 1024 * 1024 * 100;
const char *target = "gdjwgyesfobmp";

int main(){
    // const char *str = "1234514";
    // const char *substr = "45";
    
    FILE *file = fopen("data.txt", "r+");

    // fputs(gen_str(N), file);
    // return 0;
    char *genstr = (char *)malloc(sizeof(char) * N + 1);
    fgets(genstr, N, file);
    
    // int n = strlen(genstr);
    int *prefix = (int *)malloc(sizeof(int) * N);
    
    prefix_table(genstr, prefix, N);
    
    int start = time(0);
    printf("start %d\n", start);
    printf("%d\n", KMP(genstr, target, prefix, N)); // 0.05934
    printf("%d\n", BF(genstr, target)); // 0.06173
    
    unsigned int end = time(0);
    printf("end %d\n", end);
    printf("%d\n", end - start);
    
    free(genstr);
    free(prefix);
    
    return 0;
}
