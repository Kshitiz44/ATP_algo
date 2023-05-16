#include <iostream>
#include <type_traits>

// Primary template
template<typename T, typename U>
struct is_valid_addition
{
    static constexpr bool value = false;
};

// Specialization for valid addition
template<typename T>
struct is_valid_addition<T, T>
{
    static constexpr bool value = std::is_arithmetic<T>::value;
};

// Function to check if addition is valid
template<typename T, typename U>
bool check_addition(T obj1, U obj2)
{
    return is_valid_addition<T, U>::value;
}

template <typename T>
T sum(T &&a, T &&b)
{
    return a+b;
}

int main()
{
    if(!check_addition("abc", "bcd"))
    {
        std::cout<<"Error"<<std::endl;
        return 0;
    }

    else sum("abc", "bcd");

    // save abc and bcd in a string variable first before passing to the function
    // by default, abc and bcd are character arrays not strings

    return 0;
}
