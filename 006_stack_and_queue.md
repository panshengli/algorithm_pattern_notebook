## Stack and Queue

- Stack可以临时保存一些数据，之后用到依次再弹出来，常用于 DFS 深度搜索
- Queue一般常用于 BFS 广度搜索，类似一层一层的搜索
- 各种数据结构操作元素方法
    数据结构 | 向后面压入<br>一个元素 | 删除最后<br>一个元素 | 返回头元素 | 返回尾元素 | 入栈(队) | 出栈(队) | 判断空
    :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-:
    vector | push_back() | pop_back()<br>emplace_back() | at(0) | at(size(i)-1) | -- | -- | empty()
    stack | -- | -- | top()<br>peek() | -- | push()<br>emplace() | pop() [删除尾] | empty()
    queue | -- | -- | front() | back() | push()<br>emplace() | pop() [删除头] | empty()
    deque | -- | -- | front() | back() | push_front()<br>push_back() | pop_front()<br>pop_back() | empty()
---

## 📑 index
- Stack 栈
  * <a href="#minStack">1. min-stack(#155)</a>
  * <a href="#erpn">2. evaluate-reverse-polish-notation(#150)</a>
  * <a href="#ds">3. decode-string(#394)</a>
  * <a href="#cg">4. clone-graph(#133)[遍历图常用的模板，dfs&bfs]</a>
  * <a href="#noi">5. number-of-islands(#200)</a>
  * <a href="#lrih">6. largest-rectangle-in-histogram(#84)</a>








---
[//]: # (Image References)
[image1]: .readme/stack.gif "stack"


<div id="minStack" onclick="window.location.hash">

#### 1. min-stack(#155)
linkage: [leetcode](https://leetcode-cn.com/problems/min-stack/ "最小栈")
- 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈
  - push(x) —— 将元素 x 推入栈中
  - pop() —— 删除栈顶的元素
  - top() —— 获取栈顶元素
  - getMin() —— 检索栈中的最小元素
- 思路一：利用vector写出
- 注意：
  - vector删除最后一个元素可用pop_back();
  - stack删除最后一个元素可用pop(),stack返回栈顶元素用top();
  ```cpp
  class MinStack {
  public:
      /** initialize your data structure here. */
      MinStack() {
          num_.clear();
      }
      void push(int x) {
          num_.push_back(x);
      }
      void pop() {
          // vector删除最后一个元素可用pop_back()
          num_.pop_back();
      }
      int top() {
          return num_.at(num_.size()-1);
      }
      int getMin() {
          int count = num_.size();
          int get_min = INT_MAX;
          for(int i=0;i<count;i++)
          {
              if(get_min>num_.at(i))
              {
                  get_min = num_.at(i);
              }
          }
          return get_min;
      }
  private:
      std::vector<int> num_;
  };
  ```

- 思路二：利用stack写出
- 注意：
  - 注意stack出栈和入栈的方式，见图解
  - 思路：用两个栈实现，一个最小栈始终保证最小值在顶部
![][image1]
  ```cpp
  class MinStack {
  public:
      /** initialize your data structure here. */
      MinStack(){
      }

      void push(int x) {
          num_.push(x);
          // 注意：需要添加判断空的条件
          if(get_min_.empty() || x<=get_min_.top())
          {
              get_min_.push(x);
          }
      }

      void pop() {
          int x = num_.top();
          num_.pop();
          // 若 x 是当前的最小值，则也需要删除辅助栈的栈顶元素
          if (x == get_min_.top())
          {
              get_min_.pop();
          }
      }

      int top() {
          return num_.top();
      }

      int getMin() {
          return get_min_.top();
      }

  private:
      std::stack<int> num_;
      std::stack<int> get_min_;
  };
  ```
---

<div id="erpn" onclick="window.location.hash">

#### 2. evaluate-reverse-polish-notation(#150)
linkage: [leetcode](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/ "逆波兰表达式求值")
- 根据 逆波兰表示法，求表达式的值
- 说明：
  - 整数除法只保留整数部分。
  - 给定逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。
- 思路：
  - 注意：c++如何将字符转为数字stoi，思路题
  - 开始判断是否存在数字符号
  - 不存在，向栈中push数据
  - 然后进行符号赋值操作
  - 最后将表达式计算的结果push栈中
  - 返回栈顶元素
    ```cpp
    class Solution {
    public:
        int evalRPN(vector<string>& tokens)
        {
            std::stack<int> numbers;
            for(int i=0;i<tokens.size();i++)
            {
                if(tokens.at(i) == "+" || tokens.at(i) == "-" 
                    || tokens.at(i) == "*" || tokens.at(i) == "/")
                {
                    int res;
                    int n2 = numbers.top();
                    numbers.pop();
                    int n1 = numbers.top();
                    numbers.pop();

                    if(tokens.at(i) == "+")
                        res = n1+n2;
                    if(tokens.at(i) == "-")
                        res = n1-n2;
                    if(tokens.at(i) == "*")
                        res = n1*n2;
                    if(tokens.at(i) == "/")
                        res = n1/n2;
                    // 不要忘记将计算的结果push到栈中
                    numbers.push(res);
                }
                else
                {
                    // 重点：将字符串转换为数字
                    numbers.push(stoi(tokens.at(i)));
                }
            }
        return numbers.top();
        }
    };
    ```
---

<div id="ds" onclick="window.location.hash">

#### 3. decode-string(#394)
linkage: [leetcode](https://leetcode-cn.com/problems/decode-string/ "字符串解码")
- 给定一个经过编码的字符串，返回它解码后的字符串
- 思路题：利用stack思想
  - 1. 申明关于nums和strs的stack;
  - 2. 将数字push到nums，字母push到strs;
  - 3. 遇到'['入栈，push(num)和push(str),同时重置num和str;
  - 4. 遇到']'出栈，将重复字母push到栈顶，(重点)若是'['，sttr会被压入strs栈，作为上一层的运算
    ```cpp
    class Solution {
    public:
        string decodeString(string s) 
        {
            int num = 0;
            string str = "";
            std::stack<int> nums;
            std::stack<string> strs;
            int s_len = s.length();
            for(int i = 0; i<s_len;i++)
            {
                if(s[i]<='9'&&s[i]>='0')
                {
                    num = 10 * num + (s[i]-'0');
                }
                else if((s[i]>='a'&&s[i]<='z') || (s[i]>='A'&&s[i]<='Z'))
                {
                    str = str + s[i];
                }
                else if(s[i] == '[')
                {
                    nums.push(num);
                    num = 0;
                    strs.push(str);
                    str = "";
                }
                else
                {
                    int repeat = nums.top();
                    nums.pop();
                    for(int i = 0; i<repeat;i++)
                    {
                        strs.top() += str;
                    }
                    // 取出重复元素
                    str = strs.top();
                    //之后若还是字母，就会直接加到res之后，因为它们是同一级的运算
                    //若是左括号，res会被压入strs栈，作为上一层的运算
                    strs.pop();
                }
            }
            return str;
        }
    };
    ```
---

<div id="cg" onclick="window.location.hash">

#### 4. clone-graph(#133)
linkage: [leetcode](https://leetcode-cn.com/problems/clone-graph/ "克隆图")
- 给你无向连通图中一个节点的引用，请你返回该图的深拷贝(克隆)
- 因为图存在环，所以要标记访问过的结点，避免重复形成死循环
- **重点掌握，后面图遍历都和这个有关系**
- 思路一：dfs(递归方式)
  - 1. 处理遍历后的结果，防止陷入死循环
  - 2. 没遍历过进行赋值处理
  - 3. 处理neighbors节点，注意neighbors节点的结构
```cpp
class Solution {
public:
    Node* cloneGraph(Node* node)
    {
        if(node == nullptr)
        {
            return node;
        }
        // 防止陷入死循环，遍历过直接返回
        if(nodes_map_.find(node) != nodes_map_.end())
        {
            return nodes_map_[node];
        }
        // 不相等进行赋值
        nodes_map_[node] = new Node(node->val);
        // 开始处理neighbors节点
        for(auto &i : node->neighbors)
        {
            // 开始处理neighbors节点
            nodes_map_[node]->neighbors.push_back(cloneGraph(i));
        }
        return nodes_map_[node];
    }

private:
    std::unordered_map<Node*, Node*> nodes_map_;
};
```
- 思路二：bfs(queue)
  - 1. 声明queue，并对其进行入队处理
  - 2. 将开始node中的值拷贝到map中
  - 3. 申明一个临时node，用于进行当前队列值操作
  - 4. 对neighbors进行处理，同时也对没遍历的节点进行赋值操作
  - 5. 注意要将新的节点压入队中
  - 6. 最后处理neighbors中的值(注意代码)
    ```cpp
    class Solution {
    public:
        Node* cloneGraph(Node* node)
        {
            if(node == nullptr)
            {
                return node;
            }
            // 声明一个queue,并对其进行入队处理
            std::queue<Node*> q;
            q.push(node);
            // 重点：将开始node的值copy到新的节点中
            nodes_map_[node] = new Node(node->val);
            while(!q.empty())
            {
                // 声明一个临时变量
                Node* tmp = q.front();
                q.pop();
                // 重点：对neighbors进行处理，特别注意嵌套关系
                for(auto &i:tmp->neighbors)
                {
                    // 没遍历进行节点赋值操作
                    if(nodes_map_.find(i) == nodes_map_.end())
                    {
                        nodes_map_[i] = new Node(i->val);
                        // 重点：将新的node压到队中
                        q.push(i);
                    }
                    // 重点：注意放入vector中的是nodes_map_[i]，非i
                    nodes_map_[tmp]->neighbors.push_back(nodes_map_[i]);
                }
            }
            return  nodes_map_[node];
        }
    private:
        std::unordered_map<Node*,Node*> nodes_map_;
    };
    ```
---

<div id="noi" onclick="window.location.hash">

#### 5. number-of-islands(#200)
linkage: [leetcode](https://leetcode-cn.com/problems/number-of-islands/ "岛屿数量")
- 给你一个由'1'（陆地）和'0'（水）组成的的二维网格，请你计算网格中岛
- 思路一：dfs
  - 1. 遍历当前vector，当遍历字符'1'时，count加1
  - 2. 进入dfs递归操作，注意递归返回的条件
  - 3. 重点：递归处理时将遍历后的grid[i][j]置为'0'
  - 4. 进行四个方位递归
```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid)
    {
        if(grid.size() == 0)
            return 0;
        outer_size_ = grid.size();
        inner_size_ = grid[0].size();
        for(int i = 0; i<outer_size_;i++)
        {
            for(int j =0;j<inner_size_;j++)
            {
                if(grid[i][j] == '1')
                {
                    count_++;
                    dfs(grid, i, j);
                }
            }
        }
        return count_;
    }

    void dfs(vector<vector<char>>& grid, int i, int j)
    {
        if(i<0 || i>=outer_size_ || j<0 || j>=inner_size_)
            return;
        if(grid[i][j] == '0')
            return;
        // 注意：不要忘了将遍历过的grid[i][j]赋值为'0'
        grid[i][j] = '0';
        dfs(grid,i-1,j);
        dfs(grid,i+1,j);
        dfs(grid,i,j-1);
        dfs(grid,i,j+1);
    }

private:
    int inner_size_;
    int outer_size_;
    int count_;
};
```
- 思路二：bfs
  - 前一部分代码与dfs方法一样
  - 注意：bfs的索引方式，利用pair<int,int>
  - 找到条件时，不要忘了将遍历过的grid[i][j]赋值为'0'
```cpp
void bfs(vector<vector<char>>& grid, int i, int j)
    {
        // 注意：进行bfs搜索时，注意index处理的方式
        std::queue<std::pair<int,int>> neighbor_index;
        neighbor_index.push(std::make_pair(i,j));
        while(!neighbor_index.empty())
        {
            std::pair<int,int> cur_index = neighbor_index.front();
            int lhs = cur_index.first;
            int rhs = cur_index.second;
            neighbor_index.pop();
            if(lhs>=0 && lhs<outer_size_ && rhs>=0 && rhs<inner_size_ && grid[lhs][rhs] == '1')
            {
                grid[lhs][rhs] = '0';
                neighbor_index.push(std::make_pair(lhs-1,rhs));
                neighbor_index.push(std::make_pair(lhs+1,rhs));
                neighbor_index.push(std::make_pair(lhs,rhs+1));
                neighbor_index.push(std::make_pair(lhs,rhs-1));
            }
        }
    }
```
---

<div id="lrih" onclick="window.location.hash">

#### 6. largest-rectangle-in-histogram(#84)
linkage: [leetcode](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/ "柱状图中最大的矩形")
- n 个柱子，求能勾勒出来的矩形的最大面积
- 思路一：暴力求解
  - 左右端点法(不推荐，了解思路)
  - 1. 尝试所有可能矩形
  - 2. 矩形的面积等于(右端点-左端点+1)*最小的高度
  - 3. 该解法超出时间限制，如果加上打印，超出输出限制
    ```cpp
    class Solution {
    public:
        int largestRectangleArea(vector<int>& heights)
        {
            if(heights.size() == 0) return 0;
            int max_area= 0;
            for(int lhs = 0;lhs<heights.size();lhs++)
            {
                int min_value = heights[lhs];
                int length = 0;
                for(int rhs = lhs;rhs<heights.size();rhs++)
                {
                    length = rhs-lhs + 1;
                    min_value = std::min(min_value,heights[rhs]);
                    max_area = std::max(max_area,min_value*length);
                }
            }
            return max_area;
        }
    };
    ```
  - 中心扩展法(不推荐，了解思路)
  - 1. 确定一根柱子后向他的前后两个方向扫描
  - 2. 以当前柱子高度为矩形的高所围成的最大矩形
  - 写法略

- 思路二：stack
  - 单调递增栈
    - 新元素比栈顶元素大，入栈
    - 新元素较小，一直把栈内元素弹出来，直到栈顶比新元素小
        ```cpp
        // 代码模板
        stack<int> st;
        for(int i = 0; i < nums.size(); i++)
        {
            while(!st.empty() && st.top() > nums[i])
            {
                st.pop();
            }
            st.push(nums[i]);
        }
        ```

    ```cpp
    class Solution {
    public:
        int largestRectangleArea(vector<int>& heights) 
        {
            if(heights.size() == 0)
            {
                return 0;
            }
            // 构造前后哨兵为了处理边界栈为空的情况，注意vector插入的方式
            heights.insert(heights.begin(), 0);
            heights.push_back(0);

            int max_area = 0;
            std::stack<int> s;
            // 开始遍历vector
            for(int i = 0; i < heights.size();i++)
            {
                // 列表数值小于上一个值出栈处理,注意为&&条件
                while(!s.empty() && heights[s.top()] > heights[i])
                {
                    int cur = s.top();
                    s.pop();
                    // 注意(重要)：长度的在stack出栈后取出,不可写i-cur,因为非连续
                    int length = i-s.top()-1;
                    max_area = std::max(max_area,heights[cur]*length);
                }
                // 当前值为递增时，入栈处理
                s.push(i);
            }
            return max_area;
        }
    };
    ```
---

