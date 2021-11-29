//
// Created by d3Gaff on 28.09.2021.
//

#include "menu.h"

std::string LAST_CHOSEN;

void view_menu::execute() {
    LAST_CHOSEN = name;
    ch = 0;
    do {
        do{
            output_items();
            process_invalid_input();
        }while(!(safestream) || ch <= 0 || ch > items.size() + 1);
        if(ch <= items.size()) items[ch-1]->execute();
    }while(ch != items.size() + 1);
}

void view_menu::output_items() {
    system("cls");
    std::cout << "\t" << name << '\n';
    unsigned i = 1;
    for (auto & item : items) {
        std::cout << i << ". " << item->get_name() << '\n';
        ++i;
    }
    std::cout << i << ". Exit";
    std::cout << '\n' << ">  ";
}

void view_menu::process_invalid_input() {
    if(!(safestream >> ch) || ch <= 0 || ch > items.size() + 1) {
        std::cout << "Invalid input: ";
        if(!safestream) {
            std::cout << safestream.get_state();
        }
        else {
            std::cout << " no item with that number";
        }
        std::cout << '\n';
        pause();
    }
}

void action_menu::execute() {
    func();
    pause();
};

void pause() {
    std::cout << "Press Enter to continue" << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}