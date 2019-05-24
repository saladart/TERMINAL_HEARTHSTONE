//
// Created by saladart on 5/10/19.
//


#include "CCreature.h"

CCreature::CCreature(unsigned int currCardId, const std::string &currCardName, unsigned int currManaRequired,
                     unsigned int currAttackDamage, unsigned int currCardHealthLevel) : CCard(currCardId, currCardName,
                                                                                              currManaRequired, currAttackDamage),
                                                                                        healthLevel(currCardHealthLevel) {}
//============================================================================

std::shared_ptr<CCard> CCreature::Clone() const {
    return std::make_shared<CCreature>(*this);
}

//============================================================================

CCreature & CCreature::GetHit (const unsigned int damage){
    if (damage > healthLevel) healthLevel = 0;
    else healthLevel -= damage;
    return *this;
}

CCard& CCreature::AttackPlayer(std::shared_ptr<CPlayer> & opponent) {
    opponent->GetHit(attackDamage * healthLevel / 2);
    this->readyToAttack = false;
    std::cout <<"creature attacks player" << std::endl;
    return *this;
}

CCard& CCreature::AttackCard(std::shared_ptr<CCard> opponentCard) {
    std::dynamic_pointer_cast<CCreature>(opponentCard)->GetHit(attackDamage * healthLevel / 2);
    this->readyToAttack = false;
    std::cout <<"creature attacks card" << std::endl;
    return *this;
}

void CCreature::Print() {
    std::cout << std::setw(15) << "Creature: "<< std::setw(15) << cardId << std::setw(15) << cardName << std::setw(15) << manaRequired << std::setw(15) <<
    attackDamage * healthLevel / 2 << std::setw(15) << healthLevel;
}

unsigned int CCreature::getHealthLevel() const {
    return healthLevel;
}

void CCreature::setHealthLevel(unsigned int healthLevel) {
    CCreature::healthLevel = healthLevel;
}
