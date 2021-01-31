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

}
}


#endif // TYPE_H
