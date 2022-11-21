#pragma once

#include "../RED_BLACK_Tree/RDT.hpp"
#include "../utility/ft_pair.hpp"
#include "../utility/ft_lexicographical_compare.hpp"
#include <set>
namespace ft{
    template<
            class Key,
            class Compare = std::less<Key>,
            class Allocator = std::allocator<Key>
    > class set{
    public:
        typedef Key                                         key_type;
        typedef Key                                         value_type;
        typedef Compare                                     key_compare;
        typedef Allocator                                   allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;


    public:
        typedef ft::RedBlackTree<value_type, key_type, value_type , key_compare, allocator_type> _base;
        typedef typename _base::iter iterator;
        typedef typename _base::const_iter const_iterator;
        typedef typename _base::rev_iter reverse_iterator;
        typedef typename _base::const_rev_iter const_reverse_iterator;

    private:
        _base _tree;
        key_compare _cmp;
        allocator_type _alloc;

    public:
        /*--------------------- Constructors/Destructor ----------------------------*/

        explicit set(const key_compare &cmp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(cmp), _cmp(cmp), _alloc(alloc) {}

        template<class InputIt>
        set(InputIt first, InputIt last, const key_compare &comp = key_compare(),
        const Allocator &alloc = allocator_type()): _tree(comp) {
            _alloc = alloc;
            _cmp = comp;
            _tree.template insert_range(first, last);
        }

        set(const set &other) : _tree(other._cmp) {
            this->_tree = other._tree;
        }

        ~set() {}

        /*----------------------------- Operators Overloads -------------------*/

        set &operator=(const set &other) {
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

        void insert(value_type n) {
            _tree.insert(n);
        }

        /*------------------------- Element Access ---------------------*/

        value_type &operator[](const Key &key) {
            return (_tree.search_key(key));
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
            return 576460752303423487;
        }

        /*------------------- Lookup ----------------------*/

        size_type count(const Key &key) const {
            try {
                _tree.search_key_set(key);
            }
            catch (std::exception) {
                return 0;
            }
            return 1;
        }

        iterator find(const key_type &key) {
            return _tree.search_set(key);
        }

        const_iterator find(const key_type &key) const {
            return _tree.search_set(key);
        }

        ft::pair<iterator, iterator> equal_range(const Key &key) {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

//
        iterator lower_bound(const Key &key) {
            iterator it = _tree.begin();
            for (; it != _tree.end(); it++) {
                if (*it >= key)
                    return it;
            }
            return _tree.end();
        }

//
        const_iterator lower_bound(const Key &key) const {
            iterator it = _tree.begin();
            for (; it != _tree.end(); it++) {
                if (*it >= key)
                    return it;
            }
            return _tree.end();
        }

        iterator upper_bound(const Key &key) {
            iterator it = _tree.begin();
            for (; it != _tree.end(); it++) {
                if (*it > key)
                    return it;
            }
            return _tree.end();
        }

        const_iterator upper_bound(const Key &key) const {
            iterator it = _tree.begin();
            for (; it != _tree.end(); it++) {
                if (*it > key)
                    return it;
            }
            return _tree.end();
        }

        /*------------------- Lookup ----------------------*/
        key_compare key_comp() const {
            return this->_cmp;
        }

        key_compare value_comp() const {
            return _cmp;
        }

    };

    template< class Key, class Compare, class Alloc >
    bool operator==( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
    {
        if (lhs.size() == rhs.size()){
            typename ft::set<Key, Compare, Alloc>::iterator it = lhs.begin();
            typename ft::set<Key, Compare, Alloc>::iterator it1 = rhs.begin();
            for(; it != lhs.end(), it1 != rhs.end(); it++ , it1++)
            {
                if (*it != *it1)
                    return false;
            }

        }else
            return false;
        return true;
    }

    template< class Key, class Compare, class Alloc >
    bool operator!=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs ){
        return (!(lhs == rhs));
    }

    template< class Key, class Compare, class Alloc >
    bool operator<( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs ){
        return ft::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
    }

    template< class Key, class Compare, class Alloc >
    bool operator>( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs ){
        return rhs < lhs;
    }

    template< class Key, class Compare, class Alloc >
    bool operator<=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs ){
        return !(lhs<rhs);
    }

    template< class Key, class Compare, class Alloc >
    bool operator>=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs){
        return !(rhs<lhs);
    }

};