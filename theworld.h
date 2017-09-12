#ifndef THEWORLD_H
#define THEWORLD_H
#include <QDateTime>
#include "location.h"
#include "schoolupgrade.h"

namespace TheWorld {
    namespace {
        double reputation;
        int money;
        QList<QString> GlobalStats;
        //QList<UIProgressBarDefinition> ProgressBarStats;
        QList<Location> ListOfWorkplaces;
    }
    QHash<const QString&, Location> DictOfLocation;
    QString Name;
    QString Description;
    int SortOrder;
    QString FolderLocation;
    QString FilePath = "";
    int MaxGeneratedWorldPopulation = 1200;
    int MinEnrolledStudentCount = 75;
    int MaxEnrolledStudentCount = 400;
    QDate MinDate = QDate(2010, 2, 1);
    QDate MaxDate = QDate(2012, 6, 30);
    int MaxStartFetishes;
    QString StartLocationName;
    QString MapLocationName;

    double get_Reputation()
    {
        return reputation;
    }
    void set_Reputation(double& value)
    {
        reputation = value < 0.0 ? 0.0 : (value > 100.0 ? 100.0 : value);
    }
    int get_Money()
    {
        return money;
    }
        void set_Money(int& value)
    {
        money = value < -999999999 ? -999999999 : (value > 999999999 ? 999999999 : value);
    }
    static inline uint32_t ShiftAndWrap (uint32_t n, unsigned int c)
    {
        const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);  // assumes width is a power of 2.
        c &= mask;
        return (n<<c) | (n>>( (-c)&mask ));
    }
    int GetChecksum()
    {
        return ShiftAndWrap(qHash(Name), 2)
                ^ ShiftAndWrap(qHash(FolderLocation), 3)
                ^ ShiftAndWrap(17 * MaxGeneratedWorldPopulation, 4)
                ^ ShiftAndWrap(17 * MinEnrolledStudentCount, 5)
                ^ ShiftAndWrap(17 * MaxEnrolledStudentCount, 6)
                /*^ ShiftAndWrap(17 * Game.DictOfStats.count(), 7)*/
                ^ ShiftAndWrap(qHash(StartLocationName), 8)
                ^ ShiftAndWrap(qHash(MapLocationName), 9)
                ^ ShiftAndWrap(17 * DictOfLocation.count(), 10);
    }
}

#endif // THEWORLD_H
