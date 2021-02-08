## Slide Window 
- 滑动窗口: 两个指针一前一后夹着的子串（子数组）类似一个窗口，这个窗口大小和范围会随着前后指针的移动发生变化。
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
* <a href="#mws">1. minimum-window-substring(#76，很棒的滑动窗口题型)</a>
* <a href="#pis">2. permutation-in-string(#567,比较典型的滑动窗口思路)</a>
* <a href="#faaias">3. find-all-anagrams-in-a-string(#438，和T2相同)</a>
* <a href="#lswrc">4. longest-substring-without-repeating-characters(#3)</a>







---

[//]: # (Image References)
[image1]: .readme/slide_window1.gif "slide window"
[image2]: .readme/slide_window2.gif "slide window"
[image3]: .readme/hash_map.gif "hash_map"


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

<div id="pis" onclick="window.location.hash">

#### 2. permutation-in-string(#567)
linkage: [leetcode](https://leetcode-cn.com/problems/permutation-in-string/ "字符串的排列")
> 给定两个字符串s1和s2
> 第一个字符串的排列之一是第二个字符串的子串
- 思路：滑动窗口
  - 通过比较巧妙地方式：用哈希表记录窗口中各个字符出现次数的差值
    - 正数表示还应该出现几次
    - 0表示正好
    - 负数表示多出现了几次
  ```cpp
  class Solution {
  public:
      bool checkInclusion(string s1, string s2) 
      {
          if(s1.size() > s2.size() || s2.size() == 0 )
          {
              return false;
          }
          if(s1.size() == 0)
          {
              return true;
          }
          unordered_map<char, int> s1_map;
          // 对s1进行hash操作
          for(auto s1_key : s1)
          {
              s1_map[s1_key]++;
          }
          int lhs = 0;
          int rhs = 0;
          while(rhs < s2.size())
          {
              char s2_key = s2[rhs++];
              s1_map[s2_key]--;
              // 正数表示还应该出现几次
              // 0表示正好
              // 负数表示多出现了几次
              while(lhs < rhs && s1_map[s2_key] < 0)
              {
                  // 减去后加回去
                  s1_map[s2[lhs++]] ++;
              }
              if (rhs - lhs == s1.size())
              {
                  return true;
              }
          }
          return false;
      }
  };
  ```
---

<div id="faaias" onclick="window.location.hash">

#### 3. find-all-anagrams-in-a-string(#438)
linkage: [leetcode](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/ "找到字符串中所有字母异位词")
> 给定一个字符串s和一个非空字符串p
> 找到s中所有是p的字母异位词的子串
> 返回这些子串的起始索引
- 思路：滑动窗口
  - 和T2相同思路
  ```cpp
  class Solution {
  public:
      vector<int> findAnagrams(string s, string p) 
      {
          if(s.size() < p.size() || p.size() == 0)
              return vector<int>();
          unordered_map<char,int> p_map;
          for(auto p_key : p)
          {
              p_map[p_key]++;
          }
          int lhs = 0;
          int rhs = 0;
          vector<int> nums;
          while(rhs < s.size())
          {
              // 重点一：首先对p_map进行处理
              char s_key = s[rhs++];
              p_map[s_key]--;
              while(lhs < rhs && p_map[s_key] < 0)
              {
                  //处理后进行还原
                  p_map[s[lhs++]]++;
              }
              if(rhs - lhs == p.size())
              {
                  nums.push_back(lhs);
              }
          }
          return nums;
      }
  };
  ```
---

<div id="lswrc" onclick="window.location.hash">

#### 4. longest-substring-without-repeating-characters(#3)
linkage: [leetcode](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/ "无重复字符的最长子串")
> 给定一个字符串，找出**不含有重复字符**的**最长子串**的长度
- 思路：滑动窗口+hashSet/hashMap
    ```cpp
    class Solution {
    public:
        int lengthOfLongestSubstring(string s)
        {
            if(s.size() == 0)
                return 0;
            unordered_set<char> s_set;
            int lhs(0), rhs(0), max_len(0);
            while(rhs < s.size())
            {
                // 2. 如果找到，删除前面的可以
                if(s_set.find(s[rhs]) != s_set.end())
                {
                    s_set.erase(s[lhs]);
                    lhs++;
                }
                // 1. 如果没找到，添加key，计算长度
                else
                {
                    s_set.insert(s[rhs]);
                    max_len = max(max_len, rhs-lhs+1);
                    rhs++;
                }
                
            }
            return max_len;
        }
    };
    ```
---

