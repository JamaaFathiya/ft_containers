#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "ft_iterator.hpp"

namespace ft
{
    template <typename T, 
    class Allocator = std::allocator<T>
    >
    class vector
    {

    public:
        typedef T  value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::pointer         pointer;
        typedef typename ft::iterator<T> iterator;
        typedef typename ft::const_iterator<T> const_iterator;
        typedef typename ft::reverse_iterator<T> reverse_iterator;
        typedef typename ft::iterator<T> const_reverse_iterator;
        allocator_type alloc;

    private: //private
        T* _da;
        size_type _size;
        size_type _capacity;

    protected:
        class  OutOfRangeException: public std::exception{
            public:
                virtual const char* what() const throw() {return ("Exception: Index Out Of Range");}
        };
    public:
        vector(){
            this->_da = alloc.allocate(1);
            alloc.construct(this->_da, false);
            this->_size = 0;
            this->_capacity = 1;
        }

        explicit vector(size_type n, const value_type& val = value_type()){
            this->_da = alloc.allocate(n);
            alloc.construct_all(this->_da, val, n);
            this->_size = 0;
            this->_capacity = n;
        }
        ~vector(){
            // std::cout << " destructor " << std::endl;
        }
        
        

        /*------------------------- Modifiers ----------------------------*/




        /*---------------------------- Iterators -------------------------*/

        iterator begin(){ //returns iterator to the beginning 
            return iterator(this->_da);
        }

        iterator end(){ //returns iterator to the end
            return iterator(this->_da + _size);
        }

        reverse_iterator rbegin(){ //returns reverse iterator to the reverse begining(end)
            return reverse_iterator(this->_da + _size);
        }

        reverse_iterator rend(){ //returns reverse iterator to the reverse end(begining)
            return reverse_iterator(this->_da);
        }

        const_iterator cbegin() const{ //returns const iterator to the begining
            return const_iterator(this->_da);
        }

        const_iterator cend() const{ //returns const iterator to the end
            return const_iterator(this->_da + _size);
        }
        const_reverse_iterator crbegin() const{ //returns const reverse iterator to the reverse beginning (end)
            return const_reverse_iterator(this->_da + _size);
        }

        const_reverse_iterator crend(){ //returns const reverst iterator to the reverse end (beginning)
            return const_reverse_iterator(this->_da);
        }

        /*-----------------------------------------------------*/
        /*---------------------Utilitis------------------------*/

        void construct_all(pointer dest, pointer src, size_type n){
            if (dest && src){
                for(size_type i=0; i<n; i++)
                    alloc.construct(&dest[i], &src[i]);
            }
        }
        void construct_false(pointer dest, size_type n){
                for(size_type i=0; i<n ; i++)
                    alloc.construct(&dest[i], false);
        }
        void destroy_all(pointer p, size_type n){
                for(size_type i=0; i<n; i++)
                    alloc.destroy(&p[i]);
        }

        void extand(int new_capacity){
            pointer tmp = alloc.allocate(new_capacity);
            construct_false(tmp, new_capacity);
            std::memcpy(tmp, this->_da, this->_size * sizeof(size_type));
            destroy_all(this->_da, this->_capacity);
            alloc.deallocate(this->_da, this->_capacity);
            this->_da = tmp;
            this->_capacity = new_capacity;
        }
        /*----------------------------------------------------*/
        /*--------------------- Modifiers --------------------*/
        // iterator insert (iterator position, const value_type& val){

        // }
        
        void push_back(const value_type& val){
            if (this->_size >= this->_capacity)
                this->extand(this->_capacity * 2);
            this->_da[_size++] = val;
        }

        void pop_back(){
            if (this->_size)
            {
                this->_da[_size - 1] = 0;
                _size--;
            }
        }
        /*---------------------------------------------------*/
        /*---------------------Capacity----------------------*/


        size_type size() const{ //returns the number of elements in the vector
            return (this->_size);
        }

        size_type max_size() const{ //return the maximum number of elements that the vector can store
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }

        void resize (size_type n, value_type val = value_type()){ //changes the size of the vector to n (either by adding elements of destroying)
            if (n >= this->_size)
            {
                if (n > this->_capacity)
                    this->extand(n);
                for(size_type i=this->_size; i < n - this->_size; i++)
                    push_back(val);
            }
            else
                destroy_all(this->_da + n, this->_size - n);
            this->_size = n;
        }

        size_type capacity() const{ // returns the capacity of the vector
            return this->_capacity;
        }

        bool empty() const{ //returns true if the size == 0
            return (this->_size == 0);
        }

        void reserve (size_type n){ //changes(or not) the capacity of the vector to store n elements
            if (n > this->_capacity){
                this->extand(n);
                this->_capacity = n;
            }
        }

        void shrink_to_fit(){ //changes the capacity to fit the size of the vector
            this->extand(this->_size);
        }

        /*---------------------------------------------------*/
         /*-------------- Element Access --------------------*/

        reference operator[] (size_type n){
            if (n <= this->_size && n >= this->_size)
                std::cerr << "Index out of bound!" << std::endl; 
            return this->_da[n];
        }

        const_reference operator[] (size_type n) const{
            if (n <= this->_size && n >= this->_size)
                std::cerr << "Index out of bound!" << std::endl; 
            return this->_da[n];
        }

        reference at (size_type n){
            if (n >= this->_size)
                throw OutOfRangeException();
            return this->_da[n];
        }

        const_reference at (size_type n) const{
            if (n >= this->_size)
                throw OutOfRangeException();
            return this->_da[n];
        }

        reference front(){
            if (this->empty())
                std::cout << "fornt() called for empty vector" << std::endl;
            return *this->_da;
         }

        const_reference front() const{
            if (this->empty())
                std::cout << "fornt() called for empty vector" << std::endl;
            return *this->_da;   
         }

         reference back(){
            if (this->empty())
                std::cout << "back() called for empty vector" << std::endl;
            return *(this->_da + (this->_size - 1));
         }

         const_reference back() const{
            if (this->empty())
                std::cout << "back() called for empty vector" << std::endl;
            return *(this->_da + (this->_size - 1));
         }

         value_type* data() throw() {
            return this->_da;
         }

         const value_type* data() const throw() {
            return this->_da;
         }
        /*-----------------------------------------------------*/
    };
};