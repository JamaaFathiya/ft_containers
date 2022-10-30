#include "ft_stack.hpp"
#include <stack>
#include <iostream>

int main(){

    ft::stack<int> s;
    std::stack<int> s1;

    for(int i=0; i < 5000 ; i++){
        s.push(i);
        s1.push(i);
    }

    s.pop();
    s1.pop();
    
    std::cout << s.empty() << std::endl;
    std::cout << s1.empty() << std::endl;

std::cout << "size: " << s.size() << std::endl;
std::cout << "size: " << s1.size() << std::endl;

std::cout << "top: " << s.top() << std::endl;
std::cout << "top: " << s1.top() << std::endl;

    return 0;
}

