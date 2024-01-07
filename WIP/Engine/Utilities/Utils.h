/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

#include "pch.h"

namespace jci {

class Utils
{
public:
	template<class T>
	inline static void RemoveFromVectorByBackCopy(T objectBeingRemoved, std::vector<T>& vector)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector[i] != objectBeingRemoved) continue;

			vector[i] = vector.back();
			vector.pop_back();
		}
	}

	template<class T>
	inline static bool ListContains(const std::list<T>& list, T item)
	{
		for (auto it = list.begin(); it != list.end(); it++)
		{
			if (*it == item)
			{
				return true;
			}
		}

		return false;
	}

	template<class T>
	inline static bool VectorContains(const std::vector<T>& vec, const T& item)
	{
		for (T element : vec)
		{
			if (element == item)
			{
				return true;
			}
		}
		
		return false;
	}
};

} // Namespace jci.