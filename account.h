#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "json_macros.h"

class Account {
public:
    QString Name;
    int SortOrder;
    Payperiode PayPeriode;
    int Payment;
    bool Active;
    bool NoWeekend;

    const QString DailyColumn() const
    {
        if (Active && PayPeriode == Payperiode::Daily)
            return QLocale().toCurrencyString(Payment) + (NoWeekend ? "*" : "");

        return "";
    }
    const QString WeeklyColumn() const
    {
        if (PayPeriode != Payperiode::Daily)
        {
            if (PayPeriode != Payperiode::Weekly)
                return "";

            return QLocale().toCurrencyString(Payment);
        }
        return QLocale().toCurrencyString(Payment * (NoWeekend ? 5 : 7));
    }
    const QString MonthlyColumn() const
    {
        switch (PayPeriode)
        {
        case Payperiode::Daily:
            return QLocale().toCurrencyString(Payment * (NoWeekend ? 22 : 30));
        case Payperiode::Weekly:
            return QLocale().toCurrencyString(Payment * 4);
        case Payperiode::Monthly:
            return QLocale().toCurrencyString(Payment);
        default:
            return "";
        }
    }
    bool LessThanZero() const
    {
        return Payment < 0;
    }
    Account(QString n="", int p=0, Payperiode pp = Payperiode::OneTime, bool nw=false, bool actv=false, int so=0):
        Name(n), Payment(p), PayPeriode(pp), Active(nw), NoWeekend(actv), SortOrder(so)
    {}

    Account(QJsonObject *d): Account()
    {
        if (d) init(d);
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            __IF_VAR_FROM_JSON_AS(it, Name, toString)
            else __IF_VAR_FROM_JSON_AS(it, SortOrder, toInt)
            else __IF_ENUM_FROM_JSON_AS(it, PayPeriode, Payperiode)
            else __IF_VAR_FROM_JSON_AS(it, Payment, toInt)
            else __IF_VAR_FROM_JSON_AS(it, Active, toBool)
            else __IF_VAR_FROM_JSON_AS(it, NoWeekend, toBool)
        }
    }
    bool ShouldSerializePayment()
    {
        return Payment != 0;
    }
    bool ShouldSerializeActive()
    {
        return Active;
    }
    bool ShouldSerializeNoWeekend()
    {
        return NoWeekend;
    }
    QString ToString()
    {
        return "Account: " + Name;
    }
    double GetMonthlyBalance()
    {
        double balance = 0.0;
        /*IEnumerator<Account> enumerator = Game.DictOfAccounts.Values.GetEnumerator();
        while (enumerator.MoveNext())
        {
            Account ac = enumerator.Current;
            if (ac.Active)
            {
                switch (ac.PayPeriode)
                {
                case Payperiode.Daily:
                    if (ac.NoWeekend)
                    {
                        balance += ac.Payment * 260.0 / 12.0;
                    }
                    else
                    {
                        balance += ac.Payment * 365.0 / 12.0;
                    }
                    break;
                case Payperiode.Weekly:
                    balance += ac.Payment * 52.1429 / 12.0;
                    break;
                case Payperiode.Monthly:
                    balance += ac.Payment;
                    break;
                }
            }
        }*/
        return balance;
    }
};

#endif // ACCOUNT_H
