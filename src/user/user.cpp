#include "user.h"
#include "profile.h"

#include "mere/utils/stringutils.h"

Mere::Auth::User::~User()
{

}

Mere::Auth::User::User()
    : m_groups(10)
{

}

unsigned int Mere::Auth::User::uid() const
{
    return m_uid;
}

void Mere::Auth::User::setUid(unsigned int uid)
{
    m_uid = uid;
}

unsigned int Mere::Auth::User::gid() const
{
    return m_gid;
}

void Mere::Auth::User::setGid(unsigned int gid)
{
    m_gid = gid;
}

std::string Mere::Auth::User::name() const
{
    return m_name;
}

void Mere::Auth::User::setName(const std::string &name)
{
    m_name = name;
}

std::vector<unsigned int> Mere::Auth::User::groups() const
{
    return m_groups;
}

void Mere::Auth::User::addGroup(unsigned int group)
{
    m_groups.push_back(group);
}

void Mere::Auth::User::setGroups(std::vector<unsigned int> groups)
{
    m_groups.clear();

    for(auto &group : groups)
        m_groups.push_back(group);
}

std::string Mere::Auth::User::klass() const
{
    return m_klass;
}

Mere::Auth::User::Type Mere::Auth::User::type() const
{
    if (isSuperUser()) return Type::SuperUser;
    else if (isSystemUser()) return Type::SystemUser;
    else if (isUser()) return Type::NormalUser;

    return Type::UnknowUser;
}

Mere::Auth::Profile Mere::Auth::User::profile() const
{
    return m_profile;
}

void Mere::Auth::User::setProfile(Mere::Auth::Profile profile)
{
    m_profile = profile;
}

bool Mere::Auth::User::isSuperUser() const
{
    return (this->uid() == 0 && this->gid() == 0);
}

bool Mere::Auth::User::isSystemUser() const
{
    return (this->uid() > 0 && this->uid() < 1000
            &&
            this->gid() > 0 && this->gid() < 1000);
}

bool Mere::Auth::User::isUser() const
{
    // Is this a valid check?
    if (this->uid() < 1000 && this->gid() < 1000)
        return false;

    // No Login Shell
    const std::string shell = this->profile().shell();
    if (Mere::Utils::StringUtils::isEndsWidth(shell, "nologin"))
        return false;

    // No Home
    const std::string home = this->profile().home();
    if (home.compare("/nonexistent") == 0)
        return false;

    return true;
}
