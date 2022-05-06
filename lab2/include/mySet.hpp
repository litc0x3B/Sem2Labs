#include "sequence/sequence.hpp"
#include "sequence/dynamicArraySequence.hpp"


template<typename T, template<typename> typename SequenceType = DynamicArray>
class MySet
{
private:
    Sequence<T> *sequence;

    explicit MySet(bool createSequence)
    {
        static_assert(std::is_base_of_v<Sequence<T>, SequenceType<T>>, "SequenceType in not derived from Sequence");
        if (createSequence)
        {
            sequence = new SequenceType<T>;
        }
    }

public:
    MySet()
    {
        static_assert(std::is_base_of_v<Sequence<T>, SequenceType<T>>, "SequenceType in not derived from Sequence");
        sequence = new SequenceType<T>;
    }

    MySet(const MySet<T, SequenceType> &set)
    {
        static_assert(std::is_base_of_v<Sequence<T>, SequenceType<T>>, "SequenceType in not derived from Sequence");
        sequence = new SequenceType(*set.sequence);
    }

    MySet(T *arr, int size)
    {
        static_assert(std::is_base_of_v<Sequence<T>, SequenceType<T>>, "SequenceType in not derived from Sequence");
        sequence = new SequenceType(arr, size);
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

    int GetSize() const
    {
        return sequence->GetSize();
    }

    MySet<T, SequenceType> Union(const MySet<T, SequenceType> &set) const
    {
        MySet<T, SequenceType> tempSet(false);
        MySet<T, SequenceType> retSet(false);

        tempSet->sequence = sequence->Where([set](T item){return set.sequence->Find(item) == -1;});
        retSet.sequence = tempSet->Concat(set.sequence);

        return retSet;
    }

    MySet<T, SequenceType> Intersection(const MySet<T, SequenceType> &set) const
    {
        MySet<T, SequenceType> retSet(false);
        retSet->sequence = sequence->Where([set](T item){return set.sequence->Find(item) != -1;});
        return retSet;
    }

    MySet<T, SequenceType> Subtraction(const MySet<T, SequenceType> &set) const
    {
        MySet<T, SequenceType> retSet(false);
        retSet->sequence = sequence->Where([set](T item){return set.sequence->Find(item) == -1;});
    }


    bool IsSubsetOf(const MySet<T, SequenceType> &set) const
    {
        return sequence->Find(set.sequence) != -1;
    }

    bool DoesBelong(T element) const
    {
        return sequence->Find(element) != -1;
    }

    bool AreEqual(const MySet<T, SequenceType> &set) const
    {
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