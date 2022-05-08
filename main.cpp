#include <iostream>
#include <cassert>
#include "doublelist.h"

int main() {

    DoubleList<int> list1 = DoubleList<int>();
    DoubleList<int> list3 = DoubleList<int>();

    for(int i = 0; i < 10; i++)
    {
        list1.push_back(i);
    }
    std::cout << "Lista list1: ";
    list1.display();
    printf("\n");

    list1.push_front(23);
    std::cout << "List1 po operacji push_front(23): ";
    list1.display();
    printf("\n");

    std::cout << "Rozmiar listy list1 to: " << list1.size() << std::endl;
    printf("\n");

    std::cout << "Pierwszy element listy list1 to: " << list1.front() << " , ostatni: " << list1.back() << std::endl;
    printf("\n");

    list1.pop_back();
    std::cout << "List1 po operacji pop_back(): ";
    list1.display();
    printf("\n");

    list1.pop_front();
    std::cout << "List1 po operacji pop_front(): ";
    list1.display();
    printf("\n");

    std::cout << "Operacja display_reversed() na List1: ";
    list1.display_reversed();
    printf("\n");


    DoubleList<int> list2(list1);
    std::cout << "Po wywolaniu konstruktora kopiujacego DoubleList<int> list2(list1): ";
    list2.display();
    printf("\n");

    list3 = list2;
    std::cout << "Po wywolaniu kopiujacego operatora przypisania list3 = list2: " << std::endl;
    list3.display();
    printf("\n");

    list3.clear();
    std::cout << "Rozmiar list3 operacji clear: " << list3.size();
    list3.display();



    return 0;
}
