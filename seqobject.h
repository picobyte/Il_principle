#ifndef SEQOBJECT_H
#define SEQOBJECT_H
#include <QPoint>
#include <QSize>
#include <QPair>
#include <QPen>
#include <tuple>
#include "json_macros.h"
#include "visualevent.h"

class DrawingContext; // DrawingContext: windows specific storage of paint operations(?) with push and pop? requires replacement.
class VisualEvent;
class SeqObject {
public:
    bool Selected;
    float Width;
    float Height;
    unsigned ID;
    QPoint Coords;
    QString Name;
    QString Comment;

    bool ShouldSerializeComment()
    {
        return !Comment.isEmpty();
    }
    void ResetComment()
    {
        Comment.clear();
    }

    SeqObject(QJsonObject *d = NULL)
    {
        Width = 50.0f;
        Height = 50.0f;
    }
    /*object Clone()
    {
        return GetClonedObject();
    }*/
    virtual SeqObject* ReplaceObject(QString& replOption)
    {
        return NULL;
    }
    virtual QList<std::tuple<QPoint, QPoint, QPen> >* GetHorzConnectors(VisualEvent& VE) = 0;
    virtual QList<std::tuple<QPoint, QPoint, QPen> >* GetVertConnectors(VisualEvent& VE) = 0;
    virtual QRect* GetBoundingRectangleAbsolute()
    {
        return new QRect(Coords, QSize(Width, Height + 20.0f));
    }
    virtual SeqObject* HitTest(QPoint coordAbsolute)
    {
        if (GetBoundingRectangleAbsolute()->contains(coordAbsolute))
            return this;

        return NULL;

    }
    float GetZoomedWidth(double zoomfactor)
    {
        return Width * zoomfactor;
    }
    float GetZoomedHeight(double zoomfactor)
    {
        return Height * zoomfactor;
    }
    QPoint* GetCenterAbsolute()
    {
        return new QPoint(Coords.x() + 0.5 * Width, Coords.y() + 0.5 * Height);
    }
    /*virtual Type GetPropertyWindowClass()
    {
        return NULL;
    }*/
    virtual void Draw(VisualEvent VE, DrawingContext& drawingContext, QPoint origin, double zoomfactor) = 0;
    virtual const QString& GetHumanReadableName(VisualEvent& VE)
    {
        return Name;
    }
    virtual const QString& GetHumanReadableName(VisualEvent& VE, bool ForceFullName)
    {
        return GetHumanReadableName(VE);
    }
    virtual QString GetTooltip()
    {
        return "";
    }
    virtual QString* AutoFixProperties()
    {
        return new QString();
    }
    virtual QString* CheckForErrors(VisualEvent& VE)
    {
        return NULL;
    }
    virtual QString* DeprecatedBy()
    {
        return NULL;
    }
    /*QString ToString()
    {
        return ToString().substring(5);
    }*/
    int CompareTo(SeqObject& other)
    {
        return ID - other.ID;
    }
};

#endif // SEQOBJECT_H
