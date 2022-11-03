#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <__tree>
#include <map>

namespace ft
{
    enum color{
        RED,
        BLACK
    };

    enum _child{
        LEFT,
        RIGHT,
        NONE
    };
#define COUNT 10

    template<typename T, class Compare = std::less<T> >
    class BST
    {

    public:
        typedef T           value_type;
        typedef size_t      size_type;


        struct _node
        {
            value_type _data;
            _node* _parent;
            _node* _left_c;
            _node* _right_c;
            color _color;
        };

        typedef std::allocator<_node>   alloc_type;

        typedef _node* node_ptr;
        typedef Compare compare_func;

    public:
        alloc_type      _alloc;
        compare_func    _cmp;
        node_ptr        _root;
        node_ptr        _tnull;
        size_type       _size;


    public:

        BST() : _size(0) {
            this->_tnull = _alloc.allocate(1);
            _alloc.construct(this->_tnull, _node());
            this->_tnull->_right_c = nullptr;
            this->_tnull->_left_c = nullptr;
            this->_tnull->_parent = nullptr;
            this->_tnull->_color = BLACK;

            this->_root = this->_tnull;
        }


        node_ptr new_node(value_type data = value_type())
        {
            node_ptr node = _alloc.allocate(1);
            _alloc.construct(node, _node());
            node->_data = data;
            node->_parent = _tnull;
            node->_left_c = _tnull;
            node->_right_c = _tnull;
            node->_color = RED;

            return node;
        }

//        void insert(value_type data, node_ptr& node){
//            if (node == _tnull){ //if the tree is empty
//                node = new_node(node, data);
//            }
//            else if(_cmp(node->_data, data)) {
//                insert(data, node->_right_c);
//                node->_right_c->_parent = node;
//            }
//            else if(_cmp(data, node->_data)){
//                insert(data, node->_left_c);
//                node->_left_c->_parent = node;
//            }
//        }
        void insert(value_type data) {
            node_ptr tmp = this->_root;
            node_ptr insert_in = _tnull;

            while (tmp != _tnull){
                insert_in = tmp;
                if (_cmp(data, tmp->_data))
                    tmp = tmp->_left_c;
                else if (_cmp(tmp->_data, data))
                    tmp = tmp->_right_c;
                else
                    return;
            }

            tmp = new_node(data);
            tmp->_parent = insert_in;
            if (insert_in == _tnull)
                this->_root = tmp;
            else if (_cmp(data,insert_in->_data))
                insert_in->_left_c = tmp;
            else
                insert_in->_right_c = tmp;

            this->_size++;
        }

        void delete_elem(value_type data) {
            node_ptr found = search(data, this->_root);
            node_ptr node_to_delete = found;
            if (found)
            {
                if (is_leaf(found)){
                    (child_position(found->_parent, found) == LEFT ? found->_parent->_left_c = _tnull : found->_parent->_right_c = _tnull);
                } else if (found->_right_c != _tnull && found->_left_c != _tnull){
                    node_ptr tmp = maximum(found->_left_c);
                    found->_data = tmp->_data;
                 //if the maximum have a chile it's certain that it's a left_child
                    tmp->_parent->_right_c = tmp->_left_c;
                    tmp->_left_c->_parent = (tmp->_left_c != _tnull) ? tmp->_parent : nullptr;

                    node_to_delete = tmp;
                } else{
                    node_ptr tmp = found;
                    node_ptr root_child = (found->_left_c ? found->_left_c : found->_right_c);
                    root_child->_parent = found->_parent;
                    found = root_child;
                    node_to_delete = tmp;

                }
                _alloc.destroy(node_to_delete);
                _alloc.deallocate(node_to_delete, 1);
                this->_size--;
            }
        }

        _child child_position(node_ptr parent, node_ptr child) {
            if (!parent || !child || parent == _tnull || child == _tnull)
                return NONE;
            if (parent->_left_c == child)
                return LEFT;
            else if (parent->_right_c == child)
                return RIGHT;
            return NONE;
        }

        bool is_leaf(node_ptr node) {
            return (node->_right_c == _tnull) && (node->_left_c == _tnull);
        }

        node_ptr search(value_type data, node_ptr root) {
            while (root && root != _tnull){
                if (root->_data == data)
                    return  root;
                if (data > root->_data)
                    root = root->_right_c;
                else
                    root = root->_left_c;
            }
//            throw std::exception();
            return nullptr;
        }

        void inorder_traverse(node_ptr root) {
            if(root != nullptr && root != _tnull){
                inorder_traverse(root->_left_c);
                std::cout << "data: "<< root->_data << std::endl;
                std::cout << "parent data " << root->_parent->_data << std::endl;
                std::cout << "color " << (root->_color == RED ? "RED": "BLACK") << std::endl;
                std::cout << "\n";
                inorder_traverse(root->_right_c);
            }
        }

        void clear(node_ptr& root) {
            if (root == _tnull)
                return;
            clear(root->_right_c);
            clear(root->_left_c);
            _alloc.destroy(root);
            _alloc.deallocate(root, 1);
            root  = nullptr;
        }

        void clear_tree(node_ptr& root) {
            clear(root);
            _alloc.destroy(_tnull);
            _alloc.deallocate(_tnull, 1);
            _tnull = nullptr;
        }

        node_ptr maximum(node_ptr node) { //max
            while (node && node != _tnull && node->_right_c != _tnull)
                node = node->_right_c;
            return  node;
        }

        node_ptr successor(node_ptr node) {
            if (node->_right_c != _tnull)
                return minimum(node->_right_c);
            else{
                node_ptr p = node->_parent;
                while (p != _tnull && node == p->_right_c){// searching until the node is a left child or the parent is tnull
                    node = p;
                    p = p->_parent;
                }
                return p;
            }
        }

        node_ptr minimum(node_ptr node) {//min
            while (node && node != _tnull && node->_left_c != _tnull)
                node = node->_left_c;
            return  node;
        }

        node_ptr predecessor(node_ptr node) {
            if (node->_left_c != _tnull)
                return maximum(node->_left_c);
            else{
                node_ptr p = node->_parent;
                while (p != _tnull && node == p->_left_c){
                    node = p;
                    p = p->_parent;
                }
                return p;
            }
        }

        node_ptr grand_parent(node_ptr node) {
            if (node && node->_parent && node->_parent->_parent)
                return node->_parent->_parent;
            return _tnull;
        }

        node_ptr node_uncle(node_ptr node) {
            node_ptr grand_pa = grand_parent(node);
            if (grand_pa != _tnull)
                return (child_position(grand_pa, node->_parent) == LEFT ? grand_pa->_right_c : grand_pa->_left_c );
            return _tnull;
        }

        void print2DUtil(node_ptr root, int space)
        {
            // Base case
            if (root == NULL)
                return;

            // Increase distance between levels
            space += COUNT;

            // Process right child first
            print2DUtil(root->_right_c, space);

            // Print current node after space
            // count
            std::cout << std::endl;
            for (int i = COUNT; i < space; i++)
                std::cout << " ";
            std::cout << root->_data << "\n";

            // Process left child
            print2DUtil(root->_left_c, space);
        }

// Wrapper over print2DUtil()
        void print2D(node_ptr root)
        {
            // Pass initial space count as 0
            print2DUtil(root, 0);
        }
    };
};