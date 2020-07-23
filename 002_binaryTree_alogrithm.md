## BinaryTree Algorithm

## 📑 index
* <a href="#binaryTree">1. [代码框架] binaryTree</a>
* <a href="#BFS">2. [代码框架] BFS</a>
* <a href="#maxDepthBinaryTree">3. maxDepthBinaryTree</a>
* <a href="#balancedTree">4. balancedTree</a>
* <a href="#binary-tree-maximum-path-sum">5. binary-tree-maximum-path-sum</a>
* <a href="#lowest-common-ancestor-of-a-binary-tree">6. lowest-common-ancestor-of-a-binary-tree</a>
* <a href="#binary-tree-level-order-traversal">7. binary-tree-level-order-traversal[与3类似]</a>
* <a href="#binary-tree-level-order-traversal-ii">8. binary-tree-level-order-traversal-ii[与7类似]</a>
* <a href="#binary-tree-zigzag-level-order-traversal">9. binary-tree-zigzag-level-order-traversal[与8类似]</a>




[//]: # (Image References)
[image1]: .readme/dfs.png "dfs"


<div id="binaryTree" onclick="window.location.hash">

#### 1. binaryTree
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

#### 2. BFS
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

#### 3. maxDepthBinaryTree
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

#### 4. balancedTree
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

#### 5. binary-tree-maximum-path-sum
linkage: [leetcode](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/ "二叉树中的最大路径和")
- 给定一个非空二叉树，返回其最大路径和
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

<div id="lowest-common-ancestor-of-a-binary-tree" onclick="window.location.hash">

#### 6. lowest-common-ancestor-of-a-binary-tree
linkage: [leetcode](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/ "二叉树的最近公共祖先")
- 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先
- **ADT**
    left == null && right == null return null
    left == null && right ！= null return right
    right == null && left ！= null return left
    right ！= null && left ！=null return root

    ```cpp
    class Solution {
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
        {
            if(root == NULL)
            {
                return root;
            }
            if(root->val == p->val || root->val == q->val)
            {
                return root;
            }
            TreeNode* left_son = lowestCommonAncestor(root->left,p,q);
            TreeNode* right_son = lowestCommonAncestor(root->right,p,q);
            if(left_son == NULL && right_son == NULL)
            {
                return NULL;
            }
            if(left_son != NULL && right_son == NULL)
            {
                return left_son;
            }
            if(left_son == NULL && right_son != NULL)
            {
                return right_son;
            }
            if(left_son != NULL && right_son != NULL)
            {
                return root;
            }
            return root;
        }
    };
    ```
---

<div id="binary-tree-level-order-traversal" onclick="window.location.hash">

#### 7. binary-tree-level-order-traversal
- 给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 
- 即逐层地，从左到右访问所有节点 linkage: [leetcode](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/submissions/ "二叉树的层序遍历")
- **注意c++中queue()[push,pop]和deque()[push_back,pop_front]的使用**
- DFS 与 BFS区别
  1. DFS遍历的代码比BFS简洁太多了！
  2. 因为递归的方式隐含地使用了系统的栈，我们不需要自己维护一个数据结构。
  3. 如果只是简单地将二叉树遍历一遍，那么DFS显然是更方便的选择
    ```java
    void dfs(TreeNode root)
    {
        if (root == null)
        {
            return;
        }
        dfs(root.left);
        dfs(root.right);
    }
    ```
    ```java
    void bfs(TreeNode root)
    {
        // 注意c++为deque
        Queue<TreeNode> queue = new ArrayDeque<>();
        queue.add(root);
        while (!queue.isEmpty())
        {
            TreeNode node = queue.poll();
            // Java 的 pop 写作 poll()
            if (node.left != null)
            {
                queue.add(node.left);
            }
            if (node.right != null)
            {
                queue.add(node.right);
            }
        }
    }
    ```
- BFS cpp代码
    ```cpp
    class Solution {
    public:
        vector<vector<int>> levelOrder(TreeNode* root) 
        {
            std::vector<std::vector<int>> level_lists;
            if(root == nullptr)
            {
                return level_lists;
            }
            std::vector<int> level_value;
            // 注意如果使用deque 则为push_back()
            // 如果使用queue 则为push()
            std::deque<TreeNode*> q;
            q.push_back(root);
            while(!q.empty())
            {
                int num = q.size();
                for(int i = 0;i<num;i++)
                {
                    TreeNode* p = q.front();
                    level_value.push_back(p->val);
                    // 如果使用deque,则为pop_front()
                    // 使用queue 则为pop()
                    q.pop_front();
                    if (p->left) q.push_back(p->left);
                    if (p->right) q.push_back(p->right);
                }
                level_lists.emplace_back(level_value);
                level_value.clear();
            }
            return level_lists;
        }
    };
    ```
---

<div id="binary-tree-level-order-traversal-ii" onclick="window.location.hash">

#### 8. binary-tree-level-order-traversal-ii
- 给定一个二叉树，返回其节点值自底向上的层次遍历。
- 即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历
- linkage: [leetcode](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/ "二叉树的层次遍历 II")
- **注意BFS做法:**
  1. 与7类似,需要用std::list每次都往队头塞**
    ```cpp
    std::list<std::vector<int>> level_lists;
    std::vector<std::vector<int>> level_vectors;
    level_vectors.assign(level_lists.begin(),level_lists.end());
    ```
  2. 用std::reverse函数实现
   ```cpp
   std::vector<std::vector<int>> level_vectors;
   std::reverse(level_vectors.begin(),level_vectors.end());
   ```
- 本题还可用DFS实现(略)
---

<div id="binary-tree-zigzag-level-order-traversal" onclick="window.location.hash">

#### 9. binary-tree-zigzag-level-order-traversal
- 给定一个二叉树，返回其节点值的锯齿形层次遍历。
- linkage: [leetcode](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/ "二叉树的锯齿形层次遍历")
- **注意BFS做法:**
  1. 对应层判断一下奇偶
   ```cpp
    // 注意与!levels%2区别
    // 该段代码不能放入循环体内部
    if (!(levels%2))
    {
        std::reverse(level_value.begin(),level_value.end());
    }
   ```