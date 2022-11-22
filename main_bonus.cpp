//
// Created by Fathiyat olatokunbo Jamia on 11/22/22.
//
#include <iostream>
# include "tester/tester.hpp"

bool printBoolResult(std::fstream& fs, bool stl_bool, bool ft_bool)
{
    fs << "\nBool result : \n";
    fs << " - STL : " << (stl_bool ? "true" : "false") << std::endl;
    fs << " - FT  : " << (ft_bool ? "true" : "false") << std::endl;

    return (stl_bool == ft_bool);
}


int main()
{
    test_set();
}
