#include "group.h"

Mere::Auth::Group::Group()
{

}

uint32_t Mere::Auth::Group::gid() const
{
    return m_gid;
}

void Mere::Auth::Group::setGid(uint32_t gid)
{
    m_gid = gid;
}

QString Mere::Auth::Group::name() const
{
    return m_name;
}

void Mere::Auth::Group::setName(QString name)
{
    m_name = name;
}

std::vector<QString> Mere::Auth::Group::members() const
{
    return m_members;
}

void Mere::Auth::Group::addMember(QString member)
{
    m_members.push_back(member);
}

void Mere::Auth::Group::setMembers(std::vector<QString> members)
{
    m_members.clear();
    for(auto &member : members)
        m_members.push_back(member);
}
