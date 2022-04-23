#ifndef MERE_AUTH_USER_GROUP_H
#define MERE_AUTH_USER_GROUP_H

#include "../global.h"

#include <vector>

namespace Mere
{
namespace Auth
{

class MERE_AUTH_LIB_SPEC Group
{
public:
    virtual ~Group();
    Group();

    uint32_t gid() const;
    void setGid(uint32_t gid);

    std::string name() const;
    void setName(const std::string &name);

    std::vector<std::string> members() const;
    void addMember(const std::string &member);
    void setMembers(std::vector<std::string> members);

private:
    uint32_t       m_gid;
    std::string    m_name;
    std::vector<std::string> m_members;
};

}
}

#endif // MERE_AUTH_USER_GROUP_H
