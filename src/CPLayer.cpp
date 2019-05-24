//
// Created by saladart on 5/10/19.
//

#include "CPLayer.h"
#include "CGame.h"
#include "CWeapon.h"
#include "CSpell.h"


CPlayer::CPlayer(const std::string &playerName) : playerName(playerName) {}

CPlayer &CPlayer::GetHit(const unsigned int currHarm) {
    if (healthPoints < currHarm) healthPoints = 0;
    else healthPoints -= currHarm;
    return *this;
}

//==================================================================

bool CPlayer::HaveWeapon() const {
    return haveWeapon;
}

const std::string &CPlayer::getPlayerName() const {
    return playerName;
}

CPlayer &CPlayer::AttackOtherPLayer(std::shared_ptr<CPlayer> &opponent) {
    if (!haveWeapon) return *this;
    playersWeapon->AttackPlayer(opponent);
    if (std::dynamic_pointer_cast<CWeapon>(playersWeapon)->getHitsLeft() == 0)
        haveWeapon = false;
    return *this;

}

CPlayer &CPlayer::AttackCard(std::shared_ptr<CCard> &opponentCard) {
    if (!haveWeapon) return *this;
    playersWeapon->AttackCard(opponentCard);
    if (std::dynamic_pointer_cast<CWeapon>(playersWeapon)->getHitsLeft() == 0)
        haveWeapon = false;
    return *this;
}

CPlayer &CPlayer::ThrowCard(std::list<std::shared_ptr<CCard>> &  currTable,  bool & cardFound, bool & enoughMana, bool & isSpell,  const unsigned int cardId) {
    cardFound = false;
    std::shared_ptr<CCard> currCard;
    //find card in hand
    for (auto & it : currentHand)
        if (it->getCardId() == cardId){
            currCard = it;
            cardFound = true;
            break;
        }
    if (!cardFound) return *this;

    if (currCard->getManaRequired() > currentMana) {
        enoughMana = false;
        return *this;
    }
    enoughMana = true;
    if (auto card = std::dynamic_pointer_cast<CWeapon>(currCard)) {
        playersWeapon = card->Clone();
        playersWeapon->setReadyToAttack(false);
        haveWeapon = true;
    } else if (auto card = std::dynamic_pointer_cast<CSpell>(currCard)) {
        isSpell = true;
        currentMana -= currCard->getManaRequired();
        return *this;
    } else {
            currTable.push_back(currCard);
            currCard->setReadyToAttack(false);
    }
    currentMana -= currCard->getManaRequired();
    std::cout << "You thrown " << currCard->getCardName() << std::endl;
    DeleteCardFromHand(currCard);
    return *this;
}

CPlayer &CPlayer::TakeDeck(const std::shared_ptr<CDeck> &currDeck) {
    playersDeck = currDeck;
    playersDeck->ShuffleDeck();
    return *this;
}

void CPlayer::PrintHand() const {
    for (const auto &tempCard : currentHand){
        tempCard->Print();
        std::cout << std::endl;
    }
}

CPlayer &CPlayer::TakeNCardsFromDeck(unsigned int numberOfCards) {
    for (unsigned int i = 0; i < numberOfCards; ++i) {
        std::shared_ptr<CCard> tempCard;
        playersDeck->TakeFirstCard(tempCard);
        currentHand.emplace_back(tempCard);
    }
    return *this;
}

CPlayer &CPlayer::setMana(unsigned int Mana) {
    if (Mana < 10) currentMana = Mana;
    return *this;
}

void CPlayer::PrintCharacteristics() {
    std::cout << std::endl;
    std::cout << "Mana: " << currentMana << std::endl;
    std::cout << "Health Points: " << healthPoints << std::endl;
    if (haveWeapon) {
        std::dynamic_pointer_cast<CWeapon>(playersWeapon)->PrintWeaponInHand();
    } else {
        std::cout << "No weapon" << std::endl;
    }
    std::cout << std::endl;
}



unsigned int CPlayer::getCurrentMana() const {
    return currentMana;
}

const std::shared_ptr<CCard> &CPlayer::getPlayersWeapon() const {
    return playersWeapon;
}


unsigned int CPlayer::getHealthPoints() const {
    return healthPoints;
}

CPlayer& CPlayer::DeleteCardFromHand(std::shared_ptr<CCard> & currCard) {
    auto cardToDel = std::find(currentHand.begin(), currentHand.end(), currCard);
    if (cardToDel != currentHand.end())
        currentHand.erase(cardToDel);
    return *this;
}

const std::list<std::shared_ptr<CCard>> &CPlayer::getCurrentHand() const {
    return currentHand;
}

bool CPlayer::isAlive() {
    return healthPoints > 0;
}

const std::shared_ptr<CDeck> &CPlayer::getPlayersDeck() const {
    return playersDeck;
}

void CPlayer::setHaveWeapon(bool haveWeapon) {
    CPlayer::haveWeapon = haveWeapon;
}

void CPlayer::setPlayersWeapon(const std::shared_ptr<CCard> &playersWeapon) {
    CPlayer::playersWeapon = playersWeapon;
}

void CPlayer::setHealthPoints(unsigned int healthPoints) {
    CPlayer::healthPoints = healthPoints;
}

void CPlayer::setCurrentHand(const std::list<std::shared_ptr<CCard>> &currentHand) {
    CPlayer::currentHand = currentHand;
}




