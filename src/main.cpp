    
#include <vector>
#include <list>
#include <thodd/container.hpp>
#include <thodd/functional.hpp>
    
template<
    typename value_t>
class myvector 
{
    public :
    using value_type = value_t;

    inline void push_back(value_type const&) {}

    inline int* begin() { return nullptr ; }

    inline int* end() { return nullptr ; }
} ;

int main() 
{
    using namespace thodd ;

    std::vector<int> __vec {1, 2, 3, 4, 5} ;

    ($linq << with(ref(__vec)) 
           << foreach(cout_ << $0)) () ;

    std::cout << "\n" ;

    ($linq << with(ref(__vec)) 
           << foreach(cout_ << $0)
           << where($0 % val(2) == val(0))) ();  

    std::cout << "\n" ;

    ($linq << with(ref(__vec)) 
           << foreach(cout_ << $0)
           << where($0 % val(2) == val(0))) () ;  

    std::cout << "\n" ;

    ($linq << with(ref(__vec)) 
           << foreach(cout_ << $0) 
           << limit(val(2))) () ;

    std::cout << "\n" ;

    ($linq << with(ref(__vec)) 
           << foreach(cout_ << $0) 
           << where($0 % val(2) == val(1)) 
           << limit(val(3))) ();

    
    std::cout << "\n" ;

    std::list<int> __vec2 ;

    ($linq << with(cref(__vec)) 
           << transfer(ref(__vec2))) () ;

    ::myvector<int> __mvec;

    ($linq << with(ref(__mvec)) << transfer(ref(__mvec))) () ;
}
