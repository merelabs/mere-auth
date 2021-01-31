#ifndef MEREAUTH_H
#define MEREAUTH_H

#include "global.h"
#include "pam/account.h"
#include "user/user.h"

#include <pwd.h>
#include <grp.h>

#include <QObject>

namespace Mere
{
namespace Auth
{

class PAM;

class MERE_AUTH_LIBSPEC Service : public QObject
{
    Q_OBJECT
public:
    ~Service();
    explicit Service(const std::string &service = "mere", QObject *parent = nullptr);
    bool login(const std::string &username, const std::string &password);
    bool logout();

    User user(const QString &username) const;
    User user(const std::string &username) const;
    User user(const char *username) const;

    std::vector<User> users(int type = User::Type::All) const;

    Group group(const unsigned int &gid) const;
    std::vector<Group> groups(const char *username, const unsigned int &gid) const;

private:
    User user(struct passwd *pwd) const;

signals:
    void authenticated(User user);

public slots:

private:
    std::string m_service;
    PAM *m_pam;

};
}
}

#endif // MEREAUTH_H
