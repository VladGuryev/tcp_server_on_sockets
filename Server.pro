TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    tcp_server.cpp \
    server.cpp

HEADERS += \
    tcp_server.h

QMAKE_CXXFLAGS += -std=c++0x -O0 -Wall -Wextra
LIBS += -lpthread
LIBS += -lwsock32
LIBS += -lws2_32
