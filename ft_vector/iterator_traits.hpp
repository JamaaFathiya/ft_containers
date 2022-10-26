#include <iostream>
#include <cstddef> // for ptrdiff_t

//Why using iterators?
/* the STL is made so that the containers are separated than the algorithms, why again if it's not that way then every container
needs it's own algoirthms (too much repitition), so iterators act as a bridgs that connects algorithms to STL contianer classes 
this way one algorithm can work for many containers*/
//this iterator_traits is the class that provides uniform interface to the properties of iterator types.
namespace ft{

    template<class Iterator> struct iterator_traits {
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;
    };
    
    template<class T> struct iterator_traits<T*> {
        typedef ptrdiff_t                   difference_type; //for pointer arithmetic and array indexing. it's used When working with the C++ container library, the proper type for the difference between iterators
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef std::random_access_iterator_tag  iterator_category;
    };
    
    template<class T> struct iterator_traits<const T*> {
        typedef ptrdiff_t                   difference_type;
        typedef T                           value_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
        typedef std::random_access_iterator_tag  iterator_category;
    };
}