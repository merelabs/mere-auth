#ifndef MERE_AUTH_USER_H
#define MERE_AUTH_USER_H

#include "../global.h"
#include "userprofile.h"
#include "group.h"
#include "type.h"

namespace Mere
{
namespace Auth
{

class MERE_AUTH_LIB_SPEC User
{
public:
    explicit User();

    unsigned int uid() const;
    void setUid(unsigned int uid);

    unsigned int gid() const;
    void setGid(unsigned int gid);

    std::string name() const;
    void setName(const std::string &name);

    std::vector<unsigned int > groups() const;
    void addGroup(unsigned int group);
    void setGroups(std::vector<unsigned int > groups);

    std::string klass() const;

    UserProfile profile() const;
    void setProfile(UserProfile profile);

    enum Type {
        SuperUser  = 1 << 0,
        SystemUser = 1 << 1,
        NormalUser = 1 << 2,
        UnknowUser = 1 << 3,
        All        = 1111
    };

    Type type() const;

private:
    bool isSuperUser() const;
    bool isSystemUser() const;
    bool isUser() const;

private:
    unsigned int m_uid;
    unsigned int m_gid;
    std::string m_name;

    std::vector<unsigned int> m_groups;

    std::string m_klass;

    UserProfile m_profile;
};

}
}

//Q_DECLARE_METATYPE(MereUser);
#endif // MERE_AUTH_USER_H
