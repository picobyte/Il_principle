#ifndef ASPECTRATIOPIXMAPLABEL_H
#define ASPECTRATIOPIXMAPLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>

class AspectRatioPixmapLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AspectRatioPixmapLabel(QWidget *parent = 0);
    virtual int heightForWidth( const int width ) const;
    virtual QSize sizeHint() const;
    QPixmap scaledPixmap() const;
    void toggle_blur();
/*public slots:
    void setPixmap ( const QPixmap &);
    void resizeEvent(QResizeEvent *);*/
private:
    QPixmap* pix;
    QPixmap blur;
    QPixmap orig;
    bool is_blurred;
};

#endif // ASPECTRATIOPIXMAPLABEL_H
