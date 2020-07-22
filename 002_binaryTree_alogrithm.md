## BinaryTree Algorithm

## 📑 index
* <a href="#binaryTree">[代码框架] binaryTree</a>
* <a href="#BFS">[代码框架] BFS</a>
* <a href="#maxDepthBinaryTree">maxDepthBinaryTree</a>
* <a href="#balancedTree">balancedTree</a>
* <a href="#binary-tree-maximum-path-sum">binary-tree-maximum-path-sum</a>





[//]: # (Image References)
[image1]: .readme/dfs.png "dfs"


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
            return 1+std::max(maxDepth(root->left),maxDepth(root->right));
        }
    };
    ```
- **BFS**：使用队列
    ```cpp
    class Solution {
    public:
        int maxDepth(TreeNode* root)
        {
            if(root == nullptr) return 0;
            std::deque<TreeNode*> q;
            q.push_back(root);
            int deep = 0;
            while(!q.empty())
            {
                deep ++;
                int num = q.size();
                // 注意必须用num赋值，因为后面会对q.size()进行操作
                // 不可用 for(int i = 0; i<q.size();i++)
                for(int i = 0; i < num; i++)
                {
                    TreeNode* p = q.front();
                    q.pop_front();
                    if(p->left) q.push_back(p->left);
                    if(p->right) q.push_back(p->right);
                }
            }
            return deep;
        }
    };
    ```
- DFS：用栈的循环版
![alt text][image1]
    ```cpp
    class Solution {
    public:
        int maxDepth(TreeNode* root)
        {
            // DFS 
            if (root == nullptr) {return 0;}
            int curHeight = 0;
            int maxHeight = 0;
            findMaxHeight(root, curHeight,maxHeight); 
            return maxHeight;
        }
        
        void findMaxHeight(TreeNode* _root, int& _curHeight, int& _maxHeight)
        {
            _curHeight += 1;
            if (_root -> left != nullptr || _root -> right != nullptr)
            {
                if(_root -> left != nullptr)
                {
                    findMaxHeight(_root -> left, _curHeight, _maxHeight);
                    _curHeight -= 1;
                }
                // 注意：不要使用else if
                if(_root -> right != nullptr)
                {
                    findMaxHeight(_root -> right, _curHeight, _maxHeight);
                    _curHeight -= 1;
                }
            }
            else
            {
                _maxHeight = std::max(_curHeight,_maxHeight);
            }
        }
    };
    ```
---

<div id="balancedTree" onclick="window.location.hash">

#### balancedTree
linkage: [leetcode](https://leetcode-cn.com/problems/balanced-binary-tree/ "高度平衡的二叉树")
- 一棵高度平衡二叉树定义为：  一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。
    ```cpp
    class Solution {
    public:
        bool isBalanced(TreeNode* root) 
        {
            if (root == nullptr)
            {
                return true;
            }
            return std::abs(heightTree(root->left)-heightTree(root->right))<2
                && isBalanced(root->left) && isBalanced(root->right);
        }
        
    private:
        int heightTree(TreeNode* root)
        {
            if (root == nullptr)
            {
                return 0;
            }
            return 1+std::max(heightTree(root->left),heightTree(root->right));ss
        }
    };
    ```

---

<div id="binary-tree-maximum-path-sum" onclick="window.location.hash">

#### binary-tree-maximum-path-sum
linkage: [leetcode](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/ "二叉树中的最大路径和")
- 理解如何递归很关键
    ```cpp
    class Solution {
    public:
        int maxPathSum(TreeNode* root) 
        {
            if(root == nullptr)
            {
                return 0;
            }
            dfs(root);
            return maxValue_;
        }
        int dfs(TreeNode* root)
        {
            if(root == nullptr)
            {
                return 0;
            }
            int leftMax = std::max(0,dfs(root->left));
            int rightMax = std::max(0,dfs(root->right));
            maxValue_ = std::max(maxValue_,root->val+leftMax+rightMax);
            return root->val + std::max(leftMax,rightMax);
        }

    private:
        const int kMinInt = INT_MIN;
        int maxValue_ = kMinInt;
    };
    ```
---
