## Data Structure and Algorithm

## 📑 index
* <a href="#strStr">strStr</a>
* <a href="#subsets">subSets</a>
* <a href="#binaryTree">[代码框架] binaryTree</a>
* <a href="#BFS">[代码框架] BFS</a>
* <a href="#mergeSort">mergeSort</a>
* <a href="#quickSort">quickSort</a>
* <a href="#maxDepthBinaryTree">maxDepthBinaryTree</a>

<div id="strStr" onclick="window.location.hash">

#### strStr
linkage: [leetcode](https://leetcode-cn.com/problems/implement-strstr/ "字符串查找")

1. **Rabin-Karp Algorithm** instead of kmp

    ```cpp
    class Solution {
    public:
        int strStr(std::string haystack, std::string needle) 
    {
        int needle_size = needle.length();
        int haystack_size = haystack.length();
        if(haystack_size == 0 )
        {
            if (needle_size ==0)
            {
                return 0;
            }
            else 
            {
                return -1;
            }
        }
        else if (needle_size ==0)
        {
            return 0;
        }
        else if(haystack_size<needle_size)
        {
            return -1;
        }
        // using Rabin-Karp algorithm
        static const int kBase = 1000000;
        static const int kHashNum = 31;
        int power = 1.0;
        for(int i = 0; i < needle_size;++i)
        {
            power = (power*kHashNum)%kBase;
        }

        int target_code = 0;
        for(int i = 0; i<needle_size;++i)
        {
            target_code = (target_code*kHashNum+needle[i])%kBase;
        }

        int hash_code = 0;
        for(int i = 0; i<haystack_size;++i)
        {
            // abc+d
            hash_code = (hash_code*kHashNum+haystack[i])%kBase;
            if(i<needle_size-1)
            {
                continue;
            }
            // abcd-a
            if(i>=needle_size)
            {
                hash_code = hash_code -(haystack[i-needle_size]*power)%kBase;
                if(hash_code<0)
                {
                    hash_code+=kBase;
                }
            }
            // std::cout<<i<<" hash_code: "<< hash_code
            //          <<" target_code: "<< target_code <<std::endl;
            // double check the std::string
            if(hash_code==target_code)
            {
                if(haystack.substr(i-needle_size+1,needle_size)==needle)
                {
                    return i-needle_size+1;
                }
            }
        }
        return -1;
    }
    };
    ```

2. **暴力匹配**算法
 - 需要注意点
 - 循环时，i 不需要到 len-1
 - 如果找到目标字符串，len(needle)==j
  
    ```cpp
    class Solution {
    public:
        int strStr(string haystack, string needle) {
            if(haystack.length() == 0 )
            {
                if (needle.length() ==0)
                {
                    return 0;
                }
                else 
                {
                    return -1;
                }
            }
            else if(haystack.length()<needle.length())
            {
                return -1;
            }
            for(size_t i = 0;i<= haystack.length()-needle.length();++i)
            {
                size_t j;
                for(j = 0; j<needle.length();++j)
                {
                    if(haystack[i+j]!=needle[j])
                        break;
                }
                if(needle.length()==j)
                    return i;
            }
            return -1;
        }
    };
    ```
---
<div id="subSets" onclick="window.location.hash">

#### subSets
linkage: [leetcode](https://leetcode-cn.com/problems/subsets/ "查找集合所有子集")

1. backtrack algorithm

    ```go
    // ADT 
    // 应用回溯法的题目，简单来说就是穷尽所有可能性
    // 通过不停的选择，撤销选择，来穷尽所有可能性，最后将满足条件的结果返回
    result = []
    func backtrack(选择列表,路径):
    if 满足结束条件:
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
            for(int i=index;i<nums.size();i++){
                tmp.push_back(nums[i]);
                backtrack(nums,res,tmp,i+1);
                tmp.pop_back();
            }
        }
    };
    ```
---

<div id="binaryTree" onclick="window.location.hash">

#### binaryTree
1. 三种递归遍历 
    Refer by [更简单的非递归遍历二叉树的方法](https://www.jianshu.com/p/49c8cfd07410)
    ```cpp
    void order(TreeNode *root, vector<int> &path)
    {
        if(root != NULL)
        {
            // preorderTraversal
            path.push_back(root->val);
            order(root->left, path);
            order(root->right, path);
            // inorderTraversal
            order(root->left, path);
            path.push_back(root->val);
            order(root->right, path);
            // postorderTraversal
            order(root->left, path);
            order(root->right, path);
            path.push_back(root->val);
        }
    }
    ```
2. **更简单的非递归遍历二叉树**
- 有重合元素的局部有序一定能导致整体有序
- 将栈顶元素取出，使以此元素为“根”结点的局部有序入栈，但若此前已通过该结点将其局部入栈，则直接出栈输出即可。
    ```cpp
    // 非递归遍历
    void orderTraversalNew(TreeNode *root, vector<int> &path)
    {
        stack< pair<TreeNode *, bool> > s;
        s.push(make_pair(root, false));
        bool visited;
        while(!s.empty())
        {
            root = s.top().first;
            visited = s.top().second;
            s.pop();
            if(root == NULL)
                continue;
            if(visited)
            {
                path.push_back(root->val);
            }
            else
            {
                // 非递归前序遍历
                s.push(make_pair(root->right, false));
                s.push(make_pair(root->left, false));
                s.push(make_pair(root, true));
                // 非递归中序遍历
                s.push(make_pair(root->right, false));
                s.push(make_pair(root, true));
                s.push(make_pair(root->left, false));
                // 非递归后序遍历
                s.push(make_pair(root, true));
                s.push(make_pair(root->right, false));
                s.push(make_pair(root->left, false));
        }
    }
    ```
    ```cpp
    // 非递归前序遍历简化
    void preorderTraversalNew(TreeNode *root, vector<int> &path)
    {
        stack<TreeNode *> s;
        s.push(root);
        while(!s.empty())
        {
            root = s.top();
            s.pop();
            if(root == NULL)
            {
                continue;
            }
            else
            {
                path.push_back(root->val);
                s.push(root->right);
                s.push(root->left);
            }
        }
    }
    ```
3. 教科书上的非递归遍历
    ```cpp
    //非递归前序遍历
    void preorderTraversal(TreeNode *root, vector<int> &path)
    {
        stack<TreeNode *> s;
        TreeNode *p = root;
        while(p != NULL || !s.empty())
        {
            // 沿左子树一直往下搜索，直至出现没有左子树的结点
            while(p != NULL)
            {
                path.push_back(p->val);
                s.push(p);
                p = p->left;
            }
            if(!s.empty())
            {
                p = s.top();
                s.pop();
                p = p->right;
            }
        }
    }
    ```
    ```cpp
    //非递归中序遍历
    void inorderTraversal(TreeNode *root, vector<int> &path)
    {
        stack<TreeNode *> s;
        TreeNode *p = root;
        while(p != NULL || !s.empty())
        {
            while(p != NULL)
            {
                s.push(p);
                p = p->left;
            }
            if(!s.empty())
            {
                p = s.top();
                path.push_back(p->val);
                s.pop();
                p = p->right;
            }
        }
    }
    ```
---

<div id="BFS" onclick="window.location.hash">

#### BFS
- 队列 q 就不说了，BFS 的核心数据结构；
- cur.adj() 泛指 cur 相邻的节点，比如说二维数组中，cur 上下左右四面的位置就是相邻节点；
- visited 的主要作用是防止走回头路，大部分时候都是必须的，但是像一般的二叉树结构，没有子节点到父节点的指针，不会走回头路就不需要 visited。

    ```cpp
    // 计算从起点 start 到终点 target 的最近距离
    int BFS(Node start, Node target) {
        Queue<Node> q; // 核心数据结构
        Set<Node> visited; // 避免走回头路

        q.offer(start); // 将起点加入队列
        visited.add(start);
        int step = 0; // 记录扩散的步数

        while (q not empty) {
            int sz = q.size();
            /* 将当前队列中的所有节点向四周扩散 */
            for (int i = 0; i < sz; i++) {
                Node cur = q.poll();
                /* 划重点：这里判断是否到达终点 */
                if (cur is target)
                    return step;
                /* 将 cur 的相邻节点加入队列 */
                for (Node x : cur.adj())
                    if (x not in visited) {
                        q.offer(x);
                        visited.add(x);
                    }
            }
            /* 划重点：更新步数在这里 */
            step++;
        }
    }
    ```
---

<div id="mergeSort" onclick="window.location.hash">

#### mergeSort
- 排序思想：
  1. 将待排序序列从中间一分为二，对左右两边再进行递归分割操作，得到n个相互独立的子序列；
  2. 对n个独立的子序列递归的执行合并操作，最终得到有序的序列。
  3. 归并排序与快排 ：归并排序与快排两种排序思想都是分而治之，但是它们分解和合并的策略不一样：归并是从中间直接将数列分成两个，而快排是比较后将小的放左边大的放右边，所以在合并的时候归并排序还是需要将两个数列重新再次排序，而快排则是直接合并不再需要排序，所以**快排比归并排序更高效**一些
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
- cpp版本
    ```cpp
    void merge(int *ms,int startIndex,int endIndex)
    {
        //进入归并步骤时，数组将由两个数组合并，升序排序划分，左边的称之为左数组，同理，右边的称之为右数组。

        // 待定左数组的右边界
        int left_mid = (startIndex+endIndex)/2;
        //待定右数组的左边界
        int mid_right = ((startIndex+endIndex)/2)+1;
        //待定左数组长度
        int left_length = (left_mid-startIndex)+1;
        //待定右数组长度
        int right_length = (endIndex-mid_right)+1;
        //初始化左数组
        int left_array[left_length];
        //初始化右数组
        int right_array[right_length];

        for(int i=left_mid;i>=startIndex;i--)
        {
            //将左数组挂起
            left_array[i-startIndex] = ms[i];
        }

        for(int i=endIndex;i>=mid_right;i--)
        {
            //将右数组挂起
            right_array[i-mid_right] = ms[i];
        }
        //将两个指针指向左、右数组的头元素
        int l_index=0,r_index=0;

        //双数组循环排序，复杂度O(n)，排序后的结果直接赋回原数组ms上
        for(int i=startIndex;i<=endIndex;i++)
        {
            if(l_index!=left_length && r_index!=right_length)
            {
                if(left_array[l_index]<right_array[r_index])
                {
                    ms[i] = left_array[l_index++];
                }
                else
                {
                    ms[i] = right_array[r_index++];
                }
            }
            else if(l_index==left_length)
            {
                ms[i] = right_array[r_index++];
            }
            else
            {
                ms[i] = left_array[l_index++];
            }
        }
    }
    /*
    * 归并排序方法有三个参数，第一个是初始的数组，
    * 第二个是该数组的起始索引，第三是该数组的尾巴索引
    * note ms[] = {2,3,5,1,0,8,6,9,7}
    */
    void mergeSort(int *ms,int startIndex,int endIndex)
    {
        //如果数列划分至最小单位(一个数)则停止分割
        if(endIndex-startIndex>0)
        {
            //将数列分为左右部分进行分治
            //左分治
            mergeSort(ms,startIndex,(startIndex+endIndex)/2);
            //右分治
            mergeSort(ms,((startIndex+endIndex)/2)+1,endIndex);
            //归并
            merge(ms,startIndex,endIndex);
        }
    }
    ```
---

<div id="quickSort" onclick="window.location.hash">

#### quickSort
- 快速排序是一种基于分治技术的重要排序算法
- 快排是一种不稳定排序，比如基准值的前后都存在与基准值相同的元素，那么相同值就会被放在一边，这样就打乱了之前的相对顺序
- 时间复杂度：快排的时间复杂度为O(nlogn)
- 空间复杂度：排序时需要另外申请空间，并且随着数列规模增大而增大，其复杂度为：O(nlogn)
- 快速排序有一个缺点就是对于小规模的数据集性能不是很好
- 快排由于是原地交换所以没有合并过程 传入的索引是存在的索引（如：0、length-1 等），越界可能导致崩溃
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
        if (nLow < nHigh)
        {
            int index = Partition(InputArray,nLow,nHigh);
            QuickSort(InputArray,nLow,index-1);
            QuickSort(InputArray,index+1,nHigh);
        }
    }
    ```
---
<div id="maxDepthBinaryTree" onclick="window.location.hash">

#### maxDepthBinaryTree
linkage: [leetcode](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/ "二叉树的最大深度")
- struct BinaryTree
    ```cpp
    // Definition for a binary tree node.
    struct TreeNode 
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    ```
- **递归方式**
  - 三个条件：递归定义，递归出口，递归拆解
    ```cpp
    class Solution {
    public:
        int maxDepth(TreeNode* root)
        {
            // recursive function
            if(root == nullptr)
            {
                return 0;
            }
            auto lhs = maxDepth(root->left);
            auto rhs = maxDepth(root->right);
            return lhs > rhs ? lhs+1 : rhs+1;
        }
    };
    ```
- **广度优先**：使用队列
```cpp

```
- 深度优先：用栈的循环版
```cpp

```
---