#pragma once


#ifndef POKER_H
#define POKER_H

#include "main_classes.cpp"

/*
 *   POKER
 *   Standard Texas hold'em rules
 */

/*
 *   This file provides definitions for all poker-api methods
 */

/*
 *   param: players - hand participants  ( 0 < len(players) < 10 )
 *   param: flops   - all drawn cards    ( len(flops) == 5 )
 *
 *   hold_single_hand returns a vector of indices of Players
 *   where each index stands for a Player from given param: players
 *   sharing the pot (generally - winner)
 *   Any TBD Cards are auto-generated randomly
 */
std::vector<int> hold_single_hand(
        const std::vector<Player>& players,
        const std::vector<Card>& flops);
/*
 *   Same as previous, but match stands for Match(players, cards)
 */
std::vector<int> hold_single_hand(const Match& match);



/*
 *   param: players - hand participants ( 0 < len(players) < 10)
 *   param: flops   - all drawn cards ( len(flops) == 5)
 *   param: sample_size - amount of test iterations
 *
 *   Returns a vector( len(players) ) of fractions of sum 1
 *   where i-th fraction corresponds to PR[i-th player shares pot]
 *   Generally, bigger sample_size implies greater accuracy
 */
std::vector<double> calculate_pr(
        const std::vector<Player>& players,
        const std::vector<Card>& flops,
        SAMPLE_SIZE sample_size=SAMPLE_SIZE::SMALL);
/*
 *   Same as previous, but match stands for Match(players, cards)
 */
std::vector<double> calculate_pr(
        const Match& match,
        SAMPLE_SIZE sample_size=SAMPLE_SIZE::SMALL);


#include "poker.cpp"

#endif







