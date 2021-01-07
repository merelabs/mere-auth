#include "applicant.h"

Mere::Auth::Applicant::Applicant(const QString &username, const QString &password)
    : m_accout(username, password)
{

}

const Mere::Auth::Account Mere::Auth::Applicant::account() const
{
    return m_accout;
}

const QString Mere::Auth::Applicant::username() const
{
    return m_accout.username();
}

const QString Mere::Auth::Applicant::password() const
{
    return m_accout.password();
}
