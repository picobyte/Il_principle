/*
 * (c) Picobyte 2017, GPL2
 */
#ifndef PERON_INTERACTION_H
#define PERON_INTERACTION_H

#include <QWidget>
#include <QGridLayout>
#include <QGraphicsView>
#include <QListView>
#include <QLabel>
#include <QPushButton>
#include <QApplication>


namespace HHS {
    class Person_interaction;
}

class Person_interaction : public QGridLayout {
    Q_OBJECT
public:
    QListView *Interaction_view, *Category_view;
    QLabel *Category_Label, *Interaction_Label;
    QLabel *interaction_subject;
    QFrame *frame;
    QPushButton *BackButton;

    Person_interaction(QWidget* W);
    void retranslateUi();
    void setVisible(bool set_visible=true);
//public slots:
    void slot_hide();

};

#endif // PERON_INTERACTION_H
