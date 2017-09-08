#-------------------------------------------------
#
# Project created by QtCreator 2017-08-17T00:14:13
# (c) Picobyte 2017, GPL2
#-------------------------------------------------

QT	   += core gui
QT	   += charts
QT     += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = il_principle
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000	# disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
                main.cpp \
                mainwindow.cpp \
        location_view.cpp \
        person_interaction.cpp \
        aspectratiopixmaplabel.cpp \
        school_management.cpp \
        student_tab.cpp \
        game.cpp \
        schoolupgrade.cpp \
    statchange.cpp \
    ruleeffect.cpp \
    modifier.cpp \
    person.cpp \
    locationjobdetails.cpp \
    timedata.cpp \
    timeframe.cpp \
    gtime.cpp \
    schoolclass.cpp \
    clubs.cpp \
    classroomassignment.cpp \
    gamecalendar.cpp \
    schoolsubject.cpp \
    schoolclass.cpp \
    populationgenerator.cpp

HEADERS += \
                mainwindow.h \
        stat.h \
        skill.h \
        rule.h \
        schoolsubject.h \
        item.h \
        modifier.h \
        statuseffect.h \
        mind.h \
        range.h \
        classroomassignments.h \
        calendarentry.h \
        gamescenarioconfig \
populationgenerationdata.h \
gamecalendar.h \
notificationmanager.h \
personrelationshipdatabase.h \
populationgenerator.h \
statisticsmanager.h \
timeframe.h \
        adjustment.h \
        person.h \
        visualevent.h \
        location.h \
        locationaddress.h \
        locationjobdetails.h \
        location_view.h \
        person_interaction.h \
        aspectratiopixmaplabel.h \
        school_management.h \
        generic.h \
        timedata.h \
        gametime.h \
        rulechoice.h \
        rulechoicepersongroupchange.h \
        rulechange.h \
        locationpropertychange.h \
        schoolupgrade.h \
        student_tab.h \
        game.h \
        account.h \
        bodysizechange.h \
        statchange.h \
        clubs.h \
        json_macros.h \
        gametime.h \
    gtime.h

FORMS +=

DISTFILES +=
