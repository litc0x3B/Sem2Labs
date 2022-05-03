#include "sequence/sequence.hpp"
#include "sequence/dynamicArraySequence.hpp"

template<typename T, template<typename> typename SequenceType = DynamicArraySequence>
class MySet {
private:
    Sequence<T> *sequence;

private:
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

};