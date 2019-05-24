//
// Created by saladart on 5/10/19.
//

#include "CGame.h"


void CGame::InitGame() {

    std::shared_ptr<CHuman> person;
    std::string name, password, choice;
    printf("\033c");
    std::cout << "Game Started" << std::endl;

    bool ready = false;
    // choose between new game and load game and set nickname and password for player. Furthermore read decks from Decks.txt
    do {
        std::cout << "(1:New Game, 2:Load Game):" << std::flush;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == "1") {
            std::cout << "Set your nickname: " << std::flush;
            std::cin >> name;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear
            std::cout << "Welcome " << name << std::endl;
            std::cout << "Set your password, " << name << ": " << std::flush;
            std::cin >> password;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (!name.empty() && !password.empty())
                player1 = std::make_shared<CHuman>(CHuman(name, password));
            printf("\033c");
            ChooseMode();
            ReadDecks();
            isLoaded = false;
            ready = true;
        } else if (choice == "2") {
            UploadGame();
            ready = isLoaded; // Method changes flag isLoaded and if it's true, game is ready
        } else {
            ready = false;
            choice.clear();
            std::cout << "Incorrect choice try again" << std::endl;
        }
    } while (!ready);
}

//====================================================================================

CGame &CGame::ChooseMode() {

    std::string choice;
    bool ready;
    //if game is  PVP second player required
    do {
        std::cout << "Choose PLaying Mode:\n(1:PvP, 2:PvC):  " << std::flush;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printf("\033c");
        if (choice == "1") {
            std::string name, password2;
            std::shared_ptr<CHuman> opponent;
            std::cout << "Set your nickname, player2: " << std::flush;
            std::cin >> name;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Set your password " << name << ": " << std::flush;
            std::cin >> password2;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            player2 = std::make_shared<CHuman>(CHuman(name, password2));
            printf("\033c");
            std::cout << "Password successfully set" << std::endl;
            isPvP = true;
            isRunning = true;
            ready = true;
        }
            //mode PvC
        else if (choice == "2") {
            player2 = std::make_shared<CComputer>(CComputer("WorstNightmare"));
            isPvP = false;
            isRunning = true;
            ready = true;
        } else {
            ready = false;
            choice.clear();
            std::cout << "Incorrect choice try again" << std::endl;
        }
    } while (!ready);


    return *this;

}

//=================================================================================
//Method reads decks from templated file and add them to game
CGame &CGame::ReadDecks() {
    std::ifstream input_file("Decks.txt");

    if (!input_file.good()) {
        input_file.close();
        std::cout << "Cannot open the file Decks.txt" << std::endl;
        //TODO Decks.txt not found
        return *this;
    }

    while (true) {
        std::string trigger, deckName, tempCardName;
        unsigned int tempCardId, tempMana, tempAttackDamage, tempHealth;
        input_file >> trigger;
        if (trigger == "Deck:") {
            input_file.ignore(6);
            input_file >> deckName;
            CDeck tempDeck(deckName);
            while (true) {


                input_file >> trigger;
                if (trigger == "DECK_END")
                    break;
                input_file >> tempCardId;
                input_file >> tempCardName;
                input_file >> tempMana;
                input_file >> tempAttackDamage;
                input_file >> tempHealth;

                if (trigger == "Creature") {
                    CCreature tempCreature(tempCardId, tempCardName, tempMana, tempAttackDamage, tempHealth);
                    tempDeck.AddCardToDeck(tempCreature.Clone());
                } else if (trigger == "Weapon") {
                    CWeapon tempWeapon(tempCardId, tempCardName, tempMana, tempAttackDamage, tempHealth);
                    tempDeck.AddCardToDeck(tempWeapon.Clone());
                } else if (trigger == "Spell") {
                    CSpell tempSpell(tempCardId, tempCardName, tempMana, tempAttackDamage, tempHealth);
                    tempDeck.AddCardToDeck(tempSpell.Clone());
                }
            }
            playingDecks.emplace_back(tempDeck);

        } else if (trigger == "END") {
            break;
        } else
            std::cout << "Error in Deck.txt occurred" << std::endl;

    }

    if (!playingDecks.empty()) {

        printf("\033c");
        std::cout << "Decks and cards successfully added" << std::endl;

    }
    return *this;
}

//====================================================================
CGame &CGame::PLayerTurn(bool player1Turn, bool &isSave) {
    std::string password;
    bool passwordCorrect;
    std::cout << (player1Turn ? player1 : player2)->getPlayerName() << "'s turn" << std::endl;
    sleep(1);
    printf("\033c");
    if (isPvP)
        do {
            std::cout << "Fill your password, " << (player1Turn ? player1 : player2)->getPlayerName() << ": "
                      << std::flush;
            std::cin >> password;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            passwordCorrect = std::dynamic_pointer_cast<CHuman>((player1Turn ? player1 : player2))->CheckPassword(
                    password);
            printf("\033c");
            if (!passwordCorrect) std::cout << "Try again" << std::endl;
        } while (!passwordCorrect);
    std::cout << "password OK" << std::endl;
    sleep(1);
    printf("\033c");
    bool isEnd = false;
    while (!isEnd && !isSave) {
        printf("\033c");
        std::cout << "YOUR OPPONENT HAS:" << std::endl;
        (player1Turn ? player2 : player1)->PrintCharacteristics();
        std::cout << std::endl;
        std::cout << "CARDS ON TABLE:" << std::endl;
        std::cout << std::endl;
        UpdateCardsOnTable();
        PrintCardsOnTable();
        std::cout << std::endl;

        std::cout << "YOUR CURRENT HAND:" << std::endl;
        PrintTable();
        (player1Turn ? player1 : player2)->PrintHand();
        std::cout << "\n========================================================" << std::endl;
        (player1Turn ? player1 : player2)->PrintCharacteristics();
        std::cout << "========================================================" << std::endl;
        HandleEvents(player1Turn, isEnd, isSave);
        printf("\033c");
        if (!player1->isAlive() || !player2->isAlive()) break;
    }
    return *this;
}


void CGame::GameLoop() {

    bool isSave = false;
    if (isPvP) {
        if (!isLoaded) {
            mana = 1;
            player1->TakeDeck(std::make_shared<CDeck>(playingDecks.front()));
            player2->TakeDeck(std::make_shared<CDeck>(playingDecks.back()));
            player1->TakeNCardsFromDeck(3);
            player2->TakeNCardsFromDeck(3);
        } else {
            mana = 1;
            player1->setMana(mana);
            player2->setMana(mana);
        }
        bool player1Turn = true;

        while (isRunning && player1->isAlive() && player2->isAlive()) {


            PLayerTurn(player1Turn, isSave);
            (player1Turn ? player1 : player2)->TakeNCardsFromDeck(1);
            if (!player1Turn) {
                mana++;
                player1->setMana(mana);
                player2->setMana(mana);
                SetCardsReady();
            }
            player1Turn = !player1Turn;
        }
        if (!isRunning && isSave) {
            std::cout << "GAME SAVED" << std::endl;
        } else if (!player1->isAlive() && player2->isAlive())
            std::cout << player2->getPlayerName() << " WINS" << std::endl;
        else if (player1->isAlive() && !player2->isAlive())
            std::cout << player1->getPlayerName() << " WINS" << std::endl;
        else
            std::cout << "IT'S A DRAW" << std::endl;
    }
        //Computer vs Player
    else {
        std::shared_ptr<CCard> target, attacker;

        if (!isLoaded) {
            mana = 1;
            player1->TakeDeck(std::make_shared<CDeck>(playingDecks.front()));
            player2->TakeDeck(std::make_shared<CDeck>(playingDecks.back()));
            player1->TakeNCardsFromDeck(3);
            player2->TakeNCardsFromDeck(3);
            player1->setMana(mana);
            player2->setMana(mana);

        }
        bool player1Turn = true;
        while (isRunning && player1->isAlive() && player2->isAlive()) {


            PLayerTurn(player1Turn, isSave);
            player1->setMana(mana);
            if(isRunning) {
                bool playerAttacks, attackCard, endTurn = false, throwCard;
                while (!endTurn) {
                    std::pair<std::shared_ptr<CCard>, unsigned int> target, attacker;
                    std::dynamic_pointer_cast<CComputer>(player2)->DoSomething(cardsOnTableP1, cardsOnTableP2,
                                                                               playerAttacks,
                                                                               attackCard, endTurn, throwCard, target,
                                                                               attacker);
                    if (throwCard) {
                        bool cardFound, enoughMana, isSpell = false;
                        if (target.first != nullptr) {
                            player2->ThrowCard(cardsOnTableP2, cardFound, enoughMana, isSpell,
                                               target.first->getCardId());
                            if (isSpell) {
                                target.first->AttackPlayer(player1);
                                player2->GetHit(std::dynamic_pointer_cast<CSpell>(target.first)->getSelfHarm());
                                player2->DeleteCardFromHand(target.first);
                            }
                        } else
                            endTurn = true;

                    }
                        //player attacks
                    else if (playerAttacks) {
                        player2->AttackOtherPLayer(player1);
                        if (player2->HaveWeapon()) player2->getPlayersWeapon()->setReadyToAttack(false);
                    }
                        //card attacks
                    else if (!endTurn) {
                        if (attackCard) {
                            attacker.first->AttackCard(target.first);
                            attacker.first->setReadyToAttack(false);
                        }
                            //card attacks player
                        else {
                            attacker.first->AttackPlayer(player1);
                            attacker.first->setReadyToAttack(false);
                        }
                    }

                }
                player2->setMana(mana);
                //players take cards from deck
                player1->TakeNCardsFromDeck(1);
                player2->TakeNCardsFromDeck(1);
                mana++;
                SetCardsReady();
            }
        }
        if (!isRunning && isSave) {
            std::cout << "GAME SAVED" << std::endl;
        } else if (!player1->isAlive() && player2->isAlive())
            std::cout << player2->getPlayerName() << " WINS" << std::endl;
        else if (player1->isAlive() && !player2->isAlive())
            std::cout << player1->getPlayerName() << " WINS" << std::endl;
        else
            std::cout << "IT'S A DRAW" << std::endl;

    }
}


void CGame::PrintTable() const {
    std::cout << std::setw(12) << "TYPE" << std::setw(18) << "ID" << std::setw(15) << "CARD NAME" << std::setw(20)
              << "MANA REQUIRED" << std::setw(15) << "ATTACK POWER"
              << std::setw(15) << "HEALTH IMP." << std::endl;
    std::cout << std::endl;
}

void CGame::PrintCardsOnTable() const {

    if (cardsOnTableP1.empty() && cardsOnTableP2.empty()) {
        std::cout << "  TABLE IS EMPTY" << std::endl;
    } else {
        PrintTable();
        if (!cardsOnTableP1.empty()) {
            std::cout << "  " << player1->getPlayerName() << "'s CARDS: " << std::endl;
            for (const auto &currCard : cardsOnTableP1) {
                currCard->Print();
                if (currCard->isReadyToAttack()) std::cout << std::setw(15) << "ready";
                else std::cout << std::setw(15) << "Zzz..";
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        if (!cardsOnTableP2.empty()) {
            std::cout << "  " << player2->getPlayerName() << "'s CARDS: " << std::endl;
            for (const auto &currCard : cardsOnTableP2) {
                currCard->Print();
                if (currCard->isReadyToAttack()) std::cout << std::setw(15) << "ready";
                else std::cout << std::setw(15) << "Zzz..";
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
    std::cout << "\n========================================================" << std::endl;
}

CGame &CGame::HandleEvents(bool thrownByPLayer1, bool &isEnd, bool &isSave) {
    std::string trigger;
    bool rightCommand = false;

    while (!rightCommand) {
        std::cout << "Your command (throw/attack/end/save/surrender): " << std::flush;
        std::cin >> trigger;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (trigger != "throw" && trigger != "attack" && trigger != "end" && trigger != "surrender" &&
            trigger != "save") {
            std::cout << "Bad input, try again" << std::endl;
            trigger.clear();
        } else {
            //player cannot attack without ready weapon (or without weapon) and without (ready) cards
            if (trigger == "attack" &&
                ((thrownByPLayer1 ? !player1->HaveWeapon() : !player2->HaveWeapon() ||
                                                             !((thrownByPLayer1 ? player1
                                                                                : player2)->getPlayersWeapon()->isReadyToAttack())) &&
                 ((thrownByPLayer1 ? cardsOnTableP1.empty() : cardsOnTableP2.empty()) ||
                  !IsThereAnyReadyCards(thrownByPLayer1)))) {
                std::cout << "You aren't armed and there's no cards on table ready to attack" << std::endl;
                trigger.clear();
            } else
                rightCommand = true;
        }

    }
    if (trigger == "save") {
        SaveGame();
        isRunning = false;
        isSave = true;
    } else if (trigger == "surrender") {
        (thrownByPLayer1 ? player1 : player2)->GetHit(30);
        isEnd = true;
        return *this;
    } else if (trigger == "throw") { //player throws a card
        std::string buffIdStr;
        bool cardFound = false;
        bool enoughMana = true;
        bool isSpell = false;
        do {
            unsigned int buffId = -1;
            std::cout << "Type id of card you've chosen: " << std::flush;
            std::cin >> buffIdStr;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (std::all_of(buffIdStr.begin(), buffIdStr.end(), ::isdigit)) {
                buffId = atoi(buffIdStr.c_str());
                buffIdStr.clear();
            }

            if (thrownByPLayer1) {
                player1->ThrowCard(cardsOnTableP1, cardFound, enoughMana, isSpell, buffId);
            } else {
                player2->ThrowCard(cardsOnTableP2, cardFound, enoughMana, isSpell, buffId);
            }
            //situation when player's thrown spell card
            if (isSpell) {
                std::string target;
                bool correctTarget = false;
                std::shared_ptr<CCard> spellCard;
                for (const auto &it : (thrownByPLayer1 ? player1->getCurrentHand() : player2->getCurrentHand()))
                    if (it->getCardId() == buffId) {
                        spellCard = it;
                        cardFound = true;
                        break;
                    }

                do {
                    correctTarget = DefineTarget(target);
                    if (target == "card" && (thrownByPLayer1 ? cardsOnTableP2.empty() : cardsOnTableP1.empty())) {
                        std::cout << "Opponent doesn't have any cards on the table" << std::endl;
                        target.clear();
                        continue;
                    }
                } while (!correctTarget);
                //spell applied to card
                if (target == "card") {
                    do {
                        buffId = -1;
                        std::cout << "Type id of card you're attacking: " << std::flush;
                        std::cin >> buffIdStr;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (std::all_of(buffIdStr.begin(), buffIdStr.end(), ::isdigit)) {
                            buffId = atoi(buffIdStr.c_str());
                            buffIdStr.clear();
                        }
                        //card found
                        std::shared_ptr<CCard> attackedCard;
                        correctTarget = FindCardOnTable(attackedCard, buffId, !thrownByPLayer1);

                        if (!correctTarget) {
                            std::cout << "Card's not found, try again" << std::endl;
                        } else {
                            spellCard->AttackCard(attackedCard);
                            (thrownByPLayer1 ? player1 : player2)->GetHit(
                                    std::dynamic_pointer_cast<CSpell>(spellCard)->getSelfHarm());
                            (thrownByPLayer1 ? player1 : player2)->DeleteCardFromHand(spellCard);
                        }

                    } while (!correctTarget);
                } else if (target == "player") { // spell applied to player

                    spellCard->AttackPlayer(thrownByPLayer1 ? player2 : player1);
                    (thrownByPLayer1 ? player1 : player2)->GetHit(
                            std::dynamic_pointer_cast<CSpell>(spellCard)->getSelfHarm());
                    (thrownByPLayer1 ? player1 : player2)->DeleteCardFromHand(spellCard);
                }

            }

            if (!cardFound) std::cout << " Card's not found, try again" << std::endl;
            if (!enoughMana) std::cout << " You do not have enough mana, try again" << std::endl;
            sleep(1);
        } while (!cardFound && !enoughMana);
    }
        //if player attacks
    else if (trigger == "attack") {

        std::string attacker, target;
        bool correctAttack = false;
        do {
            if (!DefineAttacker(attacker, thrownByPLayer1))
                continue;
            bool correctTarget;
            //if player attacks
            if (attacker == "player") {
                //check if player has a weapon
                if (thrownByPLayer1 ? !player1->HaveWeapon() : !player2->HaveWeapon()) {
                    std::cout << "You don't have a weapon" << std::endl;
                    attacker.clear();
                    break;
                }
                    //if player has a weapon
                else {
                    correctTarget = DefineTarget(target);
                    //player attacks player
                    if (target == "player") {
                        (thrownByPLayer1 ? player1 : player2)->AttackOtherPLayer(thrownByPLayer1 ? player2 : player1);
                        correctAttack = true;
                    }
                        //player attacks card
                    else if (target == "card") {
                        unsigned int buffId = -1;
                        std::string buffIdStr;
                        do {
                            std::cout << "Type id of card you're attacking: " << std::flush;
                            std::cin >> buffIdStr;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                            if (std::all_of(buffIdStr.begin(), buffIdStr.end(), ::isdigit)) {
                                buffId = atoi(buffIdStr.c_str());
                                buffIdStr.clear();
                            }
                            //card found

                            std::shared_ptr<CCard> attackedCard;
                            correctTarget = FindCardOnTable(attackedCard, buffId, !thrownByPLayer1);
                            if (!correctTarget) {
                                std::cout << "Card's not found, try again" << std::endl;
                            } else {
                                (thrownByPLayer1 ? player1 : player2)->AttackCard(attackedCard);
                                correctAttack = true;
                            }
                        } while (!correctTarget);
                    }
                }
            }

                //if attacker is card
            else if (attacker == "card") {
                std::shared_ptr<CCard> attackerCard;
                unsigned int buffId = -1;
                std::string buffIdStr;
                bool correctAttacker = false;
                do {
                    std::cout << "Type id of card you're attacking with: " << std::flush;
                    std::cin >> buffIdStr;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (std::all_of(buffIdStr.begin(), buffIdStr.end(), ::isdigit)) {
                        buffId = atoi(buffIdStr.c_str());
                        buffIdStr.clear();
                    }

                    correctAttacker = FindCardOnTable(attackerCard, buffId, thrownByPLayer1);
                    if (!correctAttacker) {
                        std::cout << "Card was not found or not ready to attack yet" << std::endl;
                    }
                } while (!correctAttacker);

                do {
                    correctTarget = DefineTarget(target);
                    if (target == "card" &&
                        (thrownByPLayer1 ? cardsOnTableP2.empty() : cardsOnTableP1.empty())) {
                        correctTarget = false;
                        std::cout << "Opponent doesn't have any cards on table. You can only attack opponent"
                                  << std::endl;

                    }
                } while (!correctTarget);
                //card attacks player
                if (target == "player") {
                    attackerCard->AttackPlayer((thrownByPLayer1 ? player2 : player1));
                    correctAttack = true;
                }
                    //card attacks card
                else if (target == "card") {
                    correctTarget = false;
                    unsigned int buffId;
                    do {
                        buffId = -1;
                        std::cout << "Type id of card you're attacking: " << std::flush;
                        std::cin >> buffIdStr;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (std::all_of(buffIdStr.begin(), buffIdStr.end(), ::isdigit)) {
                            buffId = atoi(buffIdStr.c_str());
                            buffIdStr.clear();
                        }

                        //card found
                        std::shared_ptr<CCard> attackedCard;
                        correctTarget = FindCardOnTable(attackedCard, buffId, !thrownByPLayer1);

                        if (!correctTarget) {
                            std::cout << "Card's not found, try again" << std::endl;
                        } else {
                            attackerCard->AttackCard(attackedCard);
                            correctAttack = true;
                        }

                    } while (!correctTarget);
                }
            }
        } while (!correctAttack);
    } else if (trigger == "end") {
        isEnd = true;
        std::cout << "End of turn" << std::endl;
        sleep(1);
    }
    return *this;
}

bool CGame::FindCardOnTable(std::shared_ptr<CCard> &currentCard, unsigned int buffId, bool deckOfPlayer1) const {
    for (auto &card : (deckOfPlayer1 ? cardsOnTableP1 : cardsOnTableP2))
        if (card->getCardId() == buffId) {
            //correctTarget = true;
            currentCard = card;
            return true;
        }
    return false;
}

bool CGame::DefineTarget(std::string &target) {

    std::cout << "Your target is (card/player): " << std::flush;
    std::cin >> target;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (target != "card" && target != "player") {
        std::cout << "Wrong target, try again" << std::endl;
        target.clear();
        return false;
    } else
        return true;

}

bool CGame::DefineAttacker(std::string &attacker, bool thrownByPLayer1) {
    std::cout << std::endl;
    std::cout << "Your attacker is (card/player): " << std::flush;
    std::cin >> attacker;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (attacker != "card" && attacker != "player") {
        std::cout << "Wrong attacker, try again" << std::endl;
        attacker.clear();
        return false;
    }
    if (attacker == "card" && ((thrownByPLayer1 ? cardsOnTableP1 : cardsOnTableP2).empty() ||
                               !IsThereAnyReadyCards(thrownByPLayer1))) {
        std::cout << "You don't have any cards on the table ready to attack" << std::endl;
        attacker.clear();
        return false;
    }
    if (attacker == "player" && !(thrownByPLayer1 ? player1 : player2)->getPlayersWeapon()->isReadyToAttack()) {
        std::cout << "You cannot attack with your weapon at the moment" << std::endl;
        attacker.clear();
        return false;
    }
    return true;
}

CGame &CGame::UpdateCardsOnTable() {

    cardsOnTableP1.erase(std::remove_if(cardsOnTableP1.begin(), cardsOnTableP1.end(), [](std::shared_ptr<CCard> &card) {
        return std::dynamic_pointer_cast<CCreature>(card)->getHealthLevel() == 0;
    }), cardsOnTableP1.end());

    cardsOnTableP2.erase(std::remove_if(cardsOnTableP2.begin(), cardsOnTableP2.end(), [](std::shared_ptr<CCard> &card) {
        return std::dynamic_pointer_cast<CCreature>(card)->getHealthLevel() == 0;
    }), cardsOnTableP2.end());

    return *this;

}

CGame &CGame::SetCardsReady() {
    for (auto &player1Card : cardsOnTableP1)
        player1Card->setReadyToAttack(true);
    if (player1->HaveWeapon())
        player1->getPlayersWeapon()->setReadyToAttack(true);

    for (auto &player2Card : cardsOnTableP2)
        player2Card->setReadyToAttack(true);
    if (player2->HaveWeapon())
        player2->getPlayersWeapon()->setReadyToAttack(true);

    return *this;
}

bool CGame::IsThereAnyReadyCards(bool thrownByPlayer1) {
    for (const auto &cardOnTable : (thrownByPlayer1 ? cardsOnTableP1 : cardsOnTableP2))
        if (cardOnTable->isReadyToAttack())
            return true;
    return false;
}

void CGame::SaveGame() {
    std::ofstream output_file("save.txt");
    //std::ifstream input_file("Decks.txt");

    if (!output_file.good()) {
        std::cout << "Cannot save at the moment" << std::endl;
        output_file.close();
        return;
    }


    //copy current Decks.txt file

    output_file << std::boolalpha << std::endl << isPvP << std::endl;

    output_file << "\nCARDS_ON_TABLE_P1\n";
    for (const auto &cardOnTable : cardsOnTableP1) {
        output_file << cardOnTable->getCardId() << " "
                    << std::dynamic_pointer_cast<CCreature>(cardOnTable)->getHealthLevel() << std::endl;
    }
    output_file << "END_CARDS_ON_TABLE_P1\n\n";
    output_file << "CARDS_ON_TABLE_P2\n";
    for (const auto &cardOnTable : cardsOnTableP2) {
        output_file << cardOnTable->getCardId() << " "
                    << std::dynamic_pointer_cast<CCreature>(cardOnTable)->getHealthLevel() << std::endl;
    }
    output_file << "END_CARDS_ON_TABLE_P2\n\n";

    output_file << "PLAYER_1\n";
    output_file << player1->getPlayerName() << "\n" << std::dynamic_pointer_cast<CHuman>(player1)->getPlayerPassword()
                << std::endl;
    output_file << mana << " " << player1->getHealthPoints() << std::endl;
    output_file << std::boolalpha << player1->HaveWeapon() << std::endl;
    if (player1->HaveWeapon())
        output_file << player1->getPlayersWeapon()->getCardId() << std::endl;
    output_file << "PLAYER_1_END\n\n";

    output_file << "PLAYER_2\n";
    output_file << player2->getPlayerName() << "\n"
                << (isPvP ? std::dynamic_pointer_cast<CHuman>(player2)->getPlayerPassword() : "") << std::endl;
    output_file << mana << " " << player2->getHealthPoints() << std::endl;
    output_file << std::boolalpha << player2->HaveWeapon() << std::endl;
    if (player2->HaveWeapon())
        output_file << player2->getPlayersWeapon()->getCardId() << std::endl;
    output_file << "PLAYER_2_END\n\n";


    output_file << "PLAYER_1_HAND\n" << std::endl;
    for (const auto &cardOnTable : player1->getCurrentHand())
        output_file << cardOnTable->getCardId() << std::endl;
    output_file << "END_PLAYER_1_HAND\n\n" << std::endl;

    output_file << "PLAYER_2_HAND\n" << std::endl;
    for (const auto &cardOnTable : player2->getCurrentHand())
        output_file << cardOnTable->getCardId() << std::endl;
    output_file << "END_PLAYER_2_HAND\n\n" << std::endl;

    output_file << "PLAYER_1_DECK\n" << std::endl;
    for (const auto &cardOnTable : player1->getPlayersDeck()->getDeck())
        output_file << cardOnTable->getCardId() << std::endl;
    output_file << "END_PLAYER_1_DECK\n\n" << std::endl;

    output_file << "PLAYER_2_DECK\n" << std::endl;
    for (const auto &cardOnTable : player2->getPlayersDeck()->getDeck())
        output_file << cardOnTable->getCardId() << std::endl;
    output_file << "END_PLAYER_2_DECK\n\n" << std::endl;

    output_file << "END_SAVE" << std::endl;
}

CGame &CGame::UploadGame() {
    std::ifstream input_file("save.txt");
    if (!input_file.good()) {
        input_file.close();
        std::cout << "Cannot open the file save.txt" << std::endl;
        isLoaded = false;
        return *this;
    }

    ReadDecks();

    std::string trigger, trash;

    input_file >> trigger;

    isPvP = trigger == "true";
    trigger.clear();

    input_file >> trash;
    while (input_file >> trigger && trigger != "END_CARDS_ON_TABLE_P1") {
        unsigned int id, hp;
        if (std::all_of(trigger.begin(), trigger.end(), ::isdigit)) {
            id = atoi(trigger.c_str());
            trigger.clear();
        }
        input_file >> hp;
        auto tempCardIt = std::find_if(playingDecks.begin()->getDeck().begin(), playingDecks.begin()->getDeck().end(),
                                       [id](const std::shared_ptr<CCard> &cardInDeck) {
                                           return cardInDeck->getCardId() == id;
                                       });
        std::dynamic_pointer_cast<CCreature>(*tempCardIt)->setHealthLevel(hp);
        cardsOnTableP1.push_back(*tempCardIt);
        trigger.clear();
    }
    trigger.clear();
    input_file >> trash;
    while (input_file >> trigger && trigger != "END_CARDS_ON_TABLE_P2") {
        unsigned int id, hp;
        if (std::all_of(trigger.begin(), trigger.end(), ::isdigit)) {
            id = atoi(trigger.c_str());
            trigger.clear();
        }
        input_file >> hp;
        auto tempCardIt = std::find_if(playingDecks.back().getDeck().begin(), playingDecks.back().getDeck().end(),
                                       [id](const std::shared_ptr<CCard> &cardInDeck) {
                                           return cardInDeck->getCardId() == id;
                                       });
        std::dynamic_pointer_cast<CCreature>(*tempCardIt)->setHealthLevel(hp);
        cardsOnTableP2.push_back(*tempCardIt);
        trigger.clear();
    }

    input_file >> trash;
    std::string name, password, weapon;
    unsigned int manaTemp, hp, id;

    input_file >> name;
    input_file >> password;
    input_file >> manaTemp;
    input_file >> hp;
    input_file >> weapon;
    player1 = std::make_shared<CHuman>(CHuman(name, password));
    player1->setMana(manaTemp);
    this->mana = manaTemp;
    player1->setHealthPoints(hp);
    player1->setHaveWeapon(weapon == "true");
    weapon.clear();
    if (player1->HaveWeapon()) {
        input_file >> id;
        auto tempCardIt = std::find_if(playingDecks.begin()->getDeck().begin(), playingDecks.begin()->getDeck().end(),
                                       [id](const std::shared_ptr<CCard> &cardInDeck) {
                                           return cardInDeck->getCardId() == id;
                                       });
        player1->setPlayersWeapon(*tempCardIt);
    }

    name.clear();
    password.clear();
    weapon.clear();

    input_file >> trash;
    input_file >> trash;

    input_file >> name;
    if (isPvP) input_file >> password;
    input_file >> manaTemp;
    input_file >> hp;
    input_file >> weapon;
    if (isPvP) player2 = std::make_shared<CHuman>(CHuman(name, password));
    else player2 = std::make_shared<CComputer>(CComputer(name));
    player2->setMana(manaTemp);
    player2->setHealthPoints(hp);
    player2->setHaveWeapon(weapon == "true");
    weapon.clear();
    if (player2->HaveWeapon()) {
        input_file >> id;
        auto tempCardIt = std::find_if(playingDecks.back().getDeck().begin(), playingDecks.back().getDeck().end(),
                                       [id](const std::shared_ptr<CCard> &cardInDeck) {
                                           return cardInDeck->getCardId() == id;
                                       });
        player2->setPlayersWeapon(*tempCardIt);
    }

    input_file >> trash;
    trigger.clear();


    std::list<std::shared_ptr<CCard>> tempHand;
    input_file >> trash;
    while (input_file >> trigger && trigger != "END_PLAYER_1_HAND") {
        if (std::all_of(trigger.begin(), trigger.end(), ::isdigit)) {
            id = atoi(trigger.c_str());
            trigger.clear();
        }
        auto tempCardIt = std::find_if(playingDecks.begin()->getDeck().begin(), playingDecks.begin()->getDeck().end(),
                                       [id](const std::shared_ptr<CCard> &cardInDeck) {
                                           return cardInDeck->getCardId() == id;
                                       });
        tempHand.push_back(*tempCardIt);
        trigger.clear();
    }
    player1->setCurrentHand(tempHand);
    tempHand.clear();

    input_file >> trash;
    trigger.clear();

    while (input_file >> trigger && trigger != "END_PLAYER_2_HAND") {
        if (std::all_of(trigger.begin(), trigger.end(), ::isdigit)) {
            id = atoi(trigger.c_str());
            trigger.clear();
        }
        auto tempCardIt = std::find_if(playingDecks.back().getDeck().begin(), playingDecks.back().getDeck().end(),
                                       [id](const std::shared_ptr<CCard> &cardInDeck) {
                                           return cardInDeck->getCardId() == id;
                                       });
        tempHand.push_back(*tempCardIt);
        trigger.clear();
    }
    player2->setCurrentHand(tempHand);

    input_file >> trash;
    trigger.clear();

    std::list<std::shared_ptr<CCard>> tempDeckP1, tempDeckP2;
    std::shared_ptr<CDeck> Deck1, Deck2;
    Deck1 = std::make_shared<CDeck>(CDeck());
    Deck2 = std::make_shared<CDeck>(CDeck());
    while (input_file >> trigger && trigger != "END_PLAYER_1_DECK") {
        if (std::all_of(trigger.begin(), trigger.end(), ::isdigit)) {
            id = atoi(trigger.c_str());
            trigger.clear();
        }
        auto tempCardIt = std::find_if(playingDecks.begin()->getDeck().begin(), playingDecks.begin()->getDeck().end(),
                                       [id](const std::shared_ptr<CCard> &cardInDeck) {
                                           return cardInDeck->getCardId() == id;
                                       });
        tempDeckP1.push_back(*tempCardIt);
        trigger.clear();
    }
    Deck1->setDeck(tempDeckP1);
    player1->TakeDeck(Deck1);
    input_file >> trash;
    trigger.clear();
    while (input_file >> trigger && trigger != "END_PLAYER_2_DECK") {
        if (std::all_of(trigger.begin(), trigger.end(), ::isdigit)) {
            id = atoi(trigger.c_str());
            trigger.clear();
        }
        auto tempCardIt = std::find_if(playingDecks.back().getDeck().begin(), playingDecks.back().getDeck().end(),
                                       [id](const std::shared_ptr<CCard> &cardInDeck) {
                                           return cardInDeck->getCardId() == id;
                                       });
        tempDeckP2.push_back(*tempCardIt);
        trigger.clear();
    }
    Deck2->setDeck(tempDeckP2);
    player2->TakeDeck(Deck2);
    input_file.close();
    isRunning = true;
    isLoaded = true;
    return *this;
}
