#ifndef MERE_AUTH_SERVICE_H
#define MERE_AUTH_SERVICE_H

#include "global.h"
#include "pam/account.h"
#include "user/user.h"

#include <pwd.h>
#include <grp.h>

namespace Mere
{
namespace Auth
{

class PAM;

class MERE_AUTH_LIB_SPEC Service
{
public:
    virtual ~Service();
    explicit Service(const std::string &service = "mere");
    bool login(const std::string &username, const std::string &password) const;
    bool logout() const;

    User user(const QString &username) const;
    User user(const std::string &username) const;
    User user(const char *username) const;

    std::vector<User> users(int type = User::Type::All) const;

    Group group(const unsigned int &gid) const;
    std::vector<Group> groups(const char *username, const unsigned int &gid) const;

    bool verify(const std::string &password) const;

private:
    User user(struct passwd *pwd) const;

private:
    std::string m_service;
    PAM *m_pam;
};
}
}

#endif // MERE_AUTH_SERVICE_H
