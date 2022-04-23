#include "profile.h"

Mere::Auth::Profile::~Profile()
{

}

Mere::Auth::Profile::Profile()
{

}

Mere::Auth::Profile::Profile(int uid)
    : m_uid(uid)
{

}

std::string Mere::Auth::Profile::name() const
{
    return m_name;
}

void Mere::Auth::Profile::setName(const std::string &name)
{
    m_name = name;
}

std::string Mere::Auth::Profile::home() const
{
    return m_home;
}

void Mere::Auth::Profile::setHome(const std::string &home)
{
    m_home = home;
}

std::string Mere::Auth::Profile::shell() const
{
    return m_shell;
}

void Mere::Auth::Profile::setShell(const std::string &shell)
{
    m_shell = shell;
}

std::vector<Mere::Auth::Group> Mere::Auth::Profile::groups() const
{
    return m_groups;
}

void Mere::Auth::Profile::addGroup(const Group group)
{
    m_groups.push_back(group);
}

void Mere::Auth::Profile::setGroups(const std::vector<Group> groups)
{
    m_groups.clear();
    for(auto &group : groups)
        m_groups.push_back(group);
}

std::string Mere::Auth::Profile::icon() const
{
    return m_icon;
}

std::string Mere::Auth::Profile::mail() const
{
    return m_mail;
}
