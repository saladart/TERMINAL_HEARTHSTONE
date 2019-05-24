//
// Created by saladart on 5/10/19.
//

#include "CComputer.h"
#include "CCreature.h"

bool CComputer::isReadyCards(const std::list<std::shared_ptr<CCard>> cardsOnTable) {
    for (const auto &card : cardsOnTable)
        if (card->isReadyToAttack())
            return true;
    return false;
}

void CComputer::DoSomething(const std::list<std::shared_ptr<CCard>> cardsOnTableP1,
                            std::list<std::shared_ptr<CCard>> &cardsOnTableP2,
                            bool &playerAttacks, bool &attackCard, bool &endTurn, bool &throwCard,
                            std::pair<std::shared_ptr<CCard>, unsigned int> &target,
                            std::pair<std::shared_ptr<CCard>, unsigned int> &attacker) {
    //bool isFound, enoughMana, isSpell;
    attackCard = false;
    playerAttacks = false;
    endTurn = false;
    throwCard = false;
    target = std::make_pair(nullptr, -42);
    attacker = std::make_pair(nullptr, -42);

    std::pair<std::shared_ptr<CCard>, unsigned int> maxDamageOpp, minHPOpp, minManaMy, maxManaMy, maxDamageMy, minDamageMy, readyCardOnTable;

    bool first = true;
    //find the most powerful and weakest cards
    for (const auto &opponentCard : cardsOnTableP1) {
        if (first) {
            maxDamageOpp = std::make_pair(opponentCard, opponentCard->getAttackDamage());
            minHPOpp = std::make_pair(opponentCard,
                                      std::dynamic_pointer_cast<CCreature>(opponentCard)->getHealthLevel());
            first = false;
        } else if (opponentCard->getAttackDamage() > maxDamageOpp.second) {
            maxDamageOpp = std::make_pair(opponentCard, opponentCard->getAttackDamage());
        } else if (std::dynamic_pointer_cast<CCreature>(opponentCard)->getHealthLevel() < minHPOpp.second) {
            minHPOpp = std::make_pair(opponentCard,
                                      std::dynamic_pointer_cast<CCreature>(opponentCard)->getHealthLevel());
        }
    }

    for (const auto &myCard : cardsOnTableP2) {
        if (myCard->isReadyToAttack()) {
            readyCardOnTable = std::make_pair(myCard, myCard->getCardId());
            break;
        }
    }
    //find the cheapest and thr most expensive cards
    first = true;
    for (const auto &cardInHand : getCurrentHand()) {
        if (first) {
            minManaMy = std::make_pair(cardInHand, cardInHand->getManaRequired());
            maxManaMy = std::make_pair(cardInHand, cardInHand->getManaRequired());
            maxDamageMy = std::make_pair(cardInHand, cardInHand->getAttackDamage());
            minDamageMy = std::make_pair(cardInHand, cardInHand->getAttackDamage());
            first = false;
        } else if (cardInHand->getManaRequired() > maxManaMy.second) {
            maxManaMy = std::make_pair(cardInHand, cardInHand->getManaRequired());
        } else if (cardInHand->getManaRequired() < minManaMy.second) {
            minManaMy = std::make_pair(cardInHand, cardInHand->getManaRequired());
        } else if (cardInHand->getAttackDamage() > maxDamageMy.second) {
            maxDamageMy = std::make_pair(cardInHand, cardInHand->getAttackDamage());
        } else if (cardInHand->getAttackDamage() < minDamageMy.second) {
            minDamageMy = std::make_pair(cardInHand, cardInHand->getAttackDamage());
        }
    }

    //if player can attack he would attack an opponent
    if (HaveWeapon() && getPlayersWeapon()->isReadyToAttack()) {
        playerAttacks = true;
    }

        //if there're ready cards
    else if (isReadyCards(cardsOnTableP2)) {
        attacker = readyCardOnTable;
        if (maxDamageOpp.second > 4) {
            target = maxDamageOpp;
            attackCard = true;
        } else if (minHPOpp.second <= attacker.first->getAttackDamage()) {
            target = minHPOpp;
            attackCard = true;
        } else
            attackCard = false;
    } else if (getCurrentMana() >= minManaMy.second) {
        throwCard = true;
        if (getCurrentMana() >= maxManaMy.second) {
            target = maxManaMy;
        } else {
            target = minManaMy;
        }
    } else {
        endTurn = true;
    }
}