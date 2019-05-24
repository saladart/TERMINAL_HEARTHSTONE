//
// Created by saladart on 5/10/19.
//

#include "CWeapon.h"

CWeapon::CWeapon(unsigned int currCardId, const std::string &currCardName, unsigned int currManaRequired,
                 unsigned int currAttackDamage, unsigned int currHitsLeft) : CCard(currCardId,
                                                                                   currCardName,
                                                                                   currManaRequired,
                                                                                   currAttackDamage),
                                                                             hitsLeft(currHitsLeft) {}

std::shared_ptr<CCard> CWeapon::Clone() const {
    return std::make_shared<CWeapon>(*this);
}

CCard &CWeapon::AttackPlayer(std::shared_ptr<CPlayer> &opponent) {
    opponent->GetHit(attackDamage);
    hitsLeft--;
    this->readyToAttack = false;
    std::cout << "weapon attacks player" << std::endl;
    return *this;
}

CCard &CWeapon::AttackCard(std::shared_ptr<CCard> opponentCard) {
    std::dynamic_pointer_cast<CCreature>(opponentCard)->GetHit(attackDamage);
    hitsLeft--;
    this->readyToAttack = false;
    std::cout << "weapon attacks card" << std::endl;
    return *this;
}

void CWeapon::Print() {
    std::cout << std::setw(15) << "Weapon: " << std::setw(15) << cardId << std::setw(15) << cardName << std::setw(15)
              << manaRequired << std::setw(15) << attackDamage << std::setw(15) << hitsLeft;
}

void CWeapon::PrintWeaponInHand() {
    std::cout << "Weapon: " << cardName << " with " << hitsLeft << " hit" << (hitsLeft != 1 ? "s" : "") << " left";
    std::cout << std::setw(10) << (this->isReadyToAttack() ? "ready" : "Zzz...") << std::endl;
}

unsigned int CWeapon::getHitsLeft() const {
    return hitsLeft;
}
