#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H
#include <string>
#include <vector>
#include <tuple>
#include <memory>

#include "safe_input.h"

extern std::string LAST_CHOSEN;

void pause();

class menu_item {
public:
    menu_item(const std::string& name)
            : name(name)  {}
    virtual void execute() = 0;
    std::string get_name() { return name; }

protected:
    const std::string name;
};

typedef std::vector<std::shared_ptr<menu_item>> menu;


class view_menu : public menu_item {
public:

    view_menu(const std::string& name,
              menu items)
            : menu_item(name), items(items){

    }
    void execute() override;
    void output_items();
    void process_invalid_input();
private:
    unsigned ch = 0;
    menu items;
};

class action_menu : public menu_item {
public:
    action_menu(const std::string& name,
                void (*func)())
            : menu_item(name), func(func) {}

    void execute() override;
private:
    void (*func)();
};

#endif //UNTITLED_MENU_H
