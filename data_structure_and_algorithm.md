## Data Structure and Algorithm

## 📑 index
* <a href="#strStr">strStr</a>
* <a href="#subsets">subSets</a>
* <a href="#binaryTree">[代码框架] binaryTree</a>


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