#ifndef __THODD_CONTAINER_HAS_ITERATOR_TYPE__
#  define  __THODD_CONTAINER_HAS_ITERATOR_TYPE__ 

#  include <type_traits>

namespace
thodd
{
    template<
        typename, 
        typename = std::void_t<>>
    struct has_iterator_type : std::false_type {} ;


    template<
        typename type_t>
    struct has_iterator_type<
        type_t, 
        std::void_t<
            typename type_t::iterator_type>> 
        : std::true_type {} ;

}

#endif