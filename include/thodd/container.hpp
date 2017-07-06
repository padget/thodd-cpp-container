#ifndef __THODD_CONTAINER_HPP__
#  define __THODD_CONTAINER_HPP__

#  include <thodd/dsl.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/container/functional.hpp>

#  include <type_traits>

namespace
thodd
{
    enum class 
    container
    {
        with, 
        map,
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
                push_back (
                    __target (), 
                    static_cast<decltype(__item)&&>(__item)) ; 
            }) ;
    } ;


    extern constexpr auto
    map = 
    [] (auto&& ... __mapper) 
    {
        return 
        as_node (
            std::integral_constant<
                container, 
                container::map>{}, 
            [&] () 
            {
                return
                std::make_tuple(
                    static_cast<decltype(__mapper)&&>(__mapper)...) ; 
            }) ;
    } ;


    extern constexpr auto
    where = 
    [] (auto&& __algorithm) 
    {
        return 
        as_node (
            std::integral_constant<
                container, 
                container::where>{},
            static_cast<decltype(__algorithm)&&>(__algorithm)) ;
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
    using cquel_node = node<container, id_c, act_t> ;

    template <typename act_t>
    using with_node = cquel_node<container::with, act_t> ;

    template <typename act_t>
    using foreach_node = cquel_node<container::foreach, act_t> ;

    template <typename act_t>
    using where_node = cquel_node<container::where, act_t> ;
    
    template <typename act_t>
    using sort_node = cquel_node<container::sort, act_t> ;

    template <typename act_t>
    using limit_node = cquel_node<container::limit, act_t> ;

    template <typename act_t>
    using map_node = cquel_node<container::map, act_t> ;

    struct cquel 
    {
        constexpr auto
        get_interpretor(
            with_node<auto>    const& __with, 
            map_node<auto>     const& __map,
            foreach_node<auto> const& __foreach, 
            where_node<auto>   const& __where, 
            limit_node<auto>   const& __limit) const
        {
            return 
            [=] (auto && ... __params)
            {
                auto&& __container = __with.act(static_cast<decltype(__params)&&>(__params)...) ;
                auto&& __mapper    = std::get<0>(__map.act()) ;
                auto&& __algorithm = __foreach.act ;
                auto&& __predicate = __where.act ;
                auto&& __max       = __limit.act(static_cast<decltype(__params)&&>(__params)...) ;
                auto __cpt = 0u ;

                for (auto&& __item : __container)
                    if (__predicate(__mapper(static_cast<decltype(__item)&&>(__item))) && (__max == -1 || __cpt++ < __max))
                        __algorithm(__mapper(static_cast<decltype(__item)&&>(__item))) ; 
            } ;
        }

        constexpr auto
        get_interpretor(
            with_node<auto>    const& __with, 
            foreach_node<auto> const& __foreach) const
        {
            constexpr auto map_node_default = [] { return std::make_tuple($0) ; } ;
           
            return 
            get_interpretor ( 
                __with,
                map_node<decltype(map_node_default)> { map_node_default }, 
                __foreach, 
                where_node<decltype(val(true))> { val(true) }, 
                limit_node<decltype(val(-1))> { val(-1) }) ;
        }

        constexpr auto
        get_interpretor(
            with_node<auto>    const& __with, 
            foreach_node<auto> const& __foreach,
            limit_node<auto>   const& __limit) const
        {
            constexpr auto map_node_default = [] { return std::make_tuple($0) ; } ;

            return 
            get_interpretor (
                __with,
                map_node<decltype(map_node_default)> { map_node_default },
                __foreach, 
                where_node<decltype(val(true))> { val(true) }, 
                __limit) ;
        }


        constexpr auto
        get_interpretor(
            with_node<auto>    const& __with, 
            foreach_node<auto> const& __foreach,
            where_node<auto>   const& __where) const
        {
            constexpr auto map_node_default = [] { return std::make_tuple($0) ; } ;

            return 
            get_interpretor (
                __with,
                map_node<decltype(map_node_default)> { map_node_default },
                __foreach, 
                __where, 
                limit_node<decltype(val(-1))> { val(-1) }) ;
        }
        
        constexpr auto
        get_interpretor(
            with_node<auto> const& __with, 
            foreach_node<auto> const& __foreach,
            where_node<auto> const& __where, 
            limit_node<auto> const& __limit) const
        {
            constexpr auto map_node_default = [] { return std::make_tuple($0) ; } ;

            return 
            get_interpretor (
                __with,
                map_node<decltype(map_node_default)> { map_node_default },
                __foreach, 
                __where, 
                __limit) ;
        }

        constexpr auto
        get_interpretor(
            with_node<auto> const& __with, 
            map_node<auto> const& __map, 
            foreach_node<auto> const& __foreach) const
        {
            constexpr auto true___ = [] (...) { return true; } ;
            
            return 
            get_interpretor (
                __with,
                __map, 
                __foreach, 
                where_node<decltype(val(true))> { val(true) }, 
                limit_node<decltype(val(-1))> { val(-1) }) ;
        }
    } ;


    extern constexpr auto 
    $cquel = dsl<cquel>{} ;
}

#endif