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

    void LeftRotation(node_ptr pivot) {
        if (pivot == this->_tnull || pivot->_right_c == this->_tnull)
            return;
//        node_ptr node = pivot;
        node_ptr r_child = pivot->_right_c;

        pivot->_right_c = r_child->_left_c;
        if (r_child->_left_c != this->_tnull)
            r_child->_left_c->_parent = pivot;

        r_child->_parent = pivot->_parent;

        if (pivot->_parent == this->_tnull)
            this->_root = r_child;
        else if (this->child_position(pivot->_parent, pivot) == LEFT)
            pivot->_parent->_left_c = r_child;
        else
            pivot->_parent->_right_c = r_child;
        r_child->_left_c = pivot;
        pivot->_parent = r_child;
    }

    void RightRotation(node_ptr pivot){
        if ( pivot == this->_tnull || pivot->_left_c == this->_tnull)
            return;

//        node_ptr node = pivot;
        node_ptr l_child = pivot->_left_c;

        pivot->_left_c = l_child->_right_c;
        if (l_child->_right_c != this->_tnull)
            l_child->_right_c->_parent = pivot;

        l_child->_parent = pivot->_parent;

        if (pivot->_parent == this->_tnull)
            this->_root = l_child;
        else if (this->child_position(pivot->_parent, pivot) == LEFT)
            pivot->_parent->_left_c = l_child;
        else
            pivot->_parent->_right_c = l_child;

        l_child->_right_c = pivot;
        pivot->_parent = l_child;
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

    void fix_insert(node_ptr node) {
        while (node->_parent->_color == RED) {
            node_ptr uncle;

            if (node->_parent == node->_parent->_parent->_left_c){
                uncle = node->_parent->_parent->_right_c;

                if (uncle->_color == RED){
                    uncle->_color = BLACK;
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;

                    node = node->_parent->_parent;
                } else {
                    if (node == node->_parent->_right_c){
                        node = node->_parent;
                        LeftRotation(node);
                    }
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    RightRotation(node->_parent->_parent);
                }
            } else{
                uncle = node->_parent->_parent->_left_c;

                 if (uncle->_color == RED){
                    uncle->_color = BLACK;
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;

                    node = node->_parent->_parent;
                } else {
                   if (node == node->_parent->_left_c){
                       node = node->_parent;
                       RightRotation(node);
                   }
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    LeftRotation(node->_parent->_parent);
                }
            }
//            if (node == this->_root)
//                break;
        }
        this->_root->_color = BLACK;
    }

    void rdt_insert(value_type key){
       node_ptr  node = this->insert(key);

        if (node != this->_tnull)
            fix_insert(node);
    }


    node_ptr& root_ref(){
        return this->_root;
    }
};
};
