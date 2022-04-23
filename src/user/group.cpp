#include "group.h"

Mere::Auth::Group::~Group()
{

}

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

std::string Mere::Auth::Group::name() const
{
    return m_name;
}

void Mere::Auth::Group::setName(const std::string &name)
{
    m_name = name;
}

std::vector<std::string> Mere::Auth::Group::members() const
{
    return m_members;
}

void Mere::Auth::Group::addMember(const std::string &member)
{
    m_members.push_back(member);
}

void Mere::Auth::Group::setMembers(std::vector<std::string> members)
{
    m_members.clear();
    for(auto &member : members)
        m_members.push_back(member);
}
