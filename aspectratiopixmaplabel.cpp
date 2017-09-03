#include "aspectratiopixmaplabel.h"
//#include <QDebug>

AspectRatioPixmapLabel::AspectRatioPixmapLabel(QWidget *parent) :
	QLabel(parent)
{
	pix = &orig;
	is_blurred = false;
	setMinimumSize(1,1);
	setScaledContents(false);
}

void AspectRatioPixmapLabel::setPixmap (const QPixmap & p)
{
	orig = p;
	pix = &orig;
	blur = QPixmap();
	is_blurred = false;
	QLabel::setPixmap(scaledPixmap());
}

int AspectRatioPixmapLabel::heightForWidth(int width) const
{
	return pix->isNull() ? height() : ((qreal)pix->height()*width)/pix->width();
}

QSize AspectRatioPixmapLabel::sizeHint() const
{
	int w = width();
	return QSize(w, heightForWidth(w));
}

QPixmap AspectRatioPixmapLabel::scaledPixmap() const
{
	return pix->scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void AspectRatioPixmapLabel::resizeEvent(QResizeEvent * e)
{
	if(!pix->isNull())
		QLabel::setPixmap(scaledPixmap());
}

void AspectRatioPixmapLabel::toggle_blur()
{
	//size.scale(size.width()*4/5,size.height()*23/25,Qt::KeepAspectRatio);
	is_blurred = !is_blurred;
	if (is_blurred) {
		if (blur.isNull()) {
			QGraphicsBlurEffect *effect = new QGraphicsBlurEffect;
			effect->setBlurRadius(2);
			QGraphicsScene scene;
			QGraphicsPixmapItem item;
			item.setPixmap(orig);
			item.setGraphicsEffect(effect);
			scene.addItem(&item);
			QImage res(orig.size(), QImage::Format_ARGB32);
			res.fill(Qt::transparent);
			QPainter ptr(&res);
			scene.render(&ptr);
			blur = QPixmap::fromImage(res);
		}
		pix = &blur;
	} else {
		pix = &orig;
	}
	QLabel::setPixmap(scaledPixmap());
}
