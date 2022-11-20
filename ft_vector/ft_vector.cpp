#include "ft_vector.hpp"
#include <vector>

int main(){
    int range_array[] = {47, 152, -325, 9, 14444};

//     std::vector<int>::iterator range_array(&(range_array[0]));
    ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

    std::vector<int> stl_insert(4);
    ft::vector<int> ft_insert(4);

//    stl_insert.insert(stl_insert.begin() ,range_arrayge_array , range_array + 2);

    ft_insert.insert(ft_insert.begin(), ft_iterator_beg + 2, ft_iterator_beg);
        for( ft::vector<int>::iterator it = ft_insert.begin(); it < ft_insert.end(); it++)
        std::cout << *it << std::endl;


    return 0;
}