#include "service.h"
#include "pam/applicant.h"
#include "pam/pam.h"

#include "mere/utils/stringutils.h"

Mere::Auth::Service::~Service()
{
    if (m_pam != nullptr)
    {
        delete m_pam;
        m_pam = nullptr;
    }
}

Mere::Auth::Service::Service(const QString &service, QObject *parent)
    : QObject(parent),
      m_service(service),
      m_pam(new PAM(m_service))
{
}

bool Mere::Auth::Service::login(const QString &username, const QString &password)
{
    if ( Mere::Utils::StringUtils::isBlank(username) || Mere::Utils::StringUtils::isBlank(password))
    {
        qDebug() << "Username and/or passord can not be empty!";
        return false;
    }

    Applicant applicant(username, password);

    int result = m_pam->login(applicant);
    if (result == 0)
        emit authenticated(user(username));

    return result == 0;
}

bool Mere::Auth::Service::logout()
{
    return false;
}

Mere::Auth::User Mere::Auth::Service::user(const QString &username) const
{
    std::string str = username.toStdString();

    return this->user(str);
}

Mere::Auth::User Mere::Auth::Service::user(const std::string &username) const
{
    const char* ptr = username.c_str();

    return user(ptr);
}

Mere::Auth::User Mere::Auth::Service::user(const char *username) const
{
    if(Mere::Utils::StringUtils::isBlank(username))
        throw std::invalid_argument("username can not be empty.");

    Mere::Auth::User user;

    struct passwd *pw = getpwnam(username);
    if (pw == nullptr)
        throw std::runtime_error(std::string(username).append(" : no such user"));

    return this->user(pw);
}

std::vector<Mere::Auth::User> Mere::Auth::Service::users(User::Type type) const
{
    std::vector<Mere::Auth::User> users;

    struct passwd *pw;
    while ((pw = getpwent()) != nullptr)
    {
        Mere::Auth::User user = this->user(pw);
        if (user.type() & type)
            users.push_back(user);
    }

    endpwent();

    return users;
}

std::vector<Mere::Auth::Group> Mere::Auth::Service::groups(const char *username, const unsigned int &gid) const
{
    if(Mere::Utils::StringUtils::isBlank(username))
        throw std::invalid_argument("username can not be empty.");

    std::vector<Group> groups;

    long ngroups_max = sysconf(_SC_NGROUPS_MAX) + 1;

    gid_t *grps = (unsigned int *) malloc(sizeof(gid_t) * ngroups_max);
    if (grps == nullptr)
        throw std::runtime_error("failed to allocate memory ofr groups.");

    int ngroups = (int) ngroups_max;
    getgrouplist(username, gid, grps, &ngroups);
    for (int i = 0; i < ngroups; i++)
        groups.push_back(group(grps[i]));

    free(grps);

    return groups;
}

Mere::Auth::Group Mere::Auth::Service::group(const unsigned int &gid) const
{
    Group group;

    struct group *grp = getgrgid(gid);
    if (grp == nullptr)
        throw std::runtime_error(std::to_string(gid).append(" : no such group"));

    group.setGid(gid);
    group.setName(grp->gr_name);

    for (int i = 0; grp->gr_mem[i] != nullptr; i++)
       group.addMember(grp->gr_mem[i]);

    return group;
}

Mere::Auth::User Mere::Auth::Service::user(struct passwd *pwd) const
{
    Mere::Auth::User user;

    user.setUid(pwd->pw_uid);
    user.setGid(pwd->pw_gid);
    user.setName(pwd->pw_name);

    Mere::Auth::UserProfile profile;
    profile.setName(pwd->pw_gecos);
    profile.setHome(pwd->pw_dir);
    profile.setShell(pwd->pw_shell);

    std::vector<Group> groups = this->groups(pwd->pw_name, pwd->pw_gid);
    profile.setGroups(groups);

    user.setProfile(profile);

    return user;
}
