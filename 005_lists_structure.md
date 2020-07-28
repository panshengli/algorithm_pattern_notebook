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
                // 无重复后连接到下一个节点，再考虑下个节点
                head = head->next;
            }
            return head;
        }
    }; 
    ```
- 快慢指针
---
