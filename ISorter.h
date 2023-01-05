#include "Sequences.h"

template<typename T>
class ISorter {
public:
    virtual void Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const T &, const T &)) = 0;
};

template<typename T>
class IBubbleSort : public ISorter<T> {
public:
    void
    Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const T &, const T &) = nullptr) override {
        for (int i = 0; i < seq->GetLength(); ++i) {
            for (int j = 0; j < seq->GetLength(); ++j) {
                if (cmp1(seq->Get(i), seq->Get(j))) {
                    T tmp = seq->Get(i);
                    seq->Get(i) = seq->Get(j);
                    seq->Get(j) = tmp;
                }
            }
        }
    }
};


template<typename T>
class IQuickSort : public ISorter<T> {
public:
    void
    Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const T &, const T &) = nullptr) override {
        int i = 0;
        int j = 0;
        int left = 0;
        int right = 0;
        LinkedList<int> stack;
        stack.Append(left);
        stack.Append(seq->GetLength() - 1);

        do {
            right = stack.GetLast();
            stack.pop_back();
            left = stack.GetLast();
            stack.pop_back();

            i = left;
            j = right;

            int pivot = (left + right) / 2;
            T pivot_value = seq->Get(pivot);

            do {
                while (cmp1(seq->Get(i), pivot_value)) {
                    ++i;
                }
                while (cmp2(seq->Get(j), pivot_value)) {
                    --j;
                }
                if (i <= j) {
                    T tmp = seq->Get(i);
                    seq->Get(i) = seq->Get(j);
                    seq->Get(j) = tmp;
                    ++i;
                    --j;
                }
            } while (i <= j);
            if (i < right) {
                stack.Append(i);
                stack.Append(right);
            }
            if (j > left) {
                stack.Append(left);
                stack.Append(j);
            }
        } while (stack.GetLength());
    }
};

template<typename T>
class IShellSort : public ISorter<T> {
public:
    void
    Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const T &, const T &) = nullptr) override {
        int size = seq->GetLength();
        int gap = size / 2;

        while (gap > 0) {
            for (int i = gap; i < size; ++i) {
                T curr = seq->Get(i);
                int pos = i;
                while (pos >= gap && cmp1(seq->Get(pos - gap), curr)) {
                    seq->Get(pos) = seq->Get(pos - gap);
                    pos -= gap;
                    seq->Get(pos) = curr;
                }
            }
            gap = gap / 2;
        }
    }
};