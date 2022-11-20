#include "ft_stack/ft_stack.hpp"
#include "ft_vector/ft_vector.hpp"
#include <vector>
#include <iostream>
#include <type_traits>
# include "tester/tester.hpp"
#include <stack>

bool printBoolResult(std::fstream& fs, bool stl_bool, bool ft_bool)
{
    fs << "\nBool result : \n";
    fs << " - STL : " << (stl_bool ? "true" : "false") << std::endl;
    fs << " - FT  : " << (ft_bool ? "true" : "false") << std::endl;

    return (stl_bool == ft_bool);
}


//int main()
//{
//    test_vector();
//    std::cout << "\n";
//    // test_list();
//    // std::cout << "\n";
//    // test_map();
//    // std::cout << "\n";
//    // test_deque();
//    // std::cout << "\n";
//    test_stack();
//    std::cout << "\n";
//    // test_queue();
//}

//int main(){
//    int range_array[] = {47, 152, -325, 9, 14444};
//
////     std::vector<int>::iterator range_array(&(range_array[0]));
//    ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));
//
//    std::vector<int> stl_insert(4);
//    ft::vector<int> ft_insert(4);
//
//    std::allocator<int> alloc;
//    int *tmp = stl_insert.data() + stl_insert.size() + 1;
//    alloc.construct(tmp, int());
////    tmp = alloc.allocate(3);
//
//    std::cout << tmp << std::endl;
//    std::cout << stl_insert.data() + stl_insert.size() + 1 << std::endl;
//    for( std::vector<int>::iterator it = stl_insert.begin(); it < stl_insert.end(); it++)
//        std::cout << *it << std::endl;
//    std::cout << "size " << stl_insert.size() << std::endl;
//    stl_insert.insert(stl_insert.begin() - 5, range_array, range_array + 5);
////    ft_insert.insert(ft_insert.end() + 1, ft_iterator_beg, ft_iterator_beg + 5);
//    std::cout << "size " << stl_insert.size() << std::endl;
//    std::cout << "capacity " << stl_insert.capacity() << std::endl;
//
//    for( std::vector<int>::iterator it = stl_insert.begin(); it != stl_insert.end(); it++)
//        std::cout << *it << std::endl;
////    std::cout << ft_insert[2] << "\n" << std::endl;
//
//    return 0;
//}
//
#include "RED_BLACK_Tree/RDT.hpp"
#include "utility/ft_pair.hpp"
#include "ft_map/ft_map.hpp"


int main() {

    std::map<int, int> s;
    s.insert(std::pair<int,int>(1,2));
    s.insert(std::pair<int,int>(2,2));
    s.insert(std::pair<int,int>(3,2));
    s.insert(std::pair<int,int>(4,2));
    s.insert(std::pair<int,int>(5,2));

    ft::map<int, int> m;


    m.insert(ft::pair<int,int>(1,2));
    m.insert(ft::pair<int,int>(2,2));
    m.insert(ft::pair<int,int>(3,2));

    m.insert(ft::pair<int,int>(4,2));

    m.insert(ft::pair<int,int>(5,2));

//    ft::map<int, int> n(m);
//    n = m;
//
    ft::map<int, int>::const_iterator  it;
//    it = m.rbegin();
////    it++;
//for(; it != m.rend(); it++)
//    std::cout << (*it).first << std::endl;

//    std::cout << m[1] << std::endl;
//    it = (m.lower_bound(1));

    ft::pair<ft::map<int, int>::const_iterator, ft::map<int, int>::const_iterator>  p = m.equal_range(3);
    std::cout << (p.first)->first << std::endl;

    return 0;
}