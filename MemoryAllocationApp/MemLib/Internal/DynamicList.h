#pragma once
#include <memory.h>
#include <assert.h>

namespace MemLib
{
    template <class T>
    class OwnVector
    {
    private:
        int size;
        int capacity;
        T* vectorData;

        void AllocateMore();
    public:
        OwnVector<T>();
        OwnVector<T>(const int& p_capacity);
        // pushes the item to the end of the list
        void push_back(const T& p_item);
        // Removes the last item and returns a copy of it, no delete here
        T pop();
        // gets the item at the given index point
        T& at( const int& p_index);
        // gets the item at the end of the list
        T& endItem();
        // erases the item at the given index point effectivly reducing size of list. TODO implement
        void erase(const int& p_index);
        // Returns true if the list is empty
        bool empty();
        // Returns the size of the vector
        int getSize();
        // Deletes all elements in the vector and frees memory
        void deleteAndFree();
    };

    template<class T>
    inline OwnVector<T>::OwnVector()
    {
        capacity = 10;
        size = 0;
        vectorData = (T*)malloc(capacity * sizeof(T));
    }

    template<class T>
    inline OwnVector<T>::OwnVector(const int & p_capacity)
    {
        capacity = p_capacity;
        size = 0;
        vectorData = (T*)malloc(capacity * sizeof(T));
    }

    template<class T>
    inline void OwnVector<T>::AllocateMore()
    {
        // increase capacity by 2x
        capacity *= 2;

        // create new empty array
        T* newVectorData = (T*)malloc(capacity * sizeof(T));

        // copy data to new array...
        memcpy(newVectorData, vectorData, size * sizeof(T));

        // Delete old data and set it to copy
        delete[] vectorData;
        vectorData = newVectorData;
    }

    template<class T>
    inline void OwnVector<T>::push_back(T const & p_item)
    {
        if (size >= capacity)
        {
            AllocateMore();
        }
        vectorData[size] = p_item;
        size++;
    }

    template<class T>
    inline T& OwnVector<T>::at(int const & p_index)
    {
        assert(p_index <= size - 1);
        return vectorData[p_index];
    }

    template<class T>
    inline T& OwnVector<T>::endItem()
    {
        assert(size >= 1);
        return vectorData[size-1];
    }

    template<class T>
    inline bool OwnVector<T>::empty()
    {
        return size==0;
    }

    template<class T>
    inline int OwnVector<T>::getSize()
    {
        return size;
    }

    template<class T>
    inline void OwnVector<T>::deleteAndFree()
    {
        delete[] vectorData;
    }
    
    template<class T>
    inline T OwnVector<T>::pop()
    {
        assert(size >= 1);
        T returnItem = vectorData[size - 1];
        size--;
        return returnItem;
    }
}