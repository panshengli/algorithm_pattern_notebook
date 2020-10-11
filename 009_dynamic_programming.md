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
  - 涉及子序列问题，十有八九都需要动态规划来解决
---
- **极不可能/不适用DP的条件**
  - 求出所有**具体**的方案而非方案**个数**
    - 如: 004_backtrack-T2(palindrome-partitioning)
  - 输入数据是一个**集合**而不是**序列**
    - 如: longest-consecutive-sequence
  - **暴力**算法的复杂度已经是**多项式**级别
    - 动态规划擅长与优化指数级别复杂度(2^n,n!)到多项式级别复杂度(n^2,n^3)
    - 不擅长优化 n^3 到 n^2
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
  * <a href="#jg">3. ​jump-game​​(#55, 推荐dp做法)</a>
  * <a href="#jgii">4. ​jump-game-ii​​(#45)</a>
  * <a href="./004_backTrack_algorithm.md">5. ​​palindrome-partitioning(#131, 非dp做法,回溯T2)</a>
  * <a href="#ppii">6. ​​palindrome-partitioning-ii​(#132, Tencent 2020-08-23 T5)</a>
  * <a href="#lps">7. ​​longest-palindromic-substring​(#5, 很棒的dp题解)</a>
  * <a href="#lis">8. longest-increasing-subsequence(#300, HuaWei&美团)</a>
  * <a href="#wb">9. ​word-break​(#139, 非常经典的dp)</a>
- Two Sequences DP (40%)
  * <a href="#lcs">10. longest-common-subsequence​​(#1143，**很经典的二维dp**，Google，阿里，网易)</a>
  * <a href="#ul">11. uncrossed-lines​​(#1035，T10的另一种表述方式)</a>
  * <a href="#mlors">12. maximum-length-of-repeated-subarray(#718，T10的同一类型)</a>
  * <a href="#ed">13. ​edit-distance​(#72，很棒的二维DP题型，Tencent)</a>
- Matrix (10%)
  * <a href="#mps">14. ​​minimum-path-sum​(#64，常规dp 美团)</a>
  * <a href="#up">15. ​​unique-paths(#62)​</a>
  * <a href="#upii">16. ​​unique-paths-ii(#63)​</a>
- Two Sequences DP (40%)
  * <a href="#lcs">17. longest-common-subsequence​(#1143)​</a>​
















---

[//]: # (Image References)
[image1]: .readme/triangle_state_function.png "triangle_state_function"
[image2]: .readme/jump_game_ii.png "jump_game_ii"
[image3]: .readme/dp_300.gif "longest_increasing_subsequence"
[image4]: .readme/dp_words_break.png "words_break"
[image5_1]: .readme/dp_insert.gif "dp_insert"
[image5_2]: .readme/dp_delete.gif "dp_delete"
[image5_3]: .readme/dp_replace.gif "dp_replace"








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
- 思路一：利用回溯方法
  - 讲所有的可能找到，最后取出最小的个数，导致超出时间限制
- 思路二：dp方法
  - 1. 思考状态
    - dp[i]：表示前缀子串s[0:i]分割成子串的最小分割次数
  - 2. 状态转移方程
    - 建立dp[i]与dp[i-1], ..., dp[0]
    - s[0:i]为回文串，dp[i]=0
    - s[0:i]非回文串，尝试枚举分割的边界j
      - s[j + 1, i]是回文串，则dp[i]在dp[j]上多一个分割
        ```cpp
        for(int j = 0; j < i; j++)
        {
          if(isPalindrome(s,j+1,i))
          {
            dp[i] = min(dp[i],dp[j]+1);
          }
        }
        ```
  - 3. 初始状态
    - 单个字符，s[0] = 0
  - 4. 输出
    - dp[length-1]
  ```cpp
  class Solution {
  public:
      int minCut(string s)
      {
          int len = s.length();
          if(len <2) return 0;
          vector<int> dp(len);
          // 对状态转移方程的处理
          for(int i = 0; i< len; i++)
          {
              dp[i] = i;
          }
          for(int i = 0; i < len; i++)
          {
              if(isPalindrome(s,0,i))
              {
                  dp[i] = 0;
                  continue;
              }
              for(int j = 0; j < i; j++)
              {
                  // 如果子串为回文串，那么需要在原有基础上加1
                  if(isPalindrome(s,j+1,i))
                  {
                      dp[i] = min(dp[i],dp[j]+1);
                  }
              }
          }
          return dp[len-1];
      }

      bool isPalindrome(const string& s, int start, int end)
      {
          for(int i = start, j = end; i < j; i++, j--)
          {
              if(s[i] != s[j])
              {
                  return false;
              }
          }
          return true;
      }
  };
  ```
---

<div id="lps" onclick="window.location.hash">

#### 7. ​​longest-palindromic-substring​(#5)
linkage: [leetcode](https://leetcode-cn.com/problems/longest-palindromic-substring/ "最长回文子串")
> 给定一个字符串s，找s中最长的回文子串
> 假设s的最大长度1000
- 思路一：brute
  - 时间复杂度：O(n^3), 时间超时
```cpp
class Solution {
public:
    string longestPalindrome(string s)
    {
        string res = "";
        int len = s.size();
        for(int i = 0; i < len; i++)
        {
            // 判断每个字符串是否为回文，注意max_length取法
            int max_length = len - i;
            for (int j = 1; j <= max_length; j++)
            {
                string sub_str = s.substr(i,j);
                if(isPalindrome(sub_str) && sub_str.size() > res.size())
                {
                    res = sub_str;
                }
            }
        }
        return res;
    }

    bool isPalindrome(const string& s)
    {
        for(int i = 0, j = s.size()-1; i < j; i++, j--)
        {
            if(s[i] != s[j])
            {
                return false;
            }
        }
        return true;
    }
};
```
- 思路二：dp(**推荐**)
  - 思路：
    - 1. 对于一个子串，如果是回文串，且长度大于2，首尾去除字母后，仍是回文串
    - 2. 用P(i,j)表示字符串s的第i到j个字母组成的串(下文表示成s[i:j])是否为回文串
      > P(i,j) = {true,​ Si​到Sj是回文串},{false,​ 其他情况：s[i,j]本身不是一个回文串，i>j, s[i,j]本身不合法}
  - 四要素：
    - 1. 状态转移方程: P(i,j)=P(i+1,j−1) && (Si​==Sj​)
    - 2. 边界条件: (j-1)-(i+1)+1 < 2, 即 j-i < 3
    - 3. 初值：p[i][i] = true
    - 4. 最终答案: P(i,j)=true中记录起始位置，最后截取
  ```cpp
  class Solution {
  public:
      string longestPalindrome(string s) 
      {
          int len = s.size();
          if(len < 2)
          {
              return s;
          }
          vector<vector<bool>> dp(len, vector<bool>(len,false));
          // 注意初值的选取
          int max_len = 1;
          int begin = 0;
          // 1. 初始化：填充对角线元素，一定是回文串
          for(int i = 0; i < len; i++)
          {
              dp[i][i] = true;
          }
          // 填充左下角位置[i+1][j-1]
          for(int j = 1; j < len; j++)
          {
              for(int i = 0; i < j; i++)
              {
                  if(s[i] != s[j])
                  {
                      dp[i][j] = false;
                  }
                  else
                  {
                      // 边界条件: 长度为0和1时 j-1-(i+1)+1 < 2
                      if(j-i < 3)
                      {
                          dp[i][j] = true;
                      }
                      // 状态方程
                      else
                      {
                          dp[i][j] = dp[i+1][j-1];
                      }
                  }
                  // 输出条件
                  if(dp[i][j] && j-i+1 > max_len)
                  {
                      max_len = j-i+1;
                      begin = i;
                  }
              }
          }
          return s.substr(begin,max_len);
      }
  };
  ```
---

<div id="lis" onclick="window.location.hash">

#### 8. longest-increasing-subsequence​​(#300，huawei&m美团)
linkage: [leetcode](https://leetcode-cn.com/problems/longest-increasing-subsequence/ "最长上升子序列")
> 一个无序的整数数组，找到最长上升子序列的长度
- 思路一：dp
![][image3]
  ```cpp
  class Solution {
  public:
      int lengthOfLIS(vector<int>& nums) 
      {
          int len = nums.size();
          if(len < 2)
          {
              return len;
          }
          // 初始状态情况
          vector<int> dp(len,1);
          int max_length = 0;
          for(int i = 0; i < len; i++)
          {
              // 临界条件
              for(int j = 0; j < i; j++)
              {
                  // 状态转移方程，注意j和i的比较
                  if(nums[j] < nums[i])
                  {
                      dp[i] = max(dp[i], dp[j]+1);
                  }
              }
          }
          // 最终结果
          for(int i = 0; i < len; i++)
          {
              max_length = max(max_length,dp[i]);
          }
          return max_length;
      }
  };
  ```
- 扩展：要求时间复杂度为O(nlogn)的解法
  - 思路一：二分法
    - todo
---

<div id="wb" onclick="window.location.hash">

#### 9. ​word-break​(#139，非常经典的dp)
linkage: [leetcode](https://leetcode-cn.com/problems/word-break/ "单词拆分")
> 一个非空字符串s和一个非空单词的列表wordDict
> s是否可以被空格拆分为一个或多个在字典中出现的单词
> 相关题目：583，1035，
- 思路一：dp
  - 状态转移方程：dp=[False,⋯ ,False]，长度为n+1。n为字符串长度。dp[i]表示s的前i位是否可以用wordDict中的单词表示
![][image4]
  - 初始化：dp[0]=True, 空字符可以被表示
  - 最终结果：dp[n]
  - 临界条件：
    - 索引i，遍历区间[0,n)
    - 索引j，遍历区间[i+1,n+1)
  - 注意：
    - set的查找用法

  ```cpp
  class Solution {
  public:
      bool wordBreak(string s, vector<string>& wordDict) 
      {
          unordered_set<string> set_words;
          for(auto x : wordDict)
          {
              set_words.insert(x);
          }
          vector<bool> dp(s.size()+1,false);
          // 1. 初始值
          dp[0] = true;
          // 2. 临界条件
          for(int i = 1; i <= s.size(); i++)
          {
              for(int j = 0; j < i; j++)
              {
                  // 注意：i-j为字符串长度，由于从1开始
                  auto sub_str = s.substr(j, i-j);
                  // 3. 状态转移方程
                  if(dp[j] && set_words.find(sub_str) != set_words.end())
                  {
                      dp[i] = true;
                      break;
                  }
                  
              }
          }
          // 4. 最终结果
          return dp[s.size()];
      }
  };
  ```
---
- 对于序列类型的问题，如T9. 常见处理方式：
  - 给 0 位置占位
  - 初始化则在原来基础上length+1
  - 返回结果f[n]
---

<div id="lcs" onclick="window.location.hash">

#### 10. longest-common-subsequence​​(#1143，很经典的二维dp)
linkage: [leetcode](https://leetcode-cn.com/problems/longest-common-subsequence/ "最长公共子序列")
> 给定两个字符串text1和text2，返回这两个字符串的最长公共子序列的长度
> 若这两个字符串没有公共子序列，则返回0
- 思路一：二维dp
  - 和跳跃游戏类似
  - 注意dp在首部加一个值，被设为初始值
  - 注意状态转移方程的写法，用笔画
```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        if(text1.size() == 0 || text2.size() == 0)
        {
            return 0;
        }
        // 1. 初始值
        vector<vector<int>> dp(text1.size()+1, vector<int>(text2.size()+1,0));
        // 2. 边界条件
        for(int i = 1; i <= text1.size(); i++)
        {
            for(int j = 1; j <= text2.size(); j++)
            {
                // 3. 状态转移方程
                if(text1[i-1] == text2[j-1])
                {
                    dp[i][j] = dp[i-1][j-1]+1;
                }
                else
                {
                    dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
                }
            }
        }
        // 4. 最终结果
        return dp[text1.size()][text2.size()];
    }
};
```
---

<div id="ul" onclick="window.location.hash">

#### 11. uncrossed-lines​​(#1035，T10同类型)
linkage: [leetcode](https://leetcode-cn.com/problems/uncrossed-lines/description/ "不相交的线")
> 两条独立的水平线上按给定的顺序写下A和B中的整数
> 绘制一些连接两个数字 A[i] 和 B[j] 的直线
> 要A[i] == B[j]，且绘制的直线不与任何其他连线(非水平线)相交
> 返回绘制的最大连线数
- 思路一：二维dp
  - 本题就是T10的最长公共子串的另一种描述
  - 核心代码一模一样，解法略
---

<div id="mlors" onclick="window.location.hash">

#### 12. maximum-length-of-repeated-subarray(#718，T10的同一类型)
linkage: [leetcode](https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/ "最长重复子数组")
> 两个整数数组A和B
> 返回数组中公共的、长度最长的子数组的长度
思路一：二维dp
- 注意：状态转移矩阵的表达
  ```cpp
  class Solution {
  public:
      int findLength(vector<int>& A, vector<int>& B) 
      {
          if(A.size() == 0 || B.size() == 0)
          {
              return 0;
          }
          int ans = 0;
          vector<vector<int>> dp(A.size()+1, vector<int>(B.size()+1, 0));
          for(int i = 1; i <= A.size(); i++)
          {
              for(int j = 1; j <= B.size(); j++)
              {
                  if(A[i-1] == B[j-1])
                  {
                      dp[i][j] = dp[i-1][j-1] + 1;
                      // 注意：此处状态转移矩阵的选取
                      ans = max(ans, dp[i][j]);
                  }
              }
          }
          return dp[A.size()][B.size()];
      }
  };
  ```
---

<div id="ed" onclick="window.location.hash">

#### 13. ​edit-distance​(#72，很棒的二维DP题型，Tencent)
linkage: [leetcode](https://leetcode-cn.com/problems/edit-distance/ "编辑距离")
> 两个单词word1和word2
> 计算将word1转换成word2所使用的最少操作数
> 可对单词进行插入、删除、替换操作
- 思路一：二维dp
  - 1. 初始值: 注意临街值的选取(重要)
  - 2. 状态转移方程：
    - i:操作串， j：目标串
    - 相等时 dp[i][j] = dp[i-1][j-1]
    - 插入 dp[i][j] = dp[i][j-1] +1
![][image5_1]
    - 删除 dp[i][j] = dp[i-1][j] +1
![][image5_2]
    - 替换 dp[i][j] = dp[i-1][j-1] +1
![][image5_3]
  ```cpp
  class Solution {
  public:
      int minDistance(string word1, string word2) 
      {
          vector<vector<int>> dp(word1.size()+1, vector<int>(word2.size()+1,0));
          // 1. 初始值
          for (int i = 0; i <= word1.size(); i++) {
              dp[i][0] = i;
          }
          for (int j = 0; j <= word2.size(); j++) {
              dp[0][j] = j;
          }
          // 2. 边界条件
          for(int i = 1; i <= word1.size(); i++)
          {
              for(int j = 1; j <= word2.size(); j++)
              {
                  // 3. 状态转移方程
                  if(word1[i-1] == word2[j-1])
                  {
                      dp[i][j] = dp[i-1][j-1];
                  }
                  else
                  {
                      dp[i][j] = min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1])+1;
                  }
              }
          }
          // 4. 最终结果

          return dp[word1.size()][word2.size()];
      }
  };
  ```

<div id="mps" onclick="window.location.hash">

#### 14. ​​minimum-path-sum​(#64)
linkage: [leetcode](https://leetcode-cn.com/problems/minimum-path-sum/ "最小路径和")
> 非负整数的[m,n]网格
> 找出从左上到右下路径和最小,输出路径和
> 每次只能向下或向右移动一次
- 思路一：dp
  - 注意临界的几种条件
  ```cpp
  class Solution {
  public:
      int minPathSum(vector<vector<int>>& grid) 
      {
          if(grid.size() == 0)
              return 0;
          if(grid[0].size() == 0)
              return 0;
          vector<vector<int>> dp(grid.size(),vector<int>(grid[0].size(),0));
          for(int i = 0; i < grid.size(); i++)
          {
              for(int j = 0; j < grid[0].size(); j++)
              {
                  if(i == 0 && j == 0)
                  {
                      // 初始值
                      dp[0][0] = grid[0][0];
                  }
                  // 注意dp的条件
                  else if(i !=0 && j == 0)
                  {
                      dp[i][j] = dp[i-1][j] + grid[i][j];
                  }
                  else if(i == 0 && j != 0)
                  {
                      dp[i][j] = dp[i][j-1] + grid[i][j];
                  }
                  else
                  {
                      dp[i][j] = min(dp[i-1][j],dp[i][j-1]) + grid[i][j];
                  }
              }
          }
          return dp[grid.size()-1][grid[0].size()-1];
      }
  };
  ```
---

<div id="up" onclick="window.location.hash">

#### 15. ​​unique-paths​(#62)
linkage: [leetcode](https://leetcode-cn.com/problems/unique-paths/ "不同路径")
> 机器人位于一个mxn网格的左上角, 每次只能向下或者向右移动一步,到达右下角;
> 共有多少条不同的路径？
思路一： 二维dp(独立写出)
    - 画格子，直接找到状态转移方程
    ```cpp
    class Solution {
    public:
        int uniquePaths(int m, int n) 
        {
            // 初始值
            vector<vector<int>> dp(m,vector<int>(n,1));
            for(int i = 1; i < m; i++)
            {
                for(int j = 1; j < n; j++)
                {
                dp[i][j] = dp[i][j-1] + dp[i-1][j];
                }
            }
            return dp[m-1][n-1];
        }
    };
    ```
---

<div id="upii" onclick="window.location.hash">

#### 16. ​​unique-paths-ii​(#63)
linkage: [leetcode](https://leetcode-cn.com/problems/unique-paths-ii/ "不同路径 II")
> 机器人位于一个mxn网格的左上角, 每次只能向下或者向右移动一步,到达右下角
> 网格中有障碍物, 障碍物和空位置分别用 1 和 0 来表示
> 共有多少条不同的路径？
- 思路一：二维dp
  - 重点是对障碍物的处理，状态转移方程和t15一样
    ```cpp
    class Solution {
    public:
        int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
        {
            int m = obstacleGrid.size();
            int n = obstacleGrid[0].size();
            vector<vector<int>> dp(m,vector<int>(n,0));
            // 初始值，重点是判断网格是否存在障碍物
            for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) {
                dp[i][0] = 1;
            }
            for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) {
                dp[0][j] = 1;
            }
            for(int i = 1; i < m; i++)
            {
                for(int j = 1; j < n; j++)
                {
                    if(obstacleGrid[i][j] == 0)
                    {
                        dp[i][j] = dp[i][j-1] + dp[i-1][j];
                    }
                }
            }
            return dp[m-1][n-1];
        }
    };
    ```
---

<div id="lcs" onclick="window.location.hash">

#### 17. longest-common-subsequence​(#1143)
linkage: [leetcode](https://leetcode-cn.com/problems/longest-common-subsequence/ "最长公共子序列")
> 给定两个字符串，返回最长公共子序列的长度
