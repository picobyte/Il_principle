#ifndef SCHOOLCLASS_H
#define SCHOOLCLASS_H
#include <QList>
#include <QString>
#include "json_macros.h"
#include "schoolsubject.h"
#include "gtime.h"

class person;
class SchoolSubject;
class SchoolClass {
public:
    QList<Person> Students;
    int ClassIndex;
    QString Monday[4];
    QString Tuesday[4];
    QString Wednesday[4];
    QString Thursday[4];
    QString Friday[4];
    //readonly object thisLock;
    const QString DisplayName() const
    {
        if (ClassIndex <= 0)
            return "Unassigned Students";

        return QString::asprintf("Class %d", + ClassIndex);
    }

    SchoolClass(QJsonObject *d = NULL)
    {
        if (d) init(d);
        ClassIndex = 0;
        //thisLock = RuntimeHelpers.GetObjectValue(new object());
    }
    void init(QJsonObject *d);
    SchoolSubject* GetCurriculum() const;
    SchoolSubject* GetCurriculum(Qt::DayOfWeek Day, size_t Slot) const;
    void SetCurriculum(SchoolSubject S);
    void SetCurriculum(SchoolSubject* S, Qt::DayOfWeek Day, size_t Slot);
    void CopyMondayTo(Qt::DayOfWeek Day)
    {
        switch (Day)
        {
        case Qt::Tuesday:
            Tuesday[0] = Monday[0];
            Tuesday[1] = Monday[1];
            Tuesday[2] = Monday[2];
            Tuesday[3] = Monday[3];
            return;
        case Qt::Wednesday:
            Wednesday[0] = Monday[0];
            Wednesday[1] = Monday[1];
            Wednesday[2] = Monday[2];
            Wednesday[3] = Monday[3];
            return;
        case Qt::Thursday:
            Thursday[0] = Monday[0];
            Thursday[1] = Monday[1];
            Thursday[2] = Monday[2];
            Thursday[3] = Monday[3];
            return;
        case Qt::Friday:
            Friday[0] = Monday[0];
            Friday[1] = Monday[1];
            Friday[2] = Monday[2];
            Friday[3] = Monday[3];
            return;
        default:
            return;
        }
    }
    void CopyFirstSlotTo(unsigned Slot)
    {
        Monday[Slot] = Monday[0];
        Tuesday[Slot] = Tuesday[0];
        Wednesday[Slot] = Wednesday[0];
        Thursday[Slot] = Thursday[0];
        Friday[Slot] = Friday[0];
    }
    Location* GetLessonLocation() const;
    void AddStudent(Person Student);
    void RemoveStudent(Person Student);
    void RemoveRandomStudent();
    void RemoveAllStudents();
    QString ToString() const;
    void DistributeSpareStudentsToClasses();
    void DistributeStudentToClass(Person Student);
    void ApplyLessonProgress();
};

#endif // SCHOOLCLASS_H
