#pragma once
#include "pch.h"

template<class T>
__interface HeapItem
{
public:
	uint32 GetHeapIndex() const;
	void SetHeapIndex(uint32);
	bool HeapLowerIndexThan(T other) const;
};

template<class T>
class Heap
{
public:
	inline Heap(uint32 maxSize) : m_maxSize(maxSize) { m_items = new T[maxSize]; }
	inline ~Heap() { delete[] m_items; }
	
	inline void Add(T& item)
	{
		m_items[m_arrayIndex] = item;

		item->SetHeapIndex(m_arrayIndex);
		SortUp(item);
		m_arrayIndex++;
	}

	inline T RemoveFirstItem()
	{
		T first = m_items[0];
		m_arrayIndex--;
		m_items[0] = m_items[m_arrayIndex];
		m_items[0]->SetHeapIndex(0);
		SortDown(m_items[0]);
		return first;
	}

	inline void SortUp(T item)
	{
		if (m_arrayIndex == 0) return;

		uint32 parentIndex = (item->GetHeapIndex() - 1) / 2;
		while (1)
		{
			T parent = m_items[parentIndex];

			if (!item->HeapLowerIndexThan(parent)) return;

			Swap(item, parent);

			if (item->GetHeapIndex() == 0) return;
			parentIndex = (item->GetHeapIndex() - 1) / 2;
		}
	}

	inline void SortDown(T item)
	{
		while (1)
		{
			uint32 left = item->GetHeapIndex() * 2 + 1;
			uint32 right = left + 1;
			uint32 swapIndex = left;

			if (left > m_arrayIndex) return;

			if (right <= m_arrayIndex && !m_items[left]->HeapLowerIndexThan(m_items[right]))
			{
				swapIndex = right;
			}

			if (!item->HeapLowerIndexThan(m_items[swapIndex])) return;

			Swap(item, m_items[swapIndex]);
		}
	}

	inline bool IsElement(T item) { return (item->GetHeapIndex() >= m_arrayIndex ? false : m_items[item->GetHeapIndex()] == item); }
	inline void Update(T item) { ASSERT(IsElement(item), "The item is not an element in the heap."); SortDown(item); }
	inline uint32 size() const { return m_arrayIndex; }
private:
	uint32 m_maxSize;

	T* m_items;
	uint32 m_arrayIndex = 0;

	inline void Swap(T& a, T& b)
	{
		uint32 aIndex = a->GetHeapIndex();

		m_items[aIndex] = b;
		m_items[b->GetHeapIndex()] = a;

		a->SetHeapIndex(b->GetHeapIndex());
		b->SetHeapIndex(aIndex);
	}
};