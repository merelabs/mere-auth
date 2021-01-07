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

    QString name() const;
    void setName(QString name);

    std::vector<QString> members() const;
    void addMember(QString member);
    void setMembers(std::vector<QString> members);

private:
    uint32_t       m_gid;
    QString        m_name;
    std::vector<QString> m_members;
};

}
}
//Q_DECLARE_METATYPE(MereGroup);
#endif // MEREGROUP_H
