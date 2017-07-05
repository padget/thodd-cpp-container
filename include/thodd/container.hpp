#ifndef __THODD_CONTAINER_HPP__
#  define __THODD_CONTAINER_HPP__

#  include <thodd/dsl.hpp>
#  include <thodd/functional.hpp>
#  include <type_traits>

namespace
thodd
{
    enum class 
    container
    {
        with, 
        foreach, 
        where, 
        sort, 
        limit
    } ;


    extern constexpr auto
    with = 
    [] (auto&& __container_get)
    {
        return 
        as_node(
            std::integral_constant<
                container, 
                container::with>{},
            static_cast<decltype(__container_get)&&>(__container_get)) ;
    } ;


    extern constexpr auto
    foreach = 
    [] (auto&& __algorithm) 
    {
        return 
        as_node(
            std::integral_constant<
                container, 
                container::foreach>{},
            static_cast<decltype(__algorithm)&&>(__algorithm)) ;
    } ;

    template<
        typename, 
        typename = std::void_t<>>
    struct has_push_back : std::false_type {} ;

    template<
        typename type_t>
    struct has_push_back<type_t, 
        std::void_t<
            typename type_t::value_type, 
            decltype(
                std::declval<type_t>().push_back(
                    std::declval<typename type_t::value_type>()))>> : std::true_type {} ;

    template<
        typename, 
        typename = std::void_t<>>
    struct is_iterable : std::false_type {} ;

    template<typename type_t>
    struct is_iterable<
            type_t, 
            std::void_t<
                decltype(std::declval<type_t>().begin()), 
                decltype(std::declval<type_t>().end())>> : std::true_type {} ;

    extern constexpr auto
    push_back = 
    [] (auto& __container, auto&& __item)
    {
        static_assert(
            has_push_back<std::decay_t<decltype(__container)>>::value, 
            "__container must have push_back method") ;

        static_assert(
            is_iterable<std::decay_t<decltype(__container)>>::value, 
            "__container must be iterable") ;

        if constexpr (has_push_back<std::decay_t<decltype(__container)>>::value)
            return __container.push_back(static_cast<decltype(__item)&&>(__item)) ;
    } ;

    extern constexpr auto
    transfer = 
    [] (auto&& __target) 
    {
        return 
        as_node(
            std::integral_constant<
                container, 
                container::foreach>{}, 
            [&] (auto&& __item) 
            { 
                push_back(
                    __target(), 
                    static_cast<decltype(__item)&&>(__item)) ; 
            }) ;
    } ;


    extern constexpr auto
    where = 
    [] (auto&& __algorithm) 
    {
        return 
        as_node(
            std::integral_constant<
                container, 
                container::where>{},
            static_cast<decltype(__algorithm)&&>(__algorithm)) ;
    } ;


    extern constexpr auto
    sort = 
    [] () 
    {
        return 
        as_node(
            std::integral_constant<
                container, 
                container::sort>{},
            [] () {}) ;
    } ;


    extern constexpr auto
    limit = 
    [] (auto&& __number) 
    {
        return 
        as_node(
            std::integral_constant<
                container, 
                container::limit>{},
            static_cast<decltype(__number)&&>(__number)) ;
    } ;


    template<
        container id_c, 
        typename act_t>
    using linq_node = node<container, id_c, act_t> ;

    template <typename act_t>
    using with_node = linq_node<container::with, act_t> ;

    template <typename act_t>
    using foreach_node = linq_node<container::foreach, act_t> ;

    template <typename act_t>
    using where_node = linq_node<container::where, act_t> ;
    
    template <typename act_t>
    using sort_node = linq_node<container::sort, act_t> ;

    template <typename act_t>
    using limit_node = linq_node<container::limit, act_t> ;


    struct linq 
    {
        constexpr auto
        get_interpretor(
            with_node<auto> const& __with, 
            foreach_node<auto> const& __foreach) const
        {
            return 
            [&] (auto&&... __params) 
            {
                auto&& __container = __with.act(static_cast<decltype(__params)&&>(__params)...) ;
                auto&& __algorithm = __foreach.act ;

                for (auto&& __item : __container)
                    __algorithm(static_cast<decltype(__item)&&>(__item)) ;
            } ;
        }

        constexpr auto
        get_interpretor(
            with_node<auto> const& __with, 
            foreach_node<auto> const& __foreach,
            limit_node<auto> const& __limit) const
        {
            return 
            [&] (auto&&... __params) 
            {
                auto&& __container = __with.act(static_cast<decltype(__params)&&>(__params)...) ;
                auto&& __algorithm = __foreach.act ;
                auto&& __max = __limit.act(static_cast<decltype(__params)&&>(__params)...) ;
                auto __cpt = 0u ;
                
                for (auto&& __item : __container)
                    if (__cpt++ < __max)
                        __algorithm(static_cast<decltype(__item)&&>(__item)) ;
            } ;
        }


        constexpr auto
        get_interpretor(
            with_node<auto> const& __with, 
            foreach_node<auto> const& __foreach,
            where_node<auto> const& __where) const
        {
            return 
            [&] (auto&&... __params) 
            {
                auto&& __container = __with.act(static_cast<decltype(__params)&&>(__params)...) ;
                auto&& __algorithm = __foreach.act ;
                auto&& __predicate = __where.act ;
                
                for (auto&& __item : __container)
                    if (__predicate(static_cast<decltype(__item)&&>(__item)))
                        __algorithm(static_cast<decltype(__item)&&>(__item)) ;
            } ;
        }
        
        constexpr auto
        get_interpretor(
            with_node<auto> const& __with, 
            foreach_node<auto> const& __foreach,
            where_node<auto> const& __where, 
            limit_node<auto> const& __limit) const
        {
            return 
            [&] (auto&&... __params) 
            {
                auto&& __container = __with.act(static_cast<decltype(__params)&&>(__params)...) ;
                auto&& __algorithm = __foreach.act ;
                auto&& __predicate = __where.act ;
                auto&& __max = __limit.act(static_cast<decltype(__params)&&>(__params)...) ;
                auto __cpt = 0u ;
                
                for (auto&& __item : __container)
                    if (__predicate(static_cast<decltype(__item)&&>(__item)) && __cpt++ < __max)
                        __algorithm(static_cast<decltype(__item)&&>(__item)) ;
            } ;
        }
    } ;

    extern constexpr auto 
    $linq = dsl<linq>{} ;
}

#endif