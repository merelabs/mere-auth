#ifndef MERE_AUTH_APPLICANT_H
#define MERE_AUTH_APPLICANT_H

#include "../global.h"
#include "account.h"

namespace Mere
{
namespace Auth
{

class Account;

class MERE_AUTH_LIBSPEC Applicant
{
public:
    explicit Applicant(const QString &username, const QString &password);

    const QString username() const;
    const QString password() const;
    const Account account() const;

private:
    const Account m_accout;
};

}
}

#endif // MERE_AUTH_APPLICANT_H
