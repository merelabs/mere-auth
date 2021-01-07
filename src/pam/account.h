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
    Account(const QString &username, const QString &password);

    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

private:
    QString m_username;
    QString m_password;
};

}
}

#endif // MEREACCOUNT_H
