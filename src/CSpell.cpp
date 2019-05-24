//
// Created by saladart on 5/10/19.
//

#include "CSpell.h"

CSpell::CSpell( unsigned int currCardId, const std::string & currCardName, unsigned int currManaRequired,
                unsigned int currAttackDamage,
                unsigned int currSelfHarm) : CCard (currCardId, currCardName,
                                                    currManaRequired, currAttackDamage) , selfHarm (currSelfHarm) {}

std::shared_ptr<CCard> CSpell::Clone() const {
    return std::make_shared<CSpell>(*this);
}

CCard& CSpell::AttackPlayer(std::shared_ptr<CPlayer> & opponent) {
    opponent->GetHit(attackDamage);
    opponent->setMana(0);
    return *this;
}

CCard& CSpell::AttackCard(std::shared_ptr<CCard> opponentCard) {
    //card on table can be only CCreature
    std::dynamic_pointer_cast<CCreature>(opponentCard)->GetHit(attackDamage);
    opponentCard->setReadyToAttack(false);
    return *this;
}

void CSpell::Print() {
    std::cout << std::setw(15) << "Spell: "<< std::setw(15)
    << cardId << std::setw(15) <<
    cardName << std::setw(15) <<
    manaRequired << std::setw(15)<<
    attackDamage << std::setw(15)<<
    selfHarm;
}

unsigned int CSpell::getSelfHarm() const {
    return selfHarm;
}
