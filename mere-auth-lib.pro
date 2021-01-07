QT = core

CONFIG += c++11
CONFIG += shared

TARGET   = mere-auth
VERSION  = 0.0.1b
TEMPLATE = lib

DEFINES += LIB_CODE=\\\"auth\\\"
DEFINES += LIB_NAME=\\\"$$TARGET\\\"
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"
DEFINES += QT_DEPRECATED_WARNINGS MERE_AUTH_LIB

SOURCES += \
    src/pam/account.cpp \
    src/pam/applicant.cpp \
    src/pam/pam.cpp \
    src/service.cpp \
    src/user/group.cpp \
    src/user/user.cpp \
    src/user/userprofile.cpp

HEADERS += \
    src/pam/account.h \
    src/pam/applicant.h \
    src/global.h \
    src/pam/pam.h \
    src/service.h \
    src/user/group.h \
    src/user/type.h \
    src/user/user.h \
    src/user/userprofile.h

DESTDIR = $$PWD/../lib

INCLUDEPATH += /usr/local/include

LIBS += -lpam
LIBS += -lmere-utils

defineTest(copy) {
    source = $$1
    target = $$2

#    $$QMAKE_MKDIR $$quote($$target)

    for(file, source) {
        sdir = $${dirname(file)}
        sdir = $$replace(sdir, "src", "")
        path = $${target}$${sdir}

        QMAKE_POST_LINK += $$QMAKE_MKDIR $$quote($$path) $$escape_expand(\\n\\t)
        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$file) $$quote($$path) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

copy($$HEADERS, $$PWD/../include/mere/auth)

#
# Install
#
unix {
    target.path = /usr/local/lib
    INSTALLS += target

    INSTALL_PREFIX = /usr/local/include/mere/auth
    for(header, HEADERS) {
        sdir = $${dirname(header)}
        sdir = $$replace(sdir, "src", "")
        path = $${INSTALL_PREFIX}$${sdir}

        eval(headers_$${path}.files += $$header)
        eval(headers_$${path}.path = $$path)
        eval(INSTALLS *= headers_$${path})
    }

    config.files= $$PWD/../etc/mere
    config.path = /usr/local/etc/pam.d/
    INSTALLS += config
}
