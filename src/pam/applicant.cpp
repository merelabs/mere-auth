#include "applicant.h"

Mere::Auth::Applicant::Applicant(const std::string &username, const std::string &password)
    : m_accout(username, password)
{

}

const Mere::Auth::Account Mere::Auth::Applicant::account() const
{
    return m_accout;
}

const std::string Mere::Auth::Applicant::username() const
{
    return m_accout.username();
}

const std::string Mere::Auth::Applicant::password() const
{
    return m_accout.password();
}
