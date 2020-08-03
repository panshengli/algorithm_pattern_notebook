## Lists Structure
- struct Lists
```cpp
 // Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};
```
---


## 📑 index
* <a href="#​remove-duplicates-from-sorted-list​">​remove-duplicates-from-sorted-list​</a>
* <a href="#​​remove-duplicates-from-sorted-list-ii​​">​remove-duplicates-from-sorted-list-ii​</a>
* <a href="#​​​reverse-linked-list​​​">​​reverse-linked-list​</a>
* <a href="#​reverse-linked-list-ii​​​​">​​​reverse-linked-list-ii​​</a>


[//]: # (Image References)
[image1]: .readme/traversal.gif "traversal"
[image2]: .readme/recursion.gif "recursion"

<div id="​remove-duplicates-from-sorted-list​" onclick="window.location.hash">

#### ​remove-duplicates-from-sorted-list​
linkage: [leetcode](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/ "删除排序链表中的重复元素")
- 给定一个**排序链表**，删除所有重复的元素，使得每个元素只出现一次
- 迭代版本（直接法）
```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) 
    {
        ListNode* _head = head;
        if(head == nullptr)
        {
            return _head;
        }
        // 注意1：判断当前head->next是否为空，并非head为空
        while(head->next!=nullptr)
        {
            if(head->next->val == head->val)
            {
                //注意2：删除操作
                head->next = head->next->next;
            }
            else
            {
                head = head->next;
            }
        }
        return _head;
    }
};
```
- 递归版本一
- 有重先去重，头结点定位到重复元素最后一个
    ```cpp
    class Solution {
    public:
        ListNode* deleteDuplicates(ListNode* head) {
            if(head == nullptr || head->next == nullptr)
            {
                return head;
            }
            if(head->val == head->next->val)
            {
                // 如果有重复，头节点定位到重复元素的最后一个，相当于去重
                head = deleteDuplicates(head->next);
            }
            else
            {
                // 无重复后连接到下一个节点，再考虑下个节点
                head->next = deleteDuplicates(head->next);
            }
            return head;
        }
    };
    ```
- 递归版本二
- 删除头节点后面挂接的链表中的重复元素
    ```cpp
    class Solution {
    public:
        ListNode* deleteDuplicates(ListNode* head) {
            if(head == nullptr || head->next == nullptr)
            {
                return head;
            }
            // 删除头节点后面挂接的链表中的重复元素
            head->next = deleteDuplicates(head->next);
            if(head->val == head->next->val)
            {
                head = head->next;
            }
            return head;
        }
    }; 
    ```
- 快慢指针
    ```cpp
    class Solution {
    public:
        ListNode* deleteDuplicates(ListNode* head) 
        {
            ListNode* slow = head;
            ListNode* fast = head;
            if(head == nullptr)
            {
                return slow;
            }
            // 注意while判断的条件
            while(fast != nullptr)
            {
                if(slow->val != fast->val)
                {
                    // 若不相等，则将慢指针slow指向快指针fast的地址
                    slow->next = fast;
                    slow = slow->next;
                }
                // fast指向下一个
                fast = fast->next;
            }
            // 最后slow指向空
            slow->next = nullptr;
            return head;
        }
    };
    ```
---

<div id="​​remove-duplicates-from-sorted-list-ii​​" onclick="window.location.hash">

#### ​​remove-duplicates-from-sorted-list-ii​
linkage: [leetcode](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/ "删除排序链表中的重复元素")
- 给定一个排序链表，**删除所有含有重复数字**的节点，只保留原始链表中 没有重复出现 的数字
- 方式一： 迭代方法(注意元素去重以及边界条件处理)
    ```cpp
    class Solution {
    public:
        ListNode* deleteDuplicates(ListNode* head)
        {
            // 注意一：哨兵节点：指向链表，用于最后返回结果
            ListNode* tmp = new ListNode();
            tmp->next = head;
            ListNode* fast = head;
            ListNode* slow = tmp;
            if(head == NULL)
            {
                return fast;
            }
            // 注意二：一定要包含fast!= nullptr,需要考虑边界条件
            while(fast != nullptr&&fast->next != NULL)
            {
                // 注意三：找重复节点
                if(fast->val == fast->next->val)
                {
                    int tmp_node = fast->val;
                    // 注意四：一定要包含fast->next!= nullptr,需要考虑边界条件
                    while(fast->next != nullptr &&fast->next->val ==tmp_node)
                    {
                        fast = fast->next;
                    }
                    // 注意五：循环后返回重复元素的末尾
                    fast = fast->next;
                    slow->next = fast;
                }
                else
                {
                    fast = fast->next;
                    slow = slow->next;
                }
            }
            return tmp->next;
        }
    };
    ```
- 方式二：Recursion
    ```cpp
    class Solution {
    public:
        ListNode* deleteDuplicates(ListNode* head) 
        {
            if(head == nullptr || head->next == nullptr)
            {
                return head;
            }
            // 注意：下一个元素
            ListNode * next = head->next;
            if(next->val == head->val)
            {
                while(next != nullptr && next->val == head->val)
                {
                    next = next -> next;
                }
                // 因为要将重复的都删了，所以直接返回递归函数
                return deleteDuplicates(next);
            }
            else
            {
                //如果不重复就将当前节点指向递归函数
                head->next = deleteDuplicates(head->next);
                return head;
            }
        }
    };
    ```
---

<div id="​​​​reverse-linked-list​​​" onclick="window.location.hash">

#### ​​​reverse-linked-list​​​
linkage: [leetcode](https://leetcode-cn.com/problems/reverse-linked-list/ "反转一个单链表")
- 反转一个单链表
- 定义两个指针： preprepre 和 curcurcur ；preprepre 在前 curcurcur 在后
- 每次让 preprepre 的 nextnextnext 指向 curcurcur ，实现一次局部反转
- 局部反转完成之后， preprepre 和 curcurcur 同时往前移动一个位置
- 循环上述过程，直至 preprepre 到达链表尾部
![alt text][image1]
- 思路一：迭代双指针方式
    ```cpp
    class Solution {
    public:
        ListNode* reverseList(ListNode* head)
        {
            if(head == nullptr)
            {
                return head;
            }
            // 注意：此处pre不能等于new ListNode()
            ListNode* pre = nullptr;
            ListNode* cur = head;
            while(cur != nullptr)
            {
                // 注意：此处用临时变量指向cur->next
                ListNode* tmp_next = cur->next;
                cur->next = pre;
                // 双指针移动
                pre = cur;
                cur = tmp_next;
            }
            return pre;
        }
    };
    ```
- 思路二：递归方式
- 使用递归函数，一直递归到链表的最后一个结点，该结点就是反转后的头结点，记作ret
- 每次函数在返回的过程中，让当前结点的下一个结点的next指针指向当前节点
- 同时让当前结点的next指针指向NULL，从而实现从链表尾部开始的局部反转
- 当递归函数全部出栈后，链表反转完成
![alt text][image2]
    ```cpp
    class Solution {
    public:
        ListNode* reverseList(ListNode* head) 
        {
            // 注意：head->next == nullptr要添加，为了使cur指向最后一个node->val
            if(head == nullptr || head->next == nullptr)
            {
                return head;
            }
            // 注意：定义一个临时node，坐标链表的开头
            ListNode* cur = reverseList(head->next);
            head->next->next = head;
            head->next = nullptr;
            return cur;
        }
    };
    ```
---

<div id="​​​​reverse-linked-list-ii​​​" onclick="window.location.hash">

#### ​​​reverse-linked-list​​​-ii
linkage: [leetcode](https://leetcode-cn.com/problems/reverse-linked-list-ii/ "反转链表 II")
- 反转从位置 m 到 n 的链表。请使用一趟扫描完成反转
- 方法一：迭代法-头插法
    ```cpp
    class Solution {
    public:
        ListNode* reverseBetween(ListNode* head, int m, int n) 
        {
            ListNode* dummy = new ListNode();
            dummy->next = head;
            ListNode* pre = dummy;
            for(int i=1;i<m;i++)
            {
                pre = pre->next;
            }    
            head = pre->next;
            for(int i=m;i<n;i++)
            {
                ListNode* next = head->next;
                // 头结点指向(next)链表的next的指向
                head->next = next->next;
                // next节点指向pre节点的指向
                next->next = pre->next;
                // pre指向next节点
                pre->next = next;
            }
            return dummy->next;
        }
    };
    ```
- 方法二：递归法(值交换法)
- 核心思想：
  - 第一步：将指针分别指向所翻转的首尾位置
  - 第二步：递归，递归的出口为n==1
  - 第三步：将左右指针的值交换，同时左指针指向节点
  - 第四步：判断是否为两指针是否重合，结束
    ```cpp
    class Solution {
    public:
        ListNode* reverseBetween(ListNode* head, int m, int n) 
        {
            if(head == nullptr)
            {
                return head;
            }
            // 注意一：为了获取head的首地址
            left_ = head;
            recurseReversion(head,m,n);
            return head;
        }

        void recurseReversion(ListNode * right, int m, int n)
        {
            if(n == 1)
            {
                return;
            }
            right = right->next;
            if(m>1)
            {
                left_= left_->next;
            }
            recurseReversion(right,m-1,n-1);
            // 注意二：通过奇偶数来判断是否交换
            if(left_ == right || right->next == left_)
            {
                flag_ = true;
            }
            if(!flag_)
            {
                // 注意三：交换左右值
                int tmp_val = right->val;
                right->val = left_->val;
                left_->val = tmp_val;
                // 注意四：交换后左值向右移，右值通过traceback自动向前移动
                left_ = left_->next;
            }
        }

    private:
        bool flag_ = false;
        ListNode* left_;
    };
    ```
---
- 方法三：递归法(反向传递法)
- 该方法继承`​​​reverse-linked-list​​​`中迭代方法
- [参考方法](https://leetcode-cn.com/problems/reverse-linked-list-ii/solution/bu-bu-chai-jie-ru-he-di-gui-di-fan-zhuan-lian-biao/ "步步拆解：如何递归地反转链表的一部分")
- 本方法一定要注意**递归的出口**和**调用**及**返回值的连接**
```cpp

```