#ifndef CLASSROOMASSIGNMENTS_H
#define CLASSROOMASSIGNMENTS_H
#include "json_macros.h"

class ClassroomAssignments {
    QHash<int, QString> AssignedClassrooms;
    QHash<int, QString> AssignedSubjects;
    QHash<int, QString> AssignedTeachers;
public:
    Qt::DayOfWeek CurrentDay;
    int CurrentSlot;

    ClassroomAssignments(QJsonObject *d = NULL)
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_OBJ_FROM_JSON(it, CurrentDay)
            else __IF_VAR_FROM_JSON_AS(it, CurrentSlot, toInt)
            // *INDENT-ON*
        }
    }
    void AssignClassrooms(Qt::DayOfWeek Day, int Slot);
    void UnassignClassrooms()
    {
        AssignedClassrooms.clear();
        AssignedTeachers.clear();
        AssignedSubjects.clear();
    }
    void CheckUpdate();
};

#endif // CLASSROOMASSIGNMENTS_H
