#pragma once

#include <string>
#include <utility>
#include <unordered_set>
#include <set>
#include <random>
#include <functional>
#include <cstring>
#include <map>

#include "constants.h"

// TODO : LOL
static inline std::random_device rd;
static inline std::mt19937_64 generator(rd());


/*   poker-card class
 *   int "code" in [-1..51] represents a "Card"
 *   where -1 stands for TBD
 */

class Card {
private:
    int code = -1;
public:
    Card() = default;
    explicit Card(int code);
    explicit Card(const std::string& term);

    [[nodiscard]] bool is_tbd() const;
    [[nodiscard]] int get_code() const;

    static int termtocode(std::string term);
    static std::string codetoterm(int code);

    friend std::ostream& operator <<(std::ostream& out, Card card);
    friend bool operator ==(const Card& left, const Card& right);

};

/*
 *   overrides hash<Card> so that hash(Card) == hash(Card.code)
 */
namespace std {
    template <>
    struct hash<Card> {
        size_t operator()(const Card& x) const {
            return hash<int>()(x.get_code());
        }
    };
}


/*
 *   poker-player class
 *   vector "cards" represents Players cards(2) thyself
 */
class Player {
private:
    friend class Match;
    std::vector<Card> cards;
public:
    Player();
    Player(Card c1, Card c2);

    void assign_cards(Card c1, Card c2);
    [[nodiscard]] const std::vector<Card>& get_cards() const;
};


/*
 *   poker-game-state class
 *   integrates one poker-round Players and flop/turn/river Cards in "players" and "flops" respectively
 *   "spare_cards" stands for current deck
 */
class Match {
private:
    std::vector<Player> players;
    std::vector<Card> flops;
    std::unordered_set<Card> spare_cards;

public:
    Match(const std::vector<Player>& players_, const std::vector<Card>& flops_);

    [[nodiscard]] std::vector<double> calc_chances(SAMPLE_SIZE) const ;
    [[deprecated]] [[nodiscard]] std::vector<double> calc_thorough_chances() const ;
    [[nodiscard]] bool is_det() const;
    [[nodiscard]] std::vector<int> get_winners() const;
    [[nodiscard]] std::vector<Card> get_all_cards() const;

    [[nodiscard]] const std::vector<Player>& get_players() const;
    [[nodiscard]] const std::vector<Card>& get_flops() const;
    [[nodiscard]] const std::unordered_set<Card>& get_spare() const;

    void assign_cards(const std::vector<Player>& players_, const std::vector<Card>& flops_);
    void augment_to_det();
};


#include "main_classes_methods.cpp"
