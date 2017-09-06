#ifndef CLASSROOMASSIGNMENTS_H
#define CLASSROOMASSIGNMENTS_H
#include "json_macros.h"

class ClassroomAssignments {
    QHash<int, QString> AssignedClassrooms;
    QHash<int, QString> AssignedSubjects;
    QHash<int, QString> AssignedTeachers;
public:
    DayOfWeek CurrentDay;
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
    void AssignClassrooms(DayOfWeek Day, int Slot)
    {
        ClassroomAssignments._ClosureS__6_0 closureS__6_ = new ClassroomAssignments._ClosureS__6_0();
        closureS__6_.SVBSMe = this;
        closureS__6_.SVBSLocal_Day = Day;
        closureS__6_.SVBSLocal_Slot = Slot;
        UnassignClassrooms();
        CurrentDay = closureS__6_.SVBSLocal_Day;
        CurrentSlot = closureS__6_.SVBSLocal_Slot;
        QHash<QString, int> potentialLocations = new QHash<QString, int>();
        QList<SchoolSubject> subjects = new QList<SchoolSubject>();
        // checked {
        // try {
        for (QList<SchoolClass>::iterator it = Game.ListSchoolClasses.begin();
                it != Game.ListSchoolClasses.end(); ++it)
        {
            SchoolSubject s = enumerator.Current.GetCurriculum(closureS__6_.SVBSLocal_Day, (byte)closureS__6_.SVBSLocal_Slot);
            QList<QString> locs = s.GetAvailableLessonLocations();
            if (s.CanBeTaught && locs.count() > 0)
            {
                subjects.Add(s);
                // try {
                for (QList<QString>::iterator it2 = locs.begin();
                        it2 != locs.end(); ++it2)
                {
                    QString locName = enumerator2.Current;
                    if (potentialLocations.ContainsKey(locName))
                    {
                        QHash<QString, int> dictionary;
                        QString key;
                        (dictionary = potentialLocations)[key = locName] = dictionary[key] + 1;
                    }
                    else
                        potentialLocations.Add(locName, 1);
                }
                // }
            }
        }
        // }
        QHash<SchoolSubject, int> subjectAlternatives = new QHash<SchoolSubject, int>();
        while (subjects.count() > 0)
        {
            ClassroomAssignments._ClosureS__6_1 closureS__6_2 = new ClassroomAssignments._ClosureS__6_1();
            closureS__6_2.SVBSNonLocal_SVBSClosure_2 = closureS__6_;
            QString bestLoc = potentialLocations.FindMinimumKeyValue<QString>();
            subjectAlternatives.Clear();
            // try {
            for (QList<SchoolSubject>::iterator it = subjects.begin();
                    it != subjects.end(); ++it)
            {
                SchoolSubject s2 = enumerator3.Current;
                QList<QString> lessonLocs = s2.GetAvailableLessonLocations();
                if (lessonLocs.contains(bestLoc))
                {
                    if (subjectAlternatives.ContainsKey(s2))
                    {
                        QHash<SchoolSubject, int> dictionary2;
                        SchoolSubject key2;
                        (dictionary2 = subjectAlternatives)[key2 = s2] = dictionary2[key2] + lessonLocs.count();
                    }
                    else
                        subjectAlternatives.Add(s2, lessonLocs.count());
                }
            }
            // }
            closureS__6_2.SVBSLocal_bestSubject = subjectAlternatives.FindMinimumKeyValue<SchoolSubject>();
            SchoolClass assignClass = Game.ListSchoolClasses.Find((SchoolClass sc) => sc.GetCurriculum(closureS__6_2.SVBSNonLocal_SVBSClosure_2.SVBSLocal_Day, (byte)closureS__6_2.SVBSNonLocal_SVBSClosure_2.SVBSLocal_Slot) == closureS__6_2.SVBSLocal_bestSubject && !closureS__6_2.SVBSNonLocal_SVBSClosure_2.SVBSMe.AssignedClassrooms.ContainsKey(sc.ClassIndex));
            AssignedClassrooms.Add(assignClass.ClassIndex, bestLoc);
            AssignedSubjects.Add(assignClass.ClassIndex, closureS__6_2.SVBSLocal_bestSubject.Name);
            potentialLocations.Remove(bestLoc);
            QList<QString> locs2 = closureS__6_2.SVBSLocal_bestSubject.GetAvailableLessonLocations();
            // try {
            for (QList<QString>::iterator it = locs2.begin();
                    it != locs2.end(); ++it)
            {
                QString locName2 = enumerator4.Current;
                if (potentialLocations.ContainsKey(locName2))
                {
                    QHash<QString, int> dictionary;
                    QString key;
                    (dictionary = potentialLocations)[key = locName2] = dictionary[key] - 1;
                    if (potentialLocations[locName2] <= 0)
                        potentialLocations.Remove(locName2);
                }
            }
            // }
            subjects.Remove(closureS__6_2.SVBSLocal_bestSubject);
        }
        QHash<QString, int> teacherSubjects = new QHash<QString, int>();
        QList<QString> processedSubjects = new QList<QString>();
        // try {
        for (QHash<int, QString>::iterator it = AssignedSubjects.Values.begin();
                it != AssignedSubjects.Values.end(); ++it)
        {
            QString subName = enumerator5.Current;
            if (!processedSubjects.contains(subName))
            {
                // try {
                for (IEnumerator<Person>::iterator it2 = Game.HiredTeacher.Values.begin();
                        it2 != Game.HiredTeacher.Values.end(); ++it2)
                {
                    if (enumerator6.Current.TeacherSubjects.contains(subName))
                    {
                        if (teacherSubjects.ContainsKey(subName))
                        {
                            QHash<QString, int> dictionary;
                            QString key;
                            (dictionary = teacherSubjects)[key = subName] = dictionary[key] + 1;
                        }
                        else
                        {
                            teacherSubjects.Add(subName, 1);
                        }
                    }
                }
                // }
                processedSubjects.Add(subName);
            }
        }
        while (teacherSubjects.count() > 0) {
                    // }
                    ClassroomAssignments._ClosureS__6_2 closureS__6_3 = new ClassroomAssignments._ClosureS__6_2();
                    closureS__6_3.SVBSNonLocal_SVBSClosure_3 = closureS__6_;
                    closureS__6_3.SVBSLocal_curSubject = teacherSubjects.FindMinimumKeyValue<QString>();
                    QHash<Person, int> potentialTeachers = new QHash<Person, int>();
                    // try {
                    for (IEnumerator<Person>::iterator it = Game.HiredTeacher.Values.begin();
                                    it != Game.HiredTeacher.Values.end(); ++it)
                    {
                            Person t = enumerator7.Current;
                            if (t.TeacherSubjects.contains(closureS__6_3.SVBSLocal_curSubject) && !AssignedTeachers.ContainsValue(t.Name))
                                    potentialTeachers.Add(t, t.TeacherSubjects.count());
                    }
                    // }
                    Person bestTeacher = potentialTeachers.FindMinimumKeyValue<Person>();
                    SchoolClass assignClass2 = Game.ListSchoolClasses.Find((SchoolClass sc) => sc.GetCurriculum(closureS__6_3.SVBSNonLocal_SVBSClosure_3.SVBSLocal_Day, (byte)closureS__6_3.SVBSNonLocal_SVBSClosure_3.SVBSLocal_Slot).Name.Equals(closureS__6_3.SVBSLocal_curSubject) && !closureS__6_3.SVBSNonLocal_SVBSClosure_3.SVBSMe.AssignedTeachers.ContainsKey(sc.ClassIndex));
                    if (assignClass2 == NULL)
                    {
                            QHash<QString, int> dictionary;
                            QString key;
                            (dictionary = teacherSubjects)[key = closureS__6_3.SVBSLocal_curSubject] = dictionary[key] - potentialTeachers.count();
                            if (teacherSubjects[closureS__6_3.SVBSLocal_curSubject] <= 0)
                                    teacherSubjects.Remove(closureS__6_3.SVBSLocal_curSubject);
                    }
                    else if (bestTeacher != NULL)
                    {
                            AssignedTeachers.Add(assignClass2.ClassIndex, bestTeacher.Name);
                            bestTeacher.Work = Game.GetLocation(AssignedClassrooms[assignClass2.ClassIndex]);
                            // try {
                            for (QList<QString>::iterator it = bestTeacher.TeacherSubjects.begin();
                                            it != bestTeacher.TeacherSubjects.end(); ++it)
                            {
                                    QString subName2 = enumerator8.Current;
                                    if (teacherSubjects.ContainsKey(subName2))
                                    {
                                            QHash<QString, int> dictionary;
                                            QString key;
                                            (dictionary = teacherSubjects)[key = subName2] = dictionary[key] - 1;
                                            if (teacherSubjects[subName2] <= 0)
                                                    teacherSubjects.Remove(subName2);
                                    }
                            }
                            // }
                    }
                }
        // }
    }
    void UnassignClassrooms()
    {
        AssignedClassrooms.Clear();
        AssignedTeachers.Clear();
        AssignedSubjects.Clear();
    }
    void CheckUpdate()
    {
        if (!Game.SchoolCalendar.IsWeekend)
        {
            TimeData curTime = Game.GameTime.CurrentTime;
            if (gTime.FirstPeriod.StartTime.Equals(curTime))
            {
                Game.ClassAssignments.AssignClassrooms(Game.SchoolCalendar.TodayDate.DayOfWeek, 0);
                return;
            }
            if (gTime.SecondPeriod.StartTime.Equals(curTime))
            {
                Game.ClassAssignments.AssignClassrooms(Game.SchoolCalendar.TodayDate.DayOfWeek, 1);
                return;
            }
            if (gTime.ThirdPeriod.StartTime.Equals(curTime))
            {
                Game.ClassAssignments.AssignClassrooms(Game.SchoolCalendar.TodayDate.DayOfWeek, 2);
                return;
            }
            if (gTime.FourthPeriod.StartTime.Equals(curTime))
            {
                Game.ClassAssignments.AssignClassrooms(Game.SchoolCalendar.TodayDate.DayOfWeek, 3);
                return;
            }
            if (gTime.FirstPeriod.EndTime.Equals(curTime) || gTime.SecondPeriod.EndTime.Equals(curTime) || gTime.ThirdPeriod.EndTime.Equals(curTime) || gTime.FourthPeriod.EndTime.Equals(curTime))
            {
                SchoolClass.ApplyLessonProgress();
                Game.ClassAssignments.UnassignClassrooms();
            }
        }
    }
};

#endif // CLASSROOMASSIGNMENTS_H
