#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include "json_macros.h"

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
    Account(QJsonObject *d = NULL) {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_ENUM_FROM_JSON_AS(it, PayPeriode, Payperiode)
            else __IF_VAR_FROM_JSON_AS(it, Payment, toInt)
            else __IF_VAR_FROM_JSON_AS(it, Active, toBool)
            else __IF_VAR_FROM_JSON_AS(it, NoWeekend, toBool)
        }
    }
    QString Name;
    int SortOrder;
    Payperiode PayPeriode;
    int Payment;
    bool Active;
    bool NoWeekend;
};

#endif // ACCOUNT_H
