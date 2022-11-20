#pragma once

#include "../RED_BLACK_Tree/RDT.hpp"

namespace ft{

    template<class T,class Node, class Compare, class Allocator>
    class tree_iter{
    public:
        typedef T* pointer;
        typedef T& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

    private:
        pointer _ptr;

        tree_iter(){
            _ptr(nullptr);
        }

        tree_iter(T* ptr): _ptr(ptr){}

        tree_iter& operator++(){
            this->_ptr = ft::RedBlackTree<T,Compare, Allocator>::successor(_ptr);
            return *this;
        }

        reference operator*() const{
            return *(_ptr->data);
        }
    };
};