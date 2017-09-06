#ifndef WEIGHTEDRANDOMIZER_H
#define WEIGHTEDRANDOMIZER_H
#include "json_macros.h"

class WeightedRandomizer {
public:
	void AddItem(int weight, ref T obj)
	{
		if (weight <= 0)
			throw new ArgumentOutOfRangeException("weight", "Item weight must be a positive integer.");

		if (Count == 0)
		{
			Add(weight, obj);
			return;
		}
		int priorMax = Last<KeyValuePair<int, T>>().Key;
		Add(checked(weight + priorMax), obj);
	}
	T GetRandomItem()
	{
		if (Count == 0)
			throw new KeyNotFoundException("Collection is empty.");

		int dart = Game.RNG.Next(Last<KeyValuePair<int, T> >().Key);
		T GetRandomItem = default(T);
		// try {
		for (SortedDictionary<int, T>::iterator it = Keys.begin();
				it != Keys.end(); ++it)
			if (dart < *it)
				return base[*it];
		// }
		return GetRandomItem;
	}

	WeightedRandomizer(QJsonObject *d = NULL) {}
};

#endif // WEIGHTEDRANDOMIZER_H
