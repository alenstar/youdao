INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
PUBLIC_HEADERS         += $$PWD/../gumbo-parser/src/attribute.h \
                          $$PWD/../gumbo-parser/src/parser.h \
                          $$PWD/../gumbo-parser/src/gumbo.h \



SOURCES                += $$PWD/../gumbo-parser/src/attribute.c \
$$PWD/../gumbo-parser/src/error.c \
$$PWD/../gumbo-parser/src/string_buffer.c \
$$PWD/../gumbo-parser/src/tag.c \
$$PWD/../gumbo-parser/src/utf8.c \
$$PWD/../gumbo-parser/src/vector.c \
$$PWD/../gumbo-parser/src/char_ref.c \
$$PWD/../gumbo-parser/src/parser.c \
$$PWD/../gumbo-parser/src/string_piece.c \
$$PWD/../gumbo-parser/src/tokenizer.c \
$$PWD/../gumbo-parser/src/util.c \


#unix {
#    SOURCES            += $$PWD/qextserialport_unix.cpp
#    linux* {
#        SOURCES        += $$PWD/qextserialenumerator_linux.cpp
#    } else:macx {
#        SOURCES        += $$PWD/qextserialenumerator_osx.cpp
#    } else {
#        SOURCES        += $$PWD/qextserialenumerator_unix.cpp
#    }
#}
#win32:SOURCES          += $$PWD/qextserialport_win.cpp \
#                          $$PWD/qextserialenumerator_win.cpp

linux*{
    #!qesp_linux_udev:DEFINES += QESP_NO_UDEV
    #qesp_linux_udev: LIBS += -ludev
}

#macx:LIBS              += -framework IOKit -framework CoreFoundation
#win32:LIBS             += -lsetupapi -ladvapi32 -luser32

# moc doesn't detect Q_OS_LINUX correctly, so add this to make it work
linux*:DEFINES += __linux__
