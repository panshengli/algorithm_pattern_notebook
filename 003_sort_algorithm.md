## Search Algorithm

- 各种排序算法指标对比
    排序方法 | 平均情况 | 最好情况 | 最坏情况 | 辅助空间 | 稳定性
    :-: | :-: | :-: | :-: | :-: | :-:
    冒泡排序 | O(n2) | O(n) | O(n2) | O(1) | 稳定
    简单选择排序 | O(n2) | O(n2) | O(n2) | O(1) | 稳定
    直接插入排序 | O(n2) | O(n) | O(n2) | O(1) | 稳定
    希尔排序 | O(nlogn)~O(n2) | O(n1.3) | O(n2) | O(1) | 不稳定
    **堆排序** | **O(nlogn)** | O(nlogn) | O(nlogn) | **O(1)** | 不稳定
    **归并排序** | **O(nlogn)** | O(nlogn) | O(nlogn) | O(n) | **稳定**
    **快速排序** | **O(nlogn)** | O(nlogn) | O(n2) | O(logn)~O(n) | 不稳定
- 稳定：如果a原本在b前面，而a=b，排序之后a仍然在b的前面
- 不稳定：如果a原本在b的前面，而a=b，排序之后a可能会在b的后面
-   **归并排序与快排**：
    - 1. 都是分治思想，但分解和合并的策略不一样
    - 2. 归并是从中间分两个，合并后两个数列再次排序
    - 3. 快排是比较后，小的在左大的在右，直接合并不再需要排序
    - 所以**快排比归并排序更高效**一些
---

## 📑 index
- 分治法应用
  * <a href="#mergeSort">1. [代码框架] mergeSort</a>
  * <a href="#quickSort">2. [代码框架] quickSort</a>
- mergeSort应用
  * <a href="./005_lists_structure.md">3. [003_lists_structure 5&7] merge-sort</a>
  * <a href="sc">4. [**很棒的数组mergeSort**] sort-colors(#75)</a>
  * <a href="kleiaa">5. [**数组quickSort**] kth-largest-element-in-an-array(#215)</a>









[//]: # (Image References)
[image1]: .readme/dfs.png "dfs"


<div id="mergeSort" onclick="window.location.hash">

#### 1. [代码框架] mergeSort
- 排序思想：
  1. 将序列一分为二，对两边进行递归分割操作，得到独立子序列；
  2. 对独立子序列递归的执行合并操作，得到有序的序列。
- python版本
    ```python
    def merge(left, right):
        l = 0
        r = 0
        m = []
        while l < len(left) and r < len(right):
            if left[l] <= right[r]:
                m.append(left[l])
                l += 1
            else:
                m.append(right[r])
                r += 1
        remains = right[r:] if l == len(left) else left[l:]
        m.extend(remains)
        return m

    def merge_sort(arr):
        if len(arr) <= 1:
            return arr
        middle = len(arr) // 2
        left = merge_sort(arr[:middle])
        right = merge_sort(arr[middle:])
        return merge(left, right)
    ```
---

<div id="quickSort" onclick="window.location.hash">

#### 2. [代码框架] quickSort
- 排序思想：
  - 基于分治思想的不稳定排序(基准前后放在一边)
  - 快速排序缺点：**对小规模数据性能不是很好**
  - 快排是原地交换，无合并过程传入的索引是存在的索引（如：0、length-1等），**越界可能导致崩溃**
- python版本
    ```python
    def quick_sort(b):
        """快速排序"""
        if len(b) < 2:
            return arr
        # 选取基准，随便选哪个都可以，选中间的便于理解
        pivot = arr[len(b) // 2]
        # 定义基准值左右两个数列
        left, right = [], []
        # 从原始数组中移除基准值
        b.remove(pivot)
        for item in b:
            # 大于基准值放右边
            if item >= pivot:
                right.append(item)
            else:
                # 小于基准值放左边
                left.append(item)
        # 使用迭代进行比较
        return quick_sort(left) + [pivot] + quick_sort(right)
    ```
- cpp版本
    ```cpp
    void Swap(int &p,int &q)
    {
        int temp;
        temp = p;
        p = q;
        q = temp;
    }

    int Partition(int InputArray[],int nLow,int nHigh)
    {
        int i = nLow,j = nHigh+1;
        int x=InputArray[i];
        while (true)
        {
            //将 < x的元素交换到中轴左边区域
            while (InputArray[++i]<x);
            //将 >x的元素交换到中轴右边区域
            while (InputArray[--j]>x);
            if (i>=j)break;
            Swap(InputArray[i],InputArray[j]);
        }
        //将x交换到它在排序序列中应在的位置上
        InputArray[nLow]=InputArray[j];
        InputArray[j]=x;
        return j;
    }

    void QuickSort(int InputArray[],int nLow,int nHigh)
    {
        if (nHigh - nLow > 0)
        {
            int index = Partition(InputArray,nLow,nHigh);
            QuickSort(InputArray,nLow,index-1);
            QuickSort(InputArray,index+1,nHigh);
        }
    }
    ```
---

<div id="sc" onclick="window.location.hash">

#### 4. [数组mergeSort] sort-colors(#75)
linkage: [leetcode](https://leetcode-cn.com/problems/sort-colors/ "颜色分类")
- n个元素的**数组**，原地对它们进行排序
- 思路一：mergeSort
  - 1. 数组的合并方式，开辟临时变量
  - 2. 将临时变量的数组最终合并到nums
    ```cpp
    class Solution {
    public:
        void sortColors(vector<int>& nums) 
        {
            if(nums.size() == 0) return;
            int start = 0;
            int end = nums.size() - 1;
            mergeSort(nums, start, end);
        }
        void mergeSort(vector<int>& nums, int start, int end)
        {
            int mid = start + ((end - start) >> 1);
            if(end - start > 0)
            {
                mergeSort(nums, start, mid);
                mergeSort(nums, mid + 1, end);
                mergeTwoNums(nums, start, end);
            }
        }
        void mergeTwoNums(vector<int>& nums, int start, int end)
        {
            int length = end - start + 1;
            int mid = start + ((end - start)>>1);
            vector<int> tmp;
            tmp.resize(length);
            int index = 0;
            int lhs = start;
            int rhs = mid +1;
            // 判断两组nums是否越界
            while(lhs <= mid && rhs <= end)
            {
                if(nums[lhs] <= nums[rhs])
                {
                    tmp[index++] = nums[lhs++];
                }
                else
                {
                    tmp[index++] = nums[rhs++];
                }
            }
            // 遍历剩余的数组
            while(lhs <= mid)
            {
                tmp[index++] = nums[lhs++];
            }
            while(rhs <= end)
            {
                tmp[index++] = nums[rhs++];
            }
            // 重点：合并tmp数组到nums中
            for(int i = 0; i < length; i++)
            {
                nums[start + i] = tmp[i];
            }
        }
    };
    ```
---

<div id="sc" onclick="window.location.hash">

#### 5. [**数组quickSort**] kth-largest-element-in-an-array(#215)
linkage: [leetcode](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/ "数组中的第K个最大元素")
- 在未排序的数组中找到第k个最大的元素