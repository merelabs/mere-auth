#ifndef MEREUSERPROFILE_H
#define MEREUSERPROFILE_H

#include "../global.h"
#include "group.h"

namespace Mere
{
namespace Auth
{

class MERE_AUTH_LIBSPEC UserProfile
{
public:
    ~UserProfile();
    UserProfile();
    explicit UserProfile(int uid);

    QString name() const;
    void setName(const QString name);

    QString home() const;
    void setHome(QString home);

    QString shell() const;
    void setShell(QString shell);

    std::vector<Group> groups() const;
    void addGroup(const Group group);
    void setGroups(const std::vector<Group> groups);

    QString icon() const;
    QString mail() const;

private:
    unsigned int m_uid;
    QString m_name;
    QString m_home;
    QString m_shell;

    std::vector<Group> m_groups;

    QString m_icon;
    QString m_mail;
};

}
}

//Q_DECLARE_METATYPE(UserProfile);

#endif // MEREUSERPROFILE_H
