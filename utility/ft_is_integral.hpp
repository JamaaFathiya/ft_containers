#include <type_traits>
#pragma once

namespace ft{
    template<class T>
    struct is_integral
    {
      typedef bool value_type;
      typedef std::integral_constant<bool, value> type;
    };
 
};