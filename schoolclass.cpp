#include "game.h"
#include "schoolclass.h"

void SchoolClass::init(QJsonObject *d)
{
    for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
        // *INDENT-OFF*
        __IF_OBJLIST_FROM_JSON(it, Students, Person)
        else __IF_VAR_FROM_JSON_AS(it, ClassIndex, toInt)
        //else __IF_OBJ_FROM_JSON(it, thisLock)
        // *INDENT-ON*
    }
}

SchoolSubject SchoolClass::GetCurriculum() const
{
    if (gTime::SecondPeriod.contains(Game::GameTime.CurrentTime))
        return GetCurriculum(Game::SchoolCalendar.TodayDate.DayOfWeek, 1);

    if (gTime::ThirdPeriod.contains(Game::GameTime.CurrentTime))
        return GetCurriculum(Game::SchoolCalendar.TodayDate.DayOfWeek, 2);

    if (gTime::FourthPeriod.contains(Game::GameTime.CurrentTime))
        return GetCurriculum(Game::SchoolCalendar.TodayDate.DayOfWeek, 3);

    return GetCurriculum(Game::SchoolCalendar.TodayDate.DayOfWeek, 0);
}
SchoolSubject SchoolClass::GetCurriculum(DayOfWeek Day, size_t Slot) const
{
    switch (Day)
    {
    case DayOfWeek::Monday:
        return Game::GetSubject(Monday[Slot]);
    case DayOfWeek::Tuesday:
        return Game::GetSubject(Tuesday[Slot]);
    case DayOfWeek::Wednesday:
        return Game::GetSubject(Wednesday[Slot]);
    case DayOfWeek::Thursday:
        return Game::GetSubject(Thursday[Slot]);
    case DayOfWeek::Friday:
        return Game::GetSubject(Friday[Slot]);
    default:
        return NULL;
    }
}
void SchoolClass::SetCurriculum(SchoolSubject S)
{
    if (gTime::SecondPeriod.contains(Game::GameTime.CurrentTime))
        SetCurriculum(S, Game::SchoolCalendar.TodayDate.DayOfWeek, 1);

    if (gTime::ThirdPeriod.contains(Game::GameTime.CurrentTime))
        SetCurriculum(S, Game::SchoolCalendar.TodayDate.DayOfWeek, 2);

    if (gTime::FourthPeriod.contains(Game::GameTime.CurrentTime))
        SetCurriculum(S, Game::SchoolCalendar.TodayDate.DayOfWeek, 3);

    SetCurriculum(S, Game::SchoolCalendar.TodayDate.DayOfWeek, 0);
}
Location* SchoolClass::GetLessonLocation() const
{
    if (Game::ClassAssignments == NULL)
        return NULL;

    if (Game::ClassAssignments.AssignedClassrooms.ContainsKey(ClassIndex))
        return Game::GetLocation(Game::ClassAssignments.AssignedClassrooms[ClassIndex]);

    return NULL;

}

void SchoolClass::AddStudent(Person Student)
{
    //object obj = thisLock;
    //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
    // lock (obj) {
    if (!Students.contains(Student))
        Students.Add(Student);

    Student.Schoolclass = ClassIndex;
    if (this != Game::SpareStudentsClass)
        Game::SpareStudentsClass.RemoveStudent(Student);
    // }
}
void SchoolClass::RemoveStudent(Person Student)
{
    //object obj = thisLock;
    //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
    // lock (obj) {
    Students.Remove(Student);
    if (this != Game::SpareStudentsClass && !Game::SpareStudentsClass.Students.contains(Student))
        Game::SpareStudentsClass.AddStudent(Student);

    // }
}
void SchoolClass::RemoveRandomStudent()
{
    //object obj = thisLock;
    //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
    // lock (obj) {
    int index = Game::RNG.Next(Students.count());
    Person Student = Students[index];
    Students.removeAt(index);
    if (this != Game::SpareStudentsClass && !Game::SpareStudentsClass.Students.contains(Student))
        Game::SpareStudentsClass.AddStudent(Student);

    // }
}
void SchoolClass::RemoveAllStudents()
{
    //object obj = thisLock;
    //ObjectFlowControl.CheckForSyncLockOnValueType(obj);
    // lock (obj) {
    // try {
    for (QList<Person>::iterator stud = Students.begin(); stud != Students.end(); ++stud)
        if (this != Game::SpareStudentsClass && !Game::SpareStudentsClass.Students.contains(*stud))
            Game::SpareStudentsClass.AddStudent(*stud);

    // }
    Students.clear();
    // }
}
QString SchoolClass::ToString() const
{
    return "SchoolClass: " + Conversions.ToString(ClassIndex);
}
void SchoolClass::UpdateSchoolClasses()
{
    if (!Game::ListSchoolClasses.contains(Game::SpareStudentsClass))
        Game::ListSchoolClasses.Add(Game::SpareStudentsClass);

    // checked {
    while (Game::ListSchoolClasses.count() - 1 < Game::DesiredNumSchoolClasses)
    {
        Game::ListSchoolClasses.Insert(Game::ListSchoolClasses.count() - 1, new SchoolClass
        {
            ClassIndex = Game::ListSchoolClasses.count()
        });
    }
    while (Game::ListSchoolClasses.count() - 1 > Game::DesiredNumSchoolClasses)
    {
        SchoolClass deleteClass = Game::ListSchoolClasses[Game::ListSchoolClasses.count() - 2];
        deleteClass.RemoveAllStudents();
        Game::ListSchoolClasses.Remove(deleteClass);
    }
    if (Game::ListSchoolClasses.count() - 1 > 0)
        SchoolClass.DistributeSpareStudentsToClasses();
    // }
}
void SchoolClass::DistributeSpareStudentsToClasses()
{
    SchoolClassStudentCountComparer studentCountComparer = new SchoolClassStudentCountComparer();
    QList<SchoolClass> classesSorted = new QList<SchoolClass>(Game::ListSchoolClasses);
    classesSorted.RemoveAll((SchoolClass._ClosureS__.SI30_0 == NULL) ? (SchoolClass._ClosureS__.SI30_0 = new Predicate<SchoolClass>(SchoolClass._ClosureS__.SI._LambdaS__30_0)) : SchoolClass._ClosureS__.SI30_0);
    classesSorted.Sort(studentCountComparer);
    while (Game::SpareStudentsClass.Students.count() > 0 && classesSorted[0].Students.count() < 40)
    {
        int index = Game::RNG.Next(Game::SpareStudentsClass.Students.count());
        classesSorted[0].AddStudent(Game::SpareStudentsClass.Students[index]);
        classesSorted.Sort(studentCountComparer);
    }
}
void SchoolClass::DistributeStudentToClass(Person Student)
{
    if (Game::ListSchoolClasses.count() <= 1)
    {
        Game::SpareStudentsClass.AddStudent(Student);
        return;
    }
    SchoolClassStudentCountComparer studentCountComparer = new SchoolClassStudentCountComparer();
    QList<SchoolClass> classesSorted = new QList<SchoolClass>(Game::ListSchoolClasses);
    classesSorted.RemoveAll((SchoolClass._ClosureS__.SI31_0 == NULL) ? (SchoolClass._ClosureS__.SI31_0 = new Predicate<SchoolClass>(SchoolClass._ClosureS__.SI._LambdaS__31_0)) : SchoolClass._ClosureS__.SI31_0);
    classesSorted.Sort(studentCountComparer);
    if (classesSorted[0].Students.count() < 40)
    {
        classesSorted[0].AddStudent(Student);
        return;
    }
    Game::SpareStudentsClass.AddStudent(Student);
}
void SchoolClass::ApplyLessonProgress()
{
    // try {
    IEnumerator<SchoolClass> enumerator = Game::ListSchoolClasses.Where((SchoolClass._ClosureS__.SI32_0 == NULL) ? (SchoolClass._ClosureS__.SI32_0 = new Func<SchoolClass, bool>(SchoolClass._ClosureS__.SI._LambdaS__32_0)) : SchoolClass._ClosureS__.SI32_0).GetEnumerator();
    while (enumerator.MoveNext())
    {
        SchoolClass sc = enumerator.Current;
        if (!Game::ClassAssignments.AssignedSubjects.ContainsKey(sc.ClassIndex) || QString.IsNullOrEmpty(Game::ClassAssignments.AssignedSubjects[sc.ClassIndex]) || !Game::ClassAssignments.AssignedTeachers.ContainsKey(sc.ClassIndex))
        {
            SchoolSubject emptySubject = Game::GetSubject("");
            // try {
            for (QList<Person>::iterator stud = sc.Students.begin(); stud != sc.Students.end(); ++stud)
                emptySubject.ApplyImprovementInfluence(*stud, 1.0);

            continue;
            // }
        }
        QString curSubjectName = Game::ClassAssignments.AssignedSubjects[sc.ClassIndex];
        Person curTeacher = Game::GetPerson(Game::ClassAssignments.AssignedTeachers[sc.ClassIndex]);
        SchoolSubject curSubject = Game::GetSubject(curSubjectName);
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
