#include "ft_vector.hpp"
#include <vector>
#include <iostream>
#include <type_traits>
// #include <iterator>

typedef int t;
int main(){


  std::vector<t> tmp1;
  std::vector<t> tmp;

    tmp.push_back(12);
    tmp.push_back(13);
    tmp.push_back(14);
    // tmp.push_back(4);
    // tmp.push_back(5);
    // tmp.push_back(6);

    tmp1.push_back(1);
    tmp1.push_back(2);
    tmp1.push_back(8);
    tmp1.push_back(9);
    tmp1.push_back(10);
    tmp1.push_back(11);

  // ft::vector<t> tmp1(tmp.begin(),tmp.end());

  // tmp.assign(tmp1.begin(), tmp1.end());
  tmp1.insert(tmp1.begin() + 2, tmp.begin(), tmp.end());
  std::cout << "size = " << tmp.size() << std::endl;
    std::cout << "capacity = " << tmp.capacity() << std::endl;

  std::vector<t>::iterator i = tmp1.begin();
  std::vector<t>::iterator j = tmp1.end();
    for (; i != j ; i++)
      std::cout << *i << std::endl;


    // tmp.shrink_to_fit();
    // std::cout << tmp[130] << std::endl;
    // std::cout << tmp.size() << std::endl;

    // std::cout << tmp.at(5);
    // ft::vector<int>::reverse_iterator iter = tmp.rbegin();
    // ft::vector<int>::reverse_iterator iter1;

    // std::vector<int>::reverse_iterator iter2 = tmp1.rbegin() ;
    // std::cout << "ft: " << *iter << std::endl;
    // std::cout << "std: " << *iter2 << std::endl;

    // iter = tmp.rbegin();
    // iter1 = tmp.rend();

    // for(; iter != iter1 ; iter++){
    //   std::cout << *iter << std::endl;
    // }
}