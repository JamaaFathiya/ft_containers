#pragma once

#include <iostream>
namespace ft{
 
template <typename T>
struct is_integral
{
  static const bool value;
};

template <typename T>
const bool is_integral<T>::value = std::numeric_limits<T>::is_integer; 
//The value of std::numeric_limits<T>::is_integer is true for all integer arithmetic types T and false otherwise.
};