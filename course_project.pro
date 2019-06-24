TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    token.cpp \
    condition_parser.cpp \
    date.cpp \
    database.cpp \
    condition_parser_test.cpp \
    node.cpp

HEADERS += \
    token.h \
    condition_parser.h \
    date.h \
    database.h \
    node.h \
    test_runner.h \
    tests.h
