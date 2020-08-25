## binarySearch Algorithm


[//]: # (Image References)
[image1]: .readme/binary_search_template.png "binary_search_template"


##### 二分搜索模板
- 给一个**有序数组**和目标值，找第一次/最后一次/任何一次出现的索引，如果没有出现返回-1
- **模板四要素**
    - 1、初始化：start=0、end=len-1
    - 2、**循环退出条件：start + 1 < end**
    - 3、比较中点和目标值：A[mid] ==、 <、> target
    - 4、**判断最后两个元素是否符合**：A[start]、A[end] ? target
- 时间复杂度 O(logn)，使用场景一般是**有序数组**的查找
- 三种模板,**注意判断循环退出条件**
![binary_search_template][image1]
- 这 3 个模板的不同之处在于：
  - 左、中、右索引的分配。
  - 循环或递归终止条件。
  - 后处理的必要性。
- 模板 #1 和 #3 是最常用的，几乎所有二分查找问题都可以用其中之一轻松实现
- 模板 #2 更 高级一些，用于解决某些类型的问题。
- 详细可见：[二分查找模板分析](https://leetcode-cn.com/leetbook/read/binary-search/xewjg7/)
---

## 📑 index
* <a href="#bs">1. binary-search(#704)[典型示例]</a>
* <a href="#sfr">2. ​search-for-range​(#61_lintcode)</a>









---
<div id="bs" onclick="window.location.hash">

#### 1. binary-search(#704)
linkage: [leetcode](https://leetcode-cn.com/problems/binary-search/ "二分查找")
- 给一个有序数组和目标值，如果存在，返回目标索引，否则返回-1
- 思路一：迭代版本
  - 注意：
    - `left + (right - left) / 2` 和 `(left + right) / 2`结果相同，但防止了left和right太大直接相加导致溢出
    ```cpp
    class Solution {
    public:
        int search(vector<int>& nums, int target) 
        {
            if(nums.size() == 0)
                return -1;
            int start = 0;
            int end = nums.size()-1;
            // 一定要注意循环条件
            while(start <= end)
            {
                int mid = start+(end-start)/2;
                if(nums.at(mid) < target)
                    start = mid+1;
                else if(nums.at(mid) > target)
                    end = mid-1;
                else 
                    return mid;
            }      
            return -1;
        }
    };
    ```
    ```cpp
    // 模板三：大部分场景模板#3 都能解决问题，而且还能找第一次/最后一次出现的位置，应用更加广泛
    class Solution {
    public:
        int search(vector<int>& nums, int target) 
        {
            if(nums.size() == 0)
            {
                return -1;
            }
            int start = 0;
            int end = nums.size()-1;
            while(start+1 < end)
            {
                int mid = (start+end+1)/2;
                if(nums.at(mid) <= target)
                    start = mid;
                else
                    end = mid;
            }
            // 判断返回值是否为target
            if(nums[start] == target)
                return start;
            if(nums[end] == target)
                return end;
            return -1;
        }
    };
    ```
- 思路二：STL库
  - 注意：stl库的用法
    ```cpp
    class Solution {
    public:
        int search(vector<int>& nums, int target) 
        {
            auto ans = std::lower_bound(nums.begin(), nums.end(),target);
            // 注意：需要判断*ans和target的情况
            if(ans != nums.end() && *ans == target)
            {
                // An iterator to the lower bound of val in the range
                return ans-nums.begin();
            }
            return -1;
        }
    };
    ```
- 思路三：递归版本
- 注意递归的定义，返回值，递归的调用及结束条件
    ```cpp
    class Solution {
    public:
        int search(vector<int>& nums, int target) 
        {
            if(nums.size() == 0)
                return -1;
            int start = 0;
            int end = nums.size()-1;
            // 注意：递归的调用
            return dfs(nums,start, end, target);
        }

        int dfs(vector<int>& nums, int start, int end, int target)
        {
            // 注意：递归结束条件
            if(start > end)
                return -1;
            int mid = start + (end-start)/2;
            if(nums[mid] > target)
                // 注意：递归的处理，需要return
                return dfs(nums,start,mid-1,target);
            else if(nums[mid] < target)
                return dfs(nums,mid+1,end,target);
            else
                return mid;
        }
    };
    ```
---

<div id="sfr" onclick="window.location.hash">

#### 2. ​search-for-range​(#61_lintcode)
linkage: [leetcode](https://www.lintcode.com/problem/search-for-a-range/description "搜索区间
")
- n个整数**排序数组**，找出target起始和结束位置
- 如不在，返回[-1, -1]
