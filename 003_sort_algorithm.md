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
- mergeSort & quickSort and heapSort
  * <a href="#mergeSort">1. [代码框架] mergeSort</a>
  * <a href="#quickSort">2. [代码框架] quickSort</a>
  * <a href="./005_lists_structure.md">3. [003_lists_structure 5&7] merge-sort</a>
  * <a href="sc">4. [**很棒的数组mergeSort**] sort-colors(#75)</a>
  * <a href="kleiaa">5. [**数组quickSort**] kth-largest-element-in-an-array(#215)</a>
  * <a href="tkfe">6. [**数组heapSort**] top-k-frequent-elements(#347)</a>
* <a href="bubbleSort">7. [代码框架] bubbleSort</a>








[//]: # (Image References)
[image1]: .readme/dfs.png "dfs"
[image2]: .readme/bubble_sort.gif "bubbleSort"


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
- 思路一： quickSort(未优化)
    ```cpp
    class Solution {
    public:
        int findKthLargest(vector<int>& nums, int k)
        {
            int low = 0;
            int high = nums.size()-1;
            quickSort(nums, low, high);
            return nums[nums.size()-k];
        }

        void quickSort(vector<int>& nums, int low, int high)
        {
            // 2. 尾递归用while，普通情况if判断
            if(high-low > 0)
            {
                int pivot = partition(nums, low, high);
                quickSort(nums, low, pivot - 1);
                quickSort(nums, pivot + 1, high);
            }
        }

        int partition(vector<int>& nums, int low, int high)
        {
            int pivotKey = nums[low];
            while(high-low > 0)
            {
                //从两边向中间逼近
                while(low < high && nums[high] >= pivotKey)
                {
                    high -- ;
                }
                nums[low] = nums[high];
                while(low < high && nums[low] <= pivotKey)
                {
                    low ++;
                }
                nums[high] = nums[low];
            }
            // 重点：减少不必要的交换后要还原nums[low]
            nums[low] = pivotKey;
            return low;
        }
    };
    ```
- 思路二： quickSort(优化版)
    ```cpp
    class Solution {
    public:
        int findKthLargest(vector<int>& nums, int k) 
        {
            int low = 0;
            int high = nums.size()-1;
            quickSort(nums, low, high);
            for(auto x:nums)
            {
                cout<<"nums[]: "<<x<<endl;
            }
            return nums[nums.size()-k];
        }
        // 采用最优的quickSort方式
        // 1. 两者中取最短，为了减少递归层数
        // 2. 尾递归方式
        // 3. partition中利用三数取中
        // 4. 利用值交换方式代替swap
        void quickSort(vector<int>& nums, int low, int high)
        {
            // 2. 尾递归用while，普通情况if判断
            while(high-low > 0)
            {
                int mid = low + ((high - low)>>1);
                int pivot = partition(nums, low, high);
                // 1. 两者取短 + 尾递归优化，最坏空间复杂度优化至logn
                if(pivot < mid)
                {
                    quickSort(nums, low, pivot - 1);
                    low = pivot + 1;
                }
                else
                {
                    quickSort(nums, pivot + 1, high);
                    high = pivot - 1;
                }
            }
        }

        int partition(vector<int>& nums, int low, int high)
        {
            // 3. 省略三种取中
            int pivotKey = nums[low];
            while(high-low > 0)
            {
                //从两边向中间逼近，注意顺序一定不要写反
                while(low < high && nums[high] >= pivotKey)
                {
                    high -- ;
                }
                nums[low] = nums[high];
                while(low < high && nums[low] <= pivotKey)
                {
                    low ++;
                }
                // 4. 减少不必要的交换
                nums[high] = nums[low];
            }
            // 重点：减少不必要的交换后要还原nums[low]
            nums[low] = pivotKey;
            return low;
        }
    };
    ```
- 思路三： stl::sort库
  - std::sort()内部实现处理形式不同
    - 1. 数据量小时，利用insertSort()
    - 2. 数据量大时，利用quickSort()
    - 3. 栈深度过大时，采用heapSort()
    ```cpp
    sort(nums.begin(),nums.end());
    ```
- 思路四： priority_queue
  - 1. 本质就是二叉堆，可以使用优先队列priority_queue
  - 2. 维护一个k大小的小顶堆，堆顶就是第k个最大的数
  - 3. 注意思路和方法
    ```cpp
    class Solution {
    public:
        int findKthLargest(vector<int>& nums, int k)
        {
            // priority_queue<Type, Container, Functional>
            priority_queue<int,vector<int>,greater<int>> pq;
            for (auto n : nums)
            {
                if (pq.size() == k && pq.top() >= n)
                    continue;
                if (pq.size() == k)
                {
                    pq.pop();
                }
                pq.push(n);
            }
            return pq.top();
        }
    };
    ```
---

- 思路五： heapSort(**很棒的堆排序思路**)
  - 二叉堆
  - 根节点索引 root / 2;
  - 左子树索引 root * 2 + 1
  - 右子树索引 root * 2 + 2;
- 思路：
  - 以大顶堆为例，分为「**建堆**」,「**调整**」和「**删除**」
  - 一. 构建堆
    - 找到根节点进行遍历
  - 二. 调整堆
    - 1. 找到根节点和其左右子树比较，找到最大的索引
    - 2. 如果子树小于根节点，那么进行值交换
    - 3. 进行向上迭代重复操作
  - 三. 删除堆(大顶堆的根节点一定是最大值)
    - 1. 进行循环删除的过程
    - 2. 在删除将最后一个值赋值到第一个
    - 3. 将heapSize大小减一
    - 4. 将最大堆进行调整,调用步骤二
    ```cpp
    class Solution {
    public:
        int findKthLargest(vector<int>& nums, int k)
        {
            int heap_size = nums.size();
            // 1. 建立堆
            buildHeap(nums,heap_size);
            // 3. 删除堆
            // 注意：1. index的>=，而非<= 2. for循环注意使用nums.size()，而非heap_size
            for(int index = nums.size()-1; index >= nums.size()-k+1;index--)
            {
                swap(nums[0],nums[index]);
                heap_size--;
                // 重点：因为交换了nums[0],对顶堆0进行调整
                maxHeap(nums,0,heap_size);
            }
            return nums[0];
        }

        void buildHeap(vector<int>& nums, int heap_size)
        {
            for(int root_index = heap_size/2;root_index >= 0;root_index--)
            {
                // 2. 调整堆
                maxHeap(nums, root_index,heap_size);
            }
        }

        void maxHeap(vector<int>& nums, int root_index,int heap_size)
        {
            int largest_index = root_index;
            int left_index = root_index*2+1;
            int right_index = root_index*2+2;
            // 注意：nums[largest_index]中不能写root_index
            if(left_index<heap_size && nums[largest_index]<nums[left_index])
            {
                largest_index = left_index;
            }
            if(right_index<heap_size && nums[largest_index]<nums[right_index])
            {
                largest_index = right_index;
            }
            if(largest_index != root_index)
            {
                swap(nums[root_index],nums[largest_index]);
                // 交换后largest_index为root的索引，进行largest_index递归
                maxHeap(nums,largest_index,heap_size);
            }
        }
    };
    ```
---

<div id="tkfe" onclick="window.location.hash">

#### 6. [**数组heapSort**] top-k-frequent-elements(#347)
linkage: [leetcode](https://leetcode-cn.com/problems/top-k-frequent-elements/ "前K个高频元素")
- 非空整数数组，返回其中出现频率前k高的元素
- 时间复杂度必须优于O(nlogn)
- 思路：heapSort实现(根据题4思路四实现)
  - 利用map和priority_queue实现
  - 1. 注意临时变量的生命
  - 2. 注意push pair的次序，和pair的比较准则
    ```cpp
    class Solution {
    public:
        vector<int> topKFrequent(vector<int>& nums, int k) 
        {
            // priority_queue<Type, Container, Functional>
            priority_queue<std::pair<int,int>,vector<std::pair<int,int>>,greater<std::pair<int,int>>> pq;
            std::unordered_map<int,int> counter;
            std::vector<int> res;
            // 添加元素并计数
            for(auto x: nums)
            {
                counter[x]++;
            }
            for (auto pair : counter)
            {
                // pair的比较，先比较第一个元素，第一个相等比较第二个
                pq.push(std::make_pair(pair.second, pair.first));
                if (pq.size() > k) pq.pop();
            }
            while(!pq.empty())
            {
                res.push_back(pq.top().second);
                pq.pop();
            }
            return res;
        }
    };
    ```
---

<div id="bubbleSort" onclick="window.location.hash">

#### 7. [代码框架] bubbleSort
- 排序思想：
  - 传统思路
    - 两两比较相邻的关键字，反序进行交换，如下图
![][image2]
    - 但这样排序效率较为低效
    ```cpp
    void bubbleSort(vector<int>& nums)
        {
            for(int i = 0; i <= nums.size()-2;i++)
            {
                for(int j =i+1;j<=nums.size()-1;j++)
                {
                    if(nums[i]>nums[j])
                        swap(nums[i],nums[j]);
                }
            }
        }
    ```
    
  - 改进一：
    - 内层遍历从后向前
    - 比较前者大于后者进行值交换
    ```cpp
    void bubbleSort(vector<int>& nums)
    {
        for(int i = 0; i <= nums.size()-2;i++)
        {
            for(int j =nums.size()-1;j>i;j--)
            {
                // 比较前者大于后者进行值交换
                if(nums[j-1]>nums[j])
                    swap(nums[j-1],nums[j]);
            }
        }
    }
    ```
  - 改进二：
    - 利用flag标记，有数据交换进行排序
    - 针对部分有序
    ```cpp
    void bubbleSort(vector<int>& nums)
    {
        bool flag = true;
        // 注意flag的放置条件
        for(int i = 0; i <= nums.size()-2 && flag;i++)
        {
            flag = false;
            for(int j =nums.size()-1;j>i;j--)
            {
                if(nums[j-1]>nums[j])
                {
                    swap(nums[j-1],nums[j]);
                    // 如果后面每一个元素都大于前面，则部分有序，提高效率
                    flag = true;
                }
            }
        }
    }
    ```