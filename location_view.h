/*
 * (c) Picobyte 2017, GPL2
 */
#ifndef LOCATION_VIEW_H
#define LOCATION_VIEW_H

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QApplication>
#include <QStackedWidget>

#include "layoutwidget.h"
#include "person_interaction.h"
#include "person.h"
#include "aspectratiopixmaplabel.h"
#include "mainwindow.h"

//yourWidget->setStyleSheet("background-color: transparent;");
namespace HHS {
    class Location_view;
}

class MainWindow;

class Location_view : public QWidget
{
    Q_OBJECT
private:
    QGridLayout grid;
    static const unsigned max_alt_locations = 10;
    static const unsigned max_alt_views = 10;
    static const unsigned nrof_actions = 3;
    static const unsigned nrof_controls = 2;
    AspectRatioPixmapLabel* siteView;
    Person_interaction* pplInterAct;
    QStackedWidget* SW;
    QListView pplListView;
    QStringListModel model;
    QItemSelectionModel selectionModel;
    QStringList ppl;
    QPushButton push_alt_loc[max_alt_locations];
    QPushButton push_alt_views[max_alt_views];
    QPushButton push_actions[nrof_actions];
    QPushButton push_ctl[nrof_controls];
    QHBoxLayout horLayout2, horLayout3;
    QLabel Calendar_notes, Person_site;
public:
    Location_view(QWidget*, QRect);

    void addPerson(Person* p);
    void rmPerson();
    QStringList getPeople() const;

    void setImg(QString s);
public slots:
    void slot_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // LOCATION_VIEW_H
