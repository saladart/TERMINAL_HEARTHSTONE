//
// Created by saladart on 5/10/19.
//



#include "CDeck.h"



CDeck::CDeck(const std::string &decksName) : decksName(decksName) {}

//============================================================================================

CDeck & CDeck::ShuffleDeck() {
    std::mt19937 gen( std::chrono::system_clock::now().time_since_epoch().count() );
    std::vector<std::shared_ptr<CCard>> V( deck.begin(), deck.end() );
    shuffle( V.begin(), V.end(), gen );
    deck.assign( V.begin(), V.end() );
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
    return *this;
}

//============================================================================================


CDeck& CDeck::AddCardToDeck(const std::shared_ptr<CCard> &currCard) {
    deck.emplace_back(currCard);
    return *this;
}

void CDeck::Print() const {
    std::cout << decksName << ":" << std::endl;
    for (const auto & it : deck){
        it->Print();
        std::cout << std::endl;
    }
}

CDeck &CDeck::TakeFirstCard(std::shared_ptr<CCard>& resCard) {
    auto firstCard = deck.front()->Clone();
    deck.pop_front();
    resCard =  firstCard;
    return *this;
}

const std::list<std::shared_ptr<CCard>> &CDeck::getDeck() const {
    return deck;
}

void CDeck::setDeck(const std::list<std::shared_ptr<CCard>> &deck) {
    CDeck::deck = deck;
}
