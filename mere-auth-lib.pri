LIBTARGET = mere-auth
BASEDIR   = $${PWD}
INCLUDEPATH *= $${BASEDIR}/../include
#LIBS += -L$${DESTDIR}  -L../lib -lmere-auth
LIBS += -L$${BASEDIR}/../lib -lmere-auth
