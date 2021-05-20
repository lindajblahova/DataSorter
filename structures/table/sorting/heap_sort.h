#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include "../../../Comparator.h"

namespace structures
{

	/// <summary> Triedenie Heap sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class HeapSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Heap sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
		void sort(UnsortedSequenceTable<K, T>& table, Comparator* comparator);
	};

	template<typename K, typename T>
	inline void HeapSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
        bool swap;
        // postavenie haldy
        for (int i = 1; i < table.size(); i++)
        {
            int current = i;
            do
            {
                swap = false;
                int parent = (current - 1) / 2;
                if (current > 0 && (table.getItemAtIndex(current).getKey() > table.getItemAtIndex(parent).getKey()))
                {
                    table.swap(current, parent);
                    current = parent;
                    swap = true;
                }
            } while (swap);
        }

        // vyberanie z haldy
        for (int i = table.size() - 1; i >= 1; i--)
        {
            table.swap(0, i);
            int current = 0;
            do
            {
                swap = false;
                int max;
                int leftSon = current * 2 + 1;
                int rightSon = current * 2 + 2;
              
                if (leftSon < i && rightSon < i)
                {
                    max = table.getItemAtIndex(leftSon).getKey() > table.getItemAtIndex(rightSon).getKey() ? leftSon : rightSon;
                }
                else
                {
                    max = leftSon < i ? leftSon : rightSon;
                }    

                if (max < i && table.getItemAtIndex(max).getKey() > table.getItemAtIndex(current).getKey())
                {
                    table.swap(max, current);
                    current = max;
                    swap = true;
                }

            } while (swap);
            //notify();
        }
	}

    template<typename K, typename T>
    inline void HeapSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, Comparator* comparator)
    {
        bool swap;
        // postavenie haldy
        for (int i = 1; i < table.size(); i++)
        {
            int current = i;
            do
            {
                swap = false;
                int parent = (current - 1) / 2;
                if (current > 0 && (comparator->compareTU(table.getItemAtIndex(current).accessData(), table.getItemAtIndex(parent).accessData()) == 1))
                {
                    table.swap(current, parent);
                    current = parent;
                    swap = true;
                }
            } while (swap);
        }

        // vyberanie z haldy
        for (int i = table.size() - 1; i >= 1; i--)
        {
            table.swap(0, i);
            int current = 0;
            do
            {
                swap = false;
                int max;
                int leftSon = current * 2 + 1;
                int rightSon = current * 2 + 2;

                if (leftSon < i && rightSon < i)
                {
                    max = comparator->compareTU(table.getItemAtIndex(leftSon).accessData(), table.getItemAtIndex(rightSon).accessData()) == 1 ? leftSon : rightSon;
                }
                else
                {
                    max = leftSon < i ? leftSon : rightSon;
                }
                if (max < i && (comparator->compareTU(table.getItemAtIndex(max).accessData(), table.getItemAtIndex(current).accessData()) == 1))
                {
                    table.swap(max, current);
                    current = max;
                    swap = true;
                }

            } while (swap);
        }
    }
}