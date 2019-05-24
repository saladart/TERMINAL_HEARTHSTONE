//
// Created by saladart on 5/10/19.
//

#include "CCard.h"

CCard::CCard(unsigned int currCardId, const std::string &currCardName, unsigned int currManaRequired,
             unsigned int currAttackDamage) : cardId(currCardId),
                                              cardName(currCardName),
                                              manaRequired(currManaRequired),
                                              attackDamage(currAttackDamage) {}


unsigned int CCard::getCardId() const {
    return cardId;
}

const std::string &CCard::getCardName() const {
    return cardName;
}

unsigned int CCard::getManaRequired() const {
    return manaRequired;
}

bool CCard::isReadyToAttack() const {
    return readyToAttack;
}

void CCard::setReadyToAttack(bool readyToAttack) {
    CCard::readyToAttack = readyToAttack;
}

unsigned int CCard::getAttackDamage() const {
    return attackDamage;
}
