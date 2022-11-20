#pragma once

#include <iostream>
#include "ft_iterator_traits.hpp"
#include <iterator>

namespace ft{

template<class T>
struct iterator
{
public:
   typedef T iterator_type;
   typedef typename ft::iterator_traits<T *>::value_type value_type;
   typedef typename ft::iterator_traits<T *>::difference_type difference_type;
   typedef typename ft::iterator_traits<T *>::pointer pointer;
   typedef typename ft::iterator_traits<T *>::reference reference;
   typedef typename ft::iterator_traits<T *>::iterator_category iterator_category;

   private:
        pointer _ptr;

   public: 
        
        iterator(pointer ptr) : _ptr(ptr){};
        iterator() :_ptr(nullptr){};

        iterator& operator=(const iterator<T>& iter){
                if (this != &iter)
                        this->_ptr = iter._ptr;
                return *this;
        }

        iterator& operator++(){
                ++(this->_ptr);
                return *this;
        }

        iterator operator++(int){
                iterator _tmp(this->_ptr);
                ++(this->_ptr);
                return _tmp;
        }

        iterator& operator--(){
                --(this->_ptr);
                return *this;
        }

        iterator operator--(int){
                iterator _tmp(this->_ptr);
                --(this->_ptr);
                return _tmp;
        }

        reference operator*() const{
                return *(_ptr);
        }

        iterator operator+ (difference_type __n) const{
                iterator _tmp(this->_ptr);
                _tmp += __n;
                return _tmp;

        }
        iterator & operator+=(difference_type __n){
                _ptr += __n;
                return *this;
        }

        iterator operator-(difference_type __n) const{
                iterator _tmp(this->_ptr);
                _tmp -= __n;
                return _tmp;

        }
        iterator & operator-=(difference_type __n){
                _ptr -= __n;
                return *this;
        }
        difference_type operator-(const iterator<T>& iter){
            return this->_ptr - iter._ptr;
        }

        reference    operator[](difference_type __n) const{
                return _ptr[__n];
        }

         pointer  operator->() const{
                return &(*_ptr);
         }

         iterator_type base() const{
                return _ptr;
         }
 
        bool operator!=(const iterator& it){
                return (this->_ptr != it._ptr);
        }

        bool operator==(const iterator& it){
                return (this->_ptr == it._ptr);
        }
        
        bool operator<(const iterator& it){
                return (this->_ptr < it._ptr);
        }

        bool operator>(const iterator& it){
                return (this->_ptr > it._ptr);
        }

        bool operator<=(const iterator& it){
                return (this->_ptr <= it._ptr);
        }

        bool operator>=(const iterator& it){
                return (this->_ptr >= it._ptr);
        }
};


/*------------------------------------------------------------------------------*/
                                /*CONST ITERATOR*/
/*------------------------------------------------------------------------------*/

template<class T>
struct const_iterator
{
public:
   typedef const T iterator_type;
   typedef typename ft::iterator_traits<const T*>::value_type value_type;
   typedef typename ft::iterator_traits<const T*>::difference_type difference_type;
   typedef typename ft::iterator_traits<const T*>::pointer pointer;
   typedef typename ft::iterator_traits<const T*>::reference reference;
   typedef typename ft::iterator_traits<const T*>::iterator_category iterator_category;

   private:
        pointer _ptr;

   public: 
        
        const_iterator(pointer ptr) : _ptr(ptr){};
        const_iterator() :_ptr(nullptr){};

        const_iterator& operator=(const const_iterator<T>& iter){
                if (this != &iter)
                        this->_ptr = iter._ptr;
                return *this;
        }

        const_iterator& operator++(){
                ++(this->_ptr);
                return *this;
        }

        const_iterator operator++(int){
                const_iterator _tmp(this->_ptr);
                ++(this->_ptr);
                return _tmp;
        }

        const_iterator& operator--(){
                --(this->_ptr);
                return *this;
        }

        const_iterator operator--(int){
                const_iterator _tmp(this->_ptr);
                --(this->_ptr);
                return _tmp;
        }

        reference operator*() const{
                return *(_ptr);
        }

        const_iterator operator+ (difference_type __n) const{
                const_iterator _tmp(this->_ptr);
                _tmp += __n;
                return _tmp;

        }
        const_iterator & operator+=(difference_type __n){
                _ptr += __n;
                return *this;
        }

        const_iterator operator-(difference_type __n) const{
                const_iterator _tmp(this->_ptr);
                _tmp -= __n;
                return _tmp;

        }
        const_iterator & operator-=(difference_type __n){
                _ptr -= __n;
                return *this;
        }

        difference_type operator-(const const_iterator<T>& iter){
            return this->_ptr - iter._ptr;
        }

        reference    operator[](difference_type __n) const{
                return _ptr[__n];
        }

        pointer  operator->() const{
                return &(*_ptr);
         }

        iterator_type base() const{
                return _ptr;
         }
 
        bool operator!=(const const_iterator& it){
                return (this->_ptr != it._ptr);
        }

        bool operator==(const const_iterator& it){
                return (this->_ptr == it._ptr);
        }
        
        bool operator<(const const_iterator& it){
                return (this->_ptr < it._ptr);
        }

        bool operator>(const const_iterator& it){
                return (this->_ptr > it._ptr);
        }

        bool operator<=(const const_iterator& it){
                return (this->_ptr <= it._ptr);
        }

        bool operator>=(const const_iterator& it){
                return (this->_ptr >= it._ptr);
        }
};
/*------------------------------------------------------------------------------*/
                                /*REVERSE ITERATOR*/
/*------------------------------------------------------------------------------*/

template<class iter>
struct reverse_iterator
{

public:
   typedef iter iterator_type;
   typedef typename ft::iterator_traits<iter>::value_type value_type;
   typedef typename ft::iterator_traits<iter>::difference_type difference_type;
   typedef typename ft::iterator_traits<iter>::pointer pointer;
   typedef typename ft::iterator_traits<iter>::reference reference;
   typedef typename ft::iterator_traits<iter>::iterator_category iterator_category;

   private:
        iter _ptr;

   public: 
        
        reverse_iterator(iter ptr) : _ptr(ptr){};
        reverse_iterator() :_ptr(nullptr){};

        reverse_iterator& operator=(const reverse_iterator<iter>& itr){
                if (this != &itr)
                        this->_ptr = itr._ptr;
                return *this;
        }

        reverse_iterator& operator++(){
                --(this->_ptr);
                return *this;
        }

        reverse_iterator operator++(int){
                reverse_iterator _tmp(this->_ptr);
                --(this->_ptr);
                return _tmp;
        }

        reverse_iterator& operator--(){
                ++(this->_ptr);
                return *this;
        }

        reverse_iterator operator--(int){
                reverse_iterator _tmp(this->_ptr);
                ++(this->_ptr);
                return _tmp;
        }

        reference operator*() const{
                iter tmp = _ptr;
                return (*(--tmp));
        }

        reverse_iterator operator+ (difference_type __n) const{
                return reverse_iterator(_ptr - __n);

        }
        reverse_iterator & operator+=(difference_type __n){
                _ptr -= __n;
                return *this;
        }

        reverse_iterator operator-(difference_type __n) const{
                return reverse_iterator(_ptr + __n);

        }
        reverse_iterator & operator-=(difference_type __n){
                _ptr += __n;
                return *this;
        }
        reference    operator[](difference_type __n) const{
                return _ptr[__n];
        }

         pointer  operator->() const{
                return &(*_ptr);
         }

        iterator_type base() const{
                return _ptr;
         }
 
        bool operator!=(const reverse_iterator& it){
                return (this->_ptr != it._ptr);
        }

        bool operator==(const reverse_iterator& it){
                return (this->_ptr == it._ptr);
        }
        
        bool operator<(const reverse_iterator& it){
                return (this->_ptr < it._ptr);
        }

        bool operator>(const reverse_iterator& it){
                return (this->_ptr > it._ptr);
        }

        bool operator<=(const reverse_iterator& it){
                return (this->_ptr <= it._ptr);
        }

        bool operator>=(const reverse_iterator& it){
                return (this->_ptr >= it._ptr);
        }
};

};