#include "account.h"

Mere::Auth::Account::Account()
{

}

Mere::Auth::Account::Account(const std::string &username, const std::string &password)
    : m_username(username),
      m_password(password)
{

}

std::string Mere::Auth::Account::username() const
{
    return m_username;
}

void Mere::Auth::Account::setUsername(const std::string &username)
{
    m_username = username;
}

std::string Mere::Auth::Account::password() const
{
    return m_password;
}

void Mere::Auth::Account::setPassword(const std::string &password)
{
    m_password = password;
}

