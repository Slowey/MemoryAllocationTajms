#pragma once
#include <memory.h>
#include <assert.h>

namespace MemLib
{
    template <class T>
    class vector
    {
    private:
        int size;
        int capacity;
        T* vectorData;

        void AllocateMore();
    public:
        vector<T>();
        vector<T>(const int& p_capacity);
        // pushes the item to the end of the list
        void push_back(const T& p_item);
        // Removes the last item and returns it
        T pop();
        // gets the item at the given index point
        T at( const int& p_index);
        // erases the item at the given index point effectivly reducing size of list
        void erase(const int& p_index);
    };

    template<class T>
    inline vector<T>::vector()
    {
        capacity = 10;
        size = 0;
        vectorData = (T*)malloc(capacity * sizeof(T));
    }

    template<class T>
    inline vector<T>::vector(const int & p_capacity)
    {
        capacity = p_capacity;
        size = 0;
        vectorData = (T*)malloc(capacity * sizeof(T));
    }

    template<class T>
    inline void vector<T>::AllocateMore()
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
    inline void vector<T>::push_back(T const & p_item)
    {
        if (size >= capacity)
        {
            AllocateMore();
        }
        vectorData[size] = p_item;
        size++;
    }

    template<class T>
    inline T vector<T>::at(int const & p_index)
    {
        assert(p_index <= size - 1);
        return vectorData[p_index];
    }


    template<class T>
    inline T vector<T>::pop()
    {
        T returnItem = vectorData[size - 1];
        size--;
        return returnItem;
    }
}