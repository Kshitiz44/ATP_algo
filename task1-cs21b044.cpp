#include <bits/stdc++.h>

namespace coa
{
    // class description begins, using templated datatype "dtype"
    template<typename dtype>
    class vector
    {
        private:
        dtype *array; // stores the data
        int curSize=0, arraySize=1; // stores size of data and memory currently allocated to array respectively
        int rptr; // stores the pointer to the right end

        public:

        // iterator class for the vector
        class iterator
        {
            public:
            int curIndex; // stores the index in the array of the data stored 
            dtype *data; // pointer to the array element
            

            // constructor
            iterator(int index, dtype *ptr)
            {
                curIndex = index;
                data = ptr+index;
            }

            // dereferencing operator
            dtype operator * ()
            {
                return *data;
            }


            // prefix increment operator
            iterator & operator ++ ()
            {
                curIndex++;
                data++;
                return *this;
            }


            // prefix decrement operator
            iterator & operator -- ()
            {
                curIndex--;
                data--;
                return *this;
            }


            // postfix increment operator
            iterator operator ++ (int)
            {
                iterator temp= *this;
                curIndex++;
                data++;
                return temp;
            }


            // postfix decrement operator
            iterator operator -- (int)
            {
                iterator temp= *this;
                curIndex--;
                data--;
                return temp;
            }

            // equality checker
            bool operator == (iterator rhs)
            {
                return curIndex == rhs.curIndex;
            }

            // inequality checker
            bool operator != (iterator rhs)
            {
                return curIndex != rhs.curIndex;
            }

        };

        // class constructor
        vector(int initSize=1)
        {
            arraySize = initSize; // assigning initial memory allocation size
            array = new dtype[arraySize];

            rptr=0;
        }


        // class destructor
        ~vector()
        {
            delete array;
        }

        int size(){return curSize;}

        void push_back(dtype x)
        {
            // checking if array is full
            if(rptr == arraySize)
            {
                arraySize*=2;
                dtype *temp = new dtype[arraySize]; // allocating memory of twice the previous size

                for(int ii=0; ii<rptr; ii++) temp[ii] = array[ii]; // copying contents

                array = temp;
            }

            array[rptr] = x; // assigning value at the back
            rptr++;
            curSize++;
        }

        dtype & at(int index)
        {
            if(index>=curSize) return array[0];

            return array[index];
        }

        dtype & operator [] (int index)
        {
            if(index>=curSize) return array[0];

            return array[index];
        }

        // returns iterator to the first element
        iterator begin()
        {
            iterator i(0, array);
            return i;
        }

        // returns iterator to the element next to the last element
        iterator end()
        {
            iterator i(curSize, array+curSize);
            return i;
        }
        

    };

    template <typename dtype>
    dtype accumulate(vector<dtype> &v)
    {
        if(v.size() == 0) return dtype();

        dtype sum = v[0];

        for(int ii = 1; ii<v.size(); ii++) sum+=v[ii];

        return sum;
    }

    template<template <class, class> class Container, class dtype, class Type>
    dtype accumulate(Container<dtype, Type> v)
    {
        if(v.size() == 0) return dtype();

        dtype sum = v[0];

        for(int ii = 1; ii<v.size(); ii++) sum+=v[ii];

        return sum;
    }
}


