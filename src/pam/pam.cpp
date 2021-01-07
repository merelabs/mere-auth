#include "pam.h"

Mere::Auth::PAM::~PAM()
{

}

Mere::Auth::PAM::PAM(const QString &service, int flags)
    : m_flags(flags),
      m_service(service),
      handler(NULL)
{
}

int Mere::Auth::PAM::login(const Applicant &applicant)
{
    const struct pam_conv converse = { handshake, (void *) &applicant };

    // why target user = NULL?
    const QByteArray bytes = m_service.toUtf8();
    const char *service = bytes.data();
    int result = pam_start(service, NULL, &converse, &handler);
    if( result != PAM_SUCCESS)
    {
        qDebug() << QString("%1: Failed to initiate a PAM transaction.").arg(pam_strerror(handler, result));
        return result;
    }

    // Set information to PAM Server

    // Username
    const QString strUsername = applicant.username();
    const char *username = strUsername.toUtf8().data();
    result = pam_set_item(handler, PAM_RUSER, username);
    if( result != PAM_SUCCESS)
    {
        qDebug() << QString("%1: Failed to set authetication information (PAM_RUSER).").arg(pam_strerror(handler, result));
        pam_end(handler, result);
        return result;
    }

//    result = pam_set_item(pamh, PAM_AUTHTOK, pass);
//    if (result != PAM_SUCCESS)
//    {
//        pam_end(pamh, result);
//        return result;
//    }

    // Hostname
    char hostname[MAXHOSTNAMELEN];
    gethostname(hostname, MAXHOSTNAMELEN);
    result = pam_set_item(handler, PAM_RHOST, hostname);
    if( result != PAM_SUCCESS)
    {
        qDebug() << QString("%1: Failed to set authetication information (PAM_RHOST).").arg(pam_strerror(handler, result));

        pam_end(handler, result);
        return result;
    }

    // Authenticate the applicant
    result = pam_authenticate(handler, m_flags);
    if (result != PAM_SUCCESS)
    {
        qDebug() << QString("%1: Failed to perform authentication within the PAM framework.").arg(pam_strerror(handler, result));

        pam_end(handler, result);
        return result;
    }

    result = pam_acct_mgmt(handler, 0);
    if (result != PAM_SUCCESS)
    {
        qDebug() << QString("%1: Failed to perform PAM account validation procedures.").arg(pam_strerror(handler, result));

        pam_end(handler, result);
        return result;
    }

    result = pam_setcred(handler, PAM_ESTABLISH_CRED);
    if (result != PAM_SUCCESS)
    {
        qDebug() << QString("%1: Failed to modify / delete user credentials for an authentication.").arg(pam_strerror(handler, result));
        pam_end(handler, result);
        return result;
    }

    result = pam_open_session(handler, PAM_SILENT);
    if (result != PAM_SUCCESS)
    {
        qDebug() << QString("%1: Failed to open a user session.").arg(pam_strerror(handler, result));

        pam_setcred(handler, PAM_DELETE_CRED);
        pam_end(handler, result);
        return result;
    }

    /* get mapped user name; PAM may have changed it */
    struct passwd *pwd;
    result = pam_get_item(handler, PAM_USER, (const void **)&username);
    if (result != PAM_SUCCESS || (pwd = getpwnam(username)) == nullptr)
    {
        qDebug() << QString("%1: Failed to get PAM information (PAM_USER).").arg(pam_strerror(handler, result));

        pam_end(handler, result);
        return result;
    }

    /* export PAM environment */
    char **pam_envlist, **pam_env;
    if ((pam_envlist = pam_getenvlist(handler)) != NULL)
    {
        for (pam_env = pam_envlist; *pam_env != NULL; ++pam_env)
        {
            putenv(*pam_env);
            free(*pam_env);
        }
        free(pam_envlist);
    }

    return result;
}

int Mere::Auth::PAM::logout()
{
    int result = pam_close_session(handler, 0);
    if (result != PAM_SUCCESS)
    {
        qDebug() << QString("%1: Failed to close an existing user session.").arg(pam_strerror(handler, result));
        qDebug() << pam_strerror(handler, result);
    }

    result = pam_setcred(handler, PAM_DELETE_CRED);
    if (result != PAM_SUCCESS)
    {
        qDebug() << QString("%1: Failed to modify / delete user credentials for an authentication.").arg(pam_strerror(handler, result));
    }

    pam_end(handler, result);

    return result;
}

//static
int Mere::Auth::PAM::handshake(int num_msg, const struct pam_message **message, struct pam_response **response, void *data)
{
    if (num_msg <= 0 || num_msg > PAM_MAX_NUM_MSG)
            return PAM_CONV_ERR;

    *response = (struct pam_response *) calloc(num_msg, sizeof(struct pam_response));
    if (*response == NULL) return PAM_BUF_ERR;

    Applicant *applicant = static_cast<Applicant *>(data);

    for (int i = 0; i < num_msg; i++)
    {
        (*response)[i].resp = nullptr;
        (*response)[i].resp_retcode = 0;

        switch (message[i]->msg_style)
        {
            // PAM asking for passsowd
            case PAM_PROMPT_ECHO_OFF:
                {
                    const QString str = applicant->password();
                    QByteArray bytes = str.toUtf8();
                    char *passowrd = bytes.data();
                    (*response)[i].resp = strdup(passowrd);
                    if ((*response)[i].resp == nullptr)
                            return fail(num_msg, response);
                }
                break;

            // PAM asking for username
            case PAM_PROMPT_ECHO_ON:
                {
                    const QString str = applicant->username();
                    QByteArray bytes = str.toUtf8();
                    char *username = bytes.data();

                    (*response)[i].resp = strdup(username);
                    if ((*response)[i].resp == NULL)
                            return fail(num_msg, response);
                }
                break;

            case PAM_ERROR_MSG:
                qCritical() << message[i]->msg;
                break;

            case PAM_TEXT_INFO:
                qInfo() << message[i]->msg;
                break;

            default:
                return fail(num_msg, response);
        }
    }

    return PAM_SUCCESS;
}

//static
int Mere::Auth::PAM::fail(int num_msg, struct pam_response **response)
{
    for (int i = 0; i < num_msg; i++)
    {
            if ((*response)[i].resp != nullptr)
            {
                 free((*response)[i].resp);
                 (*response)[i].resp = nullptr;
            }
    }
    *response = nullptr;

    return PAM_CONV_ERR;
}
