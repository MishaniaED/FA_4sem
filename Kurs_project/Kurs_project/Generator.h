#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <random>
#include <set>
#include <unordered_set>
#include "Lottery_ticket.h"
using namespace std;

#define min_gain 50
#define max_gain 50000000

class Generator {
public:
    virtual ~Generator() {}
    virtual Lottery_ticket* Generation(int i, Lottery_ticket* lot_win) const = 0; // генерировать билеты и добавлять в список т.е убрать из main
    virtual Lottery_ticket* Generation_win() const = 0;
};

/* Конкретные Продукты предоставляют различные реализации интерфейса Продукта. */
class Generator4_20 : public Generator {  // 4-20
public:
    Lottery_ticket* Generation_win() const override
    {
        Lottery_ticket* ticket = new Lottery_ticket(4);
        vector<int> vec;
        set<int> st;
        unordered_set<int> ust;
        int num;


        static mt19937 gen(time(NULL));
        uniform_int_distribution<int> uid1(1, 20);

        while (true)
        {
            for (int i = 0; i < 4; i++) {
                num = uid1(gen);
                st.insert(num);
                vec.push_back(num);
            }
            if (st.size() == vec.size()) {
                break;
            }
            else
            {
                st.clear();
                vec.clear();
            }
        }
        
        for (const auto& it : vec) {
            ticket->set_numbers(it);
        }

        ticket->set_id(0);
        return ticket;
    }

    Lottery_ticket* Generation(int i, Lottery_ticket* lot_win) const override
    {
        Lottery_ticket* ticket = new Lottery_ticket ;
        vector<int> vec;
        vector<unsigned int> tmp;
        set<int> st;
        unordered_set<int> ust;
        int num;
        int counter;
        size_t size_counter = 4;

        static mt19937 gen(time(NULL));
        uniform_int_distribution<int> uid1(1, 20);
        uniform_int_distribution<int> number1(4, 8);

        tmp = lot_win->get_numbers();
        for (const auto& it : tmp)  // для назначения выигрыша
            ust.insert(it);

        while (true)
        {
            counter = number1(gen);
            for (int i = 0; i < counter; i++) {
                num = uid1(gen);
                st.insert(num); 
                vec.push_back(num);
            }
            if (st.size() == vec.size()) {
                break;
            }
            else
            {
                st.clear();
                vec.clear();
            }
        }

        for (const auto& elem : vec) {
            if (ust.count(elem)) {
                size_counter--;
            }
        }

        ticket->set_size(counter);

        if (size_counter > 0 && size_counter < ust.size() - 1) {
            ticket->set_gain(min_gain * pow(10, ust.size() - size_counter - 1) / 10);
        }
        else if (size_counter == 0) {
            ticket->set_gain(max_gain);
        }

        for (const auto& it : vec) {
            ticket->set_numbers(it);
        }

        ticket->set_id(i);
        return ticket;
    }
};

class Generator7_49 : public Generator { // 7-49
public:
    Lottery_ticket* Generation_win() const override
    {
        Lottery_ticket* ticket = new Lottery_ticket(7);
        vector<int> vec;
        set<int> st;
        unordered_set<int> ust;
        int num;


        static mt19937 gen(time(NULL));
        uniform_int_distribution<int> uid2(1, 49);

        while (true)
        {
            for (int i = 0; i < 7; i++) {
                num = uid2(gen);
                st.insert(num);
                vec.push_back(num);
            }
            if (st.size() == vec.size()) {
                break;
            }
            else
            {
                st.clear();
                vec.clear();
            }
        }

        for (const auto& it : vec) {
            ticket->set_numbers(it);
        }

        ticket->set_id(0);
        return ticket;
    }

    Lottery_ticket* Generation(int i, Lottery_ticket* lot_win) const override
    {
        Lottery_ticket* ticket = new Lottery_ticket;
        vector<int> vec;
        vector<unsigned int> tmp;
        set<int> st;
        unordered_set<int> ust;
        int num;
        int counter;
        size_t size_counter = 7;

        static mt19937 gen(time(NULL));
        uniform_int_distribution<int> uid2(1, 49);
        uniform_int_distribution<int> number2(7, 14);

        tmp = lot_win->get_numbers();
        for (const auto& it : tmp)  // для назначения выигрыша
            ust.insert(it);

        while (true)
        {
            counter = number2(gen);
            for (int i = 0; i < counter; i++) {
                num = uid2(gen);
                st.insert(num); // log(n)
                vec.push_back(num);
            }
            if (st.size() == vec.size()) {
                break;
            }
            else
            {
                st.clear();
                vec.clear();
            }
        }

        for (const auto& elem : vec) {
            if (ust.count(elem)) {
                size_counter--;
            }
        }

        ticket->set_size(counter);

        if (size_counter > 0 && size_counter < ust.size() - 1) {
            ticket->set_gain(min_gain * pow(10, ust.size() - size_counter - 1) / 10);
        }
        else if (size_counter == 0) {
            ticket->set_gain(max_gain);
        }

        for (const auto& it : vec) {
            ticket->set_numbers(it);
        }

        ticket->set_id(i);
        return ticket;
    }
};

class Generator6_45 : public Generator { // 6-45
public:
    Lottery_ticket* Generation_win() const override
    {
        Lottery_ticket* ticket = new Lottery_ticket(6);
        vector<int> vec;
        set<int> st;
        unordered_set<int> ust;
        int num;


        static mt19937 gen(time(NULL));
        uniform_int_distribution<int> uid3(1, 45);

        while (true)
        {
            for (int i = 0; i < 6; i++) {
                num = uid3(gen);
                st.insert(num);
                vec.push_back(num);
            }
            if (st.size() == vec.size()) {
                break;
            }
            else
            {
                st.clear();
                vec.clear();
            }
        }

        for (const auto& it : vec) {
            ticket->set_numbers(it);
        }

        ticket->set_id(0);
        return ticket;
    }
    Lottery_ticket* Generation(int i, Lottery_ticket* lot_win) const override
    {
        Lottery_ticket* ticket = new Lottery_ticket;
        vector<int> vec;
        vector<unsigned int> tmp;
        set<int> st;
        unordered_set<int> ust;
        int num;
        int counter;
        size_t size_counter = 6;

        static mt19937 gen(time(NULL));
        uniform_int_distribution<int> uid3(1, 45);
        uniform_int_distribution<int> number3(6, 13);

        tmp = lot_win->get_numbers();
        for (const auto& it : tmp)  // для назначения выигрыша
            ust.insert(it);

        while (true)
        {
            counter = number3(gen);
            for (int i = 0; i < counter; i++) {
                num = uid3(gen);
                st.insert(num); // log(n)
                vec.push_back(num);
            }
            if (st.size() == vec.size()) {
                break;
            }
            else
            {
                st.clear();
                vec.clear();
            }
        }

        for (const auto& elem : vec) {
            if (ust.count(elem)) {
                size_counter--;
            }
        }

        ticket->set_size(counter);

        if (size_counter > 0 && size_counter < ust.size() - 1) {
            ticket->set_gain(min_gain * pow(10, ust.size() - size_counter - 1) / 10);
        }
        else if (size_counter == 0) {
            ticket->set_gain(max_gain);
        }

        for (const auto& it : vec) {
            ticket->set_numbers(it);
        }

        ticket->set_id(i);
        return ticket;
    }
};

class Generator5_36 : public Generator { // 5-36
public:
    Lottery_ticket* Generation_win() const override
    {
        Lottery_ticket* ticket = new Lottery_ticket(5);
        vector<int> vec;
        set<int> st;
        unordered_set<int> ust;
        int num;


        static mt19937 gen(time(NULL));
        uniform_int_distribution<int> uid4(1, 36);

        while (true)
        {
            for (int i = 0; i < 5; i++) {
                num = uid4(gen);
                st.insert(num);
                vec.push_back(num);
            }
            if (st.size() == vec.size()) {
                break;
            }
            else
            {
                st.clear();
                vec.clear();
            }
        }

        for (const auto& it : vec) {
            ticket->set_numbers(it);
        }

        ticket->set_id(0);
        return ticket;
    }

    Lottery_ticket* Generation(int i, Lottery_ticket* lot_win) const override
    {
        Lottery_ticket* ticket = new Lottery_ticket;
        vector<int> vec;
        vector<unsigned int> tmp;
        set<int> st;
        unordered_set<int> ust;
        int num;
        int counter;
        size_t size_counter = 5;

        static mt19937 gen(time(NULL));
        uniform_int_distribution<int> uid4(1, 36);
        uniform_int_distribution<int> number4(5, 11);

        tmp = lot_win->get_numbers();
        for (const auto& it : tmp)  // для назначения выигрыша
            ust.insert(it);

        while (true)
        {
            counter = number4(gen);
            for (int i = 0; i < counter; i++) {
                num = uid4(gen);
                st.insert(num); // log(n)
                vec.push_back(num);
            }
            if (st.size() == vec.size()) {
                break;
            }
            else
            {
                st.clear();
                vec.clear();
            }
        }

        for (const auto& elem : vec) {
            if (ust.count(elem)) {
                size_counter--;
            }
        }

        ticket->set_size(counter);

        if (size_counter > 0 && size_counter < ust.size() - 1) {
            ticket->set_gain(min_gain * pow(10, ust.size() - size_counter - 1) / 10);
        }
        else if (size_counter == 0) {
            ticket->set_gain(max_gain);
        }

        for (const auto& it : vec) {
            ticket->set_numbers(it);
        }

        ticket->set_id(i);
        return ticket;
    }
};

class Creator {
public:
    virtual ~Creator() {};
    virtual Generator* FactoryMethod() const = 0;
};


class ConcreteCreator1 : public Creator {
public:
    Generator* FactoryMethod() const override {
        return new Generator4_20();
    }
};

class ConcreteCreator2 : public Creator {
public:
    Generator* FactoryMethod() const override {
        return new Generator7_49();
    }
};

class ConcreteCreator3 : public Creator {
public:
    Generator* FactoryMethod() const override {
        return new Generator6_45();
    }
};

class ConcreteCreator4 : public Creator {
public:
    Generator* FactoryMethod() const override {
        return new Generator5_36();
    }
};