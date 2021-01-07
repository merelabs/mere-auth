#include "account.h"

Mere::Auth::Account::Account()
{

}

Mere::Auth::Account::Account(const QString &username, const QString &password)
    : m_username(username),
      m_password(password)
{

}

QString Mere::Auth::Account::username() const
{
    return m_username;
}

void Mere::Auth::Account::setUsername(const QString &username)
{
    m_username = username;
}

QString Mere::Auth::Account::password() const
{
    return m_password;
}

void Mere::Auth::Account::setPassword(const QString &password)
{
    m_password = password;
}

