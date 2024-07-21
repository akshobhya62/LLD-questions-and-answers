#include <bits/stdc++.h>
using namespace std;

class atmmachine;
class Nocard;
class Nopin;
class Getcash;

class Bank {
public:
    unordered_map<string, int> userPin;
    unordered_map<string, int> moneyAvailable;

    void addUser(string user, int pin);
    bool validPin(string user, int pin);
    int getPin(string user);
    int getBalance(string user);
    void setBalance(string user, int money);
    void addBalance(string user, int money);
    void reduceBalance(string user, int money);
};

class atmstate {
public:
    atmmachine* obj;
    virtual void insertCard() = 0;
    virtual void insertPin(int pin) = 0;
    virtual void getCash(int money) = 0;
};

class Nocard : public atmstate {
public:
    void insertCard() override;
    void insertPin(int pin) override;
    void getCash(int money) override;
};

class Nopin : public atmstate {
public:
    void insertCard() override;
    void insertPin(int pin) override;
    void getCash(int money) override;
};

class Getcash : public atmstate {
public:
    void insertCard() override;
    void insertPin(int pin) override;
    void getCash(int money) override;
};

class atmmachine {
public:
    atmstate* nocard;
    atmstate* nopin;
    atmstate* getcash;
    atmstate* curstate;
    Bank* bank;
    string curUser;

    atmmachine();
    atmstate* getState();
    void setState(atmstate* thisstate);
    void insertCard();
    void insertPin(int pin);
    void getCash(int money);
    atmstate* getnocardstate();
    atmstate* getnopinstate();
    atmstate* getgetcashstate();
};



// Definitions for atmmachine class
atmmachine::atmmachine() {
    this->nocard = new Nocard();
    this->nopin = new Nopin();
    this->getcash = new Getcash();
    this->curstate = nocard;
    this->curUser = "";
}

atmstate* atmmachine::getState() {
    return curstate;
}

void atmmachine::setState(atmstate* thisstate) {
    this->curstate = thisstate;
}

void atmmachine::insertCard() {
    curstate->insertCard();
}

void atmmachine::insertPin(int pin) {
    curstate->insertPin(pin);
}

void atmmachine::getCash(int money) {
    curstate->getCash(money);
}

atmstate* atmmachine::getnocardstate() {
    return nocard;
}

atmstate* atmmachine::getnopinstate() {
    return nopin;
}

atmstate* atmmachine::getgetcashstate() {
    return getcash;
}




// // Definitions for atmstate class
// void atmstate::insertCard() {
//     cout << "Please insert card\n";
//     obj->setState(obj->getnopinstate());
// }

// void atmstate::insertPin(int pin) {
//     cout << "First, please insert card\n";
// }

// void atmstate::getCash(int money) {
//     cout << "First, please insert card\n";
// }

// Definitions for Bank class
void Bank::addUser(string user, int pin) {
    userPin[user] = pin;
}

bool Bank::validPin(string user, int pin) {
    return userPin[user] == pin;
}

int Bank::getPin(string user) {
    return userPin[user];
}

int Bank::getBalance(string user) {
    return moneyAvailable[user];
}

void Bank::setBalance(string user, int money) {
    moneyAvailable[user] = money;
}

void Bank::addBalance(string user, int money) {
    moneyAvailable[user] += money;
}

void Bank::reduceBalance(string user, int money) {
    moneyAvailable[user] -= money;
}

// Definitions for Nocard class
void Nocard::insertCard() {
    cout << "Please insert card\n";
    obj->setState(obj->getnopinstate());
}

void Nocard::insertPin(int pin) {
    cout << "First, please insert card\n";
}

void Nocard::getCash(int money) {
    cout << "First, please insert card\n";
}

// Definitions for Nopin class
void Nopin::insertCard() {
    cout << "Card already inserted\n";
}

void Nopin::insertPin(int pin) {
    cout<<"camer here\n";
    string curUser = obj->curUser;
    cout<<"cur user is : "<<curUser<<endl;
    if (obj->bank->getPin(curUser) != pin) {
        cout << "Invalid Pin...\n";
        obj->setState(obj->getnocardstate());
    } else {
        cout << "Pin verified, proceed to enter money\n";
    }
}

void Nopin::getCash(int money) {
    cout << "First, please enter pin\n";
}

// Definitions for Getcash class
void Getcash::insertCard() {
    cout << "Card already inserted\n";
}

void Getcash::insertPin(int pin) {
    cout << "Pin already entered\n";
}

void Getcash::getCash(int money) {
    string curUser = obj->curUser;
    if (obj->bank->getBalance(curUser) < money) {
        cout << "Insufficient balance...\n";
    } else {
        obj->bank->reduceBalance(curUser, money);
        cout << "Ejecting " << money << ", now current Bal: " << obj->bank->getBalance(curUser) << endl;
    }
    obj->setState(obj->getnocardstate());
    obj->curUser = "";
}

int main() {
    Bank* bank = new Bank();
    bank->addUser("aman", 123);
    bank->setBalance("aman", 100);

    atmmachine* obj = new atmmachine();
    obj->curUser = "aman";
    obj->insertCard();
    cout<<"Returned successfully\n";
    obj->insertPin(245);

}
