#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H
#include <QColor>
#include "json_macros.h"
#include "person.h"
#include "game.h"

class NotificationManager {
public:
    ObjectPool<NotificationPopup> notificationPool;
    TimedQueueManager playerNotifications;
    TimedQueueManager occupantNotifications;
    QHash<QString, TimedQueueManager> globalStatNotifications;
    bool disposedValue;

    NotificationManager(QJsonObject *d = NULL)
    {
        if (d) init(d);
        playerNotifications = new TimedQueueManager(0);
        occupantNotifications = new TimedQueueManager(0);
        globalStatNotifications = new QHash<QString, TimedQueueManager>();
        notificationPool = new ObjectPool<NotificationPopup>(new Func<NotificationPopup>(generateNotificationPopup));
        globalStatNotifications.Add("Money", new TimedQueueManager(1));
        globalStatNotifications.Add("Reputation", new TimedQueueManager(1));
        globalStatNotifications.Add("Students", new TimedQueueManager(1));
        // try {
        for (QList<QString>::iterator it = Game.TheSchool.GlobalStats.begin();
                it != Game.TheSchool.GlobalStats.end(); ++it)
        {
            QString stat = enumerator.Current;
            globalStatNotifications.Add(stat, new TimedQueueManager(1));
        }
        // }
    }
    void init(QJsonObject *d)
    {
        for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
            // *INDENT-OFF*
            __IF_OBJ_FROM_JSON(it, playerNotifications)
            else __IF_OBJ_FROM_JSON(it, occupantNotifications)
            else __IF_VAR_FROM_JSON_AS(it, disposedValue, toBool)
            // *INDENT-ON*
        }
    }
    void EnqueueNotification(Person owner, QString text, QColor color)
    {
        if (owner == Game.HeadTeacher)
        {
            VBSAnonymousDelegate_1 SI1 = NULL;
            playerNotifications.Enqueue(delegate
            {
                System.Windows.Application.Current.Dispatcher.BeginInvoke((SI1 == NULL) ? (SI1 = delegate
                {
                    notificationPool.GetObject().StartAnimation(text, color, GetOriginPoint(owner), new Vector(0.0, -80.0), new TimeSpan(17500000L), new TimeSpan(25000000L));
                }) : SI1, new object[0]);
            });
            return;
        }
        VBSAnonymousDelegate_1 SI3 = NULL;
        occupantNotifications.Enqueue(delegate
        {
            System.Windows.Application.Current.Dispatcher.BeginInvoke((SI3 == NULL) ? (SI3 = delegate
            {
                notificationPool.GetObject().StartAnimation(text, color, GetOriginPoint(owner), new Vector(0.0, -80.0), new TimeSpan(17500000L), new TimeSpan(25000000L));
            }) : SI3, new object[0]);
        });
    }
    void EnqueueGlobalNotification(QString key, QString text, QColor color)
    {
        if (globalStatNotifications.ContainsKey(key))
        {
            VBSAnonymousDelegate_1 SI1 = NULL;
            globalStatNotifications[key].Enqueue(delegate
            {
                System.Windows.Application.Current.Dispatcher.BeginInvoke((SI1 == NULL) ? (SI1 = delegate
                {
                    notificationPool.GetObject().StartAnimation(text, color, GetGlobalOriginPoint(key), new Vector(0.0, 60.0), new TimeSpan(20000000L), new TimeSpan(30000000L));
                }) : SI1, new object[0]);
            });
        }
    }
    Point GetOriginPoint(Person owner)
    {
        Point GetOriginPoint;
        if (owner == Game.HeadTeacher)
        {
            Point startPoint = FormManager.GameForm.lblPlayerInfo.TransformToAncestor(FormManager.GameForm).Transform(new Point(FormManager.GameForm.Left, FormManager.GameForm.Top));
            GetOriginPoint = new Point(startPoint.X + FormManager.GameForm.lblPlayerInfo.ActualWidth / 2.0, startPoint.Y);
        }
        else
        {
            GetOriginPoint = FormManager.GameForm.lbOccupants.TransformToAncestor(FormManager.GameForm).Transform(new Point(FormManager.GameForm.Left, FormManager.GameForm.Top));
        }
        return GetOriginPoint;
    }
    Point GetGlobalOriginPoint(QString key)
    {
        FrameworkElement baseComponent;
        if (Operators.CompareString(key, "Students", false) != 0)
        {
            if (Operators.CompareString(key, "Reputation", false) != 0)
            {
                if (Operators.CompareString(key, "Money", false) != 0)
                {
                    baseComponent = FormManager.GameForm.ucGlobalStats.statLabels[key];
                }
                else
                {
                    baseComponent = FormManager.GameForm.ucGlobalStats.lblMoney;
                }
            }
            else
            {
                baseComponent = FormManager.GameForm.ucGlobalStats.lblReputation;
            }
        }
        else
        {
            baseComponent = FormManager.GameForm.ucGlobalStats.lblStudents;
        }
        Point startPoint = baseComponent.TransformToAncestor(FormManager.GameForm).Transform(new Point(FormManager.GameForm.Left, FormManager.GameForm.Top));
        return new Point(startPoint.X + baseComponent.ActualWidth / 2.0, startPoint.Y + baseComponent.ActualHeight);
    }
    void HandleSkillNotification(Person* per, QString& skill, int change)
    {
        if (per && per == Game::HeadTeacher)
        {
            if (change > 0)
            {
                EnqueueNotification(per, QString:asprintf("+%d ", change) + skill, QColor(0x7f,0xff,0x0));
                return;
            }
            if (change < 0)
            {
                EnqueueNotification(per, QString:asprintf("+%d ", change) +  skill, QColor(0xff,0x45,0x0));
            }
        }
    }
    void Dispose()
    {
        Dispose(true);
    }
};

#endif // NOTIFICATIONMANAGER_H
