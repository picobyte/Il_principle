/*
 * (c) Picobyte 2017, GPL2
 */
#include "student_tab.h"

SchlMngStudentClasses::SchlMngStudentClasses(): grid(this)
{
    grid.setContentsMargins(0, 0, 0, 0);

    for (int d = 0; d != no_workdays; ++d) {
        dayLbl[d] = new QLabel(weekday[d], this);
        dayLbl[d]->setPalette(HHStyle::white_text);
        grid.addWidget(dayLbl[d], 1, 1+d*2, 1, 2);
    }
    for (int p = 0, poffs = 2; p != ARRAY_LEN(period); ++p) {
        if (p == ARRAY_LEN(period)-1) {
            lunch_break = new QLabel("Lunch Break", this);
            lunch_break->setPalette(HHStyle::white_text);
            grid.addWidget(lunch_break, poffs++ + p, 5, 1, 2);
        }
        periodLbl[p] = new QLabel(period[p], this);
        periodLbl[p]->setPalette(HHStyle::white_text);
        grid.addWidget(periodLbl[p], poffs+p, 0, 1, 1);

        for (int d = 0; d != no_workdays; ++d) {
            QComboBox* cb = classSchedule[p*no_workdays + d] = new QComboBox(this);
            grid.addWidget(cb, poffs+p, 1+d*2, 1, 2);
        }
    }
    curriculumLbl.setPalette(HHStyle::white_text);
    curriculumLbl.setAlignment(Qt::AlignTop);
    curriculumLbl.setText(QApplication::translate("MainWindow", "Arrange the curriculum for the selected class. Only subjects with available rooms in the given time slot are shown. The number next to each subject indicates how many teachers are allowed to teach it. Configure the teacher assignments in the School tab.", Q_NULLPTR));
    grid.addWidget(&curriculumLbl, ARRAY_LEN(period)+3, 0, 25, 12);
}

SchlMngClassSummary::SchlMngClassSummary(): grid(this), vertStretch(1<<16, 1<<16)
{
    grid.setContentsMargins(0, 0, 0, 0);

    classSummaryLbl.setPalette(HHStyle::white_text);
    classSummaryLbl.setText(QApplication::translate("MainWindow", "Class Summary", Q_NULLPTR));
    grid.addWidget(&classSummaryLbl, 0, 0, 1, 2);
    grid.setRowStretch(0, 2);
    grid.setColumnStretch(1, 8);

    aSFELbl.setPalette(HHStyle::white_text);
    aSFELbl.setText(QApplication::translate("MainWindow", "Average Subject Family Experience", Q_NULLPTR));
    grid.addWidget(&aSFELbl, 1, 0, 1, 2);

    int i;
    for (i = 0; i != ARRAY_LEN(subject); ++i) {
        subjLbl[i] = new QLabel(subject[i], this);
        subjLbl[i]->setPalette(HHStyle::white_text);
        grid.addWidget(subjLbl[i], i+2, 0, 1, 1);

        subjBar[i].setPalette(progressStyle(QColor(50, 200, 50, 255)));
        subjBar[i].setValue(60);
        subjBar[i].setTextVisible(false);
        grid.addWidget(&subjBar[i], i+2, 1, 1, 1);
    }
    grid.addItem(&vertStretch, i+2, 1, 1, 1);
}

SchlMngStudents::SchlMngStudents(): grid(this),
  favoritesOnly(QApplication::translate("MainWindow", "Favorites only", Q_NULLPTR), this),
  favorite(QApplication::translate("MainWindow", "Favorite", Q_NULLPTR), this),
  sbjScoreLbl(QApplication::translate("MainWindow", "Subject Scoring", Q_NULLPTR)),
  transferBtn(QApplication::translate("MainWindow", "Transfer", Q_NULLPTR))
{
    grid.setContentsMargins(0, 0, 0, 0);
    favoritesOnly.setPalette(HHStyle::white_text);
    grid.addWidget(&favoritesOnly, 0, 0, 1, 1);
    grid.setColumnStretch(1, 8);
    grid.addWidget(&studentName, 0, 1, 1, 5);
    grid.setColumnStretch(5, 10);
    favorite.setPalette(HHStyle::white_text);
    grid.addWidget(&favorite, 0, 6, 1, 1);
    grid.addWidget(&transferCmb, 0, 7, 1, 1);
    grid.setColumnStretch(7, 8);
    grid.addWidget(&transferBtn, 0, 8, 1, 1);

    grid.addWidget(&studentsList, 1, 0, 35, 2);
    int i;
    for (i = 0; i != 2; ++i) {
        statLbl[i] = new QLabel(studentInfo[i], this);
        statLbl[i]->setPalette(HHStyle::white_text);
        grid.addWidget(statLbl[i], 2, 2+i*2, 1, 1);

        statVal[i] = new QLabel(studentInfoEG[i], this);
        statVal[i]->setPalette(HHStyle::white_text);
        grid.addWidget(statVal[i], 2, 3+i*2, 1, 1);
    }

    statLbl[i] = new QLabel(studentInfo[i], this);
    statLbl[i]->setPalette(HHStyle::white_text);
    grid.addWidget(statLbl[i], 3, 2, 1, 1);

    statVal[i] = new QLabel(studentInfoEG[i], this);
    statVal[i]->setPalette(HHStyle::white_text);
    grid.addWidget(statVal[i], 3, 3, 2, 3);

    for (++i; i != ARRAY_LEN(studentInfo); ++i) {
        statLbl[i] = new QLabel(studentInfo[i], this);
        statLbl[i]->setPalette(HHStyle::white_text);
        grid.addWidget(statLbl[i], i+2, 2, 1, 1);

        statVal[i] = new QLabel(studentInfoEG[i], this);
        statVal[i]->setPalette(HHStyle::white_text);
        grid.addWidget(statVal[i], i+2, 3, 1, 3);
    }

    sbjScoreLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&sbjScoreLbl, i+2, 2, 1, 2);

    for (++i; i != ARRAY_LEN(subjectName); ++i) {
        //TODO: icon here.

        subjLbl[i] = new QLabel(subjectName[i], this);
        subjLbl[i]->setPalette(HHStyle::white_text);
        grid.addWidget(subjLbl[i], i+2, 3, 1, 1);

        subjBar[i].setPalette(progressStyle(QColor(50, 200, 50, 255)));
        subjBar[i].setValue(60);
        subjBar[i].setTextVisible(false);
        grid.addWidget(&subjBar[i], i+2, 5, 1, 2);
    }
    graphicsView.setStyleSheet("background: transparent");
    grid.addWidget(&graphicsView, 1, 7, 35, 2);
}

StudentsTab::StudentsTab(QRect geom): grid(this),
    distrBtn(QApplication::translate("MainWindow", "Distribute", Q_NULLPTR), this),
    spinBox(this), listView(this)/*, students_subtabW(this) ??*/, tab(&tabW)
{

    grid.setContentsMargins(0, 0, 0, 0);

    classesLbl.setText(QApplication::translate("MainWindow", "Classes", Q_NULLPTR));
    classesLbl.setPalette(HHStyle::white_text);
    grid.addWidget(&classesLbl, 0, 0, 1, 2);
    grid.setColumnStretch(0, 2);

    grid.addWidget(&listView, 1, 0, 2, 2);
    grid.setColumnStretch(2, 7);

    grid.addWidget(&distrBtn, 3, 0, 1, 1);
    grid.addWidget(&spinBox, 3, 1, 1, 1);

    grid.setColumnStretch(2, 22);
    grid.setRowStretch(4, 15);

    grid.addWidget(&tabW, 0, 2, 30, 1);

    geom.setWidth(geom.width()*22/25);
    geom.setHeight(geom.height()*26/27);
    tab.setGeometry(geom);
    tab.addTab(&timetableW, QString("Timetable"));
    tab.addTab(&classSummaryW, QString("Class Summary"));
    tab.addTab(&studentsW, QString("Students"));
    tab.setCurrentIndex(0);
}
