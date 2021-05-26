#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <random>
#include <fstream>
#include "Generator.h"
#include "dс_list.h"
#include "Lottery_ticket.h"
#include "Decor.h"
using namespace std;

// виды спортлото: 4-20, 7-49, 6-45, 5-36.

int main() {
    clock_t         start;
    clock_t         end;
    double          seconds;
    int             choice = -1;
    int             choice2;
    int             number_of_tickets;
    unsigned int    gn;
    unsigned int    number_of_ticket;
    Lottery_ticket* lot_win;
    Creator*        creator4_20 = new ConcreteCreator1();
    Creator*        creator7_49 = new ConcreteCreator2();
    Creator*        creator6_45 = new ConcreteCreator3();
    Creator*        creator5_36 = new ConcreteCreator4();
    Generator*      generator4_20 = creator4_20->FactoryMethod();
    Generator*      generator7_49 = creator7_49->FactoryMethod();
    Generator*      generator6_45 = creator6_45->FactoryMethod();
    Generator*      generator5_36 = creator5_36->FactoryMethod();

    List_interface<Lottery_ticket*> lst_tickets;
    Interface<List_interface, Lottery_ticket*> tickets(&lst_tickets);
    /*Vector_interface<Lottery_ticket*> vec_tickets;
    Interface<Vector_interface, Lottery_ticket*> tickets(&vec_tickets);*/


    ofstream save_tickets("save_tickets.txt", ios::trunc);
    if (save_tickets.fail()) {
        cerr << "Can't open file \"save_tickets\"\n";
        exit(-1);
    }

    mt19937 gen(time(NULL));


    while (choice != 0)
    {
        cout << "Choose the type of sportloto:\n";
        cout << "   1. 4 of 20\n";
        cout << "   2. 7 of 49\n";
        cout << "   3. 6 of 45\n";
        cout << "   4. 5 of 36\n";
        cout << "   0.  Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 0) break;

        cout << "Enter the number of tickets: ";
        cin >> number_of_tickets;

        uniform_int_distribution<int> num(number_of_tickets / 2, number_of_tickets);
        number_of_tickets = num(gen);
        number_of_tickets += 1;

        switch (choice)
        {
        case 1:
            start = clock();  
            lot_win = generator4_20->Generation_win();
            tickets.insert_back(lot_win);
            for (int i = 1; i < number_of_tickets; i++) {
                tickets.insert_back(generator4_20->Generation(i, lot_win));
            }
            end = clock();
            seconds = (double)(end - start) / 1000.0;
            std::cout << "adding time(in seconds) - " << seconds << std::endl;
            break;
        case 2:
            lot_win = generator7_49->Generation_win();
            tickets.insert_back(lot_win);
            for (int i = 1; i < number_of_tickets; i++) {
                tickets.insert_back(generator7_49->Generation(i, lot_win));
            }
            break;
        case 3:

            lot_win = generator6_45->Generation_win();
            tickets.insert_back(lot_win);
            for (int i = 1; i < number_of_tickets; i++) {
                tickets.insert_back(generator6_45->Generation(i, lot_win));
            }
            break;
        case 4:

            lot_win = generator5_36->Generation_win();
            tickets.insert_back(lot_win);
            for (int i = 1; i < number_of_tickets; i++) {

                tickets.insert_back(generator5_36->Generation(i, lot_win));
            }
            break;
        default:
            cout << "Wrong choice!" << endl << "Try again\n";
            continue;
        }
        cout << "Win ticket: ";
        lot_win->print_ticket(std::cout);
        tickets.find_winners();

        save_tickets << "Win ticket: ";
        tickets.print(save_tickets);
        save_tickets << endl;
        choice2 = -1;

        while (choice2 != 3)
        {
            cout << "Choose one of the available actions:\n";
            cout << "1. Search by number of ticket\n";
            cout << "2. Search by gain\n";
            cout << "3. Return to menu\n";
            cout << "Your choice: ";
            cin >> choice2;

            switch (choice2)
            {
            case 1:
                cout << "Enter number of ticket: ";
                cin >> number_of_ticket;
                tickets.search_by_id(number_of_ticket);
                break;
            case 2:
                cout << "Enter gain: ";
                cin >> gn;
                tickets.search_by_gain(gn);
                break;
            default:
                tickets.clear();
                break;
            }
        }
        tickets.clear();
        tickets.clear_memory();
    }
    cout << "Goodbye";// очистить память
    delete creator4_20;
    delete creator5_36;
    delete creator6_45;
    delete creator7_49;
    return 0;
}