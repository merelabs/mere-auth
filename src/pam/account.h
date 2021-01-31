#ifndef MEREACCOUNT_H
#define MEREACCOUNT_H

#include "../global.h"

namespace Mere
{
namespace Auth
{

class MERE_AUTH_LIBSPEC Account
{
public:
    Account();
    Account(const std::string &username, const std::string &password);

    std::string username() const;
    void setUsername(const std::string &username);

    std::string password() const;
    void setPassword(const std::string &password);

private:
    std::string m_username;
    std::string m_password;
};

}
}

#endif // MEREACCOUNT_H
