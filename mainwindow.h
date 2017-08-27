/*
 * (c) Picobyte 2017, GPL2
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QFrame>
#include <QGraphicsView>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QWidget>

#include "location_view.h"
#include "person_interaction.h"
#include "school_management.h"
#include "generic.h"

static const char* displaystat[] = {"Education", "Happiness", "Loyalty", "Inhibition", "Lust", "Corruption", "Reputation", "Students", "Money"};
static unsigned wait_time[] = {10, 30, 60};

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

class Location_view;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget W, gridW;
    QGridLayout grid;

    QLabel time_display, date_display, location;
    QProgressBar energy_bar, arousal_bar;
    QStackedWidget stackWidget;

    QLabel displaystat_hdr[ARRAY_LEN(displaystat)];
    QLabel displaystat_val[ARRAY_LEN(displaystat)];

    Location_view *loc;
    AspectRatioPixmapLabel siteView;

    SchoolManagement* school_management;

    QPushButton push_wait[ARRAY_LEN(wait_time)];
public:


    explicit MainWindow(QWidget *parent = 0);
    void dummy_startup();
    void retranslateUi();
public slots:
    void toggle_school_management();
};

#endif // MAINWINDOW_H
