/*
 * (c) Picobyte 2017, GPL2
 */
#ifndef STUDENT_TAB_H
#define STUDENT_TAB_H

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QListView>
#include <QProgressBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QSpinBox>
#include <QStackedWidget>
#include <QTabWidget>
#include <QWidget>
#include "generic.h"

static const char* period[] = {"7:50-9:20", "9:40-11:10", "11:30-13:00", "14:30-16:00"};
static const char* weekday[] = {"Monday", "Tuesday", "Wednesday", "Thirsday", "Friday", "Saturday", "Sunday"};

static const char* subject[] = {"Mathematics:", "Language Arts:", "Natural Science:", "Life Science:", "Computer Studies:", "Social Science:", "Humanities:", "Fine Arts:", "Physical Education:", "Sexual Education:"};

static const char* studentInfo[] = {"Birthday:", "Age:", "Family:", "Location:", "Club:", "Personality:"};

static const char* studentInfoEG[] = {"1/1/2012", "18", "Owen", "Home", "Cheerleaders", "Cheerful"};

// should be read from json..
static const char* subjectName[] = {"Anatomy Class", "Art", "Biology", "Bondage Class", "Chemistry",
                                       "Computer Science", "Economics", "English", "Geography", "History",
                                       "Math", "Music", "Philosophy", "Physics", "Practical Sex Education",
                                       "Religion", "School Sport", "Swimming", "Theoretical Sex Education"};

static const int no_workdays = ARRAY_LEN(weekday)-2;

class SchlMngStudentClasses: public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    QLabel *periodLbl[ARRAY_LEN(period)], *dayLbl[no_workdays], *lunch_break;
    QComboBox *classSchedule[ARRAY_LEN(period)*no_workdays];
    QLabel curriculumLbl;
public:
    SchlMngStudentClasses();
};

class SchlMngClassSummary: public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    QLabel classSummaryLbl, aSFELbl;
    QLabel *subjLbl[ARRAY_LEN(subject)];
    QProgressBar subjBar[ARRAY_LEN(subject)];
    QSpacerItem vertStretch;
public:
    SchlMngClassSummary();
};

class SchlMngStudents: public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    QCheckBox favoritesOnly, favorite;
    QLabel studentName, sbjScoreLbl;
    QComboBox transferCmb;
    QPushButton transferBtn;
    QListView studentsList;
    QLabel *statLbl[ARRAY_LEN(studentInfo)];
    QLabel *statVal[ARRAY_LEN(studentInfo)];
    QLabel *subjLbl[ARRAY_LEN(subjectName)];
    QProgressBar subjBar[ARRAY_LEN(subjectName)];
    QGraphicsView graphicsView;
public:
    SchlMngStudents();
};

class StudentsTab: public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    QLabel classesLbl;
    QPushButton distrBtn;
    QSpinBox spinBox;
    QListView listView;
    QWidget tabW;
    QTabWidget tab;
    SchlMngStudentClasses timetableW;
    SchlMngClassSummary classSummaryW;
    SchlMngStudents studentsW;
public:
    StudentsTab(QRect geom);
};

#endif // STUDENT_TAB_H
