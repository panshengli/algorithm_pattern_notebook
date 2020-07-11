#include<iostream>
#include<string>
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
        std::cout<<i<<" hash_code: "<< hash_code
                 <<" target_code: "<< target_code <<std::endl;
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
int main()
{
    std::string source = "sdsafsakobeasdsafsaf";
    std::string target = "kobe";
    std::cout<<strStr(source,target)<<std::endl;
}
