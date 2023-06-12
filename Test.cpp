#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace ariel;

TEST_CASE("AscendingIterator && MagicalContainer check")
{
    MagicalContainer container;
    CHECK(container.size() == 0);

    container.addElement(10);
    CHECK(container.size() == 1);

    container.removeElement(10);
    CHECK(container.size() == 0);

    MagicalContainer::AscendingIterator ai(container);
    MagicalContainer::AscendingIterator ai2 = ai;
    MagicalContainer::AscendingIterator ai3(container);
    ai3 = ai;

    CHECK(ai.begin() == ai2.begin());
    CHECK(ai3.begin() == ai.begin());
    CHECK(ai3.begin() == ai2.begin());

    container.addElement(5);
    CHECK(*ai == 5);
    CHECK(*ai2 == 5);
    CHECK(*ai3 == 5);

    container.removeElement(5);
    CHECK(ai == ai3.end());
    CHECK(ai2 == ai.end());
    CHECK(ai3 == ai2.end());

    container.addElement(10);
    ai.begin();
    ai2.begin();
    ai3.begin();

    CHECK(*ai == 10);
    CHECK(*ai2 == 10);
    CHECK(*ai3 == 10);

    container.addElement(15);

    ++ai;
    ++ai2;
    ++ai3;

    CHECK(*ai == 15);
    CHECK(*ai2 == 15);
    CHECK(*ai3 == 15);

    container.addElement(24);

    ++ai;

    CHECK(ai > ai2);
    CHECK(ai > ai3);

    CHECK(ai2 < ai);
    CHECK(ai3 < ai);
    CHECK(ai != ai2);
    CHECK(ai != ai3);

    CHECK(ai.end() == ai2.end());
    CHECK(ai.end() == ai3.end());
}

TEST_CASE("SideCrossIterator check")
{
    MagicalContainer container;

    MagicalContainer::SideCrossIterator sci(container);
    MagicalContainer::SideCrossIterator sci2 = sci;
    MagicalContainer::SideCrossIterator sci3(container);
    sci3 = sci;

    CHECK(sci.begin() == sci2.begin());
    CHECK(sci3.begin() == sci.begin());
    CHECK(sci3.begin() == sci2.begin());

    container.addElement(5);
    CHECK(*sci == 5);
    CHECK(*sci2 == 5);
    CHECK(*sci3 == 5);

    container.removeElement(5);
    CHECK(sci == sci3.end());
    CHECK(sci2 == sci.end());
    CHECK(sci3 == sci2.end());

    container.addElement(10);
    sci.begin();
    sci2.begin();
    sci3.begin();

    CHECK(*sci == 10);
    CHECK(*sci2 == 10);
    CHECK(*sci3 == 10);

    container.addElement(15);
    container.addElement(20);
    container.addElement(30);

    MagicalContainer::SideCrossIterator sci4(container);

    sci = sci4;
    
    ++sci;

    CHECK(*sci == 30);
    CHECK(*sci4 == 10);

    CHECK(sci > sci4);
    CHECK(sci4 < sci);

    CHECK(sci != sci4);

    CHECK(sci.end() == sci4.end());
}

TEST_CASE("PrimeIterator check")
{
    MagicalContainer container;
    MagicalContainer::PrimeIterator pi(container);
    MagicalContainer::PrimeIterator pi2 = pi;
    MagicalContainer::PrimeIterator pi3(container);
    pi3 = pi;

    CHECK(pi.begin() == pi2.begin());
    CHECK(pi3.begin() == pi.begin());
    CHECK(pi3.begin() == pi2.begin());

    container.addElement(5);
    CHECK(*pi == 5);
    CHECK(*pi2 == 5);
    CHECK(*pi3 == 5);

    container.removeElement(5);
    CHECK(pi == pi3.end());
    CHECK(pi2 == pi.end());
    CHECK(pi3 == pi2.end());

    container.addElement(3);
    container.addElement(7);
    container.addElement(11);

    pi.begin();
    pi2.begin();
    pi3.begin();

    CHECK(*pi == 3);
    CHECK(*pi2 == 3);
    CHECK(*pi3 == 3);

    container.addElement(15);

    ++pi;
    ++pi2;
    ++pi3;

    CHECK(*pi == 7);
    CHECK(*pi2 == 7);
    CHECK(*pi3 == 7);

    container.addElement(24);

    ++pi;

    CHECK(pi > pi2);
    CHECK(pi > pi3);

    CHECK(pi2 < pi);
    CHECK(pi3 < pi);
    CHECK(pi != pi2);
    CHECK(pi != pi3);

    CHECK(pi.end() == pi2.end());
    CHECK(pi.end() == pi3.end());
}