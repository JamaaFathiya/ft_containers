#pragma once
#include "../RED_BLACK_Tree/RDT.hpp"
#include "../utility/ft_pair.hpp"
#include "../utility/ft_lexicographical_compare.hpp"

namespace ft {
    template<
            class Key,
            class T,
            class Compare = std::less<Key>,
            class Allocator = std::allocator<ft::pair<const Key, T> >
    >
    class map {
    public:
        typedef Key                                         key_type;
        typedef T                                           mapped_type;
        typedef ft::pair<const key_type, mapped_type>       value_type;
        typedef Compare                                     key_compare;
        typedef Allocator                                   allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;

    private:
        class value_compare : public std::binary_function<value_type, value_type, bool> {
        protected:
            key_compare comp;

        public:
            value_compare(key_compare c) : comp(c) {}

            bool operator()(const value_type &lhs, const value_type &rhs) const {
                return comp(lhs.first, rhs.first);
            }
        };

    public:
        typedef ft::RedBlackTree<value_type, key_type, mapped_type, value_compare, allocator_type>  _base;
        typedef value_compare                                                                       vc;
        typedef typename _base::iter                                                                iterator;
        typedef typename _base::const_iter                                                          const_iterator;
        typedef typename _base::rev_iter                                                            reverse_iterator;
        typedef typename _base::const_rev_iter                                                      const_reverse_iterator;

    private:
        _base           _tree;
        key_compare     _cmp;
        allocator_type  _alloc;

    public:

        /*--------------------- Constructors/Destructor ----------------------------*/

        explicit map(const key_compare &cmp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(
                vc(cmp)), _cmp(cmp), _alloc(alloc) {}

        template<class InputIt>
        map(InputIt first, InputIt last, const key_compare &comp = key_compare(),
            const Allocator &alloc = allocator_type()): _tree(vc(comp)) ,_cmp(comp), _alloc(alloc) {
            _tree.insert_range(first, last); //template
        }

        map(const map &other) : _tree(vc(other._cmp)), _cmp(other._cmp), _alloc(other._alloc) {
            this->_tree = other._tree;
        }

        ~map() {}

        /*----------------------------- Operators Overloads -------------------*/

        map &operator=(const map &other) {
            this->_cmp = other._cmp;
            this->_alloc = (other._alloc);
            this->_tree = other._tree;

            return *this;
        }

        allocator_type get_allocator() const {
            return this->_alloc;
        }

        /*----------------------- Iterators -------------------------*/

        iterator begin() const {
            return _tree.begin();
        }

        iterator end() const {
            return _tree.end();
        }

        const_iterator cbegin() const {
            return _tree.cbegin();
        }

        const_iterator cend() const {
            return _tree.cend();
        }

        reverse_iterator rbegin() const {
            return _tree.rbegin();
        }

        reverse_iterator rend() const {
            return  _tree.rend();
        }

        const_reverse_iterator crbegin() const {
            return _tree.crbegin();
        }

        const_reverse_iterator crend() const {
            return _tree.crend();
        }

        /*------------------------- Element Access ---------------------*/

        mapped_type &at(const key_type &key) {
            return (_tree.search_key(key));
        }

        const mapped_type &at(const Key &key) const {
            return (_tree.search_key(key));
        }

        mapped_type &operator[](const Key &key) {
            iterator tmp = find(key);
            if (tmp != end())
                return (tmp->second);
            ft::pair<iterator, bool> n = insert(ft::make_pair(key, mapped_type()));
            return n.first->second;
        }

        /*---------------------- Capacity -------------------------*/

        bool empty() const {
            return _tree.size() == 0 ? true : false;
        }

        size_type size() const {
            return _tree.size();
        }

        size_type max_size() const {
//            return _tree.max_size();
                return 288230376151711743;
        }

        /*------------------- Lookup ----------------------*/

        size_type count(const Key &key) const {
            try {
                _tree.search_key(key);
            }
            catch (std::exception) {
                return 0;
            }
            return 1;
        }

        iterator find(const Key &key) {
            return _tree.search(key);
        }

        const_iterator find(const Key &key) const {
            return _tree.search(key);
        }

        ft::pair<iterator, iterator> equal_range(const Key &key) {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        iterator lower_bound(const Key &key) {
            iterator it = _tree.begin();
            for (; it != _tree.end(); it++) {
                if (it->first >= key)
                    return it;
            }
            return _tree.end();
        }

        const_iterator lower_bound(const Key &key) const {
            iterator it = _tree.begin();
            for (; it != _tree.end(); it++) {
                if (it->first >= key)
                    return it;
            }
            return _tree.end();
        }

        iterator upper_bound(const Key &key) {
            iterator it = _tree.begin();
            for (; it != _tree.end(); it++) {
                if (it->first > key)
                    return it;
            }
            return _tree.end();
        }

        const_iterator upper_bound(const Key &key) const {
            iterator it = _tree.begin();
            for (; it != _tree.end(); it++) {
                if (it->first > key)
                    return it;
            }
            return _tree.end();
        }

        /*------------------- Lookup ----------------------*/

        key_compare key_comp() const {
            return this->_cmp;
        }

        value_compare value_comp() const {
            return value_compare(_cmp);
        }

        /*------------------ Modifiers --------------------*/

        void clear(){
            erase(begin(), end());
        }

        ft::pair<iterator, bool> insert( const value_type& value ){
            iterator tmp = _tree.search(value.first);
            if (tmp == _tree.end())
                return  ft::make_pair(_tree.RBT_insert(value), true);
            return ft::make_pair(tmp, false);
        }

        iterator insert (iterator position, const value_type& val){

            iterator it = find(val.first);
            if (it == end()){
               _tree.RBT_insert(val);
                return position;
            }
            return it;
        }

        template< class InputIt >
        void insert( InputIt first, InputIt last ){
            _tree.template insert_range(first, last);
        }

        void erase( iterator pos ){
            _tree.delete_elem(pos->first);
        }

        size_type erase (const key_type& k){
            if (find(k) != end()){
                _tree.delete_elem(k);
                return 1;
            }
            return 0;
        }

        void erase (iterator first, iterator last){
            _tree.delete_range(first, last);
        }

        void swap (map& x){
            map tmp(x);

            x = *this;
            *this = tmp;
        }
    };


    template< class Key, class T, class Compare, class Alloc >
    bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        if (lhs.size() == rhs.size()){
            typename ft::map<Key, T, Compare, Alloc>::iterator it = lhs.begin();
            typename ft::map<Key, T, Compare, Alloc>::iterator it1 = rhs.begin();
            for(; it != lhs.end(), it1 != rhs.end(); it++ , it1++)
            {
                if (*it != *it1)
                    return false;
            }

        }else
            return false;
        return true;
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
        return (!(lhs == rhs));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
        return ft::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
        return rhs < lhs;
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
        return !(lhs<rhs);
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs){
        return !(rhs<lhs);
    }

};