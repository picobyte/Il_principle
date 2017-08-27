#ifndef SCHOOL_MANAGEMENT_H
#define SCHOOL_MANAGEMENT_H

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
#include <QStringList>
#include <QTabWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QWidget>
#include "generic.h"
#include "student_tab.h"

class genericTab: public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    QLabel tabLbl;
public:
    genericTab(): grid(this) {
        grid.setContentsMargins(0, 0, 0, 0);
        tabLbl.setPalette(HHStyle::white_text);
        tabLbl.setText(QApplication::translate("MainWindow", "Tab", Q_NULLPTR));
        grid.addWidget(&tabLbl, 0, 0, 1, 1);
    }
};

static const char* teacher[] = {"April Raymund", "Beth Manili", "Carl Walker", "Carmen Smith", "Claire Fuzushi",
                                "Jessica Underwood", "Nina Parker", "Ronda Bells", "Samantha Keller"};

static const char* balance[] = {"Monthly Loan:", "Staff Salary:"};
static const char* balanceExample[] = {"-$16,188", "$2,811"};

class ExpansionsTab: public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    QListView expansionList;
    QLabel upgradeCostLbl, upgradeCostVal;
    QLabel maintenanceCostLbl, maintenanceCostVal;
    QPushButton upgradeBtn;
    QLabel expansionViewLbl;
    QLabel lowInfoLbl;

public:
    ExpansionsTab();
};

class PollicyTab: public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    QListView topicList, ruleList;
    QLabel explanationLbl;
    QLabel topicLbl, RuleLbl, lowInfoLbl;

public:
    PollicyTab();
};

class AssignmentsTab: public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    QTableWidget table;
    QLabel explanationLbl;
    /*TODO: icons*/
    QCheckBox *tchAssignCB[ARRAY_LEN(subjectName)*ARRAY_LEN(teacher)];
    QLabel nameLbl, subjNameLbl, subjExpLbl, genQualfLbl;
    QProgressBar subjExpPB, genQualfPB;

public:
    AssignmentsTab();
};

class JobsTab: public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    QLabel applicants, hiredStaff, biographyLbl, avgSubjExpHdrLbl;
    QPushButton hireFireBtn;
    QListView staffList, applicantsList;
    QLabel biographyVal;
    QLabel *balanceLbl[ARRAY_LEN(balance)];
    QLabel *balanceVal[ARRAY_LEN(balance)];
    QLabel *subLbl[ARRAY_LEN(subjectName)];
    QProgressBar *avgSubjExpVal[ARRAY_LEN(subjectName)];
    QGraphicsView teacherDisplay;
public:
    JobsTab();
};

class SchoolManagement: public QWidget
{
    Q_OBJECT
private:
    QTabWidget mainTab;
    StudentsTab studentsTab;
    JobsTab jobsTab;
    AssignmentsTab assnTab;
    PollicyTab pollicyTab;
    ExpansionsTab expansionsTab;
    QPushButton exitBtn;

public:
    SchoolManagement(QWidget*, QRect geom);
};

#endif // SCHOOL_MANAGEMENT_H
