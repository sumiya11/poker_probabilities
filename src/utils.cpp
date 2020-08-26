//
// Created by User on 6/08/2020.
//

#pragma once


#include <iterator>

#ifndef ROMA_UTILS_H
#define ROMA_UTILS_H

#endif //ROMA_UTILS_H

/*
 *   checks whether the two cards are equal value-wise
 */
bool card_eq(Card left, Card right) {
    return left.get_code() % 13 == right.get_code() % 13;
}
/*
 *   checks whether the "left" Card is less than "right" value-wise
 */
bool card_lt(Card left, Card right) {
    return left.get_code() - left.get_code() / 13 * 13 < right.get_code() - right.get_code() / 13 * 13;
}
/*
 *   checks whether the "left" Card is greater than "right" value-wise
 */
bool card_gt(Card left, Card right) {
    return !(card_lt(left, right)) && !(card_eq(left, right));
}

/*
 *   returns the distance between two Cards
 *   where distance is defined as arithmetical difference of their values
 */
int card_dist(Card left, Card right) {
    return left.get_code() % 13 - right.get_code() % 13;
}


/*
 *   standard Card operators
 */
std::ostream& operator <<(std::ostream &out, Card card) {
    out << Card::codetoterm(card.code);
    return out;
}
bool operator==(const Card &left, const Card &right) {
    return left.get_code() == right.get_code();
}


/*
 *   returns a random-choice "Card" from "spare_cards"
 */
Card rnd_card(const std::unordered_set<Card>& spare_cards) {
    std::vector<Card> tmp(1);
    std::sample(spare_cards.begin(), spare_cards.end(), tmp.begin(), 1, generator);
    return tmp.front();
}
/*
 *   returns a random-choice "Card" from "spare_cards"
 *   and erases it from available deck
 */
Card exc_rnd_card(std::unordered_set<Card>& spare_cards) {
    Card card = rnd_card(spare_cards);
    spare_cards.erase(card);
    return card;
}


/*
 *   compares two vectors element-wise
 *   where "true" stands for existence of i such that cmp(left[i], right[i]) == true
 *   but (!cmp(left[j], right[j]) and !cmp(right[i], left[i])) == true for all j < i
 *   (as in tuple comparison)
 */
template <class Obj, class ObjCmp = std::less<Obj>>
bool vec_cmp(const std::vector<Obj>& left, const std::vector<Obj>& right, ObjCmp cmp = ObjCmp()) {
    size_t i = 0;
    while (i != right.size() && i != left.size()) {
        if (cmp(left[i], right[i]) || cmp(right[i], left[i])) {
            return cmp(left[i], right[i]);
        }
        i ++;
    }
    return left.size() < right.size();
}


/*
 *   checks whether two vectors are same element-wise
 */
template <class Obj, class ObjEq = std::equal_to<Obj>>
bool vec_eq(const std::vector<Obj>& left, const std::vector<Obj>& right, ObjEq eq = ObjEq()) {
    size_t i = 0;
    while (i < left.size() || i < right.size()) {
        if (i == left.size() || i == right.size() || !eq(left[i], right[i])) {
            return false;
        }
        i ++;
    }
    return true;
}



