#include "cli.h"

#include "mere/auth/service.h"

#include <iostream>

#include <QCommandLineParser>

Cli::Cli(QObject *parent) : QObject(parent)
{

}

void Cli::run()
{
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption usernameOption(QStringList() << "u" << "username",
                                      QCoreApplication::translate("main", "Set the username"),
                                      "username");

    QCommandLineOption passwordOption(QStringList() << "p" << "password",
                                      QCoreApplication::translate("main", "Set the username"),
                                      "password");

    QCommandLineOption serviceOption(QStringList() << "s" << "service",
                                      QCoreApplication::translate("service", "Set the service"),
                                      "service", "mere");

    QCommandLineOption userListOption(QStringList() << "l" << "list",
                                      QCoreApplication::translate("main", "List all of the users"));

    parser.addOption(usernameOption);
    parser.addOption(passwordOption);
    parser.addOption(serviceOption);
    parser.addOption(userListOption);

    parser.process(QCoreApplication::arguments());

    if(parser.isSet(userListOption))
    {
        Mere::Auth::Service service;

        for (const auto &user : service.users(Mere::Auth::User::Type::SuperUser | Mere::Auth::User::Type::NormalUser))
        {
            std::cout << user.name() << user.profile().home() << user.profile().shell() << std::endl;
        }
    }
    else
    {
        QString username = parser.value(usernameOption);
        QString password = parser.value(passwordOption);

        Mere::Auth::Service service(parser.value(serviceOption).toStdString());
        bool ok = service.login(username.toStdString(), password.toStdString());
        if (ok)
        {
            std::cout << "Yes, a valid user of this system." << std::endl;

            try
            {
                Mere::Auth::User user = service.user(username);
                std::cout << "Username:" << user.name() << std::endl;
                std::cout << "Uid:" << user.uid() << std::endl;
                std::cout << "Gid:" << user.gid() << std::endl;
                std::cout << "Name:" << user.profile().name() << std::endl;

                Mere::Auth::UserProfile profile = user.profile();
                for (const auto &group : profile.groups())
                {
                    std::cout << "Gid:" << group.gid() << std::endl;
                    std::cout << "Name:" << group.name() << std::endl;
                    for (const auto &member : group.members())
                    {
                        std::cout << "Member:" << member << std::endl;
                    }
                }
            }
            catch(std::exception &ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }
        else
        {
            std::cout << "Sorry, not a valid user of this system." << std::endl;

        }
    }
    emit done();
}
