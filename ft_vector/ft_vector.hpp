#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "ft_iterator.hpp"
#include "ft_enable_if.hpp"
#include "ft_lexicographical_compare.hpp"

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
        typedef typename ft::iterator<T>::difference_type difference;
        typedef typename ft::iterator<T> iterator;
        typedef typename ft::const_iterator<T> const_iterator;
        typedef typename ft::reverse_iterator<T> reverse_iterator;
        typedef typename ft::iterator<T> const_reverse_iterator;

    private: //private
        T* _da;
        size_type _size;
        size_type _capacity;
        allocator_type _alloc;

    protected:
        class  OutOfRangeException: public std::exception{
            public:
                virtual const char* what() const throw() {return ("Exception: Index Out Of Range");}
        };

    /*------------------------- CONSTRUCTORS -----------------------------*/

    public:
        explicit vector(const allocator_type& alloc = allocator_type()): _alloc(alloc){ //Explicit Keyword in C++ is used to mark constructors to not implicitly convert types in C++.
                this->_da = _alloc.allocate(1);
                _alloc.construct(this->_da, value_type());
                this->_size = 0;
                this->_capacity = 1;
        }


        template <class InputIterator>// SFINAE subtitution failure it's not an error
        /* when we call a constructor with two parameters with the same type the compiler choose the third constructor
        because it muchs perfectely the paramters(beeing the same type) but the subtitution of the parameters fails (which is not an erro)
        (to invoke the first constructor,
         the compiler would have to perform a type conversion. The second constructor would fit perfectly though.)
        */
        vector (typename ft::enable_if< std::is_class<InputIterator>::value , InputIterator>::type first,
         InputIterator last, const allocator_type& alloc = allocator_type()): _alloc(alloc){//enabel_if(condition, type) if the condition is true
         // the specialization of struct enable_if for true is used, and the internal type is set to Inputiterator, if the cond is false the 
         //general form of enable if is selected, and it doesn't have a type, so the type of the argument results in a subsitutuion failure.
            this->_size = 0;
            this->_capacity = 1;
            this->_da = _alloc.allocate(1);
            _alloc.construct(this->_da, value_type());
            for(; first != last; first++)
                push_back(*first);
        }

        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _alloc(alloc){
            if(n > 0)
            {
                this->_da = _alloc.allocate(n);
                construct_false(this->_da,  n, val);
                this->_size = n;
                this->_capacity = n;
            }
        }

        vector (const vector& x){
            if (this != &x){
                this->_alloc = x._alloc;
                this->_size = x._size;
                this->_capacity = x._capacity;
                this->_da = _alloc.allocate(this->_capacity);
                construct_false(this->_da, this->_capacity, value_type());
                std::memcpy(this->_da, x._da, this->_size * sizeof(size_type));
            }
        }

        /*----------------------- DESTRUCTOR ------------------------*/

        ~vector(){
            if (this->_da)
            {
                destroy_all(this->_da, this->_capacity);
                _alloc.deallocate(this->_da, this->_capacity);
            }
        }
        
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

        /*-----------------------------------------------------------------*/
        /*---------------------------Utilitis------------------------------*/

        void construct_all(pointer dest, pointer src, size_type n){
            if (dest && src){
                for(size_type i=0; i<n; i++)
                    _alloc.construct(&dest[i], &src[i]);
            }
        }
        void construct_false(pointer dest, size_type n, const value_type& val){
                for(size_type i=0; i<n ; i++)
                    _alloc.construct(&dest[i], val);
        }

        void destroy_all(pointer p, size_type n){
                for(size_type i=0; i<n; i++)
                    _alloc.destroy(&p[i]);
        }

        void extand(int new_capacity){
            pointer tmp = _alloc.allocate(new_capacity);
            construct_false(tmp, new_capacity, value_type());
            std::memcpy(tmp, this->_da, this->_size * sizeof(value_type));
            destroy_all(this->_da, this->_capacity);
            _alloc.deallocate(this->_da, this->_capacity);
            this->_da = tmp;
            this->_capacity = new_capacity;
        }

        /*---------------------------------------------------------------*/
        /*---------------------------- Modifiers ------------------------*/

        template <class InputIterator>  
        void assign (typename ft::enable_if< std::is_class<InputIterator>::value , InputIterator>::type first, InputIterator last){
            InputIterator tmp;
            tmp =  first;
            size_type count = 0;;

            for(; tmp != last; tmp++)
                count++;

            if (count > this->_capacity)
            {
                this->destroy_all(this->_da, this->_capacity);
                this->_alloc.deallocate(this->_da, this->_capacity);
                this->_da = this->_alloc.allocate(count);
                this->_capacity = count;
            }
            else
                this->destroy_all(this->_da, this->_size);

            this->_size = 0;
            for(; first != last; first++)
                push_back(*first);
         }

        void assign (size_type n, const value_type& val){//any element held int the container before the call are destroyed
       // This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size
       // surpasses the current vector capacity.
            if (n > this->_capacity)
            {
                this->destroy_all(this->_da, this->_capacity);
                this->_alloc.deallocate(this->_da, this->_capacity);
                this->_da = this->_alloc.allocate(n);
                this->_capacity = n;
            }
            else
                this->destroy_all(this->_da, this->_size);

            this->_size = n;
            this->construct_false(this->_da, n, val);
       }

        void push_back(const value_type& val){
            if (this->_size >= this->_capacity)
                this->extand(this->_capacity * 2);
            this->_da[_size++] = val;
        }

        void pop_back(){
            if (this->_size)
                this->_alloc.destroy(_da +( --_size));
        }

        void shift_n(size_type n, int pos, const value_type& val){
            for(int i = this->_size - 1; i >= pos; i--){
                this->_da[i + n] = this->_da[i];
                this->_da[i] = val;
            }
        }

        int index_of_iterator(iterator iter){
            iterator tmp = this->begin();
            int index = 0;
            for (;tmp != iter ; tmp++)
                index++;
            return index;
        }

        iterator insert (iterator position, const value_type& val){
            if (position < this->begin())
                return position;
            else if (position == this->end())
                    push_back(val);
            else{
                size_type new_size = this->_size + 1;
                int index = this->index_of_iterator(position);

                if (new_size > this->_capacity){
                    pointer tmp = this->_alloc.allocate(this->_capacity * 2);
                    this->construct_false(tmp, this->_capacity * 2, value_type());
                    std::memcpy(tmp, this->_da, index * sizeof(value_type));
                    tmp[index] = val;
                    std::memcpy(tmp + (index + 1), this->_da + index, (this->_size - index) * sizeof(value_type) );
                    this->destroy_all(this->_da, this->_capacity);
                    this->_alloc.deallocate(this->_da, this->_capacity);
                    this->_da = tmp;
                    this->_size = new_size;
                    this->_capacity = this->_capacity * 2;
                }
                else{
                    shift_n(1, index, val);
                this->_size = new_size;
                }
            }
            return position;
        }

        void insert (iterator position, size_type n, const value_type& val){
            if (position < this->begin())
                return ;
            else if (position == this->end())
                for(size_type i=0; i<n; i++)
                    push_back(val);
            else{
                size_type new_size = this->_size + n;
                int index = this->index_of_iterator(position);

                if (new_size > this->_capacity){
                    pointer tmp = this->_alloc.allocate(this->_capacity * 2);
                    this->construct_false(tmp, this->_capacity * 2, value_type());
                    std::memcpy(tmp, this->_da, index * sizeof(value_type));
                    for(size_type i=index; i < index+n; i++)
                        tmp[i] = val;
                    std::memcpy(tmp + (index + n), this->_da + index, (this->_size - index) * sizeof(value_type) );
                    this->destroy_all(this->_da, this->_capacity);
                    this->_alloc.deallocate(this->_da, this->_capacity);
                    this->_da = tmp;
                    this->_size = new_size;
                    this->_capacity = this->_capacity * 2;
                }
                else{
                    shift_n(n, index, val);
                    this->_size = new_size;
                }
            }
        }
        /* insert function iserts a range of iterators in a position 
        @desc: if the position is the end we iterate and push the elements
                if the new_size is biger than the capacity a reallocation is done
                else the elements are shifted count (the number of elments to insert) times and the range of iterators is inserted*/
        template <class InputIterator>
        void insert(iterator position, typename ft::enable_if< std::is_class<InputIterator>::value , InputIterator>::type first, InputIterator last){
            size_type count = 0;
            for(InputIterator iter=first; iter!=last; iter++)
                count++;

            if (position < this->begin())
                return ;
            else if (position == this->end())
                for(InputIterator iter=first; iter!=last; iter++)
                    push_back(*iter);
            else{
                size_type new_size = this->_size + count;
                int index = this->index_of_iterator(position);

                if (new_size > this->_capacity){
                    pointer tmp = this->_alloc.allocate(this->_capacity * 2);
                    this->construct_false(tmp, this->_capacity * 2, value_type());
                    std::memcpy(tmp, this->_da, index * sizeof(value_type));

                    size_type i = index;
                    InputIterator iter = first;
                    while(iter!=last){
                        tmp[i++] = *iter;
                        iter++; 
                    }

                    std::memcpy(tmp + (index + count), this->_da + index, (this->_size - index) * sizeof(value_type) );
                    this->destroy_all(this->_da, this->_capacity);
                    this->_alloc.deallocate(this->_da, this->_capacity);
                    this->_da = tmp;
                    this->_size = new_size;
                    this->_capacity = this->_capacity * 2;
                }
                else{
                    shift_n(count, index, value_type());
                    size_type i = index;
                    InputIterator iter = first;
                    while(iter!=last){
                        this->_da[i++] = *iter;                   
                        iter++;
                    }
                    this->_size = new_size;
                }
            }
        }

        void unshift_n(size_type n, int pos){
            for(size_type i = pos, j = 0; i < this->_size; i++, j++){
                if (j < n)
                    this->_alloc.destroy(this->_da + i);
                this->_da[i] = this->_da[i + n];
            }
        }

        iterator erase (iterator position){
            if (position >= this->begin() && position < this->end())
            {
                size_type index = index_of_iterator(position);
                unshift_n(1, index);
                this->_size--;

            }
            return position;
        }

        iterator erase (iterator first, iterator last){
            size_type count = 0;
            size_type index = index_of_iterator(first);

            for(iterator iter = first; iter != last; iter++)
                count++;
            unshift_n(count, index);
            this->_size -= count;
            return first;
        }

        void swap (vector& x){
            size_type tmp_size;
            size_type tmp_capacity;
            pointer tmp_da;
            allocator_type tmp_alloc;

            tmp_da = this->_da;
            tmp_size = this->_size;
            tmp_capacity = this->_capacity;
            tmp_alloc = this->_alloc;

            this->_da = x._da;
            this->_size = x._size;
            this->_capacity = x._capacity;
            this->_alloc = x._alloc;

            x._da = tmp_da;
            x._size = tmp_size;
            x._capacity = tmp_capacity;
            x._alloc = tmp_alloc;
        }

        void clear(){
            destroy_all(this->_da, this->_size);
            this->_size = 0;
        }

        /*------------------------------------------------------------*/
        /*--------------------------Capacity--------------------------*/


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

        /*-------------------------------------------------------------*/
        /*-------------------- Element Access -------------------------*/

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
        /*----------------------------------------------------------*/

        allocator_type get_allocator() const{
            return this->_alloc;
        }

        
    };

    /*-------------------- Relational Operators ------------------------*/

    template <class T, class Alloc>  
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        if (lhs.size() == rhs.size()){
            for (size_t i = 0; i < lhs.size(); i++)
            {
                if(lhs[i] != rhs[i])
                    return false;
            }
        }
        else
            return false;
        return true;
    }

    template <class T, class Alloc>  
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return (!(lhs == rhs));
    }

    template <class T, class Alloc> 
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
    }

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return rhs < lhs;
    }

    template <class T, class Alloc> 
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return !(rhs<lhs);
    }

    template <class T, class Alloc> 
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return !(lhs<rhs);
    }

    /*----------------------------------------------------------*/

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
        vector<T, Alloc> tmp(x);

        x.swap(y);
        y.swap(tmp);
    }
};