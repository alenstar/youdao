######################################################################
# Automatically generated by qmake (2.01a) ?? 6? 25 09:22:21 2016
######################################################################

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = youdao
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
    DEFINES += DEBUG
}
else{
    CONFIG -= debug release
    CONFIG += release
    QMAKE_CXXFLAGS += -O2
    #DEFINES += USE_TEXTURE
}

CONFIG += static
DEFINES += ELPP_QT_LOGGING    \
          ELPP_STL_LOGGING   \
          ELPP_STRICT_SIZE_CHECK ELPP_UNICODE \
          ELPP_MULTI_LOGGER_SUPPORT \
          ELPP_THREAD_SAFE

DEPENDPATH += . \
              dict \
              cpr/include \
              easyloggingpp/src \
              gumbo-query/src \
              gumbo/include


INCLUDEPATH += . \
               util \
               cpr/include \
               dict \
               easyloggingpp/src \
               gumbo-query/src \
               gumbo/include


# Input
HEADERS += dict/def.h \
           dict/dict.h \
           dict/youdao.h \
           easyloggingpp/src/easylogging++.h \
    ui/querydialog.h \
    ui/querythread.h


SOURCES += dict/main.cpp \
           dict/youdao.cpp \
           gumbo-query/src/Document.cpp \
           gumbo-query/src/Node.cpp \
           gumbo-query/src/Object.cpp \
           gumbo-query/src/Parser.cpp \
           gumbo-query/src/QueryUtil.cpp \
           gumbo-query/src/Selection.cpp \
           gumbo-query/src/Selector.cpp \
    dict/dict.cpp \
    cpr/cpr/auth.cpp \
    cpr/cpr/cookies.cpp \
    cpr/cpr/cprtypes.cpp \
    cpr/cpr/digest.cpp \
    cpr/cpr/error.cpp \
    cpr/cpr/multipart.cpp \
    cpr/cpr/parameters.cpp \
    cpr/cpr/payload.cpp \
    cpr/cpr/proxies.cpp \
    cpr/cpr/session.cpp \
    cpr/cpr/util.cpp \
    tinyxml2/tinyxml2.cpp \
    ui/querydialog.cpp \
    ui/querythread.cpp


LIBS += -lcurl -pthread \
    -Wl,-rpath ./ \
    -L./ \
    $$PWD/gumbo/lib/libgumbo.so

FORMS += \
    ui/querydialog.ui
