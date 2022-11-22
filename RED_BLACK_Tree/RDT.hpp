#pragma once
#include "BST.hpp"
#include <exception>
#include "../utility/ft_pair.hpp"
#include "../utility/ft_iterator_traits.hpp"


namespace ft {

    template <class T, class NodePtr>
    class tree_iter;

    template<class iter>
    struct rev_tree_iter;

    template<typename T, typename key_t , typename mapped_t, class Compare , class Allocator = std::allocator<T> >
    class RedBlackTree : public BST<T, Compare, Allocator> {

    public:
        typedef T                                   value_type;
        typedef key_t                               key_type;
        typedef mapped_t                            mapped_type;
        typedef BST<T, Compare, Allocator>          BST;
        typedef Compare                             cmp_func;
        typedef typename BST::node                  node;
        typedef typename BST::node_ptr              node_ptr;
        typedef typename BST::node_reference        node_reference;

        typedef tree_iter<T, node_ptr>              iter;
        typedef tree_iter<const T, node_ptr>        const_iter;
        typedef ft::rev_tree_iter<iter>             rev_iter;
        typedef ft::rev_tree_iter<const_iter>       const_rev_iter;


        RedBlackTree(const cmp_func& cmp): BST(cmp){}
        ~RedBlackTree() {}

        void LeftRotation(node_ptr pivot) {
            if (pivot == this->_tnull || pivot->_right_c == this->_tnull)
                return;

            node_ptr r_child = pivot->_right_c;

            pivot->_right_c = r_child->_left_c;
            if (r_child->_left_c != this->_tnull)
                r_child->_left_c->_parent = pivot;

            r_child->_parent = pivot->_parent;

            this->Transplant(pivot, r_child); //replace the pivot by the right-child

            r_child->_left_c = pivot;
            pivot->_parent = r_child;
        }

        void RightRotation(node_ptr pivot) {
            if (pivot == this->_tnull || pivot->_left_c == this->_tnull)
                return;
            node_ptr l_child = pivot->_left_c;

            pivot->_left_c = l_child->_right_c;
            if (l_child->_right_c != this->_tnull)
                l_child->_right_c->_parent = pivot;

            l_child->_parent = pivot->_parent;

            this->Transplant(pivot, l_child); // replace the pivot by the left-child

            l_child->_right_c = pivot;
            pivot->_parent = l_child;
        }

        void fix_insert(node_ptr node) {

            node_ptr uncle;
            node_ptr grandPa;

            while (node->_parent->_color == RED) {
                uncle = this->node_uncle(node);
                grandPa = this->grand_parent(node);

                if (uncle->_color == RED) {
                    uncle->_color = BLACK;
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;

                    node = grandPa;

                } else if (this->child_position(grandPa, node->_parent) == LEFT) { //parent is a left child

                    if (this->child_position(node->_parent, node) == RIGHT) { // node is right child
                        node = node->_parent; //move node to parent
                        LeftRotation(node); // left rotate the
                    }

                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    RightRotation(node->_parent->_parent);

                } else {

                    if (this->child_position(node->_parent, node) == LEFT) {
                        node = node->_parent;
                        RightRotation(node);
                    }

                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    LeftRotation(node->_parent->_parent);
                }
            }
            this->_root->_color = BLACK;
        }

        iter RBT_insert(value_type key) {
            node_ptr node = this->insert(key);

            if (node != this->_tnull)
                fix_insert(node);
            return iter(node);
        }

        void delete_elem(key_type data) {
            node_ptr found = this->search_node(data);
            if (found) {

                found->_prev->_next = found->_next;
                found->_next->_prev = found->_prev;
                color origin_color;
                node_ptr x;
                origin_color = found->_color;

                if (found->_left_c == this->_tnull) // if the node has only the right child we replace it by that child
                {
                    x = found->_right_c;
                    x->_parent = found->_parent;
                    this->Transplant(found, found->_right_c);
                } else if (found->_right_c == this->_tnull) // if the node has only the left child
                {
                    x = found->_left_c;
                    x->_parent = found->_parent;
                    this->Transplant(found, found->_left_c);
                } else {
                    node_ptr tmp = this->minimum(
                            found->_right_c); // if the node has both children we replace it by the min of the left subtree
                    origin_color = tmp->_color;

                    x = tmp->_right_c;
//                    if (x->_parent != this->_tnull)
//                        x->_parent = tmp->_parent;
                    if (tmp != found->_right_c) {
                        this->Transplant(tmp, tmp->_right_c);
                        tmp->_right_c = found->_right_c;
                        tmp->_right_c->_parent = tmp;
                        x->_parent = tmp->_parent; //remember
                    }
                    else
                        x->_parent = tmp;

                    this->Transplant(found, tmp);
                    tmp->_left_c = found->_left_c;
                    tmp->_left_c->_parent = tmp;

                    tmp->_color = found->_color;
                }
                if (origin_color == BLACK)
                    fix_delete(x);
            }
            this->_alloc.destroy(found);
            this->_alloc.deallocate(found, 1);
            found = nullptr;
            this->_tnull->_prev = this->maximum(this->_root);
            this->_size--;
        }

        void delete_elem_set(key_type data) {
            node_ptr found = this->search_node_set(data);
            if (found) {

                found->_prev->_next = found->_next;
                found->_next->_prev = found->_prev;
                color origin_color;
                node_ptr x;
                origin_color = found->_color;

                if (found->_left_c == this->_tnull) // if the node has only the right child we replace it by that child
                {
                    x = found->_right_c;
                    x->_parent = found->_parent;
                    this->Transplant(found, found->_right_c);
                } else if (found->_right_c == this->_tnull) // if the node has only the left child
                {
                    x = found->_left_c;
                    x->_parent = found->_parent;
                    this->Transplant(found, found->_left_c);
                } else {
                    node_ptr tmp = this->minimum(
                            found->_right_c); // if the node has both children we replace it by the min of the left subtree
                    origin_color = tmp->_color;

                    x = tmp->_right_c;
//                    if (x->_parent != this->_tnull)
//                        x->_parent = tmp->_parent;
                    if (tmp != found->_right_c) {
                        this->Transplant(tmp, tmp->_right_c);
                        tmp->_right_c = found->_right_c;
                        tmp->_right_c->_parent = tmp;
                        x->_parent = tmp->_parent; //remember
                    }
                    else
                        x->_parent = tmp;

                    this->Transplant(found, tmp);
                    tmp->_left_c = found->_left_c;
                    tmp->_left_c->_parent = tmp;

                    tmp->_color = found->_color;
                }
                if (origin_color == BLACK)
                    fix_delete(x);
            }
            this->_alloc.destroy(found);
            this->_alloc.deallocate(found, 1);
            found = nullptr;
            this->_tnull->_prev = this->maximum(this->_root);
            this->_size--;

        }

        void fix_delete(node_ptr x) {
            node_ptr w;
            while (x != this->_root && x->_color == BLACK) {

                if (x == x->_parent->_left_c) {
                    w = x->_parent->_right_c;

                    // case 1.
                    if (w->_color == RED) { //sibling is RED
                        w->_color = BLACK;
                        x->_parent->_color = RED;
                        LeftRotation(x->_parent);

                        w = x->_parent->_right_c; // the double black problem still exits which lead us to the other cases.
                    } // case 2
                    if (w->_color == BLACK && w->_left_c->_color == BLACK &&
                        w->_right_c->_color == BLACK) { //sibling and it's both children are BLACK
                        w->_color = RED;   // subtract RED from the right subtree and add it to the parent (if p is RED all good, else a new double black in the x.p)
                        x = x->_parent;
                    } else { // case 3.
                        if (w->_right_c->_color ==
                            BLACK) { // the close nephew is RED , we'll make it the root of the subtree with the color of the original root.
                            w->_left_c->_color = BLACK; // switch left color with parent
                            w->_color = RED; // ...
                            RightRotation(w); // right rotate so w.left become w
                            w = x->_parent->_right_c; //...
                        } // case 4.
                        w->_color = x->_parent->_color; // if the far nephew (both) are RED. set w color x.p 's color.
                        x->_parent->_color = BLACK; // make x.p color ,so it removes the double black problem
                        w->_right_c->_color = BLACK; // if the right child is RED => make it black , if not w already switched colors before with the left child, so we go back to the original color.
                        LeftRotation(x->_parent);
                        x = this->_root; // all good.
                    }
                } else if (x == x->_parent->_right_c) { // Mirror of the four cases above.
                    w = x->_parent->_left_c;
                    // case /1
                    if (w->_color == RED) {
                        w->_color = BLACK;
                        x->_parent->_color = RED;
                        RightRotation(x->_parent);

                        w = x->_parent->_left_c;
                    } // case /2
                    if (w->_color == BLACK && w->_left_c->_color == BLACK && w->_right_c->_color == BLACK) {
                        w->_color = RED;
                        x = x->_parent;
                    } else { // case /3
                        if (w->_left_c->_color == BLACK) {
                            w->_right_c->_color = BLACK;
                            w->_color = RED;
                            LeftRotation(w);
                            w = x->_parent->_left_c;
                        } // case /4
                        w->_color = x->_parent->_color;
                        x->_parent->_color = BLACK;
                        w->_left_c->_color = BLACK;
                        RightRotation(x->_parent);
                        x = this->_root;
                    }
                }
            }
            x->_color = BLACK;
        }

        node_ptr min() const{
            return this->minimum(this->_root);
        }

        node_ptr max() const{
            return this->maximum(this->_root);
        }

        size_t max_size() const{
            return this->p_alloc.max_size();
        }

        /*--------------- Serach functions ---------------------------*/

        mapped_type& search_key(const key_type& key) const {

            node_ptr root = this->_root;
            while (root && root != this->_tnull){
                if (root->_data->first == key)
                    return  root->_data->second;
                if (key > root->_data->first)
                    root = root->_right_c;
                else
                    root = root->_left_c;
            }
            throw std::out_of_range("key out of range");
        }

        mapped_type search_key_set(const key_type& key) const {

            node_ptr root = this->_root;
            while (root && root != this->_tnull){
                if (*(root->_data) == key)
                    return  *(root->_data);
                if (key > *(root->_data))
                    root = root->_right_c;
                else
                    root = root->_left_c;
            }
            throw std::out_of_range("key out of range");
        }

        iter search(const key_type& key) const {

            node_ptr root = this->_root;
            while (root && root != this->_tnull){
                if (root->_data->first == key)
                    return  iter(root);
                if (key > root->_data->first)
                    root = root->_right_c;
                else
                    root = root->_left_c;
            }
            return this->end();
        }

        iter search_set(const key_type& key) const {
            node_ptr root = this->_root;
            while (root && root != this->_tnull){
                if (*(root->_data) == key)
                    return  iter(root);
                if (key > *(root->_data))
                    root = root->_right_c;
                else
                    root = root->_left_c;
            }
            return this->end();
        }

        node_ptr search_node(const key_type& key) const {
            node_ptr root = this->_root;
            while (root && root != this->_tnull){
                if (root->_data->first == key)
                    return  root;
                if (key > root->_data->first)
                    root = root->_right_c;
                else
                    root = root->_left_c;
            }
            return this->_tnull;
        }

        node_ptr search_node_set(const key_type& key) const {

            node_ptr root = this->_root;
            while (root && root != this->_tnull){
                if (*root->_data == key)
                    return  root;
                if (key > *root->_data)
                    root = root->_right_c;
                else
                    root = root->_left_c;
            }
            return this->_tnull;
        }
        /*-------------------- Iterators --------------------------*/


       const tree_iter <T, node_ptr> begin() const{
            return iter(this->min());
        }

        const tree_iter <T, node_ptr> end() const{
            return iter(this->_tnull);
        }

        const tree_iter <const T, node_ptr> cbegin() const{
            return const_iter(this->min());
        }

        const tree_iter <const T,node_ptr> cend() const{
            return const_iter(this->_tnull);
        }

        const ft::rev_tree_iter<iter> rbegin() const{
            return rev_iter(this->end());
        }
        const ft::rev_tree_iter<iter> rend() const{
            return rev_iter(this->begin());
        }

        const ft::rev_tree_iter<const_iter> crbegin() const{
            return const_rev_iter(this->end());
        }
        const ft::rev_tree_iter<const_iter> crend() const{
            return const_rev_iter(this->begin());
        }

        /*---------------- Insert Range of Iterators -------------------*/

        template<class Iter>
        void insert_range(Iter begin, Iter end){
            for(; begin != end; begin++)
                this->RBT_insert(*begin);
        }

        template<class Iter>
        void delete_range(Iter begin, Iter end){
            Iter tmp = begin;
            while ( begin != end)
            {
                tmp++;
                this->delete_elem(begin->first);
                begin = tmp;
            }
        }

        template<class Iter>
        void delete_range_set(Iter begin, Iter end){
            Iter tmp = begin;
            while ( begin != end)
            {
                tmp++;
                this->delete_elem_set(*begin);
                begin = tmp;
            }
        }
        /*---------------------- Operators Overloads -------------------*/

        RedBlackTree& operator=(const RedBlackTree& other){

            this->clear(this->_root);
            this->_size = 0;
            this->_root = this->_tnull;
            this->insert_range(other.begin(), other.end());
            return *this;
        }

    };

    /*-------------------------- Tree iterator class --------------------------*/

    template <class T, class NodePtr>
    class tree_iter{

    public:
        typedef T                               value_type;
        typedef NodePtr                         pointer;
        typedef value_type&                     reference;
        typedef value_type*                     type_pointer;
        typedef ptrdiff_t                       difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;

    private:
        pointer _ptr;

    public:

        tree_iter(): _ptr(nullptr){}
        tree_iter(pointer ptr): _ptr(ptr){}


        tree_iter& operator=(const tree_iter<T, NodePtr>& iter){
            if (this != &iter)
                this->_ptr = iter._ptr;
            return *this;
        }

        //implicit conversion operator which converts the non-const version of your iterator to the const version.
        operator tree_iter<const value_type, NodePtr>() const{
            return tree_iter<const value_type, NodePtr>(_ptr);
        }

        tree_iter& operator++(){
            _ptr = _ptr->_next;
            return *this;
        }

        tree_iter& operator--(){
            _ptr = _ptr->_prev;
            return *this;
        }

        tree_iter operator++(int){
            tree_iter tmp(_ptr);
            _ptr = _ptr->_next;
            return tmp;
        }

        tree_iter operator--(int){
            tree_iter tmp(_ptr);
            _ptr = _ptr->_prev;
            return tmp;
        }
        reference  operator*(){
            return *(_ptr->_data);
        }

        type_pointer  operator->() const{
            return ((_ptr->_data));
        }

        pointer base() const{
            return this->_ptr;
        }

        bool operator!=(const tree_iter& it){
            return (this->_ptr != it._ptr);
        }

        bool operator==(const tree_iter& it){
            return (this->_ptr == it._ptr);
        }
    };

    template<class iter>
    struct rev_tree_iter {

    public:
        typedef iter                                                    iterator_type;
        typedef typename ft::iterator_traits<iter>::value_type          value_type;
        typedef typename ft::iterator_traits<iter>::difference_type     difference_type;
        typedef typename ft::iterator_traits<iter>::pointer             pointer;
        typedef typename ft::iterator_traits<iter>::reference           reference;
        typedef typename ft::iterator_traits<iter>::iterator_category   iterator_category;
        typedef typename iter::type_pointer                             type_pointer;

    private:
        iter _ptr;

    public:

        rev_tree_iter(iter ptr) : _ptr(ptr) {};

        rev_tree_iter() : _ptr(nullptr) {};

        rev_tree_iter &operator=(const rev_tree_iter<iter> &itr) {
            if (this != &itr)
                this->_ptr = itr._ptr;
            return *this;
        }

        rev_tree_iter &operator++() {
            --(this->_ptr);
            return *this;
        }

        rev_tree_iter operator++(int) {
            rev_tree_iter _tmp(this->_ptr);
            --(this->_ptr);
            return _tmp;
        }

        rev_tree_iter &operator--() {
            ++(this->_ptr);
            return *this;
        }

        rev_tree_iter operator--(int) {
            rev_tree_iter _tmp(this->_ptr);
            ++(this->_ptr);
            return _tmp;
        }

        reference operator*() const {
            iter tmp = _ptr;
            return (*(--tmp));
        }

        type_pointer operator->() const {
            iter tmp = _ptr;
            return ((--tmp).base())->_data;
        }

        bool operator!=(const rev_tree_iter& it){
            return (this->_ptr != it._ptr);
        }

        bool operator==(const rev_tree_iter& it){
            return (this->_ptr == it._ptr);
        }
    };

};
