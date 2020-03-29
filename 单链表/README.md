### 链表

> 单链表、双链表、循环单链表、循环双链表...

没什么好说的，链表会了，队列、栈也就会了，甚至BST也能掌握大部分（心虚）。

唯一值得注意的两个函数：

泛型复制，可以搜一下`Qsort`的实现了解一下。

```c
// 创建一个新的item，并将原先的item的值复制进来
// 由于这里是泛型版，所以会麻烦一点
// static 修饰符在这里表示函数仅当前文件作用域，你也可以理解为Java中的private修饰符
static ITEM copy(ITEM item, size_t size){
    ITEM temp = malloc(size);
    
    for(int i=0; i<size; i++){
        // 根据二进制位复制元素，无需知道元素的类型
        *((char *)temp + i) = *((char *)item + i);
    }
    
    return temp;
}
```

反转单链表，放在这里单纯是因为算法搞忘了w，这个会了反转双链表的也就差不多了。

```c
// 反转链表
void reverse_list(PLIST list){
    assert(list != NULL);
    
    PNODE curr = list->head,
    next = curr, prev = NULL;
    
    while(next){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    list->tail = list->head;
    list->head = prev;
}
```

