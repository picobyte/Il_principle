#ifndef SEQVARIABLE_H
#define SEQVARIABLE_H
#include "json_macros.h"
#include "seqobject.h"

class SeqVariable : public SeqObject {
public:
    object HitTest(QPoint coordAbsolute)
    {
        double radius = 0.5 * (double)Width;
        QPoint center = new QPoint(Coords.x() + radius, Coords.x() + radius);
        int dx = center.x() - coordAbsolute.x();
        int dy = center.y() - coordAbsolute.y();
        if (dx * dx + dy * dy < radius * radius)
            return this;
        return NULL;

    }
    QPoint GetEdgePointToward(QPoint targetPt)
    {
        QPoint GetEdgePointToward;
        if (this is SeqConst)
        {
            double radius = 0.5 * (double)Width;
            Vector vect = new Vector
            {
                X = targetPt.X - (Coords.X + radius),
                Y = targetPt.Y - (Coords.Y + radius)
            };
            vect.X = vect.X < -radius ? -radius : (vect.X > radius ? radius : vect.X);
            vect.Y = vect.Y < -radius ? -radius : (vect.Y > radius ? radius : vect.Y);
            QPoint* ret = new QPoint((double)Convert.ToInt32(vect.X), (double)Convert.ToInt32(vect.Y));
            ret.Offset(Coords.X, Coords.Y);
            ret.Offset(radius, radius);
            GetEdgePointToward = ret;
        }
        else
        {
            double radius2 = 0.5 * (double)Width;
            Vector vect2 = new Vector
            {
                X = targetPt.X - (Coords.X + radius2),
                Y = targetPt.Y - (Coords.Y + radius2)
            };
            vect2.Normalize();
            vect2 = Vector.Multiply(radius2, vect2);
            QPoint ret2 = new QPoint((double)Convert.ToInt32(vect2.X), (double)Convert.ToInt32(vect2.Y));
            ret2.Offset(Coords.X, Coords.Y);
            ret2.Offset(radius2, radius2);
            GetEdgePointToward = ret2;
        }
        return GetEdgePointToward;
    }
    abstract VarType GetVarType();
    virtual void CopyFrom(SeqVariable other)
    {
        throw new NotImplementedException(QString.Format("Can not copy from variable of type {0} to {1}!", other.GetType(), GetType()));
    }
    abstract object GetVarValue();
    abstract void SetVarValue(object value);
    abstract QString ValueToString();
    void Draw(VisualEvent VE, DrawingContext drawingContext, QPoint origin, double zoomfactor)
    {
        DrawBody(VE, drawingContext, origin, zoomfactor);
        DrawComment(drawingContext, origin, zoomfactor);
    }
    Type GetPropertyWindowClass()
    {
        return NULL;
    }
};

#endif // SEQVARIABLE_H
