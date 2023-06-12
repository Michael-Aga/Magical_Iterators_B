#include "MagicalContainer.hpp"

using namespace std;
using namespace ariel;

bool MagicalContainer::isPrime(int num) const
{
    if (num < 2)
    {
        return false;
    }
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

void MagicalContainer::updatePrimesIndices() {
    this->primes_indexs.clear();
    for (size_t i = 0; i < size(); ++i) {
        if (isPrime(getMyContainer()[i])) {
            primes_indexs.push_back(i);
        }
    }
}

void MagicalContainer::addElement(int elementToAdd)
{
    auto it = lower_bound(myContainer.begin(), myContainer.end(), elementToAdd);
    myContainer.insert(it, elementToAdd);
    updatePrimesIndices();
}

void MagicalContainer::removeElement(int elementToDelete)
{
    auto it = find(this->myContainer.begin(), this->myContainer.end(), elementToDelete);
    if (it != this->myContainer.end())
    {
        myContainer.erase(it);
    }
    else
    {
        throw runtime_error("Element not found in container");
    }
}

int MagicalContainer::size() const
{
    return this->myContainer.size();
}

const deque<int> &MagicalContainer::getMyContainer() const
{
    return this->myContainer;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    if (this->myMagical.getMyContainer() != other.myMagical.getMyContainer())
    {
        throw runtime_error("Cant assign diffrent container types !");
    }
    else if (this != &other)
    {
        this->current_index = other.current_index;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    return &this->myMagical == &(other.myMagical) && this->current_index == other.current_index;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    if (&this->myMagical == &other.myMagical)
    {
        return this->current_index > other.current_index;
    }
    throw runtime_error("Comparing iterators from different containers!");
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    if (&this->myMagical == &other.myMagical)
    {
        return this->current_index < other.current_index;
    }
    throw runtime_error("Comparing iterators from different containers!");
}

const int &MagicalContainer::AscendingIterator::operator*()
{
    if (this->current_index < this->myMagical.size())
    {
        return this->myMagical.getMyContainer().at(this->current_index);
    }
    else
    {
        throw out_of_range("Iterator out of bounds");
    }
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (this->current_index >= this->myMagical.size())
    {
        throw runtime_error("Iterator out of bounds");
    }
    this->current_index++;
    return *this;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::begin()
{
    this->current_index = 0;
    return *this;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::end()
{
    this->current_index = static_cast<size_t>(myMagical.size());
    return *this;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (&this->myMagical != &other.myMagical)
    {
        throw runtime_error("Comparing iterators from different containers !");
    }
    if (this != &other)
    {
        this->front_index = other.front_index;
        this->back_index = other.back_index;
        this->from_front = other.from_front;
    }
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    return &myMagical == &(other.myMagical) &&
           front_index == other.front_index &&
           back_index == other.back_index &&
           from_front == other.from_front;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    if (&myMagical == &(other.myMagical))
    {
        if (from_front && other.from_front) // both are pointing to the front index
        {
            return this->front_index > other.front_index;
        }
        else if (!from_front && !other.from_front) // both are pointing to the back index
        {
            return this->back_index < other.back_index;
        }
        else if (from_front && !other.from_front) // this pointing to front other pointing to back
        {
            return this->front_index > other.back_index;
        }
        else if (!from_front && other.from_front) // this pointing to back other pointing to front
        {
            return this->back_index > other.front_index;
        }
    }
    throw runtime_error("Comparing iterators from different containers!");
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    // If the objects are from the same container, compare their index locations.
    if (&myMagical == &(other.myMagical))
    {
        if (*this == other)
        {
            return false; // It's not less than if they are equal
        }
        else if (*this > other)
        {
            return false; // It's not less than if it's greater than
        }
        else
        {
            return true; // It must be less than if it's not equal and not greater than
        }
    }
    throw runtime_error("Comparing iterators from different containers!");
}

const int &MagicalContainer::SideCrossIterator::operator*()
{
    if (from_front)
    {
        if (front_index > myMagical.size() - 1)
        {
            throw out_of_range("Iterator out of bounds");
        }
        return myMagical.getMyContainer().at(static_cast<deque<int>::size_type>(front_index));
    }
    else
    {
        if (back_index < 0)
        {
            throw out_of_range("Iterator out of bounds");
        }
        return myMagical.getMyContainer().at(static_cast<deque<int>::size_type>(back_index));
    }
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (front_index > back_index)
    {
        throw runtime_error("Iterator out of bounds");
    }
    if (from_front)
    {
        if (front_index < (myMagical.size() + 1) / 2) // stop incrementing once we've reached the midpoint
        {
            front_index++;
        }
    }
    else
    {
        if (back_index > (myMagical.size() - 1) / 2) // stop decrementing once we're one index before the midpoint
        {
            back_index--;
        }
    }

    // After incrementing or decrementing, switch the direction for the next time
    from_front = !from_front;
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    SideCrossIterator startIterator(myMagical);
    startIterator.front_index = 0;
    startIterator.back_index = myMagical.size() - 1;
    startIterator.from_front = true;
    return startIterator;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    SideCrossIterator endIterator(myMagical);
    if (myMagical.size() % 2 == 0) // If size is even
    {
        endIterator.front_index = myMagical.size() / 2;
        endIterator.back_index = myMagical.size() / 2 - 1;
        endIterator.from_front = true;
    }
    else // If size is odd
    {
        endIterator.front_index = (myMagical.size() / 2) + 1;
        endIterator.back_index = myMagical.size() / 2;
        endIterator.from_front = false;
    }
    return endIterator;
}

size_t MagicalContainer::PrimeIterator::getPrimeCount() const
{
    size_t prime_count = 0;
    for (auto element : myMagical.getMyContainer())
    {
        if (this->myMagical.isPrime(element))
        {
            prime_count++;
        }
    }
    return prime_count;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (&this->myMagical != &other.myMagical)
    {
        throw runtime_error("Cannot assign iterators from different containers!");
    }
    if (this != &other)
    {
        this->current_index = other.current_index;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    return &myMagical == &(other.myMagical) && current_index == other.current_index;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    if (&myMagical == &(other.myMagical))
    {
        return current_index > other.current_index;
    }
    throw runtime_error("Comparing iterators from different containers!");
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    if (&myMagical == &(other.myMagical))
    {
        return current_index < other.current_index;
    }
    throw runtime_error("Comparing iterators from different containers!");
}

int MagicalContainer::PrimeIterator::operator*()
{
    return myMagical.getMyContainer()[static_cast<deque<int>::size_type>(myMagical.primes_indexs[current_index])];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (current_index >= myMagical.primes_indexs.size()) {
        throw runtime_error("Iterator out of bounds");
    }
    ++current_index;
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    PrimeIterator it(myMagical);
    it.current_index = 0;
    return it;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    PrimeIterator it(myMagical);
    size_t prime_count = 0;

    // count prime numbers
    for (auto element : myMagical.getMyContainer())
    {
        if (this->myMagical.isPrime(element))
        {
            prime_count++;
        }
    }
    it.current_index = prime_count;
    return it;
}