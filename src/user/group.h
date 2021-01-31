#ifndef MEREGROUP_H
#define MEREGROUP_H

#include "../global.h"

#include <QString>

namespace Mere
{
namespace Auth
{

class MERE_AUTH_LIBSPEC Group
{
public:
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
//Q_DECLARE_METATYPE(MereGroup);
#endif // MEREGROUP_H
