TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0

LIBS += -lgcov

# Подключаем библиотеки Boost и SFML
INCLUDEPATH += /usr/include

# Подключаем Boost
LIBS += -lboost_unit_test_framework

# Подключаем SFML
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

HEADERS +=  \
    ../app/animation.h \
    ../app/object.h

SOURCES +=  \
    ../app/animation.cpp \
    ../app/object.cpp \
    animation_logic_test.cpp \
    main.cpp \
    object_logic_test.cpp

INCLUDEPATH += ../app
