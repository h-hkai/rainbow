#include <string>
#include <iostream>
#include "boost/lexical_cast.hpp"
int main()
{
    std::string s="100";
    int a=boost::lexical_cast<int>(s);
    int b=1;
    std::cout<<(a+b) <<std::endl;//输出101
    return 0;
}
