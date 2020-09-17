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
- **DP & 贪心算法**
  - 贪心算法大多靠背答案，如果能用动态规划就尽量用动规，不用贪心算法
---


## 📑 index
- Trtorial
  * <a href="#triangle">1. triangle(#120)</a>
- Sequence (40%)
  * <a href="#cs">2. ​climbing-stairs​(#70)</a>
  * <a href="#jg">3. ​jump-game​​(#55)[推荐dp做法]</a>
  * <a href="#jgii">4. ​jump-game-ii​​(#45)</a>
  * <a href="./004_backTrack_algorithm.md">5. ​​palindrome-partitioning(#131)[非dp做法,回溯T2]</a>
  * <a href="#ppii">6. ​​palindrome-partitioning-ii​(#132)</a>








---

[//]: # (Image References)
[image1]: .readme/triangle_state_function.png "triangle_state_function"
[image2]: .readme/jump_game_ii.png "jump_game_ii"




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

<div id="jg" onclick="window.location.hash">

#### 3. ​jump-game​​(#55)
linkage: [leetcode](https://leetcode-cn.com/problems/jump-game/ "跳跃游戏")
> 非负整数数组，最初位于数组的第一个位置
> 每个元素代表该位置跳跃**最大长度**
> 判断是否能到最后一个位置
- 思路一：贪心法[从前向后]
  - 找到当前位置的最大步长
  - 索引到某一步数小于当前最大步长，返回false
```cpp
class Solution {
public:
    bool canJump(vector<int>& nums)
    {
        int k = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i > k) return false;
            k = max(k, i + nums[i]);
            // 优化
            if(k>=nums.size()-1)
                break;
        }
        return true;
    }
};
```
- 思路二：贪心法[从后向前]
```cpp
class Solution {
public:
    bool canJump(vector<int>& nums)
    {
        int last = nums.size()-1;
        // 从后向前遍历
        for(int i= last-1;i>=0;i--)
        {
            if(i+nums[i]>=last)
            {
                last = i;
            }
        }
        return last==0;
    }
};
```
- 思路三：dp(**推荐**)
  - 1. 动态规划法dp[i]表示i下标能不能到达
  - 2. dp[i]能否到达取决于dp[0:i-1]中能到达的地方
  - 3. dp[j]为dp[i]的某个位置,当dp[j]=true且nums[j]+j>=i,则i就能到达
  - 4. dp方程存在i>j,dp[j]=true,nums[j]+j>=i,则dp[i]=true
  ```cpp
  class Solution {
  public:
      bool canJump(vector<int>& nums)
      {
          vector<bool> dp(nums.size(),false);
          // 第一个格子一定能到达
          dp[0] = true;
          for(int i=0;i<=nums.size()-1;i++)
          {
              //优化一：从最后一个遍历
              for(int j=i;j>=0;j--)
              {
                  if(dp[j]==true && j+nums[j]>=i)
                  {
                      dp[i] = true;
                      // 优化二：找到最后一个直接跳出循环
                      break;
                  }
              }
          }
          return dp[nums.size()-1];
      }
  };
  ```
---

#### 4. ​jump-game-ii​​(#45)
linkage: [leetcode](https://leetcode-cn.com/problems/jump-game-ii/ "跳跃游戏 II")
> 与T3相同，多加一个条件:**最少跳跃步数**
> 输出最少跳跃步数
- 思路一：贪心法
```cpp
class Solution {
public:
    int jump(vector<int>& nums)
    {
        int max_step = 0;
        int end_max_step = 0;
        int count = 0;
        // 注意：一定能跳到终点，i的索引到终点的前一个
        for(int i = 0; i<nums.size()-1;i++)
        {
            max_step = max(nums[i]+i,max_step);
            if(i==end_max_step)
            {
                end_max_step = max_step;
                count++;
            }
        }
        return count;
    }
};
```
- 扩展：
  - 添加条件：如果不能跳到最后一个位置，返回-1
```cpp
class Solution {
public:
    int jump(vector<int>& nums) 
    {
        int max_step = 0;
        int end_max_step = 0;
        int count = 0;
        // 注意：不一定能跳到终点
        for(int i = 0; i<=nums.size()-1;i++)
        {
            if(i>max_step) return -1;
            if(i == nums.size()-1) break;
            max_step = max(nums[i]+i,max_step);
            if(i==end_max_step)
            {
                end_max_step = max_step;
                count++;
            }
        }
        return count;
    }
};
```
- 思路二：dp未优化版(无法ac，推荐)
  - 利用vector存储当前步数的值
  - 核心思想：若到i最少需要n步跳跃，则跳到i前面的点一定会小于等于n步
![][image2]
  - 如图，例如：要确定dp[5]的值，根据dp[4]=2;则dp[5]一定等于dp[4]或者dp[4]+1
  - 状态转移方程：f[i] = min(f[j]+1,f[i])
  - 注意：状态，初始化，推导，结果(见注释)
```cpp
class Solution {
public:
    int jump(vector<int>& nums)
    {
        // 状态：dp[i] 表示从起点到当前位置最小次数
        // 推导：dp[i] = dp[j],nums[j]+j >=i,min(dp[j]+1，dp[i])
        // 初始化：dp[0] = 0
        // 结果：dp[n-1]
        vector<int> dp(nums.size());
        dp[0] = 0;
        for(int i = 1;i<nums.size();i++)
        {
            //nums[i]最大步数为i
            dp[i] = i;
            for(int j = 0; j<i; j++)
            {
                if(nums[j]+j >= i)
                {
                    dp[i]=min(dp[j]+1,dp[i]);
                }
            }
        }
        return dp[nums.size()-1];
    }
};
```
---

<div id="ppii" onclick="window.location.hash">

#### 6. ​​palindrome-partitioning-ii​(#132)
linkage: [leetcode](https://leetcode-cn.com/problems/palindrome-partitioning-ii/ "分割回文串 II")
> 将字符串s分割成一些子串，使每个子串都是回文串
> 返回返回符合要求的**最少分割次数**
- 思路一：dp
  - todo

