//
// Created by saladart on 5/10/19.
//

#ifndef FINAL_SEMESTRAL_WORK_CDECK_H
#define FINAL_SEMESTRAL_WORK_CDECK_H

class CCard;

#include <iostream>
#include <string>
#include <list>
#include <random>
#include <algorithm>
#include "CCard.h"
#include <chrono>
/**
 *@brief represents the Deck (set of cards)
 */
class CDeck {
public:
    CDeck() = default;

    /**
     *@param[in]  decksName name of deck
     */
    explicit CDeck(const std::string &decksName);

    void Print() const;

    /**
     *@brief method shuffles deck
     */
    CDeck &ShuffleDeck();

    /**
     * @brief adds card to deck
     * @param[in] currCard card to add
     */
    CDeck &AddCardToDeck(const std::shared_ptr<CCard> &currCard);

    /**
     *@brief sets the whole deck for loading game from file
     * @param[in] deck the whole deck
     */
    void setDeck(const std::list<std::shared_ptr<CCard>> &deck);

    /**
     * @brief method takes top card from deck and moves it to players hand
     * @param[in] resCard card to take from Deck
     */
    CDeck &TakeFirstCard(std::shared_ptr<CCard> &resCard);

    //Getter
    const std::list<std::shared_ptr<CCard>> &getDeck() const;

private:
    std::list<std::shared_ptr<CCard>> deck;
    std::string decksName;
};


#endif //FINAL_SEMESTRAL_WORK_CDECK_H
