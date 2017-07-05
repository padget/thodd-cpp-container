    
#include <vector>
#include <list>
#include <thodd/container.hpp>
#include <thodd/functional.hpp>
    
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
}
