#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
    std::vector<int> value_vectors;
    value_vectors.push_back(8);
    value_vectors.push_back(1);
    value_vectors.push_back(5);
    value_vectors.push_back(6);
    std::reverse(value_vectors.begin(),value_vectors.end());
    for(auto x:value_vectors)
        std::cout<<"x: "<<x<<std::endl;
    return 0;
}
