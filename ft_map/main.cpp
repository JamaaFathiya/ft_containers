#include <iostream>

#include "../utility/ft_pair.hpp"
#include <map>
int main(){
 std::map<int , int> ma;


    ma.insert(std::pair<int, int>(1,2));
    ma.insert(std::pair<int, int>(7,2));
    ma.insert(std::pair<int, int>(3,2));
    ma.insert(std::pair<int, int>(4,2));
    ma.insert(std::pair<int, int>(6,2));
    ma.insert(std::pair<int, int>(2,2));


    std::map<int,int>::iterator it = ma.find(4);
    it--;
//    for(std::map<int,int>::iterator it = ma.end() ; it != ma.begin(); --it)
        std::cout << it->first << std::endl;
}