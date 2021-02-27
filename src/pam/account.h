#ifndef MERE_AUTH_ACCOUNT_H
#define MERE_AUTH_ACCOUNT_H

#include "../global.h"

namespace Mere
{
namespace Auth
{

class MERE_AUTH_LIB_SPEC Account
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

#endif // MERE_AUTH_ACCOUNT_H
