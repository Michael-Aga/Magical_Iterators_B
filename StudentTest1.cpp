#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <stdexcept>

using namespace ariel;
using namespace std;
// Test case for adding elements to the MagicalContainer
TEST_CASE("Adding elements to MagicalContainer") {
    MagicalContainer container;

    SUBCASE("Adding a single element") {
        container.addElement(10);
        CHECK(container.size() == 1);
    }

    SUBCASE("Adding multiple elements") {
        container.addElement(10);
        container.addElement(20);
        container.addElement(30);
        CHECK(container.size() == 3);
    }
}

// Test case for removing elements from the MagicalContainer
TEST_CASE("Removing elements from MagicalContainer") {
    MagicalContainer container;

    SUBCASE("Removing an existing element") {
        container.addElement(10);
        container.addElement(20);
        CHECK_NOTHROW(container.removeElement(10));
        CHECK(container.size() == 1);
    }

    SUBCASE("Removing a non-existing element") {
        container.addElement(10);
        container.addElement(20);
        CHECK_THROWS_AS(container.removeElement(30), runtime_error);
        CHECK(container.size() == 2);
    }
}

// Test case for the AscendingIterator
TEST_CASE("AscendingIterator") {
    MagicalContainer container;
    container.addElement(10);
    container.addElement(20);
    container.addElement(30);
    container.addElement(15);
    container.addElement(25);


    SUBCASE("Iterating over elements") {
        MagicalContainer::AscendingIterator it(container);
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 15);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 25);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(it == it.end());
    }

    SUBCASE("Iterating over an empty container") {
        MagicalContainer emptyContainer;
        MagicalContainer::AscendingIterator it(emptyContainer);
        CHECK(it == it.end());
    }
}

// Test case for the SideCrossIterator
TEST_CASE("SideCrossIterator") {
    MagicalContainer container;
    container.addElement(10);
    container.addElement(20);
    container.addElement(30);
    container.addElement(40);

    SUBCASE("Iterating over elements") {
        MagicalContainer::SideCrossIterator it(container);
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(it == it.end());
    }

    SUBCASE("Iterating over an empty container") {
        MagicalContainer emptyContainer;
        MagicalContainer::SideCrossIterator it(emptyContainer);
        CHECK(it == it.end());
    }
}

// Test case for the PrimeIterator
TEST_CASE("PrimeIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    container.addElement(5);
    container.addElement(6);

    SUBCASE("Iterating over elements") {
        MagicalContainer::PrimeIterator it(container);
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(it == it.end());
    }

    SUBCASE("Iterating over an empty container") {
        MagicalContainer emptyContainer;
        MagicalContainer::PrimeIterator it(emptyContainer);
        CHECK(it == it.end());
    }
}
//--------------------------------------------------------------
// Test case for comparing iterators from the same container
TEST_CASE("Comparing iterators from the same container") {
    MagicalContainer container;
    for (int i = 1; i <= 10; ++i) {
        container.addElement(i * 10);
    }

    SUBCASE("Comparing AscendingIterator with itself") {
        MagicalContainer::AscendingIterator it1(container);
        MagicalContainer::AscendingIterator it2(container);
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        CHECK(!(it1 < it2));
        CHECK(!(it1 > it2));
    }

    SUBCASE("Comparing SideCrossIterator with itself") {
        MagicalContainer::SideCrossIterator it1(container);
        MagicalContainer::SideCrossIterator it2(container);
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        CHECK(!(it1 < it2));
        CHECK(!(it1 > it2));
    }

    SUBCASE("Comparing PrimeIterator with itself") {
        MagicalContainer::PrimeIterator it1(container);
        MagicalContainer::PrimeIterator it2(container);
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        CHECK(!(it1 < it2));
        CHECK(!(it1 > it2));
    }
}
//------------------------------------------------------
// Test case for traversing the AscendingIterator
TEST_CASE("Traversing AscendingIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Iterating in ascending order") {
        MagicalContainer::AscendingIterator it(container);
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 4);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(*it == 14);
        ++it;
        CHECK(it == it.end());
    }
}

// Test case for traversing the PrimeIterator
TEST_CASE("Traversing PrimeIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Iterating over prime elements") {
        MagicalContainer::PrimeIterator it(container);
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(it == it.end());
    }
}

// Test case for the SideCrossIterator
TEST_CASE("SideCrossIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Iterating in side-cross order from start to end") {
        MagicalContainer::SideCrossIterator it(container);

        CHECK(*it == 1);
        ++it;
        CHECK(*it == 14);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(*it == 4);
        ++it;
        CHECK(it == it.end());
    }
}
//-------------------------------------------------------
// Test case for comparing AscendingIterator
TEST_CASE("Comparing AscendingIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Comparing iterators after increments") {
        MagicalContainer::AscendingIterator it1(container);
        MagicalContainer::AscendingIterator it2(container);

        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK_FALSE((it1 < it2));
        CHECK((it1 > it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK_FALSE((it1 < it2));
        CHECK((it1 > it2));

        ++it2;
        ++it2;
        ++it1;
        CHECK(it1 == it1.end());
        CHECK(it2 == it2.end());
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));
    }
}


// Test case for comparing PrimeIterator
TEST_CASE("Comparing PrimeIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Comparing iterators after increments") {
        MagicalContainer::PrimeIterator it1(container);
        MagicalContainer::PrimeIterator it2(container);

        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK_FALSE((it1 < it2));
        CHECK((it1 > it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        CHECK(it1 == it1.end());
        CHECK(it2 == it2.end());
    }
}


// Test case for comparing SideCrossIterator
TEST_CASE("Comparing SideCrossIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Comparing iterators after increments") {
        MagicalContainer::SideCrossIterator itStart1(container);
        MagicalContainer::SideCrossIterator itStart2(container);

        CHECK((itStart1 == itStart2));
        CHECK_FALSE((itStart1 != itStart2));
        CHECK_FALSE((itStart1 > itStart2));
        CHECK_FALSE((itStart1 < itStart2));

        ++itStart1;
        CHECK_FALSE((itStart1 == itStart2));
        CHECK((itStart1 != itStart2));
        CHECK_FALSE((itStart1 < itStart2));
        CHECK((itStart1 > itStart2));

        ++itStart2;
        CHECK((itStart1 == itStart2));
        CHECK_FALSE((itStart1 != itStart2));
        CHECK_FALSE((itStart1 > itStart2));
        CHECK_FALSE((itStart1 < itStart2));

        ++itStart1;
        CHECK((itStart1 == itStart1));
        CHECK_FALSE((itStart1 != itStart1));
        CHECK_FALSE((itStart1 > itStart1));
        CHECK_FALSE((itStart1 < itStart1));
    }
}
//---------------------------------------------------
TEST_CASE("Iterator Increment Beyond End") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Ascending Iterator") {
        MagicalContainer::AscendingIterator it(container);

        // Increment until the end
        while (it != it.end()) {
            ++it;
        }
    
        // Attempt to increment beyond the end
        CHECK_THROWS_AS(++it, runtime_error);
    }

    SUBCASE("Prime Iterator") {
        MagicalContainer::PrimeIterator it(container);

        // Increment until the end
        while (it != it.end()) {
            ++it;
        }

        // Attempt to increment beyond the end
        CHECK_THROWS_AS(++it, runtime_error);
    }

    SUBCASE("SideCross Iterator") {
        MagicalContainer::SideCrossIterator it(container);

        // Increment until the end
        while (it != it.end()) {
            ++it;
        }

        // Attempt to increment beyond the end
        CHECK_THROWS_AS(++it, runtime_error);
    }
}
//checking that the iterators dont impact each other
TEST_CASE("Multiple Iterators Test") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    container.addElement(5);
    container.addElement(6);
    container.addElement(7);
    container.addElement(8);
    container.addElement(9);

    SUBCASE("Ascending Iterators") {
        MagicalContainer::AscendingIterator it1(container);
        MagicalContainer::AscendingIterator it2(container);

        ++(++it1);
        CHECK(*it1 == 3);
        ++it2;
        CHECK(*it2 == 2);
        ++(++(++it1));
        CHECK(*it2 == 2);
        CHECK(*it1 == 6);
    }

    SUBCASE("SideCross Iterators") {
        MagicalContainer::SideCrossIterator it1(container);
        MagicalContainer::SideCrossIterator it2(container);

        ++it1;
        CHECK(*it1 == 9);
        ++it2;
        CHECK(*it2 == 9);
        ++it1;
        CHECK(*it2 == 9);
        CHECK(*it1 == 2);
        ++(++(++it2));
        CHECK(*it2 == 3);
    }

    SUBCASE("Prime Iterators") {
        MagicalContainer::PrimeIterator it1(container);
        MagicalContainer::PrimeIterator it2(container);

        ++it1;
        CHECK(*it1 == 3);
        CHECK(*it2 == 2);
        ++it2;
        ++it1;
        CHECK(*it2 == 3);
        CHECK(*it1 == 5);
        ++(++it2);
        CHECK(*it2 == 7);
    }
}
// Test case for the AscendingIterator with negative and positive numbers
TEST_CASE("AscendingIterator with Negative and Positive Numbers") {
    MagicalContainer container;
    container.addElement(-3);
    container.addElement(5);
    container.addElement(-2);
    container.addElement(0);
    container.addElement(4);
    container.addElement(-1);
    container.addElement(3);
    container.addElement(-4);
    container.addElement(2);
    container.addElement(1);

    SUBCASE("Iterating over elements") {
        MagicalContainer::AscendingIterator it(container);
        CHECK(*it == -4);
        ++it;
        CHECK(*it == -3);
        ++it;
        CHECK(*it == -2);
        ++it;
        CHECK(*it == -1);
        ++it;
        CHECK(*it == 0);
        ++it;
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 4);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(it == it.end());
    }
}

// Test case for the PrimeIterator with no prime numbers in the container
TEST_CASE("PrimeIterator with No Prime Numbers") {
    MagicalContainer container;
    container.addElement(4);
    container.addElement(6);
    container.addElement(8);
    container.addElement(9);
    container.addElement(10);
    container.addElement(12);

    SUBCASE("Iterating over elements") {
        MagicalContainer::PrimeIterator it(container);

        CHECK(it == it.end());
        CHECK_THROWS_AS(++it, runtime_error);
    }
}

// Test case for the SideCrossIterator with a single element in the container
TEST_CASE("SideCrossIterator with Single Element") {
    MagicalContainer container;
    container.addElement(100);

    SUBCASE("Iterating over elements") {
        MagicalContainer::SideCrossIterator it(container);
        CHECK(*it == 100);
        ++it;
        CHECK(it == it.end());
    }
}

TEST_CASE("operator= throws when iterators are pointing at different containers") {
    MagicalContainer container1;
    MagicalContainer container2;

    container1.addElement(1);
    container1.addElement(2);
    container1.addElement(3);

    container2.addElement(4);
    container2.addElement(5);
    container2.addElement(6);    

   SUBCASE("AscendingIterator")
   {
        MagicalContainer::AscendingIterator it1(container1);
        MagicalContainer::AscendingIterator it2(container2);

        CHECK_THROWS_AS(it1 = it2, std::runtime_error);
   }
   SUBCASE("SideCrossIterator")
   {
        MagicalContainer::SideCrossIterator it1(container1);
        MagicalContainer::SideCrossIterator it2(container2);

        CHECK_THROWS_AS(it1 = it2, std::runtime_error);
   }
   SUBCASE("AscendingIterator")
   {
        MagicalContainer::PrimeIterator it1(container1);
        MagicalContainer::PrimeIterator it2(container2);

        CHECK_THROWS_AS(it1 = it2, std::runtime_error);
   }
}


