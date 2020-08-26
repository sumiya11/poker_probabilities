//
// Created by User on 6/08/2020.
//
#pragma once


#ifndef ROMA_COMBS_H
#define ROMA_COMBS_H

#include "main_classes.h"
#include "utils.h"


/*
 *   a number of poker-combination related funcs with speaking names
 *   checks whether the given Cards satisfy the particular combination
 *
 *   returns a vector of Cards involved in given combination plus 1/2/3/4/5 kicker Cards
 *   if present, ordered descending
 *   in case of combination not found the result is an empty vector
 */

std::vector<Card> flush(const std::vector<Card>& cards);
std::vector<Card> straight(const std::vector<Card>& cards);
std::vector<Card> straight_flush(const std::vector<Card>& cards);

std::vector<Card> royal_flush(const std::vector<Card>& cards) {
    auto straight_flush_cards = straight_flush(cards);
    if (!straight_flush_cards.empty() && card_eq(straight_flush_cards.front(), Card("HA"))) {
        return straight_flush_cards;
    }
    return std::vector<Card>{};
}
std::vector<Card> straight_flush(const std::vector<Card>& cards) {
    std::multiset<Card, std::function<int(Card, Card)>> tmp(cards.begin(), cards.end(), card_gt);
    std::vector<Card> ans;
    for (auto it = tmp.begin(); it != tmp.end() && ans.size() != 5; it ++) {
        if (ans.empty() || card_dist(ans.back(), *it) != 1) {
            ans = { *it };
        } else if (ans.back().get_term()[0] == it->get_term()[0]) {
            ans.push_back(*it);
        }
    }
    if (ans.size() == 4 && ans.back().get_term()[1] == '2' &&
    std::any_of(cards.begin(), cards.end(), [&ans](const Card& c){
        return c.get_term()[1] == 'A' && c.get_term()[0] == ans.front().get_term()[0];
    })) {
        // pass
    } else if (ans.size() < 5) {
        ans.clear();
    }
    return ans;
}
std::vector<Card> four_of_a_kind(const std::vector<Card>& cards) {
    std::multiset<Card, std::function<bool(Card, Card)>> tmp(cards.begin(), cards.end(), card_gt);
    std::vector<Card> ans;
    for (auto it = std::next(tmp.begin()); it != std::prev(std::prev(tmp.end())); it ++) {
        if (card_eq(*it, *std::next(it)) && card_eq(*it, *std::prev(it)) &&
        card_eq(*it, *std::next(std::next(it)))) {
            for (Card c : {*std::prev(it), *it, *std::next(it), *std::next(it, 2)}) {
                ans.push_back(c);
                tmp.erase(c);
            }
            break;
        }
    }
    if (!ans.empty()) {
        std::copy_n(tmp.begin(), 1, std::back_inserter<std::vector<Card>>(ans));
    }
    return ans;
}

std::vector<Card> full_house(const std::vector<Card>& cards) {
    std::multiset<Card, std::function<bool(Card, Card)>> tmp(cards.begin(), cards.end(), card_gt);
    std::vector<Card> ans;
    for (auto it = std::next(tmp.begin()); it != std::prev(tmp.end()); it ++) {
        if (card_eq(*it, *std::next(it)) && card_eq(*it, *std::prev(it))) {
            for (Card c : {*std::prev(it), *it, *std::next(it)}) {
                ans.push_back(c);
                tmp.erase(c);
            }
            break;
        }
    }
    if (!ans.empty()) {
        for (auto it = tmp.begin(); it != std::prev(tmp.end()); it++) {
            if (card_eq(*it, *std::next(it))) {
                for (Card c : {*it, *std::next(it)}) {
                    ans.push_back(c);
                    tmp.erase(c);
                }
                break;
            }
        }
    }
    if (ans.size() < 5) {
        ans.clear();
    }
    return ans;
}

std::vector<Card> flush(const std::vector<Card>& cards) {
    std::map<char, std::vector<Card>> suit_count;
    std::multiset<Card, std::function<bool(Card, Card)>> tmp(cards.begin(), cards.end(), card_gt);
    for (auto c : tmp) {
        suit_count[Card::codetoterm(c.get_code())[0]].push_back(c);
    }
    for (const auto& [s, c] : suit_count) {
                if (c.size() >= 5) {
            return c;
        }
    }
    return std::vector<Card>();
}

std::vector<Card> straight(const std::vector<Card>& cards) {
    std::multiset<Card, std::function<int(Card, Card)>> tmp(cards.begin(), cards.end(), card_gt);
    std::vector<Card> ans;
    for (auto it = tmp.begin(); it != std::prev(tmp.end()) && ans.size() != 5; it ++) {
        if (card_dist(*it, *std::next(it)) == 1) {
            if (ans.empty()) {
                ans = { *it, *std::next(it) };
            } else {
                ans.push_back(*std::next(it));
            }
        } else {
            ans = { *it };
        }
    }
    if (ans.size() == 4  && ans.back().get_term()[1] == '2'
    && card_eq(*tmp.begin(), Card("HA"))) {
        // pass
    } else if (ans.size() < 5) {
        ans.clear();
    }
    return ans;
}

std::vector<Card> three_of_a_kind(const std::vector<Card>& cards) {
    std::multiset<Card, std::function<bool(Card, Card)>> tmp(cards.begin(), cards.end(), card_gt);
    std::vector<Card> ans;
    for (auto it = std::next(tmp.begin()); it != std::prev(tmp.end()); it ++) {
        if (card_eq(*it, *std::next(it)) && card_eq(*it, *std::prev(it))) {
            for (Card c : std::vector{*std::prev(it), *it, *std::next(it)}) {
                ans.push_back(c);
                tmp.erase(c);
            }
            break;
        }
    }
    if (!ans.empty()) {
        std::copy_n(tmp.begin(), 2, std::back_inserter<std::vector<Card>>(ans));
    }
    return ans;
}

std::vector<Card> two_pair(const std::vector<Card>& cards) {
    std::multiset<Card, std::function<bool(Card, Card)>> tmp(cards.begin(), cards.end(), card_gt);
    std::vector<Card> ans;
    for (size_t i = 0; i < 2; i ++) {
        for (auto it = tmp.begin(); it != std::prev(tmp.end()); it++) {
            if (card_eq(*it, *std::next(it))) {
                for (Card c : std::vector{*it, *std::next(it)}) {
                    ans.push_back(c);
                    tmp.erase(c);
                }
                break;
            }
        }
    }
    if (!ans.empty()) {
        std::copy_n(tmp.begin(), 1, std::back_inserter<std::vector<Card>>(ans));
    }
    return ans;
}

std::vector<Card> one_pair(const std::vector<Card>& cards) {
    std::multiset<Card, std::function<bool(Card, Card)>> tmp(cards.begin(), cards.end(), card_gt);
    std::vector<Card> ans;
    for (auto it = tmp.begin(); it != std::prev(tmp.end()); it ++) {
        if (card_eq(*it, *std::next(it))) {
            if (card_eq(*it, *std::next(it))) {
                for (Card c : std::vector{*it, *std::next(it)}) {
                    ans.push_back(c);
                    tmp.erase(c);
                }
                break;
            }
        }
    }
    if (!ans.empty()) {
        std::copy_n(tmp.begin(), 3, std::back_inserter<std::vector<Card>>(ans));
    }
    return ans;
}

std::vector<Card> higher_card(const std::vector<Card>& cards) {
    std::vector<Card> ans(5);
    std::partial_sort_copy(cards.begin(), cards.end(), ans.begin(), ans.end(), card_gt);
    return ans;
}


#endif //ROMA_COMBS_H
