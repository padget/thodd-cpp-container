#ifndef __THODD_CONTAINER_HAS_PUSH_BACK_HPP__
#  define  __THODD_CONTAINER_HAS_PUSH_BACK_HPP__ 

#  include <type_traits>
#  include <utility>

namespace
thodd
{
    template<
        typename, 
        typename,
        typename = std::void_t<>>
    struct has_push_back : std::false_type {} ;

    template<
        typename container_t, 
        typename item_t>
    struct has_push_back<
        container_t,
        item_t, 
        std::void_t<
            decltype(std::declval<container_t>().push_back(std::declval<item_t>()))>> 
        : std::true_type {} ;
}

#endif