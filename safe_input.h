//
// Created by d3Gaff on 28.09.2021.
//

#ifndef UNTITLED_SAFE_INPUT_H
#define UNTITLED_SAFE_INPUT_H
#include <iostream>
#include <limits>

enum class STATE {
    OK,
    EMPTY,
    TRASH,
    INVALID,
};


class safe_input {
public:
    safe_input(std::istream& stream, bool trash = true)
            : stream(stream), trash(trash) {
    }
    template<typename T>
    safe_input& operator>>(T& var);
    STATE get_state(char& c) { return state; }
    std::string get_state();
    explicit operator bool() const { return state == STATE::OK; }

private:
    void fail(const STATE& state) {
        this->state = state;
    }
    bool trash;
    STATE state = STATE::OK;
    std::istream& stream;
};

template<typename T>
safe_input& safe_input::operator>>(T& var) {

    state = STATE::OK;
    //failbit
    if((stream.peek() == '\n')) state = STATE::EMPTY;
    else if(!(stream >> var)) state = STATE::INVALID;
    else if(trash && stream.peek()!='\n' && stream.peek() != EOF) state = STATE::TRASH;

    stream.clear();
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return *this;
}


static safe_input safestream(std::cin);

#endif //UNTITLED_SAFE_INPUT_H
