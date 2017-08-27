/*
 * (c) Picobyte 2017, GPL2
 */

#include "school_management.h"

ExpansionsTab::ExpansionsTab(): grid(this), expansionList(this),
  upgradeCostLbl(QApplication::translate("MainWindow","Upgrade Cost:", Q_NULLPTR)),
  maintenanceCostLbl(QApplication::translate("MainWindow","Maintenance Cost:", Q_NULLPTR)),
  upgradeBtn(QApplication::translate("MainWindow", "Upgrade", Q_NULLPTR))
{
    grid.setContentsMargins(0, 0, 0, 0);

    upgradeBtn.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grid.addWidget(&upgradeBtn, 0, 0, 2, 1);
    grid.setRowStretch(0, 2);

    upgradeCostLbl.setAlignment(Qt::AlignLeft);
    upgradeCostLbl.setPalette(HHStyle::white_text);
    upgradeCostLbl.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grid.addWidget(&upgradeCostLbl, 0, 1, 1, 1);

    maintenanceCostLbl.setAlignment(Qt::AlignLeft);
    maintenanceCostLbl.setPalette(HHStyle::white_text);
    maintenanceCostLbl.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grid.addWidget(&maintenanceCostLbl, 1, 1, 1, 1);

    maintenanceCostVal.setPalette(HHStyle::white_text);
    maintenanceCostVal.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grid.addWidget(&maintenanceCostVal, 0, 2, 1, 1);

    upgradeCostVal.setPalette(HHStyle::white_text);
    upgradeCostVal.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grid.addWidget(&upgradeCostVal, 1, 2, 1, 1);

    // TODO load image
    expansionViewLbl.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    grid.addWidget(&expansionViewLbl, 1, 3, 3, 3);

    expansionList.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grid.addWidget(&expansionList, 2, 0, 1, 3);
    grid.setRowStretch(3, 10);

    lowInfoLbl.setAlignment(Qt::AlignTop);
    lowInfoLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&lowInfoLbl, 4, 0, 1, 3);
    grid.setRowStretch(4, 15);
}

PollicyTab::PollicyTab(): grid(this), topicList(this), ruleList(this),
  explanationLbl(QApplication::translate("MainWindow","This tab lets you adjust your school policies.\r\nEnacted rules may directly impact the stats of the affected persons on a daily basis or influence the outcome of certain ingame events.", Q_NULLPTR)),
  topicLbl(QApplication::translate("MainWindow","Topic", Q_NULLPTR)),
  RuleLbl(QApplication::translate("MainWindow","Rule", Q_NULLPTR))
{
    grid.setContentsMargins(0, 0, 0, 0);
    grid.setRowStretch(0, 10);
    explanationLbl.setAlignment(Qt::AlignTop);
    explanationLbl.setPalette(HHStyle::white_text);
    explanationLbl.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grid.addWidget(&explanationLbl, 0, 0, 1, 2);

    topicLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&topicLbl, 1, 0, 1, 1);
    RuleLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&RuleLbl, 1, 1, 1, 1);

    grid.addWidget(&topicList, 2, 0, 1, 1);
    grid.addWidget(&ruleList, 2, 1, 1, 1);
    grid.setRowStretch(2, 15);

    lowInfoLbl.setAlignment(Qt::AlignTop);
    lowInfoLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&lowInfoLbl, 3, 0, 1, 1);
    grid.setRowStretch(3, 15);
}

AssignmentsTab::AssignmentsTab(): grid(this),
    table(ARRAY_LEN(subjectName), ARRAY_LEN(teacher), this),
    subjExpLbl(QApplication::translate("MainWindow", "Subject Experience:", Q_NULLPTR)),
    genQualfLbl(QApplication::translate("MainWindow", "General Qualification:", Q_NULLPTR))
{
    grid.setContentsMargins(0, 0, 0, 0);
    grid.setRowStretch(0, 5);
    explanationLbl.setPalette(HHStyle::white_text);
    explanationLbl.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    explanationLbl.setText(QApplication::translate("MainWindow",
"This tab lets you assign which subjects can be taught by which teacher. Subjects must be assigned to a teacher in this panel before they can be selected in the curriculum.\n\n"
"Every teacher has a specific amount of subject experience in the inidividual subjects, which increases naturally over time as the subject is taught by that teacher.\n"
"The general qualification to teach a subject is determined by the teacher's current stats that are relevant for the specific subject. It improves as the teacher's stats\n"
"improve. Some subjects share a common field, so gaining qualification for one subject may also improve the qualification for a related subject. Each subject may have\n"
"different effects on the stats of teachers and students alike, but teachers with higher subject experience and qualification will increase those effects even further.\n\n"
"Checked entries in this list are the available subjects that this person is allowed to teach.", Q_NULLPTR));
    grid.addWidget(&explanationLbl, 0, 0, 1, 5);

    table.setStyleSheet("QTableWidget {background: rgb(41, 60, 67); gridline-color: white;}"
                        "QCheckBox {margin-left: 50%; margin-right:50%;}"
                        "QHeaderView::section, QTableCornerButton::section {"
                          "border-bottom: 1px solid white;"
                          "background: rgb(25, 45, 52);"
                          "color:white;}");

    //table.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    table.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    table.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    grid.addWidget(&table, 1, 0, 5, 5);
    grid.setRowStretch(1, 50);
    int mx = ARRAY_LEN(subjectName)* ARRAY_LEN(teacher);

    QStringList subjs, teachs;
    for (int j=0; j != ARRAY_LEN(teacher); ++j)
        teachs.append(teacher[j]);

    for (int i=0, jo = 0; i != ARRAY_LEN(subjectName); ++i, jo += ARRAY_LEN(teacher)) {
        subjs.append(subjectName[i]);

        for (int j=0; j != ARRAY_LEN(teacher); ++j) {
            tchAssignCB[jo+j] = new QCheckBox(this);
            tchAssignCB[jo+j]->setPalette(SimplePalette(QBrush(
                       QColor(255-255*(j+jo)/mx, 255*(j+jo)/mx, 0) ), HHStyle::dark_gray, QPalette::Base));
            table.setCellWidget(i, j, tchAssignCB[jo+j]);
        }
    }
    //TODO: icons, with table.setHorizontalHeaderItem();?
    table.setHorizontalHeaderLabels(teachs);
    table.setVerticalHeaderLabels(subjs);
    table.resizeColumnsToContents();
    table.resizeRowsToContents();

    // disable resizing and selection
    table.setFocusPolicy(Qt::NoFocus);
    table.setEditTriggers(QAbstractItemView::NoEditTriggers);
    table.setSelectionMode(QAbstractItemView::NoSelection);

    QHeaderView* hh = table.horizontalHeader(), *hv = table.verticalHeader();
    hh->setSectionResizeMode(QHeaderView::Fixed);
    hv->setSectionResizeMode(QHeaderView::Fixed);

    //FIXME: why is manual adjustment needed?
    table.setFixedSize(hh->length()+ hv->width() + 149, hv->length()+ hh->height() + 2);

    grid.setColumnStretch(1,6);
    grid.setColumnStretch(2,5);
    grid.setColumnStretch(4,5);
    grid.setColumnStretch(5,15);

    nameLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&nameLbl, 2, 0, 1, 2);

    subjNameLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&subjNameLbl, 2, 4, 1, 1);

    subjExpLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&subjExpLbl, 3, 1, 1, 1);
    subjExpPB.setPalette(progressStyle(QColor(50, 200, 50, 255)));
    subjExpPB.setValue(60);
    subjExpPB.setTextVisible(false);
    grid.addWidget(&subjExpPB, 3, 2, 1, 3);

    genQualfLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&genQualfLbl, 4, 1, 1, 1);
    genQualfPB.setPalette(progressStyle(QColor(50, 200, 50, 255)));
    genQualfPB.setValue(60);
    genQualfPB.setTextVisible(false);
    grid.addWidget(&genQualfPB, 4, 2, 1, 3);
}

JobsTab::JobsTab(): grid(this),
    applicants(QApplication::translate("MainWindow", "Available Applicants", Q_NULLPTR)),
    hiredStaff(QApplication::translate("MainWindow", "Hired Staff", Q_NULLPTR)),
    biographyLbl(QApplication::translate("MainWindow", "Biography:", Q_NULLPTR)),
    avgSubjExpHdrLbl(QApplication::translate("MainWindow", "Average Subject Family Experience", Q_NULLPTR)),
    hireFireBtn(QApplication::translate("MainWindow", "Hire", Q_NULLPTR)),
    staffList(this), applicantsList(this)
{
    grid.setContentsMargins(0, 0, 0, 0);
    grid.setColumnStretch(0, 3);
    grid.setColumnStretch(1, 5);
    grid.setColumnStretch(3, 4);
    grid.setColumnStretch(4, 8);

    applicants.setPalette(HHStyle::white_text);
    grid.addWidget(&applicants, 0, 0, 1, 2);

    for (int i=0; i != ARRAY_LEN(balance); ++i) {
        balanceLbl[i] = new QLabel(balance[i], this);
        balanceLbl[i]->setPalette(HHStyle::white_text);
        grid.addWidget(balanceLbl[i], i, 2, 1, 1);

        balanceVal[i] = new QLabel(balanceExample[i], this);
        balanceVal[i]->setAlignment(Qt::AlignLeft);
        balanceVal[i]->setPalette(HHStyle::white_text);
        grid.addWidget(balanceVal[i], i, 3, 1, 1);
    }

    hiredStaff.setPalette(HHStyle::white_text);
    grid.addWidget(&hiredStaff, 0, 4, 1, 1);

    grid.setRowStretch(2, 15);
    grid.addWidget(&applicantsList, 1, 0, 2, 2);
    hireFireBtn.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    grid.addWidget(&hireFireBtn,1, 2, 2, 2, Qt::AlignVCenter);
    grid.addWidget(&staffList, 1, 4, 2, 1);

    biographyLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&biographyLbl, 3, 0, 1, 1);

    grid.setRowStretch(4, 10);
    biographyVal.setAlignment(Qt::AlignTop);
    biographyVal.setPalette(HHStyle::white_text);
    biographyVal.setText(QApplication::translate("MainWindow", "", Q_NULLPTR));
    grid.addWidget(&biographyVal, 4, 0, 1, 2);

    avgSubjExpHdrLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&avgSubjExpHdrLbl, 5, 0, 1, 1);

    int i;
    for (i=0; i != ARRAY_LEN(subjectName); ++i) {
        //TODO: icon here.

        subLbl[i] = new QLabel(subjectName[i], this);
        subLbl[i]->setPalette(HHStyle::white_text);
        grid.addWidget(subLbl[i], i+6, 0, 1, 1);

        avgSubjExpVal[i] = new QProgressBar(this);
        avgSubjExpVal[i]->setPalette(progressStyle(QColor(50, 200, 50, 255)));
        avgSubjExpVal[i]->setValue(60);
        avgSubjExpVal[i]->setTextVisible(false);
        grid.addWidget(avgSubjExpVal[i], i+6, 1, 1, 2);
    }

    grid.setRowStretch(i+6, 5);
    teacherDisplay.setStyleSheet("background: transparent");
    grid.addWidget(&teacherDisplay, 3, 4, i+4, 1);
}


SchoolManagement::SchoolManagement(QWidget* parent, QRect geom): QWidget(parent), mainTab(this),
    studentsTab(geom),
    exitBtn(QApplication::translate("MainWindow", "Exit", Q_NULLPTR), this)
{
    //mainTab.setPalette(SimplePalette(HHStyle::bg, HHStyle::bg, QPalette::Button));
    setStyleSheet("QTabWidget { background-color: rgb(25, 45, 52)}");

    geom.setHeight(geom.height()*0.98);
    geom.setWidth(geom.width()*0.98);
    exitBtn.setGeometry(geom.width()-70, geom.top(), 70, 25);
    QObject::connect(&exitBtn, SIGNAL(clicked()), this->parent(), SLOT(toggle_school_management()));

    //FIXME top part of tab handle not responsive
    mainTab.setGeometry(geom);
    mainTab.setContentsMargins(0, 0, 0, 0);
    mainTab.addTab(&studentsTab, QString("Students"));
    mainTab.addTab(&jobsTab, QString("Jobs"));
    mainTab.addTab(&assnTab, QString("Teacher Assignments"));
    mainTab.addTab(&pollicyTab, QString("Pollicy"));
    mainTab.addTab(&expansionsTab, QString("Expansions"));

    mainTab.setCurrentIndex(0);
}

