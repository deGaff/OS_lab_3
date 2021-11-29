//
// Created by d3Gaff on 28.09.2021.
//

#include "safe_input.h"

std::string safe_input::get_state() {
    switch (state) {
        case STATE::OK:
            return "input is ok";
        case STATE::TRASH:
            return "elements after the input";
        case STATE::EMPTY:
            return "empty string passed";
        case STATE::INVALID:
            return "invalid value passed";
    }
}