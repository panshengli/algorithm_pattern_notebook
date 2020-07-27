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
---
