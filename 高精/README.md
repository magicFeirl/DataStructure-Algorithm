## 高精

> 此高精非彼高精

思路其实很简单，就是通过字符串模拟四则运算，不过效率不高。

### 补零函数

在大数加和大数减中都会用到，目的是简化运算:

```c++
int fill_zero(string& a, string &b){
	int lena, lenb;
	int max_len = max(lena=a.length(), lenb=b.length());
	
	for(int i=lena; i<max_len; i++){
		a = "0" + a;
	}
	
	for(int i=lenb; i<max_len; i++){
		b = "0" + b;
	}
	
	return max_len; // 此时两串长度一致所以直接返回最大值即可，大数加中会用到
}
```

### 大数加

大数加算是高精中最简单的部分了，直接根据四则运算模拟就行，不过需要注意以下几点：

1. 两串要前补0，补零后两串长度一致所以只需要一个for循环模拟按位加即可

2. 进位与结果

   1. 进位可以直接用 当前两数相加结果/10 等到，因为两个数最大不会超过9，所以可以直接除10得到，核心代码如下：

      ```c++
      for(int i=len-1; i>=0; i--){
          int temp = (a[i] + b[i]) - 2 * '0'; // 先转为int方便计算
          int curr = temp % 10; // 获取个位结果
          int ok = temp / 10; // 获取进位（0或1）
          result = result + char(ok+'0');
      }
      
      if(ok) result = result + char(ok+'0'); // 如果最后还存在进位，直接加到result串即可
      
      return result;
      ```

   2. 结果串其实没有考虑到去除前导0的问题，比如输入`001 + 001`会得到`002`，但是如果使用`string.earse(0, string.find_first_not_of('0'))`去除前导会导致大数乘在很大时出错，原因不明。

代码如下:

```c++
string add(string a, string b){
	// 第一步：字符串前端补0对齐长度
	int len = fill_zero(a, b) - 1, ok = 0;
	int temp, n;
	
	string result = "";
	
	for(int i=len; i>=0; i--){
		// 将运算数转为int
		temp = a[i] + b[i] - 2 * '0' + ok;
		// 获取结果的个位
		n = temp % 10;
		// 获取十位 由于每位最大为9+9所以结果最多只会为2位数
		ok = temp / 10; // 进位标志
		
		result = char(n + '0') + result;
	}
	
	if(ok) result = char(ok + '0') + result;
	
	return result;
}
```

### 大数减

大数减和大数加差不过，不过要考虑负数和0的情况。

* 可能出现负数的情况

  * 什么情况下可能会出现负数呢？很容易想到当a串小于b串时，就可能出现负数（废话）。为了使计算简单，我们要确保a>=b，那么出现上述情况时，交换a和b并保存一个结果为负的flag就行。代码如下:

    ```c++
    string prefix = "";
    if(a < b){
        swap(a, b);
        prefix = "-"; // 用字符串作为前缀，返回结果时直接和结果串拼接即可
    }
    ```

    然后就是补0了。

* 可能出现0的情况

  * 当结果串长度为0时，表明结果为0，在返回结果串前要先进行判断，代码如下：

    ```c++
    result.earse(0, string.find_first_not_of('0')); // 删除前导0
    
    if(result.length() == 0){
        return "0";
    }else{
        return prefix + result;
    }
    ```

代码如下（别忘了补0）:

```c++
string sub(string a, string b){
	
	string prefix = ""; // 符号前导
	
	// 如果a<b则交换两个串，那么a-b>=0，确保计算过程中不会下标溢出
	if(a < b){
		swap(a, b);
		prefix = "-";
	}
	
	int len = fill_zero(a, b) - 1, temp, n;
	string result = "";
	
	for(int i=len; i>=0; i--){
        // 最关键的部分
		if(a[i] < b[i]){ // 当被减数小于减数时，被减数向前借位，前位-1
			a[i] += 10;
			a[i-1] -= 1;
		}
		
		result = char(a[i] - b[i] + '0') + result;
	}
	
	result.erase(0, result.find_first_not_of('0'));
	
	// 如果为空串表示结果为0
	if(result.length() == 0){
		return "0";
	}
	
	return prefix + result;
}
```

### 大数乘

大数乘要考虑的情况就更多了，不过基本思路还是通过模拟基本的四则运算，这里还会用到大数加。

先举个例子：

```c++
// 计算 111 * 222
/*
	根据乘模拟展开可得结果：
	222 = (2 + 20 + 200) ->
	111 * 222 = 2*111 + 20*111 + 200*111
	             个位      十位     百位
	
	在代码中我们要模拟乘数的各位与被乘数相乘，然后将结果加起来。
	要注意的是这里的个十百位，进行运算时要转为相应的位的大小（比如如果a是百位，那么进行运算的这个值就为a*100)，依次类推，更多的位数也适用。
	没听懂？直接上代码。
*/
```

```c++
string mul(string a, string b){
    // 初始结果串为0
	string result = "0"; 
	int i, j;
    
	int lena = a.length() - 1, 
    lenb = b.length() - 1;
	
	for(i=lena; i>=0; i--){
        // 如果第a[i]为为0，那么不进行计算
		if(a[i] != '0'){
            // 三个变量分别表示：进位数，a[i]*b[i]的值，a[i]*[b]结果的个位
			int ok = 0, temp, n; 
            // 保存第b的第j位乘a的第i位的结果的临时串
			string temp_str = "";
			// 末尾补零，见上面的例子
			for(j=0; j<lena-i; j++)
				temp_str += "0";
			
            // 关键部分
			for(j=lenb; j>=0; j--){
                // ok表示进位
				temp = (b[j] - '0') * (a[i] - '0') + ok;
                // 个位结果，a[i]位和b[j]位两个数最大不超过9
				n = temp % 10;
                // 进位
				ok = temp / 10;
                // 临时结果串
				temp_str = char(n + '0') + temp_str;
			}
            
			// 运算完毕后如果存在进位，直接作为一个新位加到临时结果串上
			if(ok) temp_str = char(ok + '0') + temp_str;
            // 运算结果与临时结果串相加
			result = add(result, temp_str);
		}
	}
	
	return result;
}
```



### 大数除

不会

### 大数模

不会