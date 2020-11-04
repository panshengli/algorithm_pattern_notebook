## binarySearch Algorithm


[//]: # (Image References)
[image1]: .readme/binary_search_template.png "binary_search_template"
[image2]: .readme/binary_search_find_repeat_nums.png "binary_search_find_repeat_nums"


##### 二分搜索模板
> 给一个**有序数组**和目标值，找第一次/最后一次/任何一次出现的索引，如果没有出现返回-1
- **二分法核心模板四要素(必备&理解)**
  - 1、**初始化**：start=0、end=len-1
  - 2、**循环退出条件**：start + 1 < end
  - 3、比较**中点和目标值**：A[mid] ==、 <、> target
  - 4、**临界条件判断**：A[start]、A[end] ? target
- 三种模板,**注意判断循环退出条件**
- 模板 #1 标准的二分查找模板
  - 单个索引来确定的元素
  - 不需要后处理
    ```cpp
    int binarySearch(vector<int>& nums, int target)
    {
        if(nums.size() == 0)
            return -1;

        int left = 0, right = nums.size() - 1;
        while(left <= right)
        {
            // Prevent (left + right) overflow
            int mid = left + (right - left) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        // End Condition: left > right
        return -1;
    }
    ```

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
* <a href="#bs">1. binary-search(#704)[**典型示例，注意不同模板和递归的写法**]</a>
* <a href="#sfr">2. ​search-for-range​(#61_lintcode)</a>
* <a href="#sip">3. ​search-insert-position​(#35)</a>
* <a href="#sa2m">4. search-a-2d-matrix​​(#74)[重点查看矩阵的遍历]</a>
* <a href="#fbv">5. ​first-bad-version​​​(#278)</a>
* <a href="#fmirsa">6. find-minimum-in-rotated-sorted-array​​​​(#153)</a>
* <a href="#fmirsaii">7. find-minimum-in-rotated-sorted-array​​​​-ii(#154)[**利用二分法查找重复的最小值**]</a>
* <a href="#sirsa">8. ​search-in-rotated-sorted-array​(#33)[**利用二分法查找target**]</a>
* <a href="#sirsaii">9. ​search-in-rotated-sorted-array-ii​(#81)[**利用二分法查找重复target**]</a>


## 扩展题型
  - 二分应用：
    - #69.x的平方根(模板#1,#374与之相同) [linkage](https://leetcode-cn.com/problems/sqrtx/)





---

<div id="bs" onclick="window.location.hash">

#### 1. binary-search(#704)
linkage: [leetcode](https://leetcode-cn.com/problems/binary-search/ "二分查找")
> 给一个有序数组和目标值，如果存在，返回目标索引，否则返回-1
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
            // [左开右闭]初始化
            int start = 0;
            int end = nums.size();
            // 循环条件退出
            while(start + 1 < end)
            {
                int mid = start+(end-start)/2;
                if(nums.at(mid) == target)
                    return mid;
                else if(nums.at(mid) > target)
                    end = mid;
                else if(nums.at(mid) < target)
                    start = mid;
            }
            // 注意处理边界条件
            if(nums[start] == target)
                return start;
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
            auto ans = std::lower_bound(nums.begin(), nums.end(), target);
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
> n个整数**排序数组**，找出target起始和结束位置
> 如不存在，返回[-1, -1]
- 思路：迭代版
  - 利用题1迭代版本的模板1
  - 首先找到target是否存在
  - 存在，进行前后遍历
  - 重点处理数组是否越界问题
```cpp
class Solution {
public:
    /**
     * @param A: an integer sorted array
     * @param target: an integer to be inserted
     * @return: a list of length 2, [index1, index2]
     */
    vector<int> searchRange(vector<int> &A, int target)
    {
        std::vector<int> len_index;
        // write your code here
        if(A.size() == 0)
            return vector<int>(2,-1);
        int start = 0;
        int end = A.size()-1;
        while(start <= end)
        {
            int mid = start + ((end-start)>>1);
            if(A.at(mid) == target)
            {
                // 重点位置
                int pre = mid;
                int next = mid;
                // 防止数组越界
                if(A.size()>1)
                {
                    while(next+1<=A.size()-1 && A[next+1]==target)
                    {
                        next++;
                    }
                    while( A[pre-1]==target&&pre-1>=0)
                    {
                        pre--;
                    }
                }
                len_index.push_back(pre);
                len_index.push_back(next);
                return len_index;
            }
            else if(A.at(mid) > target)
            {
                end = mid - 1;
            }
            else if(A.at(mid) < target)
            {
                start = mid + 1;
            }
        }
        return vector<int>(2,-1);
    }
};
```
---

<div id="sip" onclick="window.location.hash">

#### 3. ​search-insert-position​(#35)
linkage: [leetcode](https://leetcode-cn.com/problems/search-insert-position/ "搜索插入位置")
> 排序数组和一个目标值，找到目标值，返回索引
> 如果不存在，返回按顺序插入的位置
- 思路：迭代版本
  - 参考题1模板1，注意最后返回值的处理
    ```cpp
    class Solution {
    public:
        int searchInsert(vector<int>& nums, int target)
        {
            if(nums.size() == 0)
                return 0;
            int start = 0;
            int end = nums.size()-1;
            while(start<=end)
            {
                int mid = start + ((end-start)>>1);
                if(nums[mid] == target)
                {
                    return mid;
                }
                else if(nums[mid] < target)
                {
                    start = mid + 1;
                }
                else if(nums[mid] > target)
                {
                    end = mid - 1;
                }
            }
            // 注意返回start或者end+1
            return start;
        }
    };
    ```
---

<div id="sa2m" onclick="window.location.hash">

#### 4. search-a-2d-matrix​​(#74)
linkage: [leetcode](https://leetcode-cn.com/problems/search-a-2d-matrix/ "搜索二维矩阵")
> 判断mxn矩阵,是否存在一个目标值
>  - 每行中的整数从左到右按升序排列
>  - 每行的第一个整数大于前一行的最后一个整数
- 思路：迭代法(利用模板#1)
```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        if(matrix.size() == 0 || matrix[0].size() == 0)
        {
            return false;
        }
        int m = matrix.size();
        int n = matrix[0].size();
        int start = 0;
        int end = m*n - 1;
        while(start <= end)
        {
            int mid = start + (end-start) / 2;
            if(matrix[mid/n][mid%n] == target)
            {
                return true;
            }
            // 重点：理解矩阵中行和列的取法
            else if(matrix[mid/n][mid%n] > target)
            {
                end = mid - 1;
            }
            else if(matrix[mid/n][mid%n] < target)
            {
                start = mid + 1;
            }
        }
        return false;
    }
};
```
---

<div id="fbv" onclick="window.location.hash">

#### 5. ​first-bad-version​​​(#278)
linkage: [leetcode](https://leetcode-cn.com/problems/first-bad-version/ "第一个错误的版本")
> 每个版本都是基于之前的版本开发的,找出第一个错误版本
- 思路一：迭代法(基于模板#1)
    ```cpp
    class Solution {
    public:
        int firstBadVersion(int n)
        {
            if(n == 0)
            {
                return 0;
            }
            int start = 0;
            int end = n-1;
            while(start <= end)
            {
                int mid = start + (end - start)/2;
                if(isBadVersion(mid) == false)
                {
                    start = mid + 1;
                }
                else
                {
                    end = mid-1;
                }
            }
            return start;
        }
    };
    ```
---

<div id="fmirsa" onclick="window.location.hash">

#### 6. find-minimum-in-rotated-sorted-array​​​​(#153)
linkage: [leetcode](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/ "寻找旋转排序数组中的最小值")
> 升序排序的数组,在未知某点旋转,找出最小元素
- 思路一：左闭右闭区间
    ```cpp
    class Solution {
    public:
        int findMin(vector<int>& nums)
        {
            int start = 0;
            int end = nums.size()-1;
            while(start<=end)
            {
                // 重点：如果[left,right]递增，直接返回
                if(nums[start] <= nums[end])
                {
                    return nums[start];
                }
                int mid = start + ((end-start)>>1);
                // [left,mid]连续递增，则在[mid+1,right]查找
                if(nums[start] <= nums[mid])
                {
                    start = mid + 1;
                }
                // [left,mid]不连续，在[left,mid]查找
                else
                {
                    end = mid;
                }
            }
            return nums[start];
        }
    };
    ```
- 思路二：左开右闭区间(**推荐**)
  - 注意最后边界条件的处理
```cpp
class Solution {
public:
    int findMin(vector<int>& nums)
    {
        int start = 0;
        int end = nums.size()-1;
        while(start+1 < end)
        {
            if(nums[start] <= nums[end])
            {
                return nums[start];
            }
            int mid = start + ((end-start)>>1);
            if(nums[start]<=nums[mid])
            {
                start = mid;
            }
            else
            {
                end = mid;
            }
        }
        if(nums[start] < nums[end])
            return nums[start];
        return nums[end];
    }
};
```
---

<div id="fmirsaii" onclick="window.location.hash">

#### 7. find-minimum-in-rotated-sorted-array​​​​-ii(#154)
linkage: [leetcode](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/ "寻找旋转排序数组中的最小值ii")
> 升序排序重复的数组,在未知某点旋转,找出最小元素
- 思路一：模板三
  - 注意mid和最右值end比较，如图
  - 最小值右边的点一定小于等于end点，最小值左边的点一定大于等于end点
![][image2]
    ```cpp
    class Solution {
    public:
        int findMin(vector<int>& nums)
        {
            int start = 0;
            int end = nums.size()-1;
            while(start+1 < end)
            {
                int mid = start + ((end - start)>>1);
                // 如果mid小于最大值，那么最小值一定在mid的左边
                if(nums[mid] < nums[end])
                {
                    end = mid;
                }
                // 如果mid大于最大值，那么最小值一定在mid的右边
                else if(nums[mid] > nums[end])
                {
                    start = mid;
                }
                // 如果相等，不知在哪边，所以最右值向前移动
                else
                {
                    end--;
                }
            }
            // 处理临界情况
            return nums[start]<=nums[end] ? nums[start] : nums[end];
        }
    };
    ```
---

<div id="sirsa" onclick="window.location.hash">

#### 8. ​search-in-rotated-sorted-array​(#33)
linkage: [leetcode](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/ "搜索旋转排序数组")
> 旋转的升序排序数组，搜索目标值，如果存在，返回索引，否则-1
- 思路一：模板三(重在思路)
  - 1. 通过mid中间节点将其分割为有序和部分有序数组
  - 2. 找到有序数组在前半部分还是后半部分
  - 3. 判断target是否在有序数组中，进行start和end赋值
  - 4. 最后判断边界条件情况
    ```cpp
    class Solution {
    public:
        int search(vector<int>& nums, int target)
        {
            if(nums.size() == 0)
            {
                return -1;
            }
            int start = 0;
            int end = nums.size() - 1;
            while(start + 1 < end)
            {
                int mid = start + ((end - start)>>1);
                if(nums[mid] == target)
                    return mid;
                // 判断哪部分有序
                if(nums[0] <= nums[mid])
                {
                    // 如果target在前半部分有序部分，将end = mid
                    if(target >= nums[0] && target <= nums[mid])
                        end = mid;
                    else
                        start = mid;
                }
                else
                {
                    // 如果target在后半部分有序部分，将start = mid
                    if(target >= nums[mid] && target <= nums[end])
                        start = mid;
                    else
                        end = mid;
                }
            }
            // 判断临界条件
            if(nums[start] == target)
                return start;
            if(nums[end] == target)
                return end;
            return -1;
        }
    };
    ```
---

<div id="sirsaii" onclick="window.location.hash">

#### 9. ​search-in-rotated-sorted-array-ii​(#81)
linkage: [leetcode](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/ "搜索旋转排序数组 II")
> 旋转重复的升序排序数组，搜索目标值，如果存在，返回true，否则false
- 思路一: 模板三(与题8思路一致)
  - **本题重点**是对题8数据进行预处理
    ```cpp
    class Solution {
    public:
        bool search(vector<int>& nums, int target)
        {
            if(nums.size() == 0)
            {
                return false;
            }
            int start = 0;
            int end = nums.size() - 1;
            while(start + 1 < end)
            {
                int mid = start + ((end - start)>>1);
                if(nums[mid] == target)
                {
                    return true;
                }
                // 重点：预处理数据
                if(nums[start] == nums[mid])
                {
                    start ++;
                    continue;
                }
                // 找不降数组
                if(nums[start] <= nums[mid])
                {
                    if(target >= nums[start] && target <= nums[mid])
                    {
                        end = mid;
                    }
                    else
                    {
                        start = mid;
                    }
                else
                {
                    if(target >= nums[mid] && target <= nums[end])
                    {
                        start = mid;
                    }
                    else
                    {
                        end = mid;
                    }
                }
            }
            if(nums[start] == target || nums[end] == target)
            {
                return true;
            }
            return false;
        }
    };
    ```
---