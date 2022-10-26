#include "vector.hpp"
#include <vector>
#include <iostream>
// #include <iterator>

int main(){


    ft::vector<int> tmp;

    tmp.push_back(1);
    tmp.push_back(2);
    tmp.push_back(3);
    tmp.push_back(4);
    tmp.push_back(5);
    tmp.push_back(6);

  std::vector<int> tmp1;
      tmp1.push_back(1);
    tmp1.push_back(2);
    tmp1.push_back(3);
    tmp1.push_back(4);
    tmp1.push_back(5);
    tmp1.push_back(6);

    tmp.shrink_to_fit();
    std::cout << tmp[130] << std::endl;
    std::cout << tmp.size() << std::endl;

    // std::cout << tmp.at(5);
    ft::vector<int>::reverse_iterator iter = tmp.rbegin();
    ft::vector<int>::reverse_iterator iter1;

    std::vector<int>::reverse_iterator iter2 = tmp1.rbegin() ;
    std::cout << "ft: " << *iter << std::endl;
    std::cout << "std: " << *iter2 << std::endl;

    // iter = tmp.rbegin();
    // iter1 = tmp.rend();

    // for(; iter != iter1 ; iter++){
    //   std::cout << *iter << std::endl;
    // }
}