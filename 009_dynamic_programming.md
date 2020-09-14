## Dynamic Programming
> 本质：把大问题变成小问题，并解决小问题重复计算的方法
---
- **DP 三个目标**
  - 1. 建立状态转移方程[难点]
    - 思维：已知f(0)～f(n-1)的值，利用它们求f(n)
  - 2. 缓存并复用以往结果[重点]
    - 如无合适处理，很可能是指数和线性时间复杂度的区别
  - 3. 按顺序从小往大算
    - 小”和“大”指问题的规模，即从f(0)到f(n)依序计算
---
- **DP 四点要素**
  - 状态 State
    - 灵感，创造力，**存储小规模问题的结果**
  - 方程 Function
    - **状态之间的联系**，怎么通过小的状态，来算大的状态
  - **初始化** Intialization
    - 最极限的小状态是什么, **起点**
  - **答案** Answer
    - 最大的那个状态是什么，**终点**
---
- **DP 使用条件**
  - 满足以下条件之一
    - 求最大/最小值(Maximum/Minimum)
    - 求是否可行(Yes/No)
    - 求可行个数(Count(*))
  - **满足不能排序或者交换**(Can not sort/swap)
---
- **DP & Recursion 区别**
  - 递归是一种程序的实现方式：**函数的自我调用**
  - 动态规划：是一种**解决问题的思想**(大问题化解小问题)，可用递归来实现
---
- **DP & DFS 区别**
  - 二叉树子节点无交集，大部分二叉树都用递归或者分治法，即 DFS就可解决
  - 有重复走的情况，**子节点/问题有交集**，用动态规划来解决
---


## 📑 index
- Example
  * <a href="#triangle">1. triangle(#120)</a>
- Sequence (40%)
  * <a href="#cs">2. ​climbing-stairs​(#70)</a>








---

[//]: # (Image References)
[image1]: .readme/triangle_state_function.png "triangle_state_function"




<div id="triangle" onclick="window.location.hash">

#### 1. triangle(#120)
linkage: [leetcode](https://leetcode-cn.com/problems/triangle/ "三角形最小路径和")
> 给定一个三角形，找出自顶向下的最小路径和
> 每一步只能移动到下一行中相邻的结点上
- 思路一：recursion方式+记忆化(自顶向下)
  - 1. 注意：考虑**临时变量是否放在递归函数**内
  - 2. 注意：**临时变量的复用**(LOC78-79)，否则极容易造成指数时间复杂度
  - 3. 注意：考虑dp的解题思路，自顶向下还是自底向上，主要是**建立状态转移方程**
  - 4. 递归需要大量堆栈上的空间，容易栈溢出，最好将递归转换为递推
  ```cpp
  class Solution {
  public:
      int minimumTotal(vector<vector<int>>& triangle) 
      {
          // min_sums(raw,column)就保存起来，下次用到其值的时候直接取用，则可免去重复计算
          // 注意：利用递归方式，临时变量要考虑是否放在递归函数内
          vector<vector<int>> min_sums(triangle.size(),vector<int>(triangle.size(),INT_MAX));
          int level = triangle.size()-1;
          // 顺序从小到大开始调用
          // 自顶向下
          return dfsSum(triangle, 0, 0, min_sums);
      }
      // 对min_sums的调用要使用&，否则导致time limit
      int dfsSum(vector<vector<int>>& nums, int raw, int column, vector<vector<int>>& min_sums)
      {

          if(min_sums[raw][column] != INT_MAX)
              return min_sums[raw][column];
          if(raw == nums.size()-1)
          {
              min_sums[raw][column] = nums[raw][column];
          }
          else
          {
              // dp的状态转移方程
              min_sums[raw][column] = min(dfsSum(nums,raw+1,column, min_sums),dfsSum(nums,raw+1,column+1, min_sums)) + nums[raw][column];
          }
          return min_sums[raw][column];
      }
  };
  ```
- 思路二：递推方式
  - **自底向上**方式
  - 状态转移方程
![][image1]
  - 参考[linkage](https://blog.csdn.net/baidu_28312631/article/details/47418773)
  ```cpp
  class Solution {
  public:
      int minimumTotal(vector<vector<int>>& triangle) 
      {
          // 利用临时变量存储最小值
          vector<vector<int>> min_sum(triangle.size(),vector<int>(triangle.size()));
          int level = triangle.size()-1;
          // 递推最后一行
          for(int i = 0; i<=level;i++)
          {
              min_sum[level][i] = triangle[level][i];
          }
          // 递推除去最后一行
          // 注意从下向上递归，因此一定i--
          for(int i = level-1; i>= 0;i--)
          {
              for(int j = 0; j <= i;j++)
              {
                  min_sum[i][j] = min(min_sum[i+1][j],min_sum[i+1][j+1])+triangle[i][j];
              }
          }
          return min_sum[0][0];
      }
  };
  ```
- 思路三：基于思路二优化(针对**空间优化**)
  - 每一行取最大值
  ```cpp
  class Solution {
  public:
      int minimumTotal(vector<vector<int>>& triangle)
      {
          // 利用临时变量存储最小值
          vector<int> min_sum(triangle.size());
          int level = triangle.size()-1;
          // 处理最后一行
          for(int i = 0;i<=level;i++)
          {
              min_sum[i] = triangle[level][i];
          }
          // 递推除去最后一行
          // 注意从下向上递归，因此一定i--
          for(int i = level-1; i>= 0;i--)
          {
              for(int j = 0; j <= i;j++)
              {
                  min_sum[j] = min(min_sum[j],min_sum[j+1])+triangle[i][j];
              }
          }
          return min_sum[0];
      }
  };
  ```
---

<div id="cs" onclick="window.location.hash">

#### 2. ​climbing-stairs​(#70)
linkage: [leetcode](https://leetcode-cn.com/problems/climbing-stairs/ "爬楼梯")
> n阶楼梯，每次可上1或2阶，有多少种方法
- 条件：
  - 可行个数
  - 排序不能交换
- 思路一：传统dp思想(Fibonacci Sequence)
  - 重点：初始值的选取，递归公式的推导
  ```cpp
  class Solution {
  public:
      int climbStairs(int n)
      {
          // 找规律，初始值为
          if(n == 1)
              return 1;
          if(n == 2)
              return 2;
          vector<int> stairs(n);
          stairs[0] = 1;
          stairs[1] = 2;
          for(int i=2;i<=n-1;i++)
          {
              stairs[i] = stairs[i-1]+stairs[i-2];
          }
          return stairs[n-1];
      }
  };
  ```
- 思路二：优化空间复杂度
  - 只存储最近的三个值，空间复杂度由6.3MB->5.9MB
  ```cpp
  for(int i=2;i<=n-1;i++)
  {
      stairs[2] = stairs[0]+stairs[1];
      stairs[0] = stairs[1];
      stairs[1] = stairs[2];
  }
  return stairs[2];
  ```
- 思路三：简单版本的recursion
  - 超出了时间限制
  ```cpp
  if(n == 1 || n ==2)
      return n;
  return climbStairs(n-1) + climbStairs(n-2);cpp
  ```
- **扩展：字节跳动20秋招T1**
  - 添加一个条件：不允许两次连续爬两阶
- 思路：耐心的进行公式推导
  - 初值：n[1] = 1, n[2] = 2, n[3] = 3
  - 递推公式：n[n] = n[n-1] + n[n-3]
---
