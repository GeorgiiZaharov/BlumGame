TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES +=  \
    gamelabels.cpp \
    gameobjects.cpp \
    gamerenderer.cpp \
    gamescreen.cpp \
    label.cpp \
    main.cpp \
    animation.cpp \
    number.cpp \
    object.cpp

HEADERS +=  \
    animation.h \
    gamelabels.h \
    gameobjects.h \
    gamerenderer.h \
    gamescreen.h \
    label.h \
    number.h \
    object.h

QMAKE_CXXFLAGS += -Wall -Wextra -Werror

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0
LIBS += -lgcov

# путь к заголовочным файлам SFML
INCLUDEPATH += /usr/include

# сами библиотеки SFML
LIBS += -lsfml-graphics -lsfml-window -lsfml-system
