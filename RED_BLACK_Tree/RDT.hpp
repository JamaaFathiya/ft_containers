#pragma once
#include "BST.hpp"
#include <map>

namespace ft{


template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
class RedBlackTree : public BST<T, Compare, Allocator>{

    typedef T                                                   value_type;
    typedef  BST<T,Compare, Allocator>                          RBT;
    typedef  typename BST<T,Compare, Allocator>::node_ptr       node_ptr;
    typedef  typename BST<T,Compare, Allocator>::node_reference node_reference;

public:
    RedBlackTree(): BST<T, Compare, Allocator>::BST() {}
    ~RedBlackTree()  { this->clear_tree(); };

    void LeftRotation(node_ptr& node){
        node_ptr pivot   = node;
        node_ptr r_child = node->_right_c;

        pivot->_right_c = r_child->_left_c;
        r_child->_left_c->_parent = pivot;

        r_child->_left_c = pivot;
        r_child->_parent = pivot->_parent;
        pivot->_parent = r_child;

        node = r_child;
    }

    void RightRotation(node_ptr& node){

        node_ptr pivot   = node;
        node_ptr l_child = node->_left_c;

        pivot->_left_c = l_child->_right_c;
        l_child->_right_c->_parent = pivot;

        l_child->_right_c = pivot;
        l_child->_parent = pivot->_parent;
        pivot->_parent = l_child;

        node = l_child;
    }

    void RightLeftRotation(node_ptr& node){
        if (node != this->_tnull)
        {
            this->RightRotation(node->_right_c);
            this->LeftRotation(node);
        }
    }

    void LeftRightRotation(node_ptr& node){
        if (node != this->_tnull)
        {
            this->LeftRotation(node->_left_c);
            this->RightRotation(node);
        }
    }

//    void Recolor(node_ptr& node){
//
//    }

    void rdt_insert(value_type key){
       node_ptr  node = this->insert(key);

        if (node){
            ;
        }
    }


    node_ptr& root_ref(){
        return this->_root;
    }
};
};
