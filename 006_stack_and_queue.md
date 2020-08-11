## Stack and Queue

- Stack可以临时保存一些数据，之后用到依次再弹出来，常用于 DFS 深度搜索
- Queue一般常用于 BFS 广度搜索，类似一层一层的搜索
---

## 📑 index
- Stack 栈
  * <a href="#minStack">1. min-stack</a>



[//]: # (Image References)
[image1]: .readme/dfs.png "dfs"


<div id="minStack" onclick="window.location.hash">

#### 1. min-stack
linkage: [leetcode](https://leetcode-cn.com/problems/min-stack/ "最小栈")
- 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈
  - push(x) —— 将元素 x 推入栈中
  - pop() —— 删除栈顶的元素
  - top() —— 获取栈顶元素
  - getMin() —— 检索栈中的最小元素

