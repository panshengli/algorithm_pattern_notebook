## Bit Opertator

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
a = 0 ^ a = a ^ 0
0 = a ^ a
// 由上面两个推导出：
a = a ^ b ^ b
b = a ^ a ^ b
```
---

## 📑 index
* <a href="#sn">1. single-number(#136)[字典遍历的典型应用]</a>
* <a href="#snii">2. single-number-ii(#137)</a>
* <a href="#sniii">3. single-number-iii(#260)</a>
* <a href="#no1b">4. number-of-1-bits(#191)</a>
* <a href="#cb">5. counting-bits(#338)</a>
* <a href="#rb">6. reverse-bits(#190)</a>
* <a href="#baonr">7. bitwise-and-of-numbers-range(#201)</a>







---

<div id="sn" onclick="window.location.hash">

#### 1. single-number(#136)
linkage: [leetcode](https://leetcode-cn.com/problems/single-number/ "只出现一次的数字")
> 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素
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
            // 重点：找出字典中count为1次的情况
            std::unordered_map<int,int>::iterator itor = counts.begin();
            // 将vector存入字典，对应元素个数
            for(auto i: nums)
            {
                counts[i]++;
            }
            for(;itor != counts.end();itor++)
            {
                //　重点２: itor为指针
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
> 非空整数数组，除了某个元素只出现一次以外，其余元素均出现三次。找出只出现了一次的元素
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
> 整数数组nums,有两个元素只出现一次，其余所有元素均出现两次。找出那两个元素
- 思路一：map版本
  - 解法与题1map版本相同
- 其他方法略
---

<div id="no1b" onclick="window.location.hash">

#### 4. number-of-1-bits(#191)
linkage: [leetcode](https://leetcode-cn.com/problems/number-of-1-bits/ "位1的个数")
> 编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为‘1’的个数(也被称为汉明重量)
```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        return hammingWeight_2(n);
    }
    //解法1: C++二进制容器,效率最高
    int hammingWeight_1(uint32_t n) {
        std::bitset<32> b(n);
        return b.count();
    }

    //解法2: 除2取余法
    int hammingWeight_2(uint32_t n) {
        int count = 0;
        while(n)
        {
            if(n%2 == 1)
                count++;
            n/=2;   // n>>=1;
        }
        return count;
    }

    // 解法3: 直接判读最低为是否为1即可[效率最高]
    int hammingWeight_3(uint32_t n) {
        int count = 0;
        while(n)
        {
            // 比如111与1相与得到001，所以直接判断最低位是不是1就好了
            count += n&1;
            n>>=1;
        }
        return count;
    }
};
```
---

<div id="cb" onclick="window.location.hash">

#### 5. counting-bits(#338)
linkage: [leetcode](https://leetcode-cn.com/problems/counting-bits/ "比特位计数")
> 非负整数 num。对于 0≤i≤ num范围中的每个数字i，计算其二进制数中的1的数目并将它们作为数组返回
- 思路一：利用题4的后两种解法
  - 利用解法2，超出内存限制
  - 利用解法3，超出时间限制
- 思路二：直接利用stl
  - 利用题4解法1，不易想
    ```cpp
    class Solution {
    public:
        vector<int> countBits(int num) 
        {
            vector<int> count_bits;
            for(int i = 0; i <= num;i++)
            {
                std::bitset<32> b(i);
                count_bits.push_back(b.count());
            }
            return count_bits;
        }
    };
    ```
- 思路三：奇偶数判别(**推荐**)
  - 需要归纳总结
  - 所有的数字，只有两类：
  - 奇数：二进制中，奇数一定比前面那个偶数多一个1
  - 偶数：二进制，偶数中1的个数和除以2的那个数一样多
    ```cpp
    class Solution {
    public:
        vector<int> countBits(int num)
        {
            // 初始化vector
            vector<int> result(num+1,0);
            for(int i = 1; i <= num; i++)
            {
                if(i % 2 == 1)
                {
                    result[i] = result[i-1] + 1;
                }
                else
                {
                    result[i] = result[i/2];
                }
            }
            return result;
        }
    };
    ```
---

<div id="rb" onclick="window.location.hash">

#### 6. reverse-bits(#190)
linkage: [leetcode](https://leetcode-cn.com/problems/reverse-bits/ "颠倒二进制位")
> 颠倒给定的 32 位无符号整数的二进制位
- 思路：逐位生成
    ```cpp
    class Solution {
    public:
        uint32_t reverseBits(uint32_t n)
        {
            uint32_t results = 0;
            uint32_t bit = 31;
            while(n)
            {
                // 注意符号优先级关系，将(n&1)<<bit
                results += ((n&1)<<bit);
                bit--;
                n>>=1;
            }
            return results;
        }
    };
    ```
---

<div id="baonr" onclick="window.location.hash">

#### 7. bitwise-and-of-numbers-range(#201)
linkage: [leetcode](https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/ "数字范围按位与")
> 给定范围[m,n]，其中0<=m<=n<=2147483647，返回此范围内所有数字的按位与(包含m,n两端点)
- 用传统方法遍历&，会导致超出时间限制
- 思路：找公共前缀
  - 1. 找到公共前缀的方法是位移
  - 2. 不断向右移动直到数字变成相等，得到的就是公共前缀
  - 3. 记录移过多少位，最后返回添上0的数字
    ```cpp
    class Solution {
    public:
        int rangeBitwiseAnd(int m, int n)
        {
            // 找公共前缀
            int shift = 0;
            while(m < n)
            {
                m >>= 1;
                n >>= 1;
                shift ++;
            }
            return m<<shift;
        }
    };
    ```
---
