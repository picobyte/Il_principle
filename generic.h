/*
 * (c) Picobyte 2017, GPL2
 */
#ifndef GENERIC_H
#define GENERIC_H

#include <QPalette>

#define ARRAY_LEN(a) (sizeof(a)/sizeof(*a))

class SimplePalette: public QPalette {
public:
    SimplePalette(const QBrush& normal, const QBrush& disabled, ColorRole CR = WindowText)
    {
        setBrush(Active, CR, QBrush(normal));
        setBrush(Inactive, CR, QBrush(normal));
        setBrush(Disabled, CR, QBrush(disabled));
    }
};

namespace HHStyle {

static const QBrush white = QColor(255, 255, 255, 255);
static const QBrush dark_gray = QColor(25, 25, 25, 255);
static const QBrush bg = QColor(25, 45, 52, 255);
static const QBrush gray = QColor(190, 190, 190, 255);
static const QBrush light_gray = QColor(100, 100, 100, 255);

static const SimplePalette white_text = SimplePalette(white, gray);
static const SimplePalette hdr_text = SimplePalette(gray, dark_gray);

}

class progressStyle: public SimplePalette {
public:
    progressStyle(const QBrush& normal):
        SimplePalette(normal, HHStyle::dark_gray, QPalette::Highlight)
    {}
};

class backgroundStyle: public SimplePalette {
public:
    backgroundStyle(): SimplePalette(HHStyle::white, HHStyle::gray, QPalette::Base)
    {
        setBrush(Active, Window, HHStyle::bg);
        setBrush(Inactive, Window, HHStyle::bg);
        setBrush(Disabled, Window, HHStyle::bg);
    }
};

#endif // GENERIC_H
