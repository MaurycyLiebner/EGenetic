QT += gui
TEMPLATE = lib
DEFINES += EGENETIC_LIBRARY

CONFIG += c++14

QMAKE_CFLAGS_RELEASE -= -O1
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -m64 -O3
QMAKE_CXXFLAGS_RELEASE += -m64 -O3

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/eatomiccont.cpp \
    src/econditionvalue.cpp \
    src/eeventloop.cpp \
    src/egenetic.cpp \
    src/egenetic_p.cpp \
    src/eworker.cpp

HEADERS += \
    include/egenetic.h \
    src/eatomiccont.h \
    src/econditionvalue.h \
    src/eeventloop.h \
    src/egenetic_global.h \
    src/egenetic_p.h \
    src/eworker.h \
    src/qeworker.h

