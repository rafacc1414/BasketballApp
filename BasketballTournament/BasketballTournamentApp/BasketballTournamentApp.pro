#-------------------------------------------------
#
# Project created by QtCreator 2022-03-14T20:21:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BasketballTournamentApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    load_teams.cpp \
    tabs/team_information.cpp \
    team.cpp \
    basketball_player.cpp \
    tabs/tournament_bracket.cpp \
    tabs/classification.cpp \
    tabs/best_players.cpp

HEADERS += \
    mainwindow.h \
    load_teams.h \
    tabs/team_information.h \
    team.h \
    basketball_player.h \
    tabs/tournament_bracket.h \
    tabs/classification.h \
    tabs/best_players.h \

FORMS += \
    mainwindow.ui \
    load_teams.ui \
    tabs/team_information.ui
