//
// Created by User on 6/08/2020.
//
#pragma once

#ifndef ROMA_CONSTANTS_H
#define ROMA_CONSTANTS_H

#endif //ROMA_CONSTANTS_H



namespace poker_const {

    const inline std::array<char, 4> SUITS = {'H', 'D', 'C', 'S'};
    const inline std::array<char, 13> VALUES = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

    enum SAMPLE_SIZE {
        size_1 = 1000,
        size_2 = 10000
    };
}