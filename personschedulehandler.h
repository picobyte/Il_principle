#ifndef PERSONSCHEDULEHANDLER_H
#define PERSONSCHEDULEHANDLER_H
#include "json_macros.h"

class PersonScheduleHandler {
public:
	int Priority;
	virtual bool IsApplicableFor(Person& Per)
	{
		return false;
	}
	//abstract void UpdateLocationFor(Person& P);
	Location GetRandomLocation(Gender ForGender, bool AllowSchoolAreas = false, bool AllowPrivateAreas = false, bool AllowNonBuiltAreas = false, bool AllowCityAreas = true, bool AllowClassrooms = false)
	{
		Location loc = NULL;
		bool found = false;
		int i = 0;
		// checked {
		while (!found)
		{
			loc = Location.GetRandomLocationWeighted(ForGender);
			found = ((AllowNonBuiltAreas || loc.Built) && (AllowSchoolAreas || loc.Region != Region.School || (AllowClassrooms && loc.IsClassroom)) && (AllowPrivateAreas || !loc.Description.contains("privatearea")) && (AllowCityAreas || loc.Region != Region.City) && (AllowClassrooms || !loc.IsClassroom));
			i++;
			if (i > 10000)
			{
				throw new TimeoutException("The operation was unable to find a random location for gender '" + Conversions.ToString((byte)ForGender) + "' in less than 10000 attempts. This may be a rare random occurrance or an actual problem.");
			}
		}
		return loc;
		// }
	}
	QString ToString()
	{
		return GetType().Name;
	}

	PersonScheduleHandler(QJsonObject *d = NULL)
	{
		if (d) init(d);

	}
	void init(QJsonObject *d)
	{
		for (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {
			// *INDENT-OFF*
			__IF_VAR_FROM_JSON_AS(it, Priority, toInt)
			// *INDENT-ON*
		}
	}
};
#endif // PERSONSCHEDULEHANDLER_H
