#include <stdio.h>

void exch(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int array[], int size){
    for(int i=1; i<size; i++){ // i �� 1 ��ʼ����
        int temp = array[i], idx = i; // ��¼��ǰԪ�غ��±�
        
        // �� idx > 0 �� idx - 1 �Ϸ�ʱ�� ��ǰԪ��С��ǰһ��Ԫ��
        // ���Ϻ���ֱ�� temp �ҵ��˺��ʵ�λ��
        while(idx > 0 && temp < array[idx-1]){
            array[idx] = array[idx-1]; // �������һλ
            idx--;
        }
        
        // ����Ԫ��
        array[idx] = temp;
    }
}

void prt_array(int array[], int size){
    for(int i=0; i<size; i++){
        printf("%d ", array[i]);
    }

    printf("\n");
}

int main(){
    int array[] = {1, 3, 4, 0, 2, -1},
    size = sizeof(array) / sizeof(array[0]);
    
    insertion_sort(array, size);
    prt_array(array, size);

    return 0;
}
