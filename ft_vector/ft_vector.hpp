#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "../utility/ft_iterator.hpp"
#include "../utility/ft_enable_if.hpp"
#include "../utility/ft_lexicographical_compare.hpp"

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
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private: 
        T* _da;
        size_type _size;
        size_type _capacity;
        allocator_type _alloc;

        /*-----------------------------------------------------------------*/
        /*---------------------------Utilitis------------------------------*/

        void construct_all(pointer dest, pointer src, size_type n){
            if (dest && src){
                for(size_type i=0; i<n; i++)
                    _alloc.construct(&dest[i], &src[i]);
            }
        }
        void construct_default(pointer dest, size_type n, const value_type& val = value_type()){
                for(size_type i=0; i<n ; i++)
                    _alloc.construct(&dest[i], val);
        }

        void destroy_all(pointer p, size_type n){
                for(size_type i=0; i<n; i++)
                    _alloc.destroy(&p[i]);
        }

        void extand(int new_capacity){
            pointer tmp = _alloc.allocate(new_capacity);
            construct_default(tmp, new_capacity);
            std::memcpy(tmp, this->_da, this->_size * sizeof(value_type));
            if (this->_capacity != 0)
            {
               destroy_all(this->_da, this->_capacity);
             _alloc.deallocate(this->_da, this->_capacity);
            }
            this->_da = tmp;
            this->_capacity = new_capacity;
        }

        void shift_n(size_type n, int pos, const value_type& val){
            for(int i = this->_size - 1; i >= pos; i--){
                this->_da[i + n] = this->_da[i];
                this->_da[i] = val;
            }
        }

        void unshift_n(size_type n, int pos){
            for(size_type i = pos, j = 0; i < this->_size; i++, j++){
                if (j < n)
                    this->_alloc.destroy(this->_da + i);
                this->_da[i] = this->_da[i + n];
            }
        }

        /*---------------------------------------------------------------*/

    protected:
        class  OutOfRangeException: public std::exception{
            public:
                virtual const char* what() const throw() {return ("Exception: Index Out Of Range");}
        };

    /*------------------------- CONSTRUCTORS -----------------------------*/

    public:
        explicit vector(const allocator_type& alloc = allocator_type()): _alloc(alloc){ //Explicit Keyword in C++ is used to mark constructors to not implicitly convert types in C++.
                this->_size = 0;
                this->_capacity = 0;
                this->_da = nullptr;
        }



        // SFINAE subtitution failure it's not an error:
        /* when we call a constructor with two parameters with the same type the compiler choose the third constructor
        because it muchs perfectely the paramters(beeing the same type) but the subtitution of the parameters fails (which is not an erro)
        (to invoke the first constructor,
        the compiler would have to perform a type conversion. The second constructor would fit perfectly though.)

        ENABLE_IF:
        enable_if(condition, type) if the condition is true
        the specialization of struct enable_if for true is used, and the internal type is set to Inputiterator, if the cond is false the 
         general form of enable if is selected, and it doesn't have a type, so the type of the argument results in a subsitutuion failure.
        */
        template <class InputIterator>
        vector (typename ft::enable_if< std::is_class<InputIterator>::value , InputIterator>::type first,
         InputIterator last, const allocator_type& alloc = allocator_type()): _alloc(alloc){

             _size = last - first; //if first > last an exception is thrown by the allocator
             _capacity = 0;

            this->_da = _alloc.allocate(_size);
            for(; first != last; first++)
                this->_alloc.construct(this->_da + (_capacity++), *first);
        }

        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _alloc(alloc){
            _size = n;
            _capacity = n;

            this->_da = _alloc.allocate(n);
            construct_default(this->_da,  n, val);
        }

        vector (const vector& x){
            if (this != &x){
                this->_alloc = x._alloc;
                this->_size = x._size;
                this->_capacity = x._capacity;
                this->_da = _alloc.allocate(this->_capacity);
                construct_default(this->_da, this->_capacity);
                std::memcpy(this->_da, x._da, this->_size * sizeof(value_type));
            }
        }

        vector& operator= (const vector& x){
            if (this->_capacity <  x.size()){
                this->extand(x.capacity());
                this->_capacity = x._capacity;
            }
            else{
                this->destroy_all(this->_da, this->_size);
                this->construct_default(this->_da, this->_size);
            }
            this->_alloc = x._alloc;
            this->_size = x._size;
            std::memcpy(this->_da, x._da, this->_size * sizeof(value_type)); 
            return *this;
        }

        /*----------------------- DESTRUCTOR ------------------------*/

        ~vector(){
            if (this->_da && this->_capacity)
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
            return reverse_iterator(this->end());
        }

        reverse_iterator rend(){ //returns reverse iterator to the reverse end(begining)
            return reverse_iterator(this->begin());
        }

        const_iterator cbegin() const{ //returns const iterator to the begining
            return const_iterator(this->_da);
        }

        const_iterator cend() const{ //returns const iterator to the end
            return const_iterator(this->_da + _size);
        }
        const_reverse_iterator crbegin() const{ //returns const reverse iterator to the reverse beginning (end)
            return const_reverse_iterator(this->cend());
        }

        const_reverse_iterator crend(){ //returns const reverse iterator to the reverse end (beginning)
            return const_reverse_iterator(this->cbegin());
        }

        /*---------------------------- Modifiers ------------------------*/

        // erase edge cases: if last < first a length exception is thrown by the allocator.
        template <class InputIterator>  
        void assign (typename ft::enable_if< std::is_class<InputIterator>::value , InputIterator>::type first, InputIterator last){
            size_type count = last - first;

            if (count > this->_capacity)
            {
                if (this->_capacity != 0)
                {
                    this->destroy_all(this->_da, this->_capacity);
                    this->_alloc.deallocate(this->_da, this->_capacity);
                }
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
                if (this->_capacity != 0)
                {
                    this->destroy_all(this->_da, this->_capacity);
                    this->_alloc.deallocate(this->_da, this->_capacity);
                }
                this->_da = this->_alloc.allocate(n);
                this->_capacity = n;
            }
            else
                this->destroy_all(this->_da, this->_size);

            this->_size = n;
            this->construct_default(this->_da, n, val);
       }

        void push_back(const value_type& val){
            if (this->_capacity == 0)
            {
                this->_da = _alloc.allocate(1);
                _alloc.construct(this->_da, value_type());
                this->_capacity++;
            }
            else if (this->_size >= this->_capacity)
                this->extand(this->_capacity * 2);
            this->_da[_size++] = val;
        }

        void pop_back(){
            if (this->_size)
                this->_alloc.destroy(_da +( --_size));
        }

        //insert : insert one element in position , if the new_size is greater than the size a reallocation with capacity * 2 is done.
        //edge cases: if position < begin()  => a construction is done in position and size = new_size  (not secure).
        //            if position is out of the storage allocated a construction without allocation is done in position.
        iterator insert (iterator position, const value_type& val){
            size_type index =  position - this->begin();

            if (position < this->begin() || index > this->capacity())
                return position; //protection: if the position is out of the allocated storage

            size_type new_size = this->_size + 1;
            if (new_size > this->_capacity){
                pointer tmp = this->_alloc.allocate(this->_capacity * 2);
                this->construct_default(tmp, this->_capacity * 2);
                std::memcpy(tmp, this->_da, index * sizeof(value_type));
                tmp[index] = val;
                std::memcpy(tmp + (index + 1), this->_da + index, (this->_size - index) * sizeof(value_type) );
            if (this->_capacity != 0)
            {
                this->destroy_all(this->_da, this->_capacity);
                this->_alloc.deallocate(this->_da, this->_capacity);
            }
                this->_da = tmp;
                this->_size = new_size;
                this->_capacity = this->_capacity * 2;
            }
            else{
                shift_n(1, index, val);
            this->_size = new_size;
            }
            return position;
        }

        // insert n element of val int the position.
        // if the new_size is greater than size a reallocation with new_size is done.
        // edge cases: position < begin() construction of n element.
        void insert (iterator position, size_type n, const value_type& val) {
            size_type index = position - this->begin();
            if (position < this->begin() || index >= this->_capacity)
                return;

            size_type new_size = this->_size + n;
            if (new_size > this->_capacity) {
                pointer tmp = this->_alloc.allocate(new_size);
                this->construct_default(tmp, new_size);
                std::memcpy(tmp, this->_da, index * sizeof(value_type));

                for (size_type i = index; i < index + n; i++)
                    tmp[i] = val;

                std::memcpy(tmp + (index + n), this->_da + index, (this->_size - index) * sizeof(value_type));
                if (this->_capacity != 0) {
                    this->destroy_all(this->_da, this->_capacity);
                    this->_alloc.deallocate(this->_da, this->_capacity);
                }
                this->_da = tmp;
                this->_size = new_size;
                this->_capacity = new_size;
            } else {
                shift_n(n, index, val);
                this->_size = new_size;
            }
        }
        /* insert function iserts a range of iterators in a position 
        @desc: if the position is the end we iterate and push the elements
                if the new_size is biger than the capacity a reallocation is done
                else the elements are shifted count (the number of elments to insert) times and the range of iterators is inserted*/
        //edge cases: if last < first: an exception is thrown.
        template <class InputIterator>
        void insert(iterator position, typename ft::enable_if< std::is_class<InputIterator>::value , InputIterator>::type first, InputIterator last){
            size_type index = position - this->begin();
            int count = last - first;

            if (position < this->begin() || index >= this->capacity())
                return ;

            size_type new_size = this->_size + count;
            if (new_size > this->_capacity){
                pointer tmp = this->_alloc.allocate(new_size);
                this->construct_default(tmp, new_size);
                std::memcpy(tmp, this->_da, index * sizeof(value_type));

                size_type i = index;
                InputIterator iter = first;
                while(iter!=last){
                    tmp[i++] = *iter;
                    iter++;
                }

                std::memcpy(tmp + (index + count), this->_da + index, (this->_size - index) * sizeof(value_type) );
                if (this->_capacity != 0)
                {
                    this->destroy_all(this->_da, this->_capacity);
                    this->_alloc.deallocate(this->_da, this->_capacity);
                }
                this->_da = tmp;
                this->_size = new_size;
                this->_capacity = new_size;
            }
            else{
                if (first < last) {
                    shift_n(count, index, value_type());
                    size_type i = index;
                    InputIterator iter = first;
                    while (iter != last) {
                        this->_da[i++] = *iter;
                        iter++;
                    }
                    this->_size = new_size;
                }
            }

        }

        //edge cases: if position is out of range => segfault.
        iterator erase (iterator position){
            if (position < this->begin())
                return erase(this->begin());// in case of erasing before the beginning
            if (position >= this->begin() && position < this->end())
            {
                size_type index = position - this->begin() ;
                unshift_n(1, index);
                this->_size--;
            }
            return position;
        }

        //edge cases: if last < first => endless loop.
        iterator erase (iterator first, iterator last){
            size_type count = last - first;
            size_type index = first - this->begin();

            if (first < last){
                unshift_n(count, index);
                this->_size -= count;
            }
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

        size_type   max_size(void) const { //return the maximum number of elements that the vector can store
            return allocator_type().max_size();
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