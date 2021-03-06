#pragma once

#include "main_classes.h"
#include "combinations_utils.h"
#include "utils.h"



/*
 *   Card(std::string) constructs a "Card" from string repr
 *   (format: '[H-D-C-S] + [2-A]' OR '-' (for TBD))
 */
Card::Card(int code_) : code(code_) {}
Card::Card(const std::string& term) : code(Card::termtocode(term)) {}

/*
 *   converts term "Card" repr to code "Card" repr
 */
int Card::termtocode(std::string term) {
    if (term == std::string{"-"}) {
        return int(-1);
    }
    return 13 * std::distance(SUITS.begin(),
            std::find(SUITS.begin(), SUITS.end(), term[0]))
        +
        std::distance(VALUES.begin(),
                std::find(VALUES.begin(), VALUES.end(), term[1]));
}

/*
 *   converts code "Card" repr to term "Card" repr
 */
std::string Card::codetoterm(int code) {
    if (code == -1) {
        return std::string("-");
    }
    return std::string{ SUITS[code / 13], VALUES[code -  code / 13 * 13] };
}

/*
 *   checks whether the card is defined
 */
bool Card::is_tbd() const {
    return code == -1;
}
int Card::get_code() const {
    return code;
}
std::string Card::get_term() const {
    return Card::codetoterm(code);
}

Player::Player(Card c1, Card c2) {
    assign_cards(c1, c2);
}

void Player::assign_cards(Card c1, Card c2) {
    cards = std::vector<Card>{c1, c2};
}

Player::Player() = default;
const std::vector<Card> &Player::get_cards() const {
    return cards;
}


/*
 *   Match(players_, flops_) constructs a "Match" as a poker-round
 *   with given players and postflop cards
 */
Match::Match(const std::vector<Player> &players_, const std::vector<Card>& flops_) {
    spare_cards = std::unordered_set<Card>();
    for (size_t i = 0; i < 52; i ++) {
        spare_cards.insert(Card(i));
    }
    assign_cards(players_, flops_);
}

/*
 *
 */
void Match::augment_to_det() {
    for (Player& player : this->players) {
        player.cards[0] = player.cards[0].is_tbd() ? exc_rnd_card(this->spare_cards) : player.cards[0];
        player.cards[1] = player.cards[1].is_tbd() ? exc_rnd_card(this->spare_cards) : player.cards[1];
    }
    for (Card& card : this->flops) {
        card = card.is_tbd() ? exc_rnd_card(this->spare_cards) : card;
    }
}

/*
 *   Returns a vector of fractions of sum 1
 *   where i-th fraction corresponds to PR[i-th player shares pot]
 */
std::vector<double> Match::calc_chances(SAMPLE_SIZE sample_size) const {
    std::vector<int> acc_players(players.size());
    for (size_t i = 0; i < sample_size; i ++) {
        Match match_copy_1(*this);
        match_copy_1.augment_to_det();
        for (int winner_idx : match_copy_1.get_winners()) {
            acc_players[winner_idx] += 1;
        }
    }
    std::vector<double> ans(players.size());
    for (int i = 0; i < ans.size(); i ++) {
        ans[i] = static_cast<double>(acc_players[i]) / std::accumulate(acc_players.begin(), acc_players.end(), 0);
    }
    return ans;
}

/*
 *   Do not call it
 */
std::vector<double> Match::calc_thorough_chances() const {
    return std::vector<double>();
}

/*
 *   Thoroughly replaces current Match "players" and "flops" with in-params respectively
 *   Generates new deck
 */
void Match::assign_cards(const std::vector<Player> &players_, const std::vector<Card>& flops_) {
    std::vector<Card> tmp = get_all_cards();
    std::for_each(tmp.begin(), tmp.end(), [&](const Card& c){ if (!c.is_tbd()) { spare_cards.insert(c); } });

    players = players_;
    flops = flops_;

    tmp = get_all_cards();
    std::for_each(tmp.begin(), tmp.end(), [&](const Card& c){ spare_cards.erase(c); });
}

/*
 *   Checks whether the poker-round is over and a certain winner(s) could be determined
 *   Determined "Match" basically contains none of TBD Cards
 */
bool Match::is_det() const {
    return !std::any_of(get_all_cards().begin(), get_all_cards().end(), [](Card c){ return c.is_tbd(); });
}

/*
 *   WARNING : in order to avoid UB can only be called for determined "Match"
 *
 *   Calculates an array of indices each standing for a player who shares pot
 *   Intrinsically every not-a-loser player counts in
 */
std::vector<int> Match::get_winners() const {
    std::vector<std::function<std::vector<Card>(const std::vector<Card>&)>>
            comb_funcs = {royal_flush, straight_flush, four_of_a_kind, full_house, flush, straight,
                          three_of_a_kind, two_pair, one_pair, higher_card};
    std::vector<int> ans;
    for (auto& comb_func : comb_funcs) {
        std::vector<Card> strongest;
        for (size_t i = 0; i < players.size(); i ++) {
            std::vector<Card> player_related_cards_1 = players[i].get_cards();
            player_related_cards_1.insert(player_related_cards_1.begin(), flops.begin(), flops.end());
            if (vec_cmp<Card, decltype(card_lt)>(strongest, comb_func(player_related_cards_1), card_lt)) {
                ans = std::vector<int>{ static_cast<int>(i) };
                strongest = comb_func(player_related_cards_1);
            } else if (vec_eq<Card, decltype(card_eq)>(strongest, comb_func(player_related_cards_1), card_eq)) {
                ans.push_back(static_cast<int>(i));
            }
        }
        if (!strongest.empty()) {
            break;
        }
    }
    return ans;
}

/*
 *   Returns a vector of all "players" and "flops" Cards occurring in poker-round
 */
std::vector<Card> Match::get_all_cards() const {
    std::vector<Card> ans(flops.begin(), flops.end());
    for (const Player& player : players) {
        ans.insert(ans.begin(), player.get_cards().begin(), player.get_cards().end());
    }
    return ans;
}


const std::unordered_set<Card>& Match::get_spare() const {
    return spare_cards;
}
const std::vector<Player> &Match::get_players() const {
    return players;
}
const std::vector<Card> &Match::get_flops() const {
    return flops;
}

