/*
 * (c) Picobyte 2017, GPL2
 */

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), W(this),
    gridW(&W), grid(&gridW), time_display(&W), date_display(&W), location(&W),
    energy_bar(&W), arousal_bar(&W), stackWidget(this)
{
    QRect geom = QDesktopWidget().availableGeometry(this);
    geom.setTop(10);
    geom.setLeft(10);
    geom.setWidth(geom.width()-20);
    geom.setHeight(geom.height()-20);
    setGeometry(geom);

    geom.setWidth(geom.width()-20);
    geom.setHeight(geom.height()-20);
    W.setContentsMargins(0, 0, 0, 0);
    W.setGeometry(geom);

    geom.setHeight(geom.height()*0.98);
    gridW.setContentsMargins(0, 0, 0, 0);
    gridW.setGeometry(geom);
    grid.setContentsMargins(0, 0, 0, 0);
    //grid.setGeometry(geom);

    setPalette(backgroundStyle());

    // FIXME: only shown if window contains locationview
    for (int i = 0; i != ARRAY_LEN(wait_time); ++i) {
        push_wait[i].setParent(&W);
        grid.addWidget(&push_wait[i], 0, i, 2, 1);
    }

    QFont font("sans", 13);

    QFont font1;
    font1.setPointSize(11);
    font1.setBold(true);
    font1.setWeight(75);

    time_display.setPalette(HHStyle::hdr_text);
    time_display.setFont(font1);
    time_display.setAlignment(Qt::AlignCenter);

    grid.addWidget(&time_display, 0, 5, 1, 2);

    date_display.setPalette(HHStyle::white_text);
    date_display.setFont(font1);
    date_display.setAlignment(Qt::AlignCenter);

    grid.addWidget(&date_display, 0, 3, 1, 2);

    energy_bar.setPalette(progressStyle(QColor(0, 255, 255, 255)));
    energy_bar.setValue(60);
    energy_bar.setTextVisible(false);

    grid.addWidget(&energy_bar, 0, 7, 1, 5);

    arousal_bar.setPalette(progressStyle(QColor(255, 110, 249, 255)));
    arousal_bar.setValue(48);
    arousal_bar.setTextVisible(false);

    grid.addWidget(&arousal_bar, 1, 7, 1, 5);

    location.setPalette(HHStyle::white_text);
    location.setFont(font);

    grid.addWidget(&location, 2, 0, 3, 3);

    for (int i = 0; i != ARRAY_LEN(displaystat_hdr); ++i) {
        displaystat_hdr[i].setParent(&W);
        displaystat_hdr[i].setPalette(HHStyle::hdr_text);
        displaystat_hdr[i].setAlignment(Qt::AlignCenter);

        grid.addWidget(&displaystat_hdr[i], 2, 3+i, 1, 1);

        displaystat_val[i].setParent(&W);
        displaystat_val[i].setPalette(HHStyle::white_text);
        displaystat_val[i].setAlignment(Qt::AlignCenter);

        grid.addWidget(&displaystat_val[i], 3, 3+i, 1, 1);
    }

    //Center

    //stackWidget.setGeometry(geom);
    geom.setHeight(geom.height()*10/11); // removes space for header
    loc = new Location_view(this, geom); //use copy of geom
    stackWidget.addWidget(loc);

    school_management = new SchoolManagement(this, geom);
    stackWidget.addWidget(school_management);

    stackWidget.setCurrentIndex(0);

    grid.addWidget(&stackWidget, 4, 0, 50, 12);
    //loc->grid.setParent(W);

    retranslateUi();
    dummy_startup();
}

void MainWindow::dummy_startup()
{
    Person annette;
    annette.forename = "Annette";
    loc->addPerson(&annette);

    Person peter_hooter;
    peter_hooter.forename = "Peter";
    loc->addPerson(&peter_hooter);
}

void MainWindow::toggle_school_management()
{
    stackWidget.setCurrentIndex(!stackWidget.currentIndex());
}

void MainWindow::retranslateUi()
{
    int i;
    setWindowTitle(QApplication::translate("HHSpp", "MainWindow", Q_NULLPTR));
    for (i = 0; i != ARRAY_LEN(displaystat); ++i)
        displaystat_hdr[i].setText(QApplication::translate("HHSpp", displaystat[i], Q_NULLPTR));

    //FIXME: read these from somewhere
    for (i = 0; i != ARRAY_LEN(displaystat)-2; ++i)
        displaystat_val[i].setText(QApplication::translate("HHSpp", "30.1", Q_NULLPTR));
    displaystat_val[i++].setText(QApplication::translate("HHSpp", "91", Q_NULLPTR));
    displaystat_val[i++].setText(QApplication::translate("HHSpp", "$10,000", Q_NULLPTR));

    for (i = 0; i != ARRAY_LEN(wait_time); ++i)
        push_wait[i].setText(QApplication::translate("HHSpp", QString::fromLatin1("Wait %1 Min").arg(wait_time[i]).toUtf8(), Q_NULLPTR));

    time_display.setText(QApplication::translate("HHSpp", "8:00", Q_NULLPTR));

    date_display.setText(QApplication::translate("HHSpp", "Monday (1/1/2017)", Q_NULLPTR));
    location.setText(QApplication::translate("HHSpp", "Home", Q_NULLPTR));
}
