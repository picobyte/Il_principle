/*
 * (c) Picobyte 2017, GPL2
 */
#ifndef SCHOOL_MANAGEMENT_H
#define SCHOOL_MANAGEMENT_H

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QListView>
#include <QLocale>
#include <QProgressBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QSpinBox>
#include <QStackedWidget>
#include <QStringList>
#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QWidget>
#include "generic.h"
#include "student_tab.h"

/*
 * class genericTab: public QWidget
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
*/

static const char* teacher[] = {"April Raymund", "Beth Manili", "Carl Walker", "Carmen Smith", "Claire Fuzushi",
                                "Jessica Underwood", "Nina Parker", "Ronda Bells", "Samantha Keller"};

static const char* balance[] = {"Monthly Loan:", "Staff Salary:"};
static const char* balanceExample[] = {"-$16,188", "$2,811"};

static const char* clubInfo[] = {"Members:", "time:", "Club President:", "Location:", "Weekly Balance:"};
static const char* clubInfoExample[] = {"12", "16:00-18:00", "Anette", "Sports Area", "-$50"};

static const char* balanceItem[] = {
    "State Funding",
    "Principal Salary",
    "Staff Salary",
    "Investigator",
    "Building Maintenance",
    "Cabaret Rental",
    "Bathroom Spycam Pics",
    "Changing Room Spycam Pics",
    "Cheerleading Club Spycam Pics",
    "Swim Club Spycam Pics",
    "Secret Panty Exchange sales",
    "Your Sister's rent"};

static int balanceItemExample[] = {
    18945, 2585, -34563, -3000, -1684, -600, 252, 504, 504, 352, 384, 400};

template <class T> class leftandRightT: public QWidget
{    // template classes cannot have Q_OBJECT, signals or slots. see:
    // http://doc.qt.io/qt-4.8/moc.html
protected:
    QGridLayout grid;
    QLabel leftLbl, rightLbl;
    QPushButton midBtn;
    T leftT, rightT;
    leftandRightT(const char*, const char*, const char*);
};

class AccountingTab: public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    QTableWidget table;
    QLabel balanceLbl, balanceVal;
    QSpacerItem vertStretch;
public:
    AccountingTab();
};

class ClubsTab: public leftandRightT<QListView>
{
    Q_OBJECT
private:
    QLabel *clubInfoLbl[ARRAY_LEN(clubInfo)];
    QLabel *clubInfoVal[ARRAY_LEN(clubInfo)];
    QGraphicsView clubDisplay;
public:
    ClubsTab();
};

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


class JobsTab: public leftandRightT<QListView>
{
    Q_OBJECT
private:
    QLabel biographyLbl, avgSubjExpHdrLbl;
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
    ClubsTab clubsTab;
    AccountingTab accountingTab;
    QPushButton exitBtn;

public:
    SchoolManagement(QWidget*, QRect geom);
};

#endif // SCHOOL_MANAGEMENT_H
