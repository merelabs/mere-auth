#ifndef MERE_AUTH_PAM_H
#define MERE_AUTH_PAM_H

#include "../global.h"
#include "applicant.h"

#include <pwd.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <security/pam_appl.h>

namespace Mere
{
namespace Auth
{

class MERE_AUTH_LIB_SPEC PAM
{
public:
    ~PAM();
    explicit PAM(const std::string &service, int flags = (PAM_SILENT | PAM_DISALLOW_NULL_AUTHTOK));

    int login(const Applicant &applicant);
    int logout();

private:
    static int fail(int num_msg, struct pam_response **response);
    static int handshake(int num_msg, const struct pam_message **message, struct pam_response **resp, void *data);

private:
    int m_flags;
    const std::string &m_service;

    pam_handle_t *handler;
};

}
}

#endif // MERE_AUTH_PAM_H
