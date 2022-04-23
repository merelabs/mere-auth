#ifndef MERE_AUTH_PAM_APPLICANT_H
#define MERE_AUTH_PAM_APPLICANT_H

#include "../global.h"
#include "account.h"

namespace Mere
{
namespace Auth
{

class Account;

class MERE_AUTH_LIB_SPEC Applicant
{
public:
    virtual ~Applicant();
    explicit Applicant(const std::string &username, const std::string &password);

    const std::string username() const;
    const std::string password() const;
    const Account account() const;

private:
    const Account m_accout;
};

}
}

#endif // MERE_AUTH_PAM_APPLICANT_H
