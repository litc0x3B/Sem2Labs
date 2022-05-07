#include "linkedList.hpp"
#include "sequence/sequence.hpp"
#include "sequence/dynamicArraySequence.hpp"
#include <functional>

template<typename T, template<typename> class SequenceType = DynamicArraySequence>
class MySet
{
private:
    Sequence<T> *sequence;

    explicit MySet(bool createSequence)
    {
        static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType in not derived from Sequence");
        if (createSequence)
        {
            sequence = new SequenceType<T>;
        }
    }

public:
    MySet()
    {
        static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType in not derived from Sequence");
        sequence = new SequenceType<T>;
    }

    MySet(const MySet<T, SequenceType> &set)
    {
        static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType in not derived from Sequence");
        sequence = new SequenceType<T>(*(SequenceType<T> *)set.sequence);
    }

    MySet(const T *arr, int size)
    {
        static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType in not derived from Sequence");
        sequence = new SequenceType<T>;

        for (int i = 0; i < size; i++)
        {
            bool found = false;
            for (int j = i + 1; j < size; j++)
            {
                if (arr[i] == arr[j])
                {
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                sequence->Append(arr[i]);
            }
        }        
    }

    ~MySet()
    {
        delete sequence;
    }

    bool Append(T element)
    {
        if (sequence->Find(element) == -1)
        {
            sequence->Append(element);
            return true;
        }

        return false;
    }

    bool Delete(T element)
    {
        int index = sequence->Find(element);
        if (index != -1)
        {
            sequence->Delete(element);
            return true;
        }

        return false;
    }

    void Map(const std::function<void(T&)> &func)
    {
        sequence->Map(func);
    }

    MySet<T, SequenceType> Where(const std::function<bool(T)> &func) const
    {
        MySet<T, SequenceType> newSet(false);
        newSet.sequence = sequence->Where(func);
        return newSet;
    }

    int GetSize() const
    {
        return sequence->GetSize();
    }

    MySet<T, SequenceType> Union(const MySet<T, SequenceType> &set) const
    {
        MySet<T, SequenceType> tempSet(false);
        MySet<T, SequenceType> retSet(false);

        tempSet.sequence = sequence->Where([set](T item){return set.sequence->Find(item) == -1;});
        retSet.sequence = tempSet.sequence->Concat(set.sequence);

        return retSet;
    }

    MySet<T, SequenceType> Intersection(const MySet<T, SequenceType> &set) const
    {
        MySet<T, SequenceType> retSet(false);
        retSet.sequence = sequence->Where([set](T item){return set.sequence->Find(item) != -1;});
        return retSet;
    }

    MySet<T, SequenceType> Subtraction(const MySet<T, SequenceType> &set) const
    {
        MySet<T, SequenceType> retSet(false);
        retSet.sequence = sequence->Where([set](T item){return set.sequence->Find(item) == -1;});
        return retSet;
    }


    bool IsSubsetOf(const MySet<T, SequenceType> &set) const
    {
        for (int i = 0; i < this->GetSize(); i++)
        {
            if (set.sequence->Find(this->sequence->operator[](i)) == -1)
            {
                return false;
            }
        }

        return true;
    }

    bool HasElement(T element) const
    {
        return sequence->Find(element) != -1;
    }

    bool IsEqualTo(const MySet<T, SequenceType> &set) const
    {
        if (set.GetSize() != this->GetSize())
        {
            return false;
        }

        for (int i = 0; i < this->GetSize(); i++)
        {
            if (this->sequence->Find(set.sequence->operator[](i)) == -1)
            {
                return false;
            }
        }

        return true;
    }

};