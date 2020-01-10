#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <iostream>

enum class Player {Blue, Red, Orange, Yellow, Bank, None};

inline std::ostream &operator<<(std::ostream &out, const Player &player) {
    if (player == Player::Blue) {
        return out << "Blue";
    }
    else if (player == Player::Red) {
        return out << "Red";
    }
    else if (player == Player::Orange) {
        return out << "Orange";
    }
    else if (player == Player::Yellow) {
        return out << "Yellow";
    }
    else if (player == Player::Bank) {
        return out << "Bank";
    }
    else {
        return out << "None";
    }
}

#endif
