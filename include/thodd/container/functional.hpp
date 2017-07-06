#ifndef __THODD_CONTAINER_FUNCTIONAL_HPP__
#  define __THODD_CONTAINER_FUNCTIONAL_HPP__

#  include <thodd/container/has_push_back.hpp>
#  include <type_traits>

namespace
thodd
{
    extern constexpr auto
    push_back = 
    [] (auto& __container, auto&& __item)
    {
        constexpr auto __has_push_back = 
            has_push_back<
                decltype(__container), 
                decltype(__item)>::value ;

        static_assert (__has_push_back, "__container must have push_back method") ;

        if constexpr (__has_push_back)
            return 
            __container.push_back(
                static_cast<decltype(__item)&&>(__item)) ;
    } ;
}

#endif