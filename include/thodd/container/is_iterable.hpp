#ifndef __THODD_CONTAINER_IS_ITERABLE_HPP__
#  define __THODD_CONTAINER_IS_ITERABLE_HPP__

#  include <type_traits>
#  include <utility>

namespace
thodd
{
    template<
        typename, 
        typename = std::void_t<>>
    struct is_iterable : std::false_type {} ;

    template<typename type_t>
    struct is_iterable<
            type_t, 
            std::void_t<
                decltype(std::declval<type_t>().begin()), 
                decltype(std::declval<type_t>().end())>> 
        : std::true_type {} ;
}

#endif