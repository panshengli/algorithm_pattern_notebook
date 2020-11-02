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
* <a href="#removeDuplicatesFromSortedList">​1. remove-duplicates-from-sorted-list(#83)​</a>
* <a href="#remove-duplicates-from-sorted-list-ii">2. remove-duplicates-from-sorted-list-ii(#82)</a>
* <a href="#reverseLinkedList">​​3. reverse-linked-list(#206)[*基础框架*，**注重recursion和traversal的写法**]</a>
* <a href="#rlli">​​​4. reverse-linked-list-ii​​(#92)</a>
* <a href="#mergeTwoSortedLists">​​​​5. merge-two-sorted-lists(#21)​​​ </a>
* <a href="#partitionList">​6. partition-list​​​​((#86)</a>
* <a href="#sortList">7. ​sort-list(#148)[很棒的list**归并排序**示例，5题的强化版]​</a>
* <a href="#reorderList">8. ​reorder-list(#143)[3题，5题的强化应用，重点是思路]​</a>
* <a href="#llc">9. ​​linked-list-cycle​(#141)[快慢指针的典型应用]​</a>
* <a href="#llcii">10. ​​​linked-list-cycle-ii(#142)[思路篇：9的加强应用(**推荐**)]​​​​</a>
* <a href="#pll">11. ​palindrome-linked-list(#234)[3题，5题的强化应用]​​​​​</a>
* <a href="#clwrp">12. ​copy-list-with-random-pointer​​​​​​(#138)[链表的插入，复制，拆分，**很棒的思路**]</a>

### 扩展题型：
- 链表的操作:
  - #707.设计链表　[linkage](https://leetcode-cn.com/problems/design-linked-list/)
  - #203.移除链表 [linkage](https://leetcode-cn.com/problems/remove-linked-list-elements/)
  - #328.奇偶链表 [linkage](https://leetcode-cn.com/problems/odd-even-linked-list/)
  - #2.两数加和 [linkage](https://leetcode-cn.com/problems/add-two-numbers/submissions/)
- 双指针操作:
  - #160.相交链表(比较巧妙地思路) [linkage](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/)
  - #19.删除链表的倒数第N个节点(重点为思路)[linkage](https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/)
- 用栈的方式处理双链表
  - ＃430.扁平化多级双向链表 [linkage](https://leetcode-cn.com/problems/flatten-a-multilevel-doubly-linked-list/)




[//]: # (Image References)
[image1]: .readme/traversal.gif "traversal"
[image2]: .readme/recursion.gif "recursion"
[image3]: .readme/circularlinkedlist.png "circularlinkedlist"
[image4]: .readme/circularlinkedlistII.png "circularlinkedlistII"
[image5]: .readme/circularlinkedlistII_2.png "circularlinkedlistII_2"
[image6]: .readme/copy_list.png "copy_list"


<div id="removeDuplicatesFromSortedList" onclick="window.location.hash">

#### 1. ​remove-duplicates-from-sorted-list​(#83)
linkage: [leetcode](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/ "删除排序链表中的重复元素")
> 给定一个**排序链表**，删除所有重复的元素，使得每个元素只出现一次
- 迭代版本（直接法）
```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        ListNode* cur = head;
        if(head == nullptr)
        {
            return cur;
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
        return cur;
    }
};
```
- 递归版本一
- 有重先去重，头结点定位到重复元素最后一个
    ```cpp
    class Solution {
    public:
        ListNode* deleteDuplicates(ListNode* head)
        {
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
        ListNode* deleteDuplicates(ListNode* head)
        {
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

#### ​​2. remove-duplicates-from-sorted-list-ii​(#82)
linkage: [leetcode](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/ "删除排序链表中的重复元素 II")
> 给定一个排序链表，**删除所有含有重复数字**的节点，只保留原始链表中 没有重复出现 的数字
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
                head = deleteDuplicates(next);
                return head;
            }
            else
            {
                //如果不重复就将当前节点指向递归函数
                head->next = deleteDuplicates(next);
                return head;
            }
        }
    };
    ```
---

<div id="reverseLinkedList" onclick="window.location.hash">

#### 3. ​​​reverse-linked-list​​​(#206)
linkage: [leetcode](https://leetcode-cn.com/problems/reverse-linked-list/ "反转一个单链表")
> 反转一个单链表
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
                //　二遍复习: 注意为什么不能cur = cur->next
                cur = tmp_next;
            }
            return pre;
        }
    };
    ```
- 思路二：递归方式
  - 一直递归到链表的最后一个结点，记作ret
  - 每次返回过程，让当前结点的下一个结点的next指针指向当前节点
  - 让当前结点的next指针指向NULL，实现局部反转
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
        // 二遍复习: 注意head的位置 
        head->next->next = head;
        head->next = nullptr;
        return cur;
    }
};
```
---

<div id="rlli" onclick="window.location.hash">

#### 4. ​​​reverse-linked-list​​​-ii(#92)
linkage: [leetcode](https://leetcode-cn.com/problems/reverse-linked-list-ii/ "反转链表 II")
> 反转从位置m到n的链表。请使用一趟扫描完成反转
- 方法一：迭代法-头插法
  - 节点交换思路主要为渐进式的交换节点顺序
  - [reference linkage](https://leetcode-cn.com/problems/reverse-linked-list-ii/solution/tu-jie-die-dai-he-di-gui-jie-fa-chao-xiang-xi-by-s/)
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
                // 注意四：交换后左值向右移，右值通过backtrace自动向前移动
                left_ = left_->next;
            }
        }

    private:
        bool flag_ = false;
        ListNode* left_ = new ListNode();
    };
    ```

- 方法三：递归法(反向传递法,推荐)
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
            //　二遍复习：注意successor变量的定义
            static ListNode* successor = nullptr;
            if(n == 1)
            {
                // 注意：successor_后驱节点
                successor = head->next;
                // 注意：一定要有递归的出口，即返回值
                return head;
            }
            ListNode* last = reverseN(head->next,n-1);
            head->next->next = head;
            // 注意：反转之后的head节点和后面的节点连起来
            head->next = successor;
            return last;
        }
    };
    ```
---

<div id="mergeTwoSortedLists" onclick="window.location.hash">

#### 5. ​merge-two-sorted-lists(#21)
linkage: [leetcode](https://leetcode-cn.com/problems/merge-two-sorted-lists/ "合并两个有序链表")
> 将两个**升序链表**合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的
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
                // 注意递归需要连接，
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

#### 6. ​​partition-list​​​​(#86)
linkage: [leetcode](https://leetcode-cn.com/problems/partition-list/ "分隔链表")
> 给定一个链表和一个特定值x，对链表进行分隔，使得所有小于x的节点都在大于或等于x的节点之前。
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
            // 添加较小列表尾端指向较大 列表 的首部
            small_tmp->next =large_list->next;
            return small_list->next;
        }
    };
    ```
---

<div id="sortList" onclick="window.location.hash">

#### 7. ​sort-list(#148)
linkage: [leetcode](https://leetcode-cn.com/problems/sort-list/ "排序链表")
> **O(nlogn)时间复杂度**和常数级空间复杂度，对链表排序
- 思路：只有 heapSort, mergeSort, quickSort
  - **时间复杂度想到二分法**，从而联想到归并排序
  - [参考思路：快慢指针+二路归并（C++）](https://leetcode-cn.com/problems/sort-list/solution/kuai-man-zhi-zhen-er-lu-gui-bing-c-by-jiangtianyu0/)
  - 主要步骤：
    - 利用**快慢指针**进行列表的**二分(迭代)**分割，调用**有序链表**两两合并
    - **中点确认**：快指针走两步，慢指针走一步，遍历完时，慢指针指向中点
    - 确认完中点后，**切开链表**，需要用一个变量**保存中点节点的前驱**
    - 调用**有序链表**两两合并(**两路归并**),见`6. ​​partition-list`
  - 注意点：
    - 调用两路归并算法时，不能用迭代方式，因为题目要求空间复杂度为常数级
- 思路一: 递归版本(**两路归并用递归，如果不要求空间复杂度情况下**)
    ```cpp
    class Solution {
    public:
        ListNode* sortList(ListNode* head)
        {
            // 注意if在recursion中的判断条件和快慢指针的条件
            if(head == nullptr || head->next == nullptr)
            {
                return head;
            }
            // 注意：快慢指针初始时指向同一起点
            ListNode* pre_slow = new ListNode();
            ListNode* slow = head;
            pre_slow->next = slow;
            ListNode* fast = head;
            // 注意：运行fast = fast->next->next之前，需要检查fast和fast->next不为空
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
- 思路二：迭代版本（注意思路，特别时mergeTwoList中，ListNode的定义）
    ```cpp
    class Solution {
    public:
        ListNode* sortList(ListNode* head)
        {
            // 同上
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
- 思路三：quickSort链表
  - 思路见注释
    ```cpp
    class Solution {
    public:
        ListNode* sortList(ListNode* head)
        {
            quickSort(head, nullptr);
            return head;
        }
        ListNode* partition(ListNode* begin, ListNode* end)
        {
            // 1. 基准选为首元素，声明两个变量
            ListNode* slow = begin;
            ListNode* fast = begin->next;
            int privot = begin->val;
            // 2. 小于key，更新slow指向，slow与fast值交换，更新fast指向
            while (fast != end)
            {
                if (fast->val < privot)
                {
                    // slow始终指向<=key
                    // slow->next始终>key或者为fast指向的节点
                    slow = slow->next;
                    swap(slow->val, fast->val);
                }
                fast = fast->next;
            }
            // 3. 循环执行2直至fast至尾部；交换链表头元素与slow指向元素值
            swap(begin->val, slow->val);
            // 4. 以slow为分割点分两部分，两个序列递归上述步骤排序完成
            return slow;
        }

        void quickSort(ListNode* begin, ListNode* end)
        {
            if (begin != end) {
                ListNode* temp = partition(begin, end);
                quickSort(begin, temp);
                quickSort(temp->next, end);
            }
        }
    };
    ```
---


<div id="reorderList" onclick="window.location.hash">

#### 8. ​reorder-list(#143)
linkage: [leetcode](https://leetcode-cn.com/problems/reorder-list/ "重排链表")
> 示例
> 给定链表 1->2->3->4, 重新排列为 1->4->2->3.
> 给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.
- 思路：一、找到中点；二、反转后面链表；三、拼接前后链表
- 迭代+递归（根据思路自己写出，相应的对应题型有3,4）
    ```cpp
    class Solution {
    public:
        void reorderList(ListNode* head)
        {
            // 二遍复习：需要加上判断head->next的判断情况，由于快慢指针的原因
            if(head == nullptr || head->next == nullptr)
            {
                return;
            }
            // 快慢指针找中点
            ListNode* slow = head;
            ListNode* pre_slow = new ListNode();
            pre_slow->next = slow;
            ListNode* fast = head;

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

            // 合并指针临时变量
            ListNode* reorder_list = head;
            ListNode* cur = new ListNode();
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

#### 9. ​​linked-list-cycle(#141)
linkage: [leetcode](https://leetcode-cn.com/problems/linked-list-cycle/ "环形链表")
> 给定一个链表，判断链表中是否有环,
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
                // 二遍复习: 不要返回head,和递归不同
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
---

<div id="llcii" onclick="window.location.hash">

#### 10. ​​​linked-list-cycle-ii​(#142)
linkage: [leetcode](https://leetcode-cn.com/problems/linked-list-cycle-ii/ "环形链表 II")
> 给定一个链表，返回链表开始入环的第一个节点(索引从0开始)
- 如果链表无环，则返回null
![][image4]
- 迭代版本(快慢指针)[**推荐**]
  - 思路数学证明：
    1. 通过数学证明的方式，得出x=z
    2. 判断是否有环
    3. 一个指针从头开始，慢指针继续走，两指针相遇，则为入环起点
    ![][image5]
    ```cpp
    class Solution {
    public:
        ListNode *detectCycle(ListNode *head)
        {
            if(head == nullptr || head->next == nullptr)
            {
                return nullptr;
            }
            ListNode* slow = head;
            ListNode* fast = head;
            // 为了找到有环的index
            ListNode* tmp = head;
            while(fast != nullptr && fast->next != nullptr)
            {
                slow = slow->next;
                fast = fast->next->next;
                // 判断是否有环
                if(slow == fast)
                {
                    // 一个指针从头开始，慢指针继续走，两指针相遇，则为入环起点
                    while(tmp != slow)
                    {
                        tmp = tmp->next;
                        slow = slow->next;
                    }
                    return tmp;
                }
            }
            return nullptr;
        }
    };
    ```

- 哈希函数版本(同样适用于9题)
- 思路：
  - 使用map将节点地址与访问的次数关联
  - 如果有一个地址访问了超过1一次，说明链表中存在环
    ```cpp
    class Solution {
    public:
        ListNode *detectCycle(ListNode *head)
        {
            // 注意：此处if的判断条件，不能包含 || head->next == nullptr
            if(head == nullptr)
            {
                return head;
            }
            std::unordered_map<ListNode*,int> u_map;
            while(head != nullptr)
            {
                // 如果map的索引大于1，则说明入环位置
                if(u_map[head]>1)
                {
                    return head;
                }
                // 不要忘了，向map里面添加键和值
                u_map[head]++;
                head = head->next;
            }
            return nullptr;
        }
    };
    ```
---

<div id="pll" onclick="window.location.hash">

#### 11. ​palindrome-linked-list​​​​​(#234)
linkage: [leetcode](https://leetcode-cn.com/problems/palindrome-linked-list/ "回文链表")
> 请判断一个链表是否为回文链表
- 思路(独立写出)：
  - 1.快慢指针找到链表中点
  - 2.翻转后半部分链表
  - 3.比较前一部分链表和翻转后链表的值
    ```cpp
    class Solution {
    public:
        bool isPalindrome(ListNode* head)
        {
            if(head == nullptr || head->next == nullptr)
            {
                return true;
            }
            ListNode* fast = head;
            ListNode* slow = head;
            ListNode* pre_slow = new ListNode();
            // 1. 找链表中点
            while(fast != nullptr && fast->next != nullptr)
            {
                pre_slow = slow;
                slow = slow->next;
                fast = fast->next->next;
            }
            pre_slow->next = nullptr;
            // 2. 翻转后半部分链表
            ListNode* reverse_list = reverseListRecursion(slow);
            // 3. 比较两个链表是否相等
            while(head != nullptr)
            {
                if(head->val != reverse_list->val)
                {
                    return false;
                }
                head = head->next;
                reverse_list = reverse_list->next;
            }
            return true;
        }

        ListNode* reverseListRecursion(ListNode* head)
        {
            if(head == nullptr || head->next == nullptr)
            {
                return head;
            }
            // 注意:递归填入的条件为head->next
            ListNode* first_head = reverseList(head->next);
            head->next->next = head;
            head->next = nullptr;
            return first_head;
        }

        ListNode* reverseListTraversal(ListNode* head)
        {
            if(head == nullptr)
            {
                return head;
            }
            // 注意：非遍历方式
            ListNode* cur = head;
            ListNode* pre = nullptr;
            while(cur != nullptr)
            {
                // 注意：一定要用临时变量操作前后指针
                ListNode* tmp_next = cur->next;
                cur->next = pre;
                pre = cur;
                cur = tmp_next;
            }
            return pre;
        }
    };
    ```
---
- 思路二：将值复制到数组中后用双指针法
  - 复制链表值到数组列表中
  - 使用双指针法判断是否为回文
- **注意：回文串的判断循环**
- **`for(int i = 0, j=values.size()-1;i<j;i++,j--)`**
    ```cpp
    class Solution {
    public:
        bool isPalindrome(ListNode* head)
        {
            if(head == nullptr)
            {
                return true;
            }
            std::vector<int> vector_values;
            while(head!= nullptr)
            {
                vector_values.push_back(head->val);
                head = head->next;
            }
            return isPalindrome(vector_values);
        }

        bool isPalindrome(std::vector<int>& values)
        {
            if(values.size()<2)
            {
                return true;
            }
            // 注意：回文串的判断循环
            for(int i = 0, j = values.size()-1; i < j; i++,j--)
            {
                if(values[i] != values[j])
                {
                    return false;
                }
            }
            return true;
        }
    };
    ```
---

<div id="clwrp" onclick="window.location.hash">

#### 12. ​copy-list-with-random-pointer(#138)
linkage: [leetcode](https://leetcode-cn.com/problems/copy-list-with-random-pointer/ "复制带随机指针的链表")
> 给定一个链表，每个节点包含一个额外增加的随机指针
> 该指针可以指向链表中的任何节点或空节点,要求返回这个链表的深拷贝
- 思路一：hashMap
  - 常用模板，借助哈希保存节点信息，时间复杂度：O(n)，空间复杂度：O(n)
    ```cpp
    class Solution {
    public:
        Node* copyRandomList(Node* head)
        {
            if(head == nullptr)
            {
                return head;
            }
            std::unordered_map<Node*,Node*> umap;
            Node* cur = head;
            // 1. 将value拷贝到新的链表中
            while(cur != nullptr)
            {
                umap[cur] = new Node(cur->val);
                // 此时不能将下面两行放在此处，这样会改变其指向，导致copy的链表终止复制
                // umap[cur]->random = umap[cur->random];
                // umap[cur]->next = umap[cur->next];
                cur = cur->next;
            }
            // 2. 复制链表next和random指针
            cur = head;
            while(cur != nullptr)
            {
                // 注意：后面指向copy的list,而不是指向cur->random
                umap[cur]->random = umap[cur->random];
                umap[cur]->next = umap[cur->next];
                cur = cur->next;
            }
            return umap[head];
        }
    };
    ```
- 思路二：原地复制方式(思路篇)
  - 推荐，虽然比较复杂，但是可以很好的理解链表的操作
  - 1. 复制链表节点 如A->B->C 变为 A->A'->B->B'->C->C'
  - 2. 设置节点random值
  - 3. 将复制链表从原链表分离
  - 第二步中复制random节点，有如下关系，即`A'->random = A->random->next`,如图
    ![][image6]
    ```cpp
    class Solution {
    public:
        Node* copyRandomList(Node* head)
        {
            if(head == nullptr)
            {
                return head;
            }
            // 1. 创建组合链表
            Node* cur = head;
            while(cur != nullptr)
            {
                // 注意：此处链表复制的写法
                Node* copy = new Node(cur->val);
                copy->next = cur->next;
                cur->next = copy;
                cur = copy->next;
            }
            // 2. 拷贝random节点
            cur = head;
            while(cur != nullptr)
            {
                if(cur->random != nullptr)
                {
                    // 注意：random节点拷贝的对应关系
                    cur->next->random = cur->random->next;
                }
                cur = cur->next->next;
            }
            // 拆分链表
            cur = head;
            Node* copy_list = head->next;
            Node* copy_node = copy_list;
            while(cur != nullptr)
            {
                cur->next = copy_node->next;
                // 注意：一定要判断copy_node->next是否为空,或者cur->next != nullptr
                if(copy_node->next != nullptr)
                {
                    copy_node->next = copy_node->next->next;
                }
                // 注意：由于前面已经修改了指向，
                // 因此此处只需要指向下一个node就可以了
                cur = cur->next;
                copy_node = copy_node->next;
            }
            return copy_list;
        }
    };
    ```
---
