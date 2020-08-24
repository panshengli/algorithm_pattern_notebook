## binarySearch Algorithm

##### 二分搜索模板
- 给一个**有序数组**和目标值，找第一次/最后一次/任何一次出现的索引，如果没有出现返回-1
- **模板四要素**
    - 1、初始化：start=0、end=len-1
    - 2、**循环退出条件：start + 1 < end**
    - 3、比较中点和目标值：A[mid] ==、 <、> target
    - 4、**判断最后两个元素是否符合**：A[start]、A[end] ? target
- 时间复杂度 O(logn)，使用场景一般是**有序数组**的查找
---

## 📑 index
* <a href="#bs">1. binary-search(#704)[典型示例]</a>





---
<div id="bs" onclick="window.location.hash">

#### 1. binary-search(#704)
linkage: [leetcode](https://leetcode-cn.com/problems/binary-search/ "二分查找")
- 给一个有序数组和目标值，如果存在，返回目标索引，否则返回-1
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
        while(start+1 < end)
        {
            int mid = start+(end-start)/2;
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
        // 注意：结果返回-1，因为值可能不在数组中        
        return -1;
    }
};
```

