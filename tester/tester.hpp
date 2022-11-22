
#ifndef TESTER_HPP
# define TESTER_HPP

# include <sys/stat.h> 
# include <sys/types.h>
# include <iostream>
# include <string>
# include <fstream>

# define NORMAL "\033[0;37m"
# define UNDERLINE "\033[4m"
# define BOLD_RED "\033[1;31m"
# define BOLD_GREEN "\033[1;32m"

# define OK	"\e[92;5;118m[OK]\e[0m"
# define NOP "\033[0;31m[NOP]\e[0m"

# define YELLOW			"\e[93;5;226m"
# define CURSIVE        "\e[33;2;37m"	
# define GRAY			"\e[33;2;37m"
# define RESET			"\e[0m"



template <class T>
std::string equal(const T& t1, const T& t2)
{
    return (t1 == t2 ? "✔" : "✘");
}

template <class T>
bool equalbool(const T& t1, const T& t2)
{
    return (t1 == t2 ? true : false);
}

// t1 == stl
// t2 == ft
template<class T>
static bool printSingleValue(std::fstream& fs, const T& t1, const T& t2)
{
    fs << "\n══════════════════════════════════════════════════════════════\n";
    fs << "Value from :\n";
    fs << "STL    : " << t1 << "\n";
    fs << "FT  [" << equal(t1, t2) << "]: " << t2 << "\n";
    fs << "══════════════════════════════════════════════════════════════\n";
    return (t1 == t2 ? true : false);
}

bool printBoolResult(std::fstream& fs, bool stl_bool, bool ft_bool);

void test_vector();
void test_set();
void test_map();
void test_stack();

#endif