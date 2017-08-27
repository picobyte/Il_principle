#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QList>
#include <QDateTime>

class Person {
public:
    long UID;
    QString forename;
    QString lastname;
    QString customForename;
    //Gender Gender;
    QDateTime Birthday;
    bool SpecialPerson;
    QString TextColor;
    QString InitParams;
    //SerializableAttributeDictionary<Gender, double> GenderPreferences;
    //QList<Fetish> Fetish;
    bool Virgin;
    bool AnalVirgin;
    QString Job;
    uint intJobSlot;
    int Salary;
    //static readonly object unemployedQListLock = RuntimeHelpers.GetObjectValue(new object());
    //static readonly object jobLock = RuntimeHelpers.GetObjectValue(new object());
    QList<QString> Children;
    QString intFather;
    QString intMother;
    QString intLove;
    bool Autoenroll;
    int Schoolclass;
    QString Subject;
    QString GoodInSubject;
    QList<QString> TeacherSubjects;
    //SerializableAttributeDictionary<SchoolSubjectFamily, double> SubjectFamilyExp;
    //SerializableAttributeDictionary<QString, double> SubjectInstanceExp;
    //readonly object subjectStatLock;
    //SerializableStringToDoubleDict DictProposalSupport;
    bool HasDetention;
    bool IsRogue;
    QString ClubMember;
    QString ImageLocation;
    QString PaperDollEventFileName;
    //FacialExpressions FaceExpression;
    QString MaleHeadFileName;
    QString FemaleHeadFileName
