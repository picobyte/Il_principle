#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QJsonObject>;

enum Payperiode
{
    OneTime,
    Daily,
    Weekly,
    Monthly
};

class Account
{
public:
    Account() {}
    Account(QJsonObject &v):
        //Name(v["Name"].toString()),
        SortOrder(v["SortOrder"].toInt()),
        PayPeriode(static_cast<Payperiode>(v["PayPeriode"].toInt())),
        Payment(v["Payment"].toInt()),
        Active(v["Active"].toBool()),
        NoWeekend(v["NoWeekend"].toBool())
    {}
    //QString Name;
    int SortOrder;
    Payperiode PayPeriode;
    int Payment;
    bool Active;
    bool NoWeekend;
};

#endif // ACCOUNT_H
