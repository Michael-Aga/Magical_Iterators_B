#pragma once
#include <stdio.h>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <limits>
#include <iostream>

namespace ariel
{
    class MagicalContainer
    {
    private:
        std::deque<int> myContainer;
        std::deque<int> primes_indexs;
        void updatePrimesIndices();

    public:
        MagicalContainer() {}
        void addElement(int element);
        void removeElement(int element);
        int size() const;
        const std::deque<int> &getMyContainer() const;
        bool isPrime(int num) const;

        class AscendingIterator
        {
        private:
            const MagicalContainer &myMagical;
            std::size_t current_index;

        public:
            AscendingIterator(const MagicalContainer &myMagical) : myMagical(myMagical), current_index(0) {}
            AscendingIterator(const AscendingIterator &other) : myMagical(other.myMagical), current_index(other.current_index) {}
            ~AscendingIterator() {}
            AscendingIterator(AscendingIterator &&other) noexcept
                : myMagical(other.myMagical), current_index(other.current_index) {}
            AscendingIterator &operator=(AscendingIterator &&other) noexcept
            {
                if (this != &other)
                {
                    current_index = other.current_index;
                }
                return *this;
            }

            AscendingIterator &operator=(const AscendingIterator &other);
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            const int &operator*();
            AscendingIterator &operator++();
            AscendingIterator &begin();
            AscendingIterator &end();
        };

        class SideCrossIterator
        {
        private:
            const MagicalContainer &myMagical; // Reference to original MagicalContainer
            int front_index;                   // Index of the next front element to be returned
            int back_index;                    // Index of the next back element to be returned
            bool from_front;                   // If true, return element from front next; if false, return element from back next

        public:
            SideCrossIterator(const MagicalContainer &myMagical) : myMagical(myMagical), front_index(0), back_index(myMagical.size() - 1), from_front(true) {}
            SideCrossIterator(const SideCrossIterator &other) : myMagical(other.myMagical), front_index(other.front_index), back_index(other.back_index), from_front(other.from_front) {}
            ~SideCrossIterator() {}
            SideCrossIterator(SideCrossIterator &&other) noexcept
                : myMagical(other.myMagical), front_index(other.front_index), back_index(other.back_index), from_front(other.from_front) {}
            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept
            {
                if (this != &other)
                {
                    front_index = other.front_index;
                    back_index = other.back_index;
                    from_front = other.from_front;
                }
                return *this;
            }

            SideCrossIterator &operator=(const SideCrossIterator &other);
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            const int &operator*();
            SideCrossIterator &operator++();
            SideCrossIterator begin();
            SideCrossIterator end();
        };

        class PrimeIterator
        {
        private:
            const MagicalContainer &myMagical; // Reference to the original MagicalContainer
            std::size_t current_index;         // Index of the current element in the prime number sequence
            std::size_t getPrimeCount() const;

        public:
            PrimeIterator(const MagicalContainer &myMagical) : myMagical(myMagical), current_index(0) {}
            PrimeIterator(const PrimeIterator &other) : myMagical(other.myMagical), current_index(other.current_index) {}
            ~PrimeIterator() {}
            PrimeIterator(PrimeIterator &&other) noexcept
                : myMagical(other.myMagical), current_index(other.current_index) {}
            PrimeIterator &operator=(PrimeIterator &&other) noexcept
            {
                if (this != &other)
                {
                    current_index = other.current_index;
                }
                return *this;
            }

            PrimeIterator &operator=(const PrimeIterator &other);
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            int operator*();
            PrimeIterator &operator++();
            PrimeIterator begin();
            PrimeIterator end();
        };
    };
}