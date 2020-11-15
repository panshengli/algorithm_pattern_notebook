## BinaryTree Algorithm
- struct BinaryTree
    ```cpp
    // Definition for a binary tree node.
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    ```
- BST特点：
  - 左子树所有节点小于(或等于)根节点
  - 右子树所有节点大于(或等于)根节点
  - 可用中序遍历进行排序
---

## 📑 index
- 二叉树遍历
  * <a href="#bt">1. [代码框架] binary-tree(相关题型#94，二叉树中序遍历)</a>
  * <a href="#midobt">2. minimum-depth-of-binary-tree(#111)</a>
  * <a href="#mdobt">3. maximum-depth-of-binary-tree(#104，相似的题型#101, #112)</a>
  * <a href="#bbt">4. balanced-binary-tree(#110)</a>
  * <a href="#btnps">5. binary-tree-maximum-path-sum(#124)</a>
  * <a href="#lcaoabt">6. lowest-common-ancestor-of-a-binary-tree(#236)</a>
- BFS 层次应用
  * <a href="#btlot">7. binary-tree-level-order-traversal(#102)[与3类似,相关#116，#117, #297]</a>
  * <a href="#btlotii">8. binary-tree-level-order-traversal-ii(#107)[与7类似]</a>
  * <a href="#btzlot">9. binary-tree-zigzag-level-order-traversal(#103)[与8类似]</a>
- 二叉搜索树应用
  * <a href="#vbst">10. validate-binary-search-tree(#98)</a>
  * <a href="#iiabst">11. insert-into-a-binary-search-tree(#701)</a>
  * <a href="#dniab">12. delete-node-in-a-bst(#450，注意体会与T11区别)</a>





---


[//]: # (Image References)
[image1]: .readme/dfs.png "dfs"
[image2]: .readme/del_bst1.png "delete bst"
[image3]: .readme/del_bst2.png "delete bst"
[image4]: .readme/del_bst3.png "delete bst"
---




<div id="bt" onclick="window.location.hash">

#### 1. [代码框架] binary-tree(相关题型#94，二叉树中序遍历)
1. 三种递归遍历 
    Refer by [更简单的非递归遍历二叉树的方法](https://blog.csdn.net/u012102306/article/details/52841163)
    ```cpp
    void order(TreeNode *root, vector<int> &path)
    {
        if(root != nullptr)
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
- 有重合元素的**局部有序**一定能导致**整体有序**
- 将栈顶元素取出，使以此元素为“根”结点的局部有序入栈，但若此前已通过该结点将其局部入栈，则直接出栈输出即可。
    ```cpp
    // 非递归遍历
    void orderTraversal(TreeNode *root, vector<int> &path)
    {
        stack< pair<TreeNode *, bool> > s;
        // 注意： make_pair不能使用尖括号"<>"
        s.push(make_pair(root, false));
        bool visited;
        while(!s.empty())
        {
            root = s.top().first;
            visited = s.top().second;
            s.pop();
            // 二遍复习忘记点：注意： 不要忘记root为空的处理
            if(root == nullptr)
                continue;
            // 若此前已通过该结点将其局部入栈，则直接出栈输出即可
            if(visited)
            {
                path.push_back(root->val);
            }
            else
            {
                // 非递归前序遍历
                s.push(make_pair(root->right, false));
                s.push(make_pair(root->left, false));
                s.push(make_pair(root, true));    // 只剩下一个元素，因此从stack拿出来即可
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
    }
    ```
    ```cpp
    // 非递归前序遍历简化
    void preorderTraversal(TreeNode *root, vector<int> &path)
    {
        stack<TreeNode *> s;
        s.push(root);
        while(!s.empty())
        {
            root = s.top();
            s.pop();
            if(root == nullptr)
            {
                continue;
            }
            else
            {
                // 只剩下一个元素，因此从stack拿出来即可
                path.push_back(root->val);
                s.push(root->right);
                s.push(root->left);
            }
        }
    }
    ```
---

<div id="midobt" onclick="window.location.hash">

#### 2. minimum-depth-of-binary-tree(#111)
linkage: [leetcode](https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/ "二叉树的最小深度")
> 给定一个二叉树，找出其最小深度
> 最小深度：根节点到最近叶子最短路径的节点数量
- 思路一：dfs
    ```cpp
    class Solution {
    public:
        int minDepth(TreeNode* root)
        {
            if(root == nullptr)
            {
                return 0;
            }
            else if(root->left == nullptr)
            {
                return minDepth(root->right) + 1;
            }
            else if(root->right == nullptr)
            {
                return minDepth(root->left) + 1;
            }
            else
            {
                return min(minDepth(root->left), minDepth(root->right)) + 1;
            }
        }
    };
    ```
- 思路二：bfs版本
    ```cpp
    class Solution {
    public:
        int minDepth(TreeNode* root)
        {
            if(root == nullptr)
            {
                return 0;
            }
            queue<pair<TreeNode*,int>> q;
            int depth = 1;
            q.push(make_pair(root,1));
            while(!q.empty())
            {
                TreeNode *node = q.front().first;
                depth = q.front().second;
                q.pop();
                if (node->left == nullptr && node->right == nullptr) {
                    return depth;
                }
                if(node->left != nullptr)
                {
                    q.push(make_pair(node->left, depth + 1));
                }
                if(node->right != nullptr)
                {
                    q.push(make_pair(node->right, depth + 1));
                }
            }
            return depth;
        }
    };
    ```
---

<div id="mdobt" onclick="window.location.hash">

#### 3. maximum-depth-of-binary-tree(#104)
linkage: [leetcode](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/ "二叉树的最大深度")
> 给定一个二叉树，找出其最大深度
- 思路一：**递归方式**
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
- 思路二：**BFS**：使用队列
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
---

<div id="bbt" onclick="window.location.hash">

#### 4. balanced-binary-tree(#110)
linkage: [leetcode](https://leetcode-cn.com/problems/balanced-binary-tree/ "高度平衡的二叉树")
> 高度平衡二叉树： 每个节点左右子树的高度差不超过1
- 思路一:递归版本
    ```cpp
    class Solution {
    public:
        bool isBalanced(TreeNode* root)
        {
            if (root == nullptr)
            {
                return true;
            }
            return std::abs(heightTree(root->left) - heightTree(root->right)) < 2
                && isBalanced(root->left) && isBalanced(root->right);
        }

    private:
        int heightTree(TreeNode* root)
        {
            if (root == nullptr)
            {
                return 0;
            }
            return 1 + std::max(heightTree(root->left),heightTree(root->right));
        }
    };
    ```
---

<div id="btnps" onclick="window.location.hash">

#### 5. binary-tree-maximum-path-sum(#124)
linkage: [leetcode](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/ "二叉树中的最大路径和")
> 给定一个非空二叉树，返回其最大路径和
- 思路一：递归版本
    ```cpp
    class Solution {
    public:
        int maxPathSum(TreeNode* root)
        {
            if(root == nullptr)
            {
                return 0;
            }
            int max_value = INT_MIN;
            dfs(root, max_value);
            return max_value;
        }

        int dfs(TreeNode* root, int& max_value)
        {
            if(root == nullptr)
            {
                return 0;
            }
            // 空节点的最大贡献值等于0
            int leftMax = std::max(0, dfs(root->left, max_value));
            int rightMax = std::max(0, dfs(root->right, max_value));
            // 更新最大值
            max_value = std::max(max_value, root->val+leftMax+rightMax);
            // 注意返回节点的最大贡献值
            return root->val + std::max(leftMax,rightMax);
        }
    };
    ```
---

<div id="lcaoabt" onclick="window.location.hash">

#### 6. lowest-common-ancestor-of-a-binary-tree(#236)
linkage: [leetcode](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/ "二叉树的最近公共祖先")
> 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先
- 思路一：递归版本**ADT**
    - 通过递归子节点分别找到不同的4种情况

    ```cpp
    class Solution {
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
        {
            if(root == nullptr)
            {
                return root;
            }
            if(root->val == p->val || root->val == q->val)
            {
                return root;
            }
            TreeNode* left_son = lowestCommonAncestor(root->left,p,q);
            TreeNode* right_son = lowestCommonAncestor(root->right,p,q);
            if(left_son == nullptr && right_son == nullptr)
            {
                return nullptr;
            }
            if(left_son != nullptr && right_son == nullptr)
            {
                return left_son;
            }
            if(left_son == nullptr && right_son != nullptr)
            {
                return right_son;
            }
            if(left_son != nullptr && right_son != nullptr)
            {
                return root;
            }
            return root;
        }
    };
    ```
---

<div id="btlot" onclick="window.location.hash">

#### 7. binary-tree-level-order-traversal(#102)
linkage: [leetcode](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/submissions/ "二叉树的层序遍历")
> 给你一个二叉树，请你返回其按层序遍历得到的节点值
> 即逐层地，从左到右访问所有节点
- 注意：
  - **c++中queue()[push,pop]和deque()[push_back,pop_front]的使用**
  - DFS与BFS区别：
    - 1. DFS遍历的代码比BFS简洁
    - 2. 因为递归的方式隐含地使用了系统的栈，我们不需要自己维护一个数据结构
    - 3. 如果只是简单地将二叉树遍历一遍，那么DFS显然是更方便的选择
- 思路一：BFS cpp代码
    ```cpp
    class Solution {
    public:
        vector<vector<int>> levelOrder(TreeNode* root) 
        {
            vector<vector<int>> level_lists;
            if(root == nullptr)
            {
                return level_lists;
            }
            std::queue<TreeNode*> q;
            q.push(root);
            while(!q.empty())
            {
                vector<int> level_list;
                int num = q.size();
                for(int i=0;i<num;i++)
                {
                    // 二遍重做：注意queue为front
                    TreeNode* cur = q.front();
                    level_list.push_back(cur->val);
                    q.pop();
                    // 注意每一层的处理
                    if(cur->left != nullptr) q.push(cur->left);
                    if(cur->right != nullptr) q.push(cur->right);
                }
                level_lists.push_back(level_list);
            }
            return level_lists;
        }
    };
    ```
---

<div id="btlotii" onclick="window.location.hash">

#### 8. binary-tree-level-order-traversal-ii(#107)
linkage: [leetcode](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/ "二叉树的层次遍历 II")
> 给定一个二叉树，返回其节点值自底向上的层次遍历。
> 即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历
- **注意BFS做法:**
  1. 与7类似,需要用std::list每次都往队头塞**
    ```cpp
    list<vector<int>> level_lists;
    vector<vector<int>> level_vectors;
    level_vectors.assign(level_lists.begin(),level_lists.end());
    ```
  2. 用std::reverse函数实现
   ```cpp
   vector<vector<int>> level_vectors;
   reverse(level_vectors.begin(),level_vectors.end());
   ```
- 本题还可用DFS实现(略)
---

<div id="btzlot" onclick="window.location.hash">

#### 9. binary-tree-zigzag-level-order-traversal(#103)
linkage: [leetcode](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/ "二叉树的锯齿形层次遍历")
> 给定一个二叉树，返回其节点值的锯齿形层次遍历。
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
---

<div id="vbst" onclick="window.location.hash">

#### 10. validate-binary-search-tree(#98)
linkage: [leetcode](https://leetcode-cn.com/problems/validate-binary-search-tree/ "验证二叉搜索树")
> 给定一个二叉树，判断其是否是一个有效的二叉搜索树
- 思路一：**利用Recursion方法**
    ```cpp
    class Solution {
    public:
        bool isValidBST(TreeNode* root)
        {
            return recursionBST(root,LONG_MAX, LONG_MIN);
        }

        bool recursionBST(TreeNode* root, long max, long min)
        {
            // 递归的出口
            if(root == nullptr)
            {
                return true;
            }
            //递归的判断条件
            if(root->val >= max || root->val <= min)
            {
                return false;
            }
            return recursionBST(root->left, root->val, min) && recursionBST(root->right, max, root->val);
        }
    };
    ```
- 思路二：中序遍历方式
二叉搜索树一个明显的特点就是**中序遍历以后是一个有序数组**，通过这个对比判断是否二叉搜索树
  - 递归版本
    ```cpp
    class Solution {
    public:
        bool isValidBST(TreeNode* root)
        {
            if (root == nullptr)
            {
                return true;
            }
            inOrderTraversal(root);
            int inorder_num = inorder_lists_.size();
            for(int i = 1; i<inorder_num;i++)
            {
                if(inorder_lists_[i-1]>=inorder_lists_[i])
                    return false;
            }
            return true;
        }

        void inOrderTraversal(TreeNode* root)
        {
            // 注意recursion的出口
            if(root != nullptr)
            {
                inOrderTraversal(root->left);
                inorder_lists_.push_back(root->val);
                inOrderTraversal(root->right);
            }
            
        }

    private:
        vector<int64_t> inorder_lists_;
    };
    ```
- 非递归版本 **更简单的非递归遍历二叉树版本一致**
    ```cpp
    class Solution {
    public:
        bool isValidBST(TreeNode* root) {
            if(root == nullptr)
            {
                return true;
            }
            inOrderTravesal(root);
            int num = vector_paths_.size();
            for(int i=0; i<num-1;i++)
            {
                if(vector_paths_[i]>=vector_paths_[i+1])
                {
                    return false;
                }
            }
            return true;
        }
        void inOrderTravesal(TreeNode* root)
        {
            std::stack<std::pair<TreeNode*,bool>> s;
            s.push(std::make_pair(root,false));
            bool visited;
            while(!s.empty())
            {
                root = s.top().first;
                visited = s.top().second;
                s.pop();
                if(root==nullptr)
                {
                    continue;
                }
                // 重点核心: 此前已通过该结点将其局部入栈，则直接出栈输出
                if(visited)
                {
                    vector_paths_.push_back(root->val);
                }
                else
                {
                    s.push(std::make_pair(root->right,false));
                    s.push(std::make_pair(root,true));
                    s.push(std::make_pair(root->left,false));
                }
            }
        }
    private:
        std::vector<int64_t> vector_paths_;
    };
    ```
---

<div id="iiabst" onclick="window.location.hash">

#### 11. insert-into-a-binary-search-tree(#701)
linkage: [leetcode](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/ "二叉搜索树中的插入操作")
> 给定BST根节点和要插入的值，将值插入二叉搜索树
> 返回插入后二叉搜索树的根节点，不插入存在的值。
> 符合二叉搜索树即可，不需要维护子树高度差
- 思路一：**DFS Recursion**
    1、若 root == null，则返回 TreeNode(val)。
    2、若 val > root.val，插入到右子树
    3、若 val < root.val，插入到左子树
    4、返回 root
```cpp
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == nullptr)
        {
            // 注意： 返回一个new TreeNode
            return new TreeNode(val);
        }
        if(val > root->val)
        {
            // 注意：向右递归后返回结果
            root->right = insertIntoBST(root->right, val);
        }
        if(val < root->val)
        {
            root->left = insertIntoBST(root->left, val);
        }
        return root;
    }
};
```
- 思路二：**迭代非Recursion**
    1、二叉搜索树，如果val小于等于当前节点，向左遍历；若大于当前节点，则向右遍历
    2、终止条件为下一个遍历节点为空，这个节点也就是需要插入节点的位置
    3、在开始需要保存一个root指针，用于当做返回结果
    ```cpp
    class Solution {
    public:
        TreeNode* insertIntoBST(TreeNode* root, int val)
        {
            // 重点1：一定赋予临时变量， 直接操作root只返回插入后的三个值
            TreeNode* res = root;
            if(root==nullptr)
            {
                // 注意要new
                return new TreeNode(val);
            }
            while(root != nullptr)
            {
                if(val < root->val)
                {
                    if(root->left ==nullptr)
                    {
                        root->left = new TreeNode(val);
                        break;
                    }
                    else
                    {
                        //重点2：将下一节点赋予当前指针
                        root = root->left;
                    }
                }
                if(val > root->val)
                {
                    if(root->right ==nullptr)
                    {
                        root->right = new TreeNode(val);
                        break;
                    }
                    else
                    {
                        root = root->right;
                    }
                }
            }
            return res;
        }
    };
    ```
---

<div id="dniab" onclick="window.location.hash">

#### 12. delete-node-in-a-bst(#450)
linkage: [leetcode](https://leetcode-cn.com/problems/delete-node-in-a-bst/ "删除二叉搜索树中的节点")
> 给定一个二叉搜索树的根节点root和一个值key，删除二叉搜索树中的key对应的节点
> 返回根节点
- 思路一：递归
  - 方法：
    - 删除节点分为两步， 1. 找到删除位置； 2. 分析不同情况
    - 画图分析可知：
      - 1. 当删除节点在叶子节点，代码：
        ```cpp
        root = nullptr
        ```
        ![][image2]
      - 2. 当节点在后继successor上，找到其右子树对应的左节点,代码如下：
        ```cpp
        TreeNode* successorNode(TreeNode* root)
        {
            root = root->right;
            while(root->left != nullptr)
            {
                root = root->left;
            }
            return root;
        }
        ```
        ![][image3]
      - 3. 节点在前驱predecessor上，找到其左子树对应的右节点
        ```cpp
        TreeNode* predecessorNode(TreeNode* root)
        {
            root = root->left;
            while(root->right != nullptr)
            {
                root = root->right;
            }
            return root;
        }
        ```
        ![][image4]
    - 最终利用递归，代码如下：
    ```cpp
    class Solution {
    public:
        TreeNode* deleteNode(TreeNode* root, int key) 
        {
            if(root == nullptr)
            {
                return nullptr;
            }
            // 利用递归找到对应节点
            if(key < root->val)
            {
                // 返回值起到连接指向
                root->left = deleteNode(root->left, key);
            }
            else if(key > root->val)
            {
                root->right = deleteNode(root->right, key);
            }
            else
            {
                //找到key，分三种情况
                if(root->left == nullptr && root->right == nullptr)
                {
                    root = nullptr;
                }
                else if(root->right != nullptr)
                {
                    // 找后驱节点
                    root->val = successorNode(root);
                    root->right = deleteNode(root->right,root->val);
                }
                else
                {
                    root->val = predecessorNode(root);
                    root->left = deleteNode(root->left,root->val);
                }
            }
            return root;
        }

        int successorNode(TreeNode* root)
        {
            root = root->right;
            while(root->left != nullptr)
            {
                root = root->left;
            }
            return root->val;
        }

        int predecessorNode(TreeNode* root)
        {
            root = root->left;
            while(root->right != nullptr)
            {
                root = root->right;
            }
            return root->val;
        }
    };
    ```