#pragma once

template <typename T>
class DynamicArray
{
private:
    T *storage;
    unsigned int size;

    void Init(unsigned int size);

public:
    DynamicArray(const T *items, unsigned int size);
    DynamicArray(unsigned int size);
    DynamicArray(const DynamicArray<T> &dynamicArray);
    ~DynamicArray();

    T &operator[](unsigned int index);
    unsigned int GetSize() const;
    void Resize(unsigned int newSize);
};

#pragma region constructors and destructors
template <typename T>
void DynamicArray<T>::Init(unsigned int size)
{
    this->size = size;
    storage = new T[size];
}

template <typename T>
DynamicArray<T>::DynamicArray(const T *items, unsigned int size)
{
    Init(size);
    for (unsigned int i = 0; i < size; i++)
    {
        storage[i] = items[i];
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(unsigned int size)
{
    Init(size);
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &dynamicArray)
{
    Init(dynamicArray.GetSize());
    for (unsigned int i = 0; i < dynamicArray.GetSize(); i++)
    {
        storage[i] = dynamicArray.storage[i];
    }
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] storage;
}
#pragma endregion constructors and destructors

template <typename T>
T &DynamicArray<T>::operator[](unsigned int index)
{
    return storage[index];
}

template <typename T>
unsigned int DynamicArray<T>::GetSize() const
{
    return size;
}

template <typename T>
void DynamicArray<T>::Resize(unsigned int newSize)
{
    T *tempStorage = new T[newSize];

    for (unsigned int i = 0; i < newSize; i++)
    {
        tempStorage[i] = storage[i];
    }

    delete[] storage;
    storage = tempStorage;

    size = newSize;
}
