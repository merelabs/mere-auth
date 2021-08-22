#include "pam.h"

#include <iostream>

Mere::Auth::PAM::~PAM()
{

}

Mere::Auth::PAM::PAM(const std::string &service, int flags)
    : m_flags(flags),
      m_service(service),
      handler(NULL)
{
}

int Mere::Auth::PAM::login(const Applicant &applicant)
{
    const struct pam_conv converse = { handshake, (void *) &applicant };

    // why target user = NULL?
    const char *service = m_service.c_str();
    int result = pam_start(service, applicant.username().c_str(), &converse, &handler);
    if( result != PAM_SUCCESS)
    {
        std::cout << pam_strerror(handler, result) << std::endl;
        return result;
    }

    if ((result = pam_set_item(handler, PAM_TTY, getenv("DISPLAY"))) != PAM_SUCCESS)
    {
        std::cout << "PAM: %s" << pam_strerror(handler, result) << std::endl;
        return result;
    }

    // Set information to PAM Server

    // Username
    const std::string strUsername = applicant.username();
    if (strUsername.length() == 0) return 1;

    const char *username = strUsername.c_str();
    result = pam_set_item(handler, PAM_RUSER, username);
    if( result != PAM_SUCCESS)
    {
        std::cout << pam_strerror(handler, result) << std::endl;
        pam_end(handler, result);
        return result;
    }

//    result = pam_set_item(handler, PAM_AUTHTOK, applicant.password().c_str());
//    if (result != PAM_SUCCESS)
//    {
//        pam_end(handler, result);
//        return result;
//    }

    // Hostname
    char hostname[MAXHOSTNAMELEN];
    gethostname(hostname, MAXHOSTNAMELEN);
    result = pam_set_item(handler, PAM_RHOST, hostname);
    if( result != PAM_SUCCESS)
    {
        std::cout << pam_strerror(handler, result) << std::endl;
        pam_end(handler, result);
        return result;
    }

    // Authenticate the applicant
    result = pam_authenticate(handler, m_flags);
    if (result != PAM_SUCCESS)
    {
        std::cout << pam_strerror(handler, result) << std::endl;
        pam_end(handler, result);
        return result;
    }

    result = pam_acct_mgmt(handler, 0);
    if (result != PAM_SUCCESS)
    {
        std::cout << pam_strerror(handler, result) << std::endl;
        pam_end(handler, result);
        return result;
    }

    result = pam_setcred(handler, PAM_ESTABLISH_CRED);
    if (result != PAM_SUCCESS)
    {
        std::cout << pam_strerror(handler, result) << std::endl;
        pam_end(handler, result);
        return result;
    }

    result = pam_open_session(handler, PAM_SILENT);
    if (result != PAM_SUCCESS)
    {
        std::cout << pam_strerror(handler, result) << std::endl;

        pam_setcred(handler, PAM_DELETE_CRED);
        pam_end(handler, result);
        return result;
    }

    /* get mapped user name; PAM may have changed it */
    struct passwd *pwd;
    result = pam_get_item(handler, PAM_USER, (const void **)&username);
    if (result != PAM_SUCCESS || (pwd = getpwnam(username)) == nullptr)
    {
        std::cout << pam_strerror(handler, result) << std::endl;

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
        std::cerr << pam_strerror(handler, result) << std::endl;
        return result;
    }

    result = pam_setcred(handler, PAM_DELETE_CRED);
    if (result != PAM_SUCCESS)
    {
        std::cerr << pam_strerror(handler, result) << std::endl;
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
                    const std::string strPassword = applicant->password();
                    const char *passowrd = strPassword.c_str();
                    (*response)[i].resp = strdup(passowrd);
                    if ((*response)[i].resp == nullptr)
                            return fail(num_msg, response);
                }
                break;

            // PAM asking for username
            case PAM_PROMPT_ECHO_ON:
                {
                    const std::string strUsername = applicant->username();
                    const char *username = strUsername.c_str();

                    (*response)[i].resp = strdup(username);
                    if ((*response)[i].resp == NULL)
                            return fail(num_msg, response);
                }
                break;

            case PAM_ERROR_MSG:
                std::cerr << message[i]->msg << std::endl;
                break;

            case PAM_TEXT_INFO:
                std::cout  << message[i]->msg << std::endl;
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
