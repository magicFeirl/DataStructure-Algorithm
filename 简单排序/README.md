# 简单排序

不同于快排堆排之类的排序算法，简单排序代码简单且容易理解，在数据量较小的情况下也是总不错的选择。

## 冒泡排序

时间复杂度 O(N^2)。

代码:

```c
void bubble_sort(int array[], int size){
    for(int i=0; i<size; i++){
        for(int j=i; j<size-1; j++){
            if(array[j] > array[j+1]){
                exch(&array[j], &array[j+1]);
            }
        }
    }
}
```



## 插入排序

时间复杂度 O(N^2)，在数组有序的情况下表现不错。

代码:

```c
void insertion_sort(int array[], int size){
    for(int i=1; i<size; i++){ // i 从 1 开始插入
        int temp = array[i], idx = i; // 记录当前元素和下标
        
        // 当 idx > 0 即 idx - 1 合法时且 当前元素小于前一个元素
        // 不断后移直到 temp 找到了合适的位置
        while(idx > 0 && temp < array[idx-1]){
            array[idx] = array[idx-1]; // 整体后移一位
            idx--;
        }
        
        // 插入元素
        array[idx] = temp;
    }
}
```



## 选择排序

时间复杂度 O(N^2)。

代码:

```c
// 在 [i+1, N] 内选择一个最小的元素，交换 i 和 k
// 这样从 [0, i] 内的元素就是有序的了，重复 N 次即完成排序
void selection_sort(int array[], int size){
    for(int i=0; i<size; i++){
        int k = i;
        
        for(int j=i+1; j<size; j++){
            if(array[j] < array[k]){
                k = j;
            }
        }
        
        exch(&array[i], &array[k]);
    }
}
```

