## Slide Window 
- 滑动窗口:两个指针一前一后夹着的子串（子数组）类似一个窗口，这个窗口大小和范围会随着前后指针的移动发生变化。
- 两类问题：
  - 双指针
  - 特定数据结构，如sorted_map
- **核心点**是维护一个窗口集，根据窗口集来进行处理
- 核心步骤
  - 1. 设定两个指针，l和r，表示滑动窗口最左端和最右端,初始，两个指针指向S的第一个字符
  - 2. l不动，r向右移动，直到找到一个字符串能匹配T串,即match匹配串
  - 3. 右移动l，同时每右移一次l,通过右移r找match的字符串
  - 4. 如果能找到，且比当前串短，update。如果找不到，继续右移动left
--- 

## 📑 index
* <a href="#mws">1. minimum-window-substring(#76)</a>






---

[//]: # (Image References)
[image1]: .readme/slide_window1.gif "slide window"




<div id="mws" onclick="window.location.hash">

#### 1. minimum-window-substring(#76，很棒的滑动窗口题型)
linkage: [leetcode](https://leetcode-cn.com/problems/minimum-window-substring/ "最小覆盖子串")
> 一个字符串S、一个字符串T
> 字符串S里面找出：包含T所有字符的最小子串
> 不存这样的子串，则返回空字符串""
> 要求O(n)的时间复杂度
- 思路一：滑动窗口
  - 步骤：
    - 1. 通过hash_map找到其实覆盖子串
      - 统计t的hash关系
      - 利用t的字符统计s的hash
    - 2. 检查
    - 2. 左窗口移动，右窗口再找覆盖子串，update最短子串
![][image1]
  ```cpp
  class Solution {
  public:
      string minWindow(string s, string t) 
      {
          if(s.size()< t.size() || t.size() == 0)
              return "";
          // 重点3：对t进行字符串hash统计
          for(auto t_char : t)
          {
              t_map_[t_char]++;
          }

          int lhs = 0;
          int rhs = 0;
          int minLen = INT_MAX;
          int startLen = -1;
          // 右滑动开始遍历s子串
          while(rhs < s.size())
          {
              // 重点2：对s中字符是否存在t中字符进行hash统计
              if(t_map_.find(s[rhs]) != t_map_.end())
              {
                  s_map_[s[rhs]]++;
              }
              // 查找滑动窗口
              while(check() && lhs <= rhs)
              {
                  if(rhs-lhs+1 < minLen)
                  {
                      minLen = rhs-lhs+1;
                      startLen = lhs;
                  }
                  // 滑动左窗口移动
                  if(t_map_.find(s[lhs]) != t_map_.end())
                  {
                      s_map_[s[lhs]]--;
                  }
                  lhs++;
              }
              // 注意rhs的++
              rhs++;
          }
          return startLen == -1 ? "" : s.substr(startLen,minLen);
      }

      bool check()
      {
          // 重点1：检查是否存在公共子串：s_key的count是否大于t_key的count
          for(auto t_key : t_map_)
          {
              if(s_map_[t_key.first] < t_key.second)
              {
                  return false;
              }
          }
          return true;
      }

  private:
      unordered_map<char, int> s_map_, t_map_;
  };
  ```
---

