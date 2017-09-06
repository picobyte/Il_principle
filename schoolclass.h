#ifndef SCHOOLCLASS_H
#define SCHOOLCLASS_H
#include <QList>
#include <QString>
#include "json_macros.h"
#include "schoolsubject.h"
#include "person.h"

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
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_OBJLIST_FROM_JSON(it, _Students, Person)
            else __IF_VAR_FROM_JSON_AS(it, ClassIndex, toInt)
            //else __IF_OBJ_FROM_JSON(it, thisLock)
            // *INDENT-ON*
        }
    }
    SchoolSubject GetCurriculum()
    {
        if (Time.SecondPeriod.contains(Game.GameTime.CurrentTime))
            return GetCurriculum(Game.SchoolCalendar.TodayDate.DayOfWeek, 1);

        if (Time.ThirdPeriod.contains(Game.GameTime.CurrentTime))
            return GetCurriculum(Game.SchoolCalendar.TodayDate.DayOfWeek, 2);

        if (Time.FourthPeriod.contains(Game.GameTime.CurrentTime))
            return GetCurriculum(Game.SchoolCalendar.TodayDate.DayOfWeek, 3);

        return GetCurriculum(Game.SchoolCalendar.TodayDate.DayOfWeek, 0);
    }
    SchoolSubject GetCurriculum(DayOfWeek Day, byte Slot)
    {
        switch (Day)
        {
        case DayOfWeek::Monday:
            return Game.GetSubject(Monday[(int)Slot]);
        case DayOfWeek::Tuesday:
            return Game.GetSubject(Tuesday[(int)Slot]);
        case DayOfWeek::Wednesday:
            return Game.GetSubject(Wednesday[(int)Slot]);
        case DayOfWeek::Thursday:
            return Game.GetSubject(Thursday[(int)Slot]);
        case DayOfWeek::Friday:
            return Game.GetSubject(Friday[(int)Slot]);
        default:
            return NULL;
        }
    }
    void SetCurriculum(SchoolSubject S)
    {
        if (Time.SecondPeriod.contains(Game.GameTime.CurrentTime))
            SetCurriculum(S, Game.SchoolCalendar.TodayDate.DayOfWeek, 1);

        if (Time.ThirdPeriod.contains(Game.GameTime.CurrentTime))
            SetCurriculum(S, Game.SchoolCalendar.TodayDate.DayOfWeek, 2);

        if (Time.FourthPeriod.contains(Game.GameTime.CurrentTime))
            SetCurriculum(S, Game.SchoolCalendar.TodayDate.DayOfWeek, 3);

        SetCurriculum(S, Game.SchoolCalendar.TodayDate.DayOfWeek, 0);
    }
    void SetCurriculum(SchoolSubject S, DayOfWeek Day, byte Slot)
    {
        if (S != NULL)
        {
            switch (Day)
            {
            case DayOfWeek::Monday:
                Monday[(int)Slot] = S.Name;
                return;
            case DayOfWeek::Tuesday:
                Tuesday[(int)Slot] = S.Name;
                return;
            case DayOfWeek::Wednesday:
                Wednesday[(int)Slot] = S.Name;
                return;
            case DayOfWeek::Thursday:
                Thursday[(int)Slot] = S.Name;
                return;
            case DayOfWeek::Friday:
                Friday[(int)Slot] = S.Name;
                break;
            default:
                return;
            }
        }
    }
    void CopyMondayTo(DayOfWeek Day)
    {
        switch (Day)
        {
        case DayOfWeek::Tuesday:
            Tuesday[0] = Monday[0];
            Tuesday[1] = Monday[1];
            Tuesday[2] = Monday[2];
            Tuesday[3] = Monday[3];
            return;
        case DayOfWeek::Wednesday:
            Wednesday[0] = Monday[0];
            Wednesday[1] = Monday[1];
            Wednesday[2] = Monday[2];
            Wednesday[3] = Monday[3];
            return;
        case DayOfWeek::Thursday:
            Thursday[0] = Monday[0];
            Thursday[1] = Monday[1];
            Thursday[2] = Monday[2];
            Thursday[3] = Monday[3];
            return;
        case DayOfWeek::Friday:
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
        Monday[(int)Slot] = Monday[0];
        Tuesday[(int)Slot] = Tuesday[0];
        Wednesday[(int)Slot] = Wednesday[0];
        Thursday[(int)Slot] = Thursday[0];
        Friday[(int)Slot] = Friday[0];
    }
    Location GetLessonLocation()
    {
        if (Game.ClassAssignments == NULL)
            return NULL;

        if (Game.ClassAssignments.AssignedClassrooms.ContainsKey(ClassIndex))
            return Game.GetLocation(Game.ClassAssignments.AssignedClassrooms[ClassIndex]);

        return NULL;

    }
    void AddStudent(Person Student)
    {
        //object obj = thisLock;
        //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        if (!Students.contains(Student))
            Students.Add(Student);

        Student.Schoolclass = ClassIndex;
        if (this != Game.SpareStudentsClass)
            Game.SpareStudentsClass.RemoveStudent(Student);
        // }
    }
    void RemoveStudent(Person Student)
    {
        //object obj = thisLock;
        //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        Students.Remove(Student);
        if (this != Game.SpareStudentsClass && !Game.SpareStudentsClass.Students.contains(Student))
            Game.SpareStudentsClass.AddStudent(Student);

        // }
    }
    void RemoveRandomStudent()
    {
        //object obj = thisLock;
        //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        int index = Game.RNG.Next(Students.count());
        Person Student = Students[index];
        Students.removeAt(index);
        if (this != Game.SpareStudentsClass && !Game.SpareStudentsClass.Students.contains(Student))
            Game.SpareStudentsClass.AddStudent(Student);

        // }
    }
    void RemoveAllStudents()
    {
        //object obj = thisLock;
        //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
        // lock (obj) {
        // try {
        for (QList<Person>::iterator stud = Students.begin(); stud != Students.end(); ++stud)
            if (this != Game.SpareStudentsClass && !Game.SpareStudentsClass.Students.contains(*stud))
                Game.SpareStudentsClass.AddStudent(*stud);

        // }
        Students.clear();
        // }
    }
    QString ToString()
    {
        return "SchoolClass: " + Conversions.ToString(ClassIndex);
    }
    void UpdateSchoolClasses()
    {
        if (!Game.ListSchoolClasses.contains(Game.SpareStudentsClass))
            Game.ListSchoolClasses.Add(Game.SpareStudentsClass);

        // checked {
        while (Game.ListSchoolClasses.count() - 1 < Game.DesiredNumSchoolClasses)
        {
            Game.ListSchoolClasses.Insert(Game.ListSchoolClasses.count() - 1, new SchoolClass
            {
                ClassIndex = Game.ListSchoolClasses.count()
            });
        }
        while (Game.ListSchoolClasses.count() - 1 > Game.DesiredNumSchoolClasses)
        {
            SchoolClass deleteClass = Game.ListSchoolClasses[Game.ListSchoolClasses.count() - 2];
            deleteClass.RemoveAllStudents();
            Game.ListSchoolClasses.Remove(deleteClass);
        }
        if (Game.ListSchoolClasses.count() - 1 > 0)
            SchoolClass.DistributeSpareStudentsToClasses();
        // }
    }
    void DistributeSpareStudentsToClasses()
    {
        SchoolClassStudentCountComparer studentCountComparer = new SchoolClassStudentCountComparer();
        QList<SchoolClass> classesSorted = new QList<SchoolClass>(Game.ListSchoolClasses);
        classesSorted.RemoveAll((SchoolClass._ClosureS__.SI30_0 == NULL) ? (SchoolClass._ClosureS__.SI30_0 = new Predicate<SchoolClass>(SchoolClass._ClosureS__.SI._LambdaS__30_0)) : SchoolClass._ClosureS__.SI30_0);
        classesSorted.Sort(studentCountComparer);
        while (Game.SpareStudentsClass.Students.count() > 0 && classesSorted[0].Students.count() < 40)
        {
            int index = Game.RNG.Next(Game.SpareStudentsClass.Students.count());
            classesSorted[0].AddStudent(Game.SpareStudentsClass.Students[index]);
            classesSorted.Sort(studentCountComparer);
        }
    }
    void DistributeStudentToClass(Person Student)
    {
        if (Game.ListSchoolClasses.count() <= 1)
        {
            Game.SpareStudentsClass.AddStudent(Student);
            return;
        }
        SchoolClassStudentCountComparer studentCountComparer = new SchoolClassStudentCountComparer();
        QList<SchoolClass> classesSorted = new QList<SchoolClass>(Game.ListSchoolClasses);
        classesSorted.RemoveAll((SchoolClass._ClosureS__.SI31_0 == NULL) ? (SchoolClass._ClosureS__.SI31_0 = new Predicate<SchoolClass>(SchoolClass._ClosureS__.SI._LambdaS__31_0)) : SchoolClass._ClosureS__.SI31_0);
        classesSorted.Sort(studentCountComparer);
        if (classesSorted[0].Students.count() < 40)
        {
            classesSorted[0].AddStudent(Student);
            return;
        }
        Game.SpareStudentsClass.AddStudent(Student);
    }
    void ApplyLessonProgress()
    {
        // try {
        IEnumerator<SchoolClass> enumerator = Game.ListSchoolClasses.Where((SchoolClass._ClosureS__.SI32_0 == NULL) ? (SchoolClass._ClosureS__.SI32_0 = new Func<SchoolClass, bool>(SchoolClass._ClosureS__.SI._LambdaS__32_0)) : SchoolClass._ClosureS__.SI32_0).GetEnumerator();
        while (enumerator.MoveNext())
        {
            SchoolClass sc = enumerator.Current;
            if (!Game.ClassAssignments.AssignedSubjects.ContainsKey(sc.ClassIndex) || QString.IsNullOrEmpty(Game.ClassAssignments.AssignedSubjects[sc.ClassIndex]) || !Game.ClassAssignments.AssignedTeachers.ContainsKey(sc.ClassIndex))
            {
                SchoolSubject emptySubject = Game.GetSubject("");
                // try {
                for (QList<Person>::iterator stud = sc.Students.begin(); stud != sc.Students.end(); ++stud)
                    emptySubject.ApplyImprovementInfluence(*stud, 1.0);

                continue;
                // }
            }
            QString curSubjectName = Game.ClassAssignments.AssignedSubjects[sc.ClassIndex];
            Person curTeacher = Game.GetPerson(Game.ClassAssignments.AssignedTeachers[sc.ClassIndex]);
            SchoolSubject curSubject = Game.GetSubject(curSubjectName);
            double teacherXP = curTeacher.GetSubjectExp(curSubjectName);
            // try {
            for (QList<Person>::iterator it = sc.Students.begin();
                    it != sc.Students.end(); ++it)
            {
                Person stud2 = enumerator3.Current;
                double gainedXP = teacherXP / 50.0;
                stud2.AddSubjectExp(curSubjectName, gainedXP * (1.0 + curSubject.GetLearningBoostInfluence(stud2)));
            }
            // }
            curTeacher.AddSubjectExp(curSubjectName, curTeacher.GetStat("Intelligence") / 100.0 * (1.0 + curSubject.GetLearningBoostInfluence(curTeacher)));
        }
        // }
    }
};

#endif // SCHOOLCLASS_H
