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
        std::shared_ptr<std::deque<int>> myContainer;

    public:
        MagicalContainer() : myContainer(std::make_shared<std::deque<int>>()) {}
        void addElement(int element);
        void removeElement(int element);
        int size() const;

        const std::deque<int> &getMyContainer() const;

        class AscendingIterator
        {
        private:
            const MagicalContainer &myMagical;
            std::size_t current_index;

        public:
            AscendingIterator(const MagicalContainer &myMagical) : myMagical(myMagical), current_index(0) {}
            AscendingIterator(const AscendingIterator &other) : myMagical(other.myMagical), current_index(other.current_index) {}

            ~AscendingIterator() {}

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
            const MagicalContainer &myMagical; // Reference to original MagicalContainer
            int front_index;                   // Index of the next front element to be returned
            int back_index;                    // Index of the next back element to be returned
            bool from_front;                   // If true, return element from front next; if false, return element from back next
            std::size_t unified_index;
        public:
            SideCrossIterator(const MagicalContainer &myMagical) : myMagical(myMagical), front_index(0), back_index(myMagical.size() - 1), from_front(true) {}
            SideCrossIterator(const SideCrossIterator &other) : myMagical(other.myMagical) {}
            ~SideCrossIterator() {}

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
            bool isPrime(int num) const;
            std::size_t getPrimeCount() const;
        public:
            PrimeIterator(const MagicalContainer &myMagical) : myMagical(myMagical), current_index(0) {}
            PrimeIterator(const PrimeIterator &other) : myMagical(other.myMagical), current_index(other.current_index) {}
            ~PrimeIterator() {}

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