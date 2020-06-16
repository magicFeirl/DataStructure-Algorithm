# DFS

水DFS，没什么好讲的。

赠品：~~（银行卡密码生成器）~~ 数字排列生成器

根据有重复排列总数公式`n^m`可知答案正确。

```c++
#include <cstdio>
#include <vector>

using namespace std;

vector<int> res;
long long count;

// 起始位置 结束位置 总数限制 当前步（其实可以用 res.size() 替代）
void dfs(int begin, int end, int limit, int step){
	if(step == limit){
		for(int i=0; i<res.size(); i++){
			printf("%d ", res[i]);
		}
		
		printf("\n");
		
		count++;
		return ;
	}
	
	for(int i=begin; i<end; i++){
		res.push_back(i);
		dfs(begin, end, limit, step + 1);
		res.pop_back();
	}
}

int main(){
	// 生成 0-9 总数为 2 的重复排列
	dfs(0, 9, 2, 0);
	
	printf("count: %lld\n", count); // 81
	
	return 0;
}
```

