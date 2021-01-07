#ifndef TYPE_H
#define TYPE_H

#include<type_traits>

namespace Mere
{
namespace Auth
{

enum class AccountType
{
    SuperUser  = 1 << 0,
    SystemUser = 1 << 1,
    User       = 1 << 2,
    UnknowUser = 1 << 3,
    All        = 1 << 4
};

template<typename AccountType>
struct enable_bitmask{
    static const bool enable=true;
};

template<typename E>
typename std::enable_if<enable_bitmask<E>::enable, E>::type
operator|(E lhs, E rhs){
//    using underlying = typename std::underlying_type<E>;
    typedef typename std::underlying_type<E>::type underlying;

    return static_cast<E>(
        static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

}
}


#endif // TYPE_H
