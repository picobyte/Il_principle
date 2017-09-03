/*
 * (c) Picobyte 2017, GPL2
 */
#include "location_view.h"

Location_view::Location_view(QWidget* parent, QRect geom): QWidget(parent), grid(this),
	pplListView(this), model(this), selectionModel(&model),
	Calendar_notes(this), Person_site(this)
{
	siteView = new AspectRatioPixmapLabel(this);
	pplInterAct = new Person_interaction(this);

	siteView->setScaledContents(true);
	setContentsMargins(0,0,0,0);

	QSizePolicy maximized(QSizePolicy::Expanding, QSizePolicy::Expanding);
	maximized.setHorizontalStretch(0);
	maximized.setVerticalStretch(0);

	//grid.setGeometry(geom);
	setSizePolicy(maximized);

	grid.setRowStretch(0,2);
	//grid.setRowStretch(1,1);
	grid.setColumnStretch(0,1);
	grid.setColumnStretch(1,7);
	grid.setColumnStretch(2,2);
	//grid.setParent(stackWidget->layout());
	//grid.setGeometry(geom);

	geom.setWidth(geom.width()*5/6);

	//siteView->setSizePolicy(maximized);
	QDir dir;
	dir.setPath(QCoreApplication::applicationDirPath()+"/../Il_principle/Schools/NormalSchool/Images/Locations/Your Home/empty.jpg");
	setImg(dir.path());
	grid.addWidget(siteView, 0, 0, 1, 2);
	geom.setHeight(siteView->heightForWidth(geom.width()));
	siteView->setGeometry(geom);
	//itemAtPosition(0,0)->geometry().width()

	//loc_frame.setGeometry(this->geometry());
	//loc_frame.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//siteView.setAlignment(Qt::AlignTop | Qt::AlignLeft);
	//siteView.setContentsMargins(0,0,0,0);
	//siteView.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);


	//loc_btns.setStyleSheet("background-color: transparent;");

	model.setStringList(ppl);

	pplListView.setModel(&model);
	pplListView.setSelectionModel(&selectionModel);
	//pplListView.setEditTriggers(QAbstractItemView::AnyKeyPressed);

	//maximized.setHeightForWidth(pplListView.sizePolicy().hasHeightForWidth());
	pplListView.setSizePolicy(maximized);
	//pplListView.setWidgetResizable(true);
	pplListView.setStyleSheet(QLatin1String("color: rgb(255, 110, 249);selection-color: rgb(255, 110, 249);selection-background-color: rgb(10, 36, 106);background-color: qlineargradient(spread:reflect, x1:0.495, y1:0, x2:1, y2:0, stop:0.409574 rgba(19, 34, 39, 255), stop:1 rgba(25, 45, 52, 255));"));
	pplListView.setFrameShape(QFrame::NoFrame);
	pplListView.setFrameShadow(QFrame::Plain);
	pplListView.setLineWidth(0);
	pplListView.setEditTriggers(QAbstractItemView::NoEditTriggers);
	pplListView.setProperty("showDropIndicator", QVariant(false));
	pplListView.setDefaultDropAction(Qt::IgnoreAction);
	grid.addWidget(&pplListView, 0, 2, 1, 1);

	//FIXME: location buttons belong to a location
	QPalette alt_view_btn;
	QBrush brush8(QColor(166, 202, 240, 255));
	brush8.setStyle(Qt::SolidPattern);
	alt_view_btn.setBrush(QPalette::Active, QPalette::Button, brush8);
	alt_view_btn.setBrush(QPalette::Inactive, QPalette::Button, brush8);
	alt_view_btn.setBrush(QPalette::Disabled, QPalette::Button, brush8);

	push_alt_views[0].setParent(this);
	push_alt_views[0].setText("Paperwork:\nManage School");
	push_alt_views[0].setGeometry(315, 750, 100, 35);
	push_alt_views[0].setPalette(alt_view_btn);

	QObject::connect(&push_alt_views[0], SIGNAL(clicked()), this->parent(), SLOT(toggle_school_management()));

	push_alt_views[1].setParent(this);
	push_alt_views[1].setText("Kitchen:\nOpen Fridge");
	push_alt_views[1].setGeometry(125, 350, 100, 35);
	push_alt_views[1].setPalette(alt_view_btn);

	push_alt_views[2].setParent(this);
	push_alt_views[2].setText("Video Library:\nOpen Library");
	push_alt_views[2].setGeometry(1515, 680, 100, 35);
	push_alt_views[2].setPalette(alt_view_btn);

	push_alt_views[3].setParent(this);
	push_alt_views[3].setText("Computer");
	push_alt_views[3].setGeometry(1555, 930, 100, 35);
	push_alt_views[3].setPalette(alt_view_btn);

	// BOTTOM
	for (int i = 0; i != nrof_actions; ++i) {
		push_actions[i].setParent(this);
		horLayout2.addWidget(&push_actions[i]);
	}

	grid.addLayout(&horLayout2, 1, 0, 1, 1);

	Calendar_notes.setPalette(HHStyle::white_text);
	Calendar_notes.setAlignment(Qt::AlignCenter);

	grid.addWidget(&Calendar_notes, 1, 1, 1, 1);

	Person_site.setPalette(HHStyle::hdr_text);
	Person_site.setAlignment(Qt::AlignCenter);

	horLayout3.addWidget(&Person_site, 2, Qt::AlignLeft);
	for (int i = 0; i != nrof_controls; ++i) {
		push_ctl[i].setParent(this);
		horLayout3.addWidget(&push_ctl[i]);
	}

	grid.addLayout(&horLayout3, 1, 2, 1, 1);

	connect(&selectionModel, SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
					 this, SLOT(slot_selectionChanged(const QItemSelection&, const QItemSelection&)));

	Person_site.setText(QApplication::translate("HHSpp", "Oliver Klozoff | Lubriscity", Q_NULLPTR));
	Calendar_notes.setText(QApplication::translate("HHSpp", "No calendar notes for Today", Q_NULLPTR));
	push_actions[0].setText(QApplication::translate("HHSpp", "Smartphone", Q_NULLPTR));
	push_actions[1].setText(QApplication::translate("HHSpp", "Inventory", Q_NULLPTR));
	push_actions[2].setText(QApplication::translate("HHSpp", "Map", Q_NULLPTR));

	push_ctl[0].setText(QApplication::translate("HHSpp", "Settings", Q_NULLPTR));
	push_ctl[1].setText(QApplication::translate("HHSpp", "Debug", Q_NULLPTR));
}

void Location_view::addPerson(Person* p) {
	int rows = model.rowCount();
	model.insertRow(rows);
	model.setData(model.index(rows), p->Forename.toUtf8());
}
void Location_view::rmPerson() {
	model.removeRows(pplListView.currentIndex().row(), 1);
}

QStringList Location_view::getPeople() const
{
	return model.stringList();
}

void Location_view::setImg(QString s)
{
	siteView->setPixmap(QPixmap(s));
}

void Location_view::slot_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
	siteView->toggle_blur();
	pplInterAct->setVisible();
	//selected.at(0).topLeft().row();
}
