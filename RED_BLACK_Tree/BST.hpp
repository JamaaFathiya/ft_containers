#pragma once
#include <iostream>
#include <functional>
#include <memory>

namespace ft
{
    enum color{
        RED,
        BLACK
    };

    template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
    class BST
    {

    public:
        typedef T           value_type;
        typedef Compare     cmp;
        typedef size_t      size_type;

        struct node
        {
            value_type _data;
            node* _parent;
            node* _left_c;
            node* _right_c;
            color _color;
        };
        typedef std::allocator<node>   alloc_type;

        typedef node* node_ptr;
        typedef std::allocator<node> node_alloc;

    public:
        node_alloc  _alloc;
        node_ptr    _tree;
        node_ptr    _tnull;
        size_type   _size;


    public:

        BST() : _size(0) {
            std::allocator<int> alloc;
            this->_tnull = _alloc.allocate(1);
            _alloc.construct(this->_tnull, node());
            this->_tnull->_right_c = nullptr;
            this->_tnull->_left_c = nullptr;
            this->_tnull->_parent = nullptr;
            this->_tnull->_color = BLACK;

            this->_tree = this->_tnull;
        }


        node_ptr new_node(node_ptr node, value_type data = value_type())
        {
            node = _alloc.allocate(1);
//            _alloc.construct(node, data);
            node->_data = data;
            node->_parent = _tnull;
            node->_left_c = _tnull;
            node->_right_c = _tnull;
            node->_color = RED;

            return node;
        }

        void insert(value_type data, node_ptr& node){
            if (node == _tnull){ //if the tree is empty
                node = new_node(node, data);
            }
            else if(data > node->_data) {
                insert(data, node->_left_c);
                node->_left_c->_parent = node;
            }
            else if(data < node->_data){
                insert(data, node->_right_c);
                node->_right_c->_parent = node;
            }
        }

        node_ptr search(value_type data, node_ptr root){
            if (root != _tnull){
                if (root->_data == data)
                    return root;
                else if(data > root->_data)
                    return search(data, root->_right_c);
                else if(data < root->_data)
                    return search(data, root->_left_c);
            }
            return this->root;
        }

        void preorder_traverse(node_ptr root){
            if(root != _tnull){
                preorder_traverse(root->_left_c);
                std::cout << "data: "<< root->_data << std::endl;
                std::cout << "parent data " << root->_parent->_data << std::endl;
                std::cout << "color " << (root->_color == RED ? "RED": "BLACK") << std::endl;
                std::cout << "\n";
                preorder_traverse(root->_right_c);
            }
        }


    };
};