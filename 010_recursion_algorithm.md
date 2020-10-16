## Recursion Algorithm
- 大问题转化为小问题，通过递归依次解决各个小问题
--- 

## 📑 index
* <a href="#rs">1. reverse-string(#344)</a>
* <a href="#snip">2. swap-nodes-in-pairs(#24,很典型的递归题型)</a>
* <a href="#ubstii">3. unique-binary-search-trees-ii(#95，很好的bst构建方法)</a>
* <a href="#fn">4. fibonacci-number(#509)</a>






---




<div id="rs" onclick="window.location.hash">

#### 1. reverse-string(#344)
linkage: [leetcode](https://leetcode-cn.com/problems/reverse-string/ "反转字符串")
> 将输入的字符串反转过来
> 原地修改输入数组、使用O(1)的额外空间解决这一问题
- 思路一：双指针交换
  - 利用swap(s[i],s[j]),解法省略
- 思路二：递归方法
  - 注意递归的三个步骤
    ```cpp
    class Solution {
    public:
        void reverseString(vector<char>& s) {
            if(s.size() < 2)
                return;
            // 递归的调用
            recursionString(s,0,s.size()-1);
        }

        void recursionString(vector<char>& s, int lhs, int rhs)
        {
            // 递归的结束条件
            if(lhs >= rhs)
                return;
            swap(s[lhs],s[rhs]);
            recursionString(s,lhs+1,rhs-1);
        }
    };
    ```
---

<div id="snip" onclick="window.location.hash">

#### 2. swap-nodes-in-pairs(#24,很典型的递归题型)
linkage: [leetcode](https://leetcode-cn.com/problems/swap-nodes-in-pairs/ "两两交换链表中的节点")
> 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表
- 思路：递归
    ```cpp
    class Solution {
    public:
        ListNode* swapPairs(ListNode* head) 
        {
            if(head == nullptr || head->next == nullptr)
                return head;
            ListNode * newNode = head->next;
            head->next = swapPairs(newNode->next);
            newNode->next = head;
            return newNode;
        }
    };
    ```
---

<div id="ubstii" onclick="window.location.hash">

#### 3. unique-binary-search-trees-ii(#95，很好的bst构建方法)
linkage: [leetcode](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/ "不同的二叉搜索树 II")
> 给定一个整数n，生成所有由1...n为节点所组成的二叉搜索树
- 搜索二叉树：左子树的所有值小于根节点，右子树的所有值大于根节点
- 构建二叉搜索树：1. 选择根节点； 2. 递归去构建左右子树；
- 构建平衡二叉树框架：
```cpp

public TreeNode createBinaryTree(int n){
    return helper(1, n);
}

public TreeNode helper(int start, int end){
    if(start > end)
        return null;
    // 这里可以选择从start到end的任何一个值做为根结点，
    // 这里选择它们的中点，实际上，这样构建出来的是一颗平衡二叉搜索树
    int val = (start + end) / 2;
    TreeNode root = new TreeNode(val);
    root.left = helper(start, val - 1);
    root.right = helper(val + 1, end);
    return root;
}
```
- 思路：[参考链接](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/solution/cong-gou-jian-dan-ke-shu-dao-gou-jian-suo-you-shu-/)
```cpp
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) 
    {
        vector<TreeNode*> ans;
        if(n == 0)
            return ans;
        return getAns(1,n);
    }

    vector<TreeNode*> getAns(int start, int end)
    {
        vector<TreeNode*> ans;
        //此时没有数字，将 null 加入结果中
        if (start > end) 
        {
            ans.push_back(nullptr);
            return ans;
        }
        //只有一个数字，当前数字作为一棵树加入结果中
        if (start == end)
        {
            TreeNode* tree = new TreeNode(start);
            ans.push_back(tree);
            return ans;
        }
        //为了构建所有根节点
        for (int i = start; i <= end; i++)
        {
            // 想想为什么这行不能放在这里，而放在下面？
            // TreeNode root = new TreeNode(i);

            //递归构建左子树，并拿到左子树所有可能的根结点列表left
            vector<TreeNode*> leftTrees = getAns(start, i - 1);
            //递归构建右子树，并拿到右子树所有可能的根结点列表right
            vector<TreeNode*> rightTrees = getAns(i + 1, end);
            //左子树右子树两两组合
            for (TreeNode* leftTree : leftTrees)
            {
                for (TreeNode* rightTree : rightTrees)
                {
                    TreeNode* root = new TreeNode(i);
                    root->left = leftTree;
                    root->right = rightTree;
                    //加入到最终结果中
                    ans.push_back(root);
                }
            }
        }
        return ans;
    }
};
```
---

<div id="fn" onclick="window.location.hash">

#### 4. fibonacci-number(#509)
linkage: [leetcode](https://leetcode-cn.com/problems/fibonacci-number/ "斐波那契数")
> 斐波那契数,给定N，计算F(N)
- 思路：用dp和recursion均可
    ```cpp
    class Solution {
    public:
        int fib(int N) 
        {
            // 注意临界条件，否则越界
            vector<int> fn(N+1,0);
            if(N < 2)
                return N;
            fn[0] = 0;
            fn[1] = 1;
            recursionFib(fn,2);
            return fn[N];
        }

        void recursionFib(vector<int>& fn, int n)
        {
            if(n > fn.size()-1)
                return;
            fn[n] = fn[n-1] + fn[n-2];
            recursionFib(fn, n+1);
        }
    };
    ```
---
