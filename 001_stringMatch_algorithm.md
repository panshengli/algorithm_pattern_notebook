## StringMatch Algorithm

## 📑 index
* <a href="#strStr">1. strStr(#28)</a>


<div id="strStr" onclick="window.location.hash">

#### 1. strStr(#28)
linkage: [leetcode](https://leetcode-cn.com/problems/implement-strstr/ "字符串查找")
> 给定一个字符串和一个目标字符串，在字符串中找出目标字符串出现的第一个位置(从0开始)，否则返回-1
1. **Rabin-Karp Algorithm** instead of kmp

    ```cpp
    class Solution {
    public:
        int strStr(std::string haystack, std::string needle)
        {
            int needle_size = needle.length();
            int haystack_size = haystack.length();
            if(haystack_size == 0 )
            {
                if (needle_size ==0)
                {
                    return 0;
                }
                else
                {
                    return -1;
                }
            }
            else if (needle_size ==0)
            {
                return 0;
            }
            else if(haystack_size<needle_size)
            {
                return -1;
            }
            // using Rabin-Karp algorithm
            static const int kBase = 1000000;
            static const int kHashNum = 31;
            int power = 1.0;
            for(int i = 0; i < needle_size;++i)
            {
                power = (power*kHashNum)%kBase;
            }

            int target_code = 0;
            for(int i = 0; i<needle_size;++i)
            {
                target_code = (target_code*kHashNum+needle[i])%kBase;
            }

            int hash_code = 0;
            for(int i = 0; i<haystack_size;++i)
            {
                // abc+d
                hash_code = (hash_code*kHashNum+haystack[i])%kBase;
                if(i<needle_size-1)
                {
                    continue;
                }
                // abcd-a
                if(i>=needle_size)
                {
                    hash_code = hash_code -(haystack[i-needle_size]*power)%kBase;
                    if(hash_code<0)
                    {
                        hash_code+=kBase;
                    }
                }
                // std::cout<<i<<" hash_code: "<< hash_code
                //          <<" target_code: "<< target_code <<std::endl;
                // double check the std::string
                if(hash_code==target_code)
                {
                    if(haystack.substr(i-needle_size+1,needle_size)==needle)
                    {
                        return i-needle_size+1;
                    }
                }
            }
            return -1;
        }
    };
    ```

2. **暴力匹配**算法
 - 需要注意点
 - 循环时，i 不需要到 len-1
 - 如果找到目标字符串，len(needle)==j
  
    ```cpp
    class Solution {
    public:
        int strStr(string haystack, string needle) {
            if(haystack.length() == 0 )
            {
                if (needle.length() ==0)
                {
                    return 0;
                }
                else 
                {
                    return -1;
                }
            }
            else if(haystack.length()<needle.length())
            {
                return -1;
            }
            for(size_t i = 0;i<= haystack.length()-needle.length();++i)
            {
                size_t j;
                for(j = 0; j<needle.length();++j)
                {
                    if(haystack[i+j]!=needle[j])
                        break;
                }
                if(needle.length()==j)
                    return i;
            }
            return -1;
        }
    };
    ```
---
