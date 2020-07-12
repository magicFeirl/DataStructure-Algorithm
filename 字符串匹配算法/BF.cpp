// ������ƥ���ַ���
// s: 1 2 3 4 5 6
// t: 4 5
// �ȶ�������ָ�� i��j��Ȼ��ѭ���ж� s[i] �Ƿ���� t[j]
// �������� i��j ��ָ������ƶ� 1 λ
// ���������� i ���ݵ� i - j + 1 ��λ�ã��ϴ���ʼλ�õĺ�һλ������ j ��Ϊ 0���Ӵ����¿�ʼƥ�䣩
// ѭ�������ǵ� s[i] �� t[j] ����Ϊ��
// ����ж� t[j] ��ֵ����� t[j] Ϊ�գ������Ӵ��Ѿ���������ɨ��һ�飬���� i - j ��ֵ�����Ӵ���ʼλ��
// ���򷵻� -1 ����û���ҵ��Ӵ�
// ʱ�临�Ӷ� O(n * m)

#include <stdio.h>
#include <string.h>

int BF(const char *str, const char *substr){
    int i = 0, j = 0;
    
    // ���������ƶ���ָ��ɼ������
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
