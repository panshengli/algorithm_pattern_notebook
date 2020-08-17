## BackTrack Algorithm

## 📑 index
* <a href="#subsets">1. subSets(#78)</a>


<div id="subSets" onclick="window.location.hash">

#### 1. subSets(#78)
linkage: [leetcode](https://leetcode-cn.com/problems/subsets/ "查找集合所有子集")

1. backtrack algorithm

    ```go
    // ADT 
    // 应用回溯法的题目，简单来说就是穷尽所有可能性
    // 通过不停的选择，撤销选择，来穷尽所有可能性，最后将满足条件的结果返回
    result = []
    func backtrack(选择列表,路径):
    if 满足结束条件:
        result.add(路径)
        return
    for 选择 in 选择列表:
        做选择
        backtrack(选择列表,路径)
        撤销选择
    ```

    ```cpp
    class Solution {
    public:
        vector<vector<int>> subsets(vector<int>& nums) 
        {
            vector<vector<int>> res;
            vector<int> tmp;
            backtrack(nums,res,tmp,0);
            return res;
        }
        void backtrack(vector<int>& nums,vector<vector<int>>& res,vector<int> tmp,int index)
        {
            res.push_back(tmp);//由于所有子集都要，所以不用判断返回条件
            for(int i=index;i<nums.size();i++){
                tmp.push_back(nums[i]);
                backtrack(nums,res,tmp,i+1);
                tmp.pop_back();
            }
        }
    };
    ```
---