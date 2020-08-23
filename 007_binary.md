## Binary

##### 交换两个数
```cpp
a=a^b
b=a^b
a=a^b
```
##### 移除最后一个 1
```cpp
a=n&(n-1)
```
##### 获取最后一个 1
```cpp
diff=(n&(n-1))^n
```
##### 重要应用
```cpp
a ^ a = 0
a ^ a ^ b = b
```
---

## 📑 index
* <a href="#sn">1. single-number(#136)[字典遍历的典型应用]</a>
* <a href="#snii">2. single-number-ii(#137)</a>
* <a href="#sniii">3. single-number-iii(#260)</a>






---

<div id="sn" onclick="window.location.hash">

#### 1. single-number(#136)
linkage: [leetcode](https://leetcode-cn.com/problems/single-number/ "只出现一次的数字")
- 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素
- 思路一：XOR版本
  - 注意： a ^ b ^ b = a;
    ```cpp
    class Solution {
    public:
        int singleNumber(vector<int>& nums) 
        {
            int ans = nums[0];
            for(int i = 1; i<nums.size();i++)
            {
                ans ^= nums[i];
            }
            return ans;
        }
    };
    ```
- 思路二：map版本
  - **字典遍历的典型应用**
    ```cpp
    class Solution {
    public:
        int singleNumber(vector<int>& nums) 
        {
            int result;
            std::unordered_map<int,int> counts;
            // 将vector存入字典，对应元素个数
            for(auto i: nums)
            {
                counts[i]++;
            }
            // 找出字典中count为1次的情况
            std::unordered_map<int,int>::iterator itor = counts.begin();
            for(;itor != counts.end();itor++)
            {
                std::cout<<"itor->first: "<<itor->first<< "  itor->second: "<<itor->second<<endl;
                if(itor->second == 1)
                {
                    result = itor->first;
                }
            }
            return result;
        }
    };
    ```
- 思路三：sort版本
  - 先排序，通过双指针找到不等的情况
  - 解法略
---

<div id="snii" onclick="window.location.hash">

#### 2. single-number-ii(#137)
linkage: [leetcode](https://leetcode-cn.com/problems/single-number-ii/ "只出现一次的数字 II")
- 非空整数数组，除了某个元素只出现一次以外，其余元素均出现三次。找出只出现了一次的元素
- 思路一：map版本
  - 解法与题1map版本相同
- 思路二：python set版本(不推荐)
```python
class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        return (sum(set(nums))*3-sum(nums))//2
```
---

<div id="sniii" onclick="window.location.hash">

#### 3. single-number-iii(#260)
linkage: [leetcode](https://leetcode-cn.com/problems/single-number-iii/ "只出现一次的数字 III")
- 整数数组nums,有两个元素只出现一次，其余所有元素均出现两次。找出那两个元素
- 思路一：map版本
  - 解法与题1map版本相同
- 其他方法略
---


