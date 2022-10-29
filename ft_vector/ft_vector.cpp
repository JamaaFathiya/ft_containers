#include "ft_vector.hpp"
#include <vector>
#include <iostream>
#include <type_traits>
// #include <iterator>

typedef std::string t;
int main(){


  std::vector<t> tmp1;
  ft::vector<t> tmp;

    tmp1.push_back("12");
    tmp1.push_back("13");
    tmp1.push_back("14");
    tmp1.push_back("4");
    tmp1.push_back("5");
    tmp1.push_back("6");

    tmp.push_back("12");
    tmp.push_back("13");
    tmp.push_back("14");
    tmp.push_back("4");
    tmp.push_back("5");
    tmp.push_back("6");

  tmp1.clear();
  tmp.clear();

  std::cout << "size1 = " << tmp1.size() << std::endl;
    std::cout << "capacity1 = " << tmp1.capacity() << std::endl;
  std::cout << "size = " << tmp.size() << std::endl;
    std::cout << "capacity = " << tmp.capacity() << std::endl;
  
  std::cout << "tmp1" << std::endl;
  std::vector<t>::iterator i = tmp1.begin();
  std::vector<t>::iterator j = tmp1.end();
    for (; i != j ; i++)
      std::cout << *i << std::endl;

 std::cout << "tmp" << std::endl;
  ft::vector<t>::iterator k = tmp.begin();
  ft::vector<t>::iterator l = tmp.end();
    for (; k != l ; k++)
      std::cout << *k << std::endl;

}