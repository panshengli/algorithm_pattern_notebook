## BackTrack Algorithm
- 回溯法(backtrack)常用于遍历列表所有子集，是DFS的一种
- 时间复杂度一般O(N!)，纯暴力穷举
- 核心思路
  - 从选择列表里做一个选择
  - 然后一直递归往下搜索答案
  - 如果遇到路径不通，就返回来撤销这次选择
- DFS和BackTrace区别
  - DFS是一直向一个方向搜索
  - 回溯算法在DFS基础之上，但在搜索过程中，达到结束条件后，恢复状态，回溯上一层，再次搜索。
- 使用回溯条件
  - 当问题需要"回头"，查找出**所有的解**的情况
---
## 📑 index
* <a href="#subsets">1. subSets(#78)</a>
* <a href="#pp">2. ​​palindrome-partitioning(#131)[非dp做法,回溯]</a>







---

<div id="subSets" onclick="window.location.hash">

#### 1. subSets(#78)
linkage: [leetcode](https://leetcode-cn.com/problems/subsets/ "查找集合所有子集")
> 给定一组不含重复元素的整数数组nums，返回所有可能的子集
1. backtrack algorithm

    ```go
    // ADT
    // 应用回溯法的题目，简单来说就是穷尽所有可能性
    // 通过不停的选择，撤销选择，来穷尽所有可能性，最后将满足条件的结果返回
    result = []
    func backtrack(选择列表,路径):
    if (终止条件):
        result.add(路径)
        return
    for 选择 in 选择列表:
        做选择
        backtrack(选择列表,路径)
        撤销选择
    ```

    ```cpp
    class Solution {
    public:
        vector<vector<int>> subsets(vector<int>& nums)
        {
            vector<vector<int>> res;
            vector<int> tmp;
            backtrack(nums,res,tmp,0);
            return res;
        }
        void backtrack(vector<int>& nums,vector<vector<int>>& res,vector<int> tmp,int index)
        {
            res.push_back(tmp);//由于所有子集都要，所以不用判断返回条件
            for(int i=index;i<nums.size();i++)
            {
                // 做出选择
                tmp.push_back(nums[i]);
                // 递归进入下一层，注意i+1，标识下一个选择列表的开始位置，最重要的一步
                backtrack(nums,res,tmp,i+1);
                //撤销选择
                tmp.pop_back();
            }
        }
    };
    ```
---

<div id="pp" onclick="window.location.hash">

#### 2. ​​palindrome-partitioning(#131)[非dp做法,回溯]
linkage: [leetcode](https://leetcode-cn.com/problems/palindrome-partitioning/ "分割回文串")
> 将字符串s分割成一些子串，使每个子串都是回文串
> 返回s所有可能的分割方案
- 思路一：backtrack
  - 经过分析，**一般情况下返回所有可能的方案，不能使用dp的情况**
  ```cpp
  class Solution {
  public:
      vector<vector<string>> partition(string s)
      {
          backtracking(s, 0);
          return result_;
      }

      void backtracking(const string& s,int startIndex)
      {
          // 申明临时变量path，注意最后要还原path
          static vector<string> path;
          // backtracking
          // 1. 回溯结束条件
          if(startIndex >= s.size())
          {
              result_.push_back(path);
              return;
          }
          // 2. 回溯选择处理
          for(int i=startIndex; i<s.size(); i++)
          {
              // 判断是否palindrome
              if(isPalindrome(s,startIndex,i))
              {
                  string palindrome_str = s.substr(startIndex,i-startIndex+1);
                  path.push_back(palindrome_str);
              }
              else
              {
                  continue;
              }
              // 进行回溯递归
              backtracking(s,i+1);
              // 还原方案，为下一次backtracking准备
              path.pop_back();
          }
      }

      bool isPalindrome(const string& s, int start, int end)
      {
          // 注意结束判断的条件
          for(int i = start, j = end; i < j; i++, j--)
          {
              if(s[i] != s[j])
              {
                  return false;
              }
          }
          return true;
      }
  private:
      vector<vector<string>> result_;
  };
  ```
---