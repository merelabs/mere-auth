#include "userprofile.h"

Mere::Auth::UserProfile::~UserProfile()
{

}

Mere::Auth::UserProfile::UserProfile()
{

}

Mere::Auth::UserProfile::UserProfile(int uid)
    : m_uid(uid)
{

}

std::string Mere::Auth::UserProfile::name() const
{
    return m_name;
}

void Mere::Auth::UserProfile::setName(const std::string &name)
{
    m_name = name;
}

std::string Mere::Auth::UserProfile::home() const
{
    return m_home;
}

void Mere::Auth::UserProfile::setHome(const std::string &home)
{
    m_home = home;
}

std::string Mere::Auth::UserProfile::shell() const
{
    return m_shell;
}

void Mere::Auth::UserProfile::setShell(const std::string &shell)
{
    m_shell = shell;
}

std::vector<Mere::Auth::Group> Mere::Auth::UserProfile::groups() const
{
    return m_groups;
}

void Mere::Auth::UserProfile::addGroup(const Group group)
{
    m_groups.push_back(group);
}

void Mere::Auth::UserProfile::setGroups(const std::vector<Group> groups)
{
    m_groups.clear();
    for(auto &group : groups)
        m_groups.push_back(group);
}

std::string Mere::Auth::UserProfile::icon() const
{
    return m_icon;
}

std::string Mere::Auth::UserProfile::mail() const
{
    return m_mail;
}
