## Slide Window 
- 滑动窗口:两个指针一前一后夹着的子串（子数组）类似一个窗口，这个窗口大小和范围会随着前后指针的移动发生变化。
- 两类问题：
  - 双指针
  - 特定数据结构，如sorted_map
- **核心点**是维护一个窗口集，根据窗口集来进行处理
- 核心步骤
  - 1. 设定两个指针，l和r，表示滑动窗口最左端和最右端,初始，两个指针指向S的第一个字符
  - 2. l不动，r向右移动，直到找到一个字符串能匹配T串,即match匹配串
  - 3. 右移动l，同时每右移一次l,通过右移r找match的字符串
  - 4. 如果能找到，且比当前串短，update。如果找不到，继续右移动left
--- 

## 📑 index
* <a href="#mws">1. minimum-window-substring(#76)</a>






---




<div id="mws" onclick="window.location.hash">

#### 1. minimum-window-substring(#76)
linkage: [leetcode](https://leetcode-cn.com/problems/minimum-window-substring/ "最小覆盖子串")
> 一个字符串S、一个字符串T
> 字符串S里面找出：包含T所有字符的最小子串
> 不存这样的子串，则返回空字符串""
> 要求O(n)的时间复杂度
- 思路一：
- 
---

