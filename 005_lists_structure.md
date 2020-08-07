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
* <a href="#removeDuplicatesFromSortedList">​1. remove-duplicates-from-sorted-list​</a>
* <a href="#remove-duplicates-from-sorted-list-ii">2. remove-duplicates-from-sorted-list-ii</a>
* <a href="#reverseLinkedList">​​3. reverse-linked-list​</a>
* <a href="#rlli">​​​4. reverse-linked-list-ii​​</a>
* <a href="#mergeTwoSortedLists">​​​​5. merge-two-sorted-lists​​​</a>
* <a href="#partitionList">​6. partition-list​​​​</a>
* <a href="#sortList">7. ​sort-list [很棒的list归并排序示例，5题的强化版]​</a>
* <a href="#llc">8. ​​linked-list-cycle​ [3题，5题的强化应用，注意思路]​</a>





[//]: # (Image References)
[image1]: .readme/traversal.gif "traversal"
[image2]: .readme/recursion.gif "recursion"
[image3]: .readme/circularlinkedlist.png "circularlinkedlist"




<div id="removeDuplicatesFromSortedList" onclick="window.location.hash">

#### 1. ​remove-duplicates-from-sorted-list​
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

<div id="remove-duplicates-from-sorted-list-ii" onclick="window.location.hash">

#### ​​2. remove-duplicates-from-sorted-list-ii​
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

<div id="reverseLinkedList" onclick="window.location.hash">

#### 3. ​​​reverse-linked-list​​​
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
            // 注意：不要忘了此处定义的cur，作为链表的开头
            ListNode* cur = reverseList(head->next);
            head->next->next = head;
            head->next = nullptr;
            return cur;
        }
    };
    ```
---

<div id="rlli" onclick="window.location.hash">

#### 4. ​​​reverse-linked-list​​​-ii
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

- 方法三：递归法(反向传递法)
- 该方法继承`​​​reverse-linked-list​​​`中迭代方法
- [参考方法: 如何递归地反转链表的一部分](https://leetcode-cn.com/problems/reverse-linked-list-ii/solution/bu-bu-chai-jie-ru-he-di-gui-di-fan-zhuan-lian-biao/ "步步拆解：如何递归地反转链表的一部分")
- 本方法一定要注意**递归的出口**和**调用**及**返回值的连接**
    ```cpp
    class Solution {
    public:
        ListNode* reverseBetween(ListNode* head, int m, int n) 
        {
            if(head == nullptr)
            {
                return head;
            }
            if(m == 1)
            {
                // 注意：需要返回reverse前N项翻转
                return reverseN(head,n);
            }
            // 注意：前m项指向翻转后第一个节点
            head->next = reverseBetween(head->next,m-1,n-1);
            return head;
        }
        
        ListNode* reverseN(ListNode* head, int n)
        {
            if(n == 1)
            {
                // 注意：pre_flag_需要指向最后节点的下一节点
                pre_flag_ = head->next;
                // 注意：一定要有递归的出口，即返回值
                return head;
            }
            ListNode* last = reverseN(head->next,n-1);
            head->next->next = head;
            // 注意：反转之后的head节点和后面的节点连起来
            head->next = pre_flag_;
            return last;
        }

    private:
        ListNode* pre_flag_ = nullptr;
    };
    ```
---

<div id="mergeTwoSortedLists" onclick="window.location.hash">

#### 5. ​merge-two-sorted-lists
linkage: [leetcode](https://leetcode-cn.com/problems/merge-two-sorted-lists/ "合并两个有序链表")
- 将两个**升序链表**合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的
- 迭代版本(谁值大指向谁，然后节点指向下一节点)
- 关键步骤：
  - 1.临时变量的定义和操作
  - 2.列表的遍历循环条件
  - 3.遍历后列表的指向
    ```cpp
    class Solution {
    public:
        ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
        {
            if(l1 == nullptr)
            {
                return l2;
            }
            if(l2 == nullptr)
            {
                return l1;
            }
            // 注意：声明临时变量，用于返回
            ListNode* merge_list = new ListNode();
            // 注意：对merge_list进行操作
            ListNode* cur = merge_list;
            // 注意：当遍历完某一个链表时，退出循环
            while(l1 != nullptr && l2 != nullptr)
            {
                if(l1->val <= l2->val)
                {
                    // 注意：cur指向l1，并非cur =l1
                    cur->next = l1;
                    l1 = l1->next;
                }
                else
                {
                    cur->next = l2;
                    l2 = l2->next;
                }
                cur = cur->next;
            }
            // cur指向剩余链表
            if(l1 == nullptr)
            {
                cur->next = l2;
            }
            if(l2 == nullptr)
            {
                cur->next = l1;
            }
            return merge_list->next;
        }
    };
    ```
- 递归版本
- 思路参考：[一看就会，一写就废？详解递归](https://leetcode-cn.com/problems/merge-two-sorted-lists/solution/yi-kan-jiu-hui-yi-xie-jiu-fei-xiang-jie-di-gui-by-/)
    ```cpp
    class Solution {
    public:
        ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
        {
            // 终止条件：当两个链表都为空时，表示我们对链表已合并完成
            if(l1==nullptr)
                return l2;
            if(l2==nullptr)
                return l1;
            if(l1->val <= l2->val)
            {
                l1->next = mergeTwoLists(l1->next,l2);
                // 注意：递归的结束后返回的结果
                return l1;
            }
            else
            {
                l2->next = mergeTwoLists(l1,l2->next);
                return l2;
            }
        }
    };
    ```
---

<div id="partitionList" onclick="window.location.hash">

#### 6. ​​partition-list​​​​
linkage: [leetcode](https://leetcode-cn.com/problems/partition-list/ "分隔链表")
- 给定一个**排序链表**，删除所有重复的元素，使得每个元素只出现一次
- **思路：将大于等于x的节点，放到另外一个链表，最后连接这两个链表**
- 独立写出，需要注意
  - **写出两个链表后连接时，不要忘了尾端链表指向为空**
    ```cpp
    class Solution {
    public:
        ListNode* partition(ListNode* head, int x) 
        {
            if (head == nullptr)
            {
                return head;
            }    
            ListNode* small_list = new ListNode();
            ListNode* large_list = new ListNode();
            ListNode* small_tmp = small_list;
            ListNode* large_tmp = large_list;
            while(head != nullptr)
            {
                if(head->val < x)
                {
                    small_tmp->next = head;
                    small_tmp = small_tmp->next;
                }
                else
                {
                    large_tmp->next = head;
                    large_tmp = large_tmp->next;
                }
                head = head->next;
            }
            // 注意：一定要添加较大列表尾端指向为nullptr
            large_tmp->next = nullptr;
            // 添加较小列表尾端指向较大列表的首部
            small_tmp->next =large_list->next;
            return small_list->next;
        }
    };
    ```
---

<div id="sortList" onclick="window.location.hash">

#### 7. ​sort-list
linkage: [leetcode](https://leetcode-cn.com/problems/sort-list/ "排序链表")
- 在**O(nlogn)时间复杂度**和常数级空间复杂度下，对链表进行排序
- 只有 heapSort, mergeSort, quickSort
- **时间复杂度想到二分法**，从而联想到归并排序
- [参考思路：快慢指针+二路归并（C++）](https://leetcode-cn.com/problems/sort-list/solution/kuai-man-zhi-zhen-er-lu-gui-bing-c-by-jiangtianyu0/)
- 主要思路（根据思路做出）：
  - 利用**快慢指针**进行列表的**二分(迭代)**分割，调用**有序链表**两两合并
  - **中点确认**：快指针走两步，慢指针走一步，遍历完时，慢指针指向中点
  - 确认完中点后，**切开链表**，需要用一个变量**保存中点节点的前驱**
  - 调用**有序链表**两两合并(**两路归并**),见`6. ​​partition-list`
- 注意点：
  - 调用两路归并算法时，不能用迭代方式，因为题目要求空间复杂度为常数级
- 迭代版本
```cpp

```
- 递归版本(**两路归并用递归，如果不要求空间复杂度情况下**)
- 执行用时：88 ms, 在所有 C++ 提交中击败了37.07% 的用户
- 内存消耗：31 MB, 在所有 C++ 提交中击败了6.29% 的用户
    ```cpp
    class Solution {
    public:
        ListNode* sortList(ListNode* head) 
        {
            // 注意if在recursion中的判断条件
            if(head == nullptr || head->next == nullptr)
            {
                return head;
            }
            ListNode* pre_slow = new ListNode();
            ListNode* slow = head;
            pre_slow->next = slow;
            ListNode* fast = head;
            // 注意：要判断fast->next是否为空(合并的list个数为偶数时)
            while(fast != nullptr && fast->next != nullptr)
            {
                pre_slow = slow;
                slow = slow->next;
                fast = fast->next->next;
            }
            // 将切割后的链表结束指向空
            pre_slow->next = nullptr;
            return mergeTwoList(sortList(head),sortList(slow));
        }
        ListNode* mergeTwoList(ListNode* l1, ListNode* l2)
        {
            if(l1 == nullptr)
            {
                return l2;
            }
            if(l2 == nullptr)
            {
                return l1;
            }
            if(l1->val <= l2->val)
            {
                l1->next = mergeTwoList(l1->next,l2);
                return l1;
            }
            else
            {
                l2->next = mergeTwoList(l1,l2->next);
                return l2;
            }
        }
    };
    ```
- 迭代版本（注意思路，特别时mergeTwoList中，ListNode的定义）
- 执行用时：100 ms, 在所有 C++ 提交中击败了23.40% 的用户
- 内存消耗：36.4 MB, 在所有 C++ 提交中击败了5.15% 的用户
    ```cpp
    class Solution {
    public:
        ListNode* sortList(ListNode* head) 
        {
            // 注意if在recursion中以及在快慢指针的判断条件
            if(head == nullptr || head->next == nullptr)
            {
                return head;
            }
            ListNode* pre_slow = new ListNode();
            ListNode* slow = head;
            pre_slow->next = slow;
            ListNode* fast = head;
            // 注意：要判断fast->next是否为空(合并的list个数为偶数时)
            while(fast != nullptr && fast->next != nullptr)
            {
                pre_slow = slow;
                slow = slow->next;
                fast = fast->next->next;
            }
            // 将切割后的链表结束指向空
            pre_slow->next = nullptr;
            return mergeTwoList(sortList(head),sortList(slow));
        }
        ListNode* mergeTwoList(ListNode* l1, ListNode* l2)
        {
            if(l1 == nullptr)
            {
                return l2;
            }
            if(l2 == nullptr)
            {
                return l1;
            }
            // 注意思路
            ListNode* merge_list = new ListNode();
            ListNode* cur_head = merge_list;
            // 处理列表排序
            while(l1 != nullptr && l2 != nullptr)
            {
                if(l1->val <= l2->val)
                {
                    cur_head->next = l1;
                    l1 = l1->next;
                }
                else
                {
                    cur_head->next = l2;
                    l2 = l2->next;
                }
                cur_head = cur_head->next;
            }
            if(l1 != nullptr)
            {
                cur_head->next = l1;
            }
            if(l2 != nullptr)
            {
                cur_head->next = l2;
            }
            return merge_list->next;
        }
    };
    ```
---

<div id="reorderList" onclick="window.location.hash">

#### 8. ​reorder-list
linkage: [leetcode](https://leetcode-cn.com/problems/reorder-list/ "重排链表")
- 示例
- 给定链表 1->2->3->4, 重新排列为 1->4->2->3.
- 给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.
- 思路：一、找到中点；二、反转后面链表；三、拼接前后链表
- 迭代+递归（根据思路自己写出，相应的对应题型有3,4）
    ```cpp
    class Solution {
    public:
        void reorderList(ListNode* head) 
        {
            // 注意：需要加上判断head->next的判断情况，由于快慢指针的原因
            if(head == nullptr || head->next == nullptr)
            {
                return;
            }
            // 快慢指针找中点
            ListNode* slow = head;
            ListNode* pre_slow = new ListNode();
            ListNode* fast = head;
            // 合并指针临时变量
            ListNode* reorder_list = head;
            ListNode* cur = new ListNode();

            // 第一步：快慢指针找中点
            while(fast != nullptr && fast->next != nullptr)
            {
                pre_slow = slow;
                slow = slow->next;
                fast = fast->next->next;
            }
            // 切断首链表
            pre_slow->next = nullptr;
            // 第二步：翻转后面列表
            ListNode* reverse_list = reverseList(slow);

            // 第三步：合并列表
            while(head != nullptr)
            {
                cur->next = head;
                cur = cur->next;
                head = head->next;
                cur->next = reverse_list;
                cur = cur->next;
                reverse_list = reverse_list->next;
            }
            // 第四步：前面链表的尾指针指向后面链表的后续部分
            cur->next = reverse_list;
            head = reorder_list;
        }

        ListNode* reverseList(ListNode* head)
        {
            if(head == nullptr || head->next == nullptr)
            {
                return head;
            }
            // 注意：返回的变量结果
            ListNode* cur = reverseList(head->next);
            head->next->next = head;
            head->next = nullptr;
            return cur;
        }
    };
    ```
---

<div id="llc" onclick="window.location.hash">

#### 8. ​​linked-list-cycle
linkage: [leetcode](https://leetcode-cn.com/problems/linked-list-cycle/ "环形链表")
- 给定一个链表，判断链表中是否有环,
- pos索引从0开始，如果pos是-1，则在该链表中没有环，如图：
![alt text][image3]
  - 解释：链表中有一个环，其尾部连接到第二个节点
  - 输入：head = [3,2,0,-4]
  - 输出：true
- 快慢指针迭代(思路题)
    ```cpp
    class Solution {
    public:
        bool hasCycle(ListNode *head) 
        {
            if(head == nullptr || head->next == nullptr)
            {
                return false;
            }
            // 注意：快慢指针如何声明
            ListNode* fast = head;
            ListNode* slow = head;
            while(fast != nullptr && fast->next != nullptr)
            {
                fast = fast->next->next;
                slow = slow->next;
                if(slow == fast)
                {
                    return true;
                }
            }
            return false;
        }
    };
    ```