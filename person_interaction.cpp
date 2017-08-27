/*
 * (c) Picobyte 2017, GPL2
 */
#include "person_interaction.h"


Person_interaction::Person_interaction(QWidget* W)
{
    Interaction_view = new QListView(W);
    QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(Interaction_view->sizePolicy().hasHeightForWidth());
    Interaction_view->setSizePolicy(sizePolicy);

    addWidget(Interaction_view, 4, 9, 1, 1);

    Category_view = new QListView(W);
    sizePolicy.setHeightForWidth(Category_view->sizePolicy().hasHeightForWidth());
    Category_view->setSizePolicy(sizePolicy);

    addWidget(Category_view, 2, 9, 1, 1);

    QBrush white_brush(QColor(255, 255, 255, 255));
    QBrush gray_brush(QColor(190, 190, 190, 255));

    QPalette text_palette;
    text_palette.setBrush(QPalette::Active, QPalette::WindowText, white_brush);
    text_palette.setBrush(QPalette::Inactive, QPalette::WindowText, white_brush);
    text_palette.setBrush(QPalette::Disabled, QPalette::WindowText, gray_brush);

    Category_Label = new QLabel(W);
    Category_Label->setPalette(text_palette);
    QFont font2;
    font2.setPointSize(14);
    Category_Label->setFont(font2);
    Category_Label->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

    addWidget(Category_Label, 1, 9, 1, 1);

    Interaction_Label = new QLabel(W);
    Interaction_Label->setPalette(text_palette);
    Interaction_Label->setFont(font2);
    Interaction_Label->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

    addWidget(Interaction_Label, 3, 9, 1, 1);

    interaction_subject = new QLabel(W);
    interaction_subject->setPalette(text_palette);
    QFont font3("sans", 14);
    interaction_subject->setFont(font3);
    interaction_subject->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

    addWidget(interaction_subject, 0, 9, 1, 1);

    frame = new QFrame(W);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Plain);
    BackButton = new QPushButton(frame);
    BackButton->setGeometry(QRect(140, 170, 91, 25));

    addWidget(frame, 6, 9, 1, 1);

    QObject::connect(BackButton, SIGNAL(clicked()), this, SLOT(slot_hide()));
    retranslateUi();
    setVisible(false);
}
void Person_interaction::retranslateUi()
{
    Category_Label->setText(QApplication::translate("HHSpp", "Category", Q_NULLPTR));
    Interaction_Label->setText(QApplication::translate("HHSpp", "Interaction", Q_NULLPTR));
    interaction_subject->setText(QApplication::translate("HHSpp", "Susan Hooter", Q_NULLPTR));
    BackButton->setText(QApplication::translate("HHSpp", "Back", Q_NULLPTR));
}
void Person_interaction::setVisible(bool set_visible)
{
    for (int i = 0; i < count(); ++i) {
      QWidget *widget = itemAt(i)->widget();
      if (widget != NULL) widget->setVisible(set_visible);
    }
}

void Person_interaction::slot_hide()
{
    setVisible(false);
}
