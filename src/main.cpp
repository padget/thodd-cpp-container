    
#include <vector>
#include <list>
#include <string>

#include <thodd/container.hpp>
#include <thodd/functional.hpp>
    
template<
    typename value_t>
class myvector 
{
    public :
    using value_type = value_t;

    inline void push_back (value_type const&) {}
    inline int* begin () { return nullptr ; }
    inline int* end () { return nullptr ; }
} ;


template<
        typename type_t>
struct 
in_vector
{
    std::vector<type_t> data ;
} ;

int main() 
{
    using namespace thodd ;

    std::vector<int> __vec {1, 2, 3, 4, 5} ;

    ($cquel << with(ref(__vec)) 
            << foreach(cout_ << $0)) () ;

    std::cout << "\n" ;

    ($cquel << with(ref(__vec)) 
            << foreach(cout_ << $0)
            << where($0 % val(2) == val(0))) ();  

    std::cout << "\n" ;

    ($cquel << with(ref(__vec)) 
            << foreach(cout_ << $0)
            << where($0 % val(2) == val(0))) () ;  

    std::cout << "\n" ;

    ($cquel << with(ref(__vec)) 
            << foreach(cout_ << $0) 
            << limit(val(2))) () ;

    std::cout << "\n" ;

    ($cquel << with(ref(__vec)) 
            << foreach(cout_ << $0) 
            << where($0 % val(2) == val(1)) 
            << limit(val(3))) ();
                

    
    std::cout << "\n" ;

    std::list<int> __vec2 ;

    ($cquel << with(cref(__vec)) 
            << copy(ref(__vec2))) () ;

    ($cquel << with(ref(__vec)) << foreach(cout_ << $0 << val(' '))) ();

    ::myvector<int> __mvec;

    ($cquel << with(ref(__mvec)) 
            << copy(ref(__mvec))) () ;

    struct 
    person 
    {
        int age {0} ;
        std::string name ;
    } ;

    std::vector<person> __tomap {
        { 12, "jhon" }, 
        { 17, "harry" }, 
        { 25, "bertrand" }, 
        { 18, "marrion" }, 
        { 23, "maxime" }, 
        { 31, "myriam" } } ;

    ($cquel << with(ref(__tomap)) 
            << map([](auto&& __item) { return __item.name ; })
            << foreach(cout_ << $0 << val(' '))) () ;

    

    std::vector<::in_vector<person>> __twodim { 
        {__tomap}, 
        {__tomap}, 
        {__tomap}, 
        {__tomap} } ;

    ($cquel << with(ref(__twodim)) 
            << map([](auto&& __item) { return __item.data[0].name ; }, 
                   [](auto&& __item) { return __item.name ; }) 
            << foreach(cout_ << $0 << val(' '))) () ;

     std::vector<float> __tosum { 1 , 2 , 3 , 4 , 5 , 6 } ;
     constexpr auto sumall = [](auto&& __container){auto sum = 0u ; for(auto&& __item : __container) sum += __item ; return sum ; } ;
     auto sum = ($cquel << with(ref(__tosum)) << all(sumall)) ();
     auto size = ($cquel << with(ref(__tosum)) << all([] (auto&& __container) {return __container.size() ;})) () ;
     auto mean = ($cquel << with(ref(sum)) << all([&size] (auto&& __sum){return __sum / size;})) () ;
     std::cout << "mean " << mean ;   

}
