#ifndef MIND_H
#define MIND_H
#include "json_macros.h"

class Mind {
public:
	QList<Adjustment> AdjustStatQList;

	Mind(QJsonObject *d = NULL)
	{
		if (d) init(d);
	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			//QList<Adjustment> AdjustStatQList
		}
	}
};

#endif // MIND_H
