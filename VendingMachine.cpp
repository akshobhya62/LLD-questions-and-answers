#include <bits/stdc++.h>
using namespace std;

// Forward declaration
class VendingMachine;

class Product {
public:
    string productName;
    int price;
    Product(string productName, int price);
};

class Inventory {
public:
    unordered_map<Product*, int> count;
    void addProduct(Product* product);
    void removeProduct(Product* product);
    bool isAvailable(Product* product);
};

class VendingMachineState {
public:
    virtual void selectProduct(Product* product) = 0;
    virtual void insertCash(int money) = 0;
    virtual void dispenseProduct() = 0;
    virtual void returnChange() = 0;
};

class IdleState : public VendingMachineState {
public:
    VendingMachine* machine;
    IdleState(VendingMachine* machine);
    void selectProduct(Product* product) override;
    void insertCash(int money) override;
    void dispenseProduct() override;
    void returnChange() override;
};

class ReadyState : public VendingMachineState {
public:
    VendingMachine* machine;
    ReadyState(VendingMachine* machine);
    void selectProduct(Product* product) override;
    void insertCash(int money) override;
    void dispenseProduct() override;
    void returnChange() override;
};

class DispenseState : public VendingMachineState {
public:
    VendingMachine* machine;
    DispenseState(VendingMachine* machine);
    void selectProduct(Product* product) override;
    void insertCash(int money) override;
    void dispenseProduct() override;
    void returnChange() override;
};

class ReturnState : public VendingMachineState {
public:
    VendingMachine* machine;
    ReturnState(VendingMachine* machine);
    void selectProduct(Product* product) override;
    void insertCash(int money) override;
    void dispenseProduct() override;
    void returnChange() override;
};

class VendingMachine {
public:
    VendingMachineState* idleState;
    VendingMachineState* readyState;
    VendingMachineState* dispenseState;
    VendingMachineState* returnState;
    VendingMachineState* curState;
    Inventory* inventory;
    Product* selectedProduct;
    int totalPayment;

    VendingMachine();
    void addProduct(Product* product, int cnt);
    void selectProduct(Product* product);
    void insertCash(int money);
    void dispenseProduct();
    void returnChange();
    void setState(VendingMachineState* state);
    VendingMachineState* getIdleState();
    VendingMachineState* getReadyState();
    VendingMachineState* getDispenseState();
    VendingMachineState* getReturnState();
};

// Definitions

Product::Product(string productName, int price) : productName(productName), price(price) {}

void Inventory::addProduct(Product* product) {
    count[product]++;
}

void Inventory::removeProduct(Product* product) {
    count[product]--;
}

bool Inventory::isAvailable(Product* product) {
    return count[product] > 0;
}

IdleState::IdleState(VendingMachine* machine) : machine(machine) {}

void IdleState::selectProduct(Product* product) {
    if (!machine->inventory->isAvailable(product)) {
        cout << "Sorry, this product is not available\n";
        return;
    }
    cout << "You have selected this product : " << product->productName << endl;
    machine->selectedProduct = product;
    machine->setState(machine->getReadyState());
}

void IdleState::insertCash(int money) {
    cout << "Please select a product first\n";
}

void IdleState::dispenseProduct() {
    cout << "Please select a product first\n";
}

void IdleState::returnChange() {
    cout << "Please select a product first\n";
}

ReadyState::ReadyState(VendingMachine* machine) : machine(machine) {}

void ReadyState::selectProduct(Product* product) {
    cout << "Please make a payment first\n";
}

void ReadyState::insertCash(int money) {
    if (money < machine->selectedProduct->price) {
        cout << "Insufficient payment\n";
        return;
    }
    machine->totalPayment = money;
    machine->setState(machine->getDispenseState());
}

void ReadyState::dispenseProduct() {
    cout << "Please make a payment first\n";
}

void ReadyState::returnChange() {
    cout << "Please make a payment first\n";
}

DispenseState::DispenseState(VendingMachine* machine) : machine(machine) {}

void DispenseState::selectProduct(Product* product) {
    cout << "Dispensing product, please wait\n";
}

void DispenseState::insertCash(int money) {
    cout << "Dispensing product, please wait\n";
}

void DispenseState::dispenseProduct() {
    machine->inventory->count[machine->selectedProduct]--;
    cout << "Product dispensed\n";
    machine->setState(machine->getReturnState());
}

void DispenseState::returnChange() {
    cout << "Dispensing product, please wait\n";
}

ReturnState::ReturnState(VendingMachine* machine) : machine(machine) {}

void ReturnState::selectProduct(Product* product) {
    cout << "Returning change, please wait\n";
}

void ReturnState::insertCash(int money) {
    cout << "Returning change, please wait\n";
}

void ReturnState::dispenseProduct() {
    cout << "Returning change, please wait\n";
}

void ReturnState::returnChange() {
    if (machine->totalPayment == machine->selectedProduct->price) {
        cout << "No change to return\n";
    } else {
        cout << "Returning change : " << machine->totalPayment - machine->selectedProduct->price << endl;
    }
    machine->totalPayment = 0;
    machine->selectedProduct = NULL;
    machine->setState(machine->getIdleState());
}

VendingMachine::VendingMachine() {
    inventory = new Inventory();
    idleState = new IdleState(this);
    readyState = new ReadyState(this);
    dispenseState = new DispenseState(this);
    returnState = new ReturnState(this);
    curState = idleState;
}

void VendingMachine::addProduct(Product* product, int cnt) {
    inventory->count[product] += cnt;
}

void VendingMachine::selectProduct(Product* product) {
    curState->selectProduct(product);
}

void VendingMachine::insertCash(int money) {
    curState->insertCash(money);
}

void VendingMachine::dispenseProduct() {
    curState->dispenseProduct();
}

void VendingMachine::returnChange() {
    curState->returnChange();
}

void VendingMachine::setState(VendingMachineState* state) {
    curState = state;
}

VendingMachineState* VendingMachine::getIdleState() {
    return idleState;
}

VendingMachineState* VendingMachine::getReadyState() {
    return readyState;
}

VendingMachineState* VendingMachine::getDispenseState() {
    return dispenseState;
}

VendingMachineState* VendingMachine::getReturnState() {
    return returnState;
}

int main() {
    VendingMachine* m = new VendingMachine();
    Product* apple = new Product("apple", 10);
    Product* orange = new Product("orange", 5);
    m->addProduct(apple, 1);
    m->addProduct(orange, 3);
    m->selectProduct(apple);
    m->insertCash(20);
    m->dispenseProduct();
    m->returnChange();
}

//THE FOLLOWING CODE DOESN'T WORK BECAUSE BOTH VENDINGMACHINE CLASS AND OTHER STATE CLASSES DEPEND ON
//EACH OTHER THEREFORE COMPILER MUST KNOW OTHER BEFORE COMPILING ONE BUT THE OTHER CAN ONLY BE COMPILED
//WHEN ONE IS FINISHED COMPILING. TO BREAK THIS CYCLE WE USE FIRST DECLARATION AND THE DEFINITON
// #include <bits/stdc++.h>
// using namespace std;

// class VendingMachine; // Forward declaration
// class IdleState;
// class ReadyState;
// class DispenseState;
// class ReturnState;

// class Product {
// public:
//     string productName;
//     int price;
//     Product(string productName, int price) {
//         this->productName = productName;
//         this->price = price;
//     }
// };

// class Inventory {
// public:
//     unordered_map<Product*, int> count;
//     void addProduct(Product* product) {
//         count[product]++;
//     }
//     void removeProduct(Product* product) {
//         count[product]--;
//     }
//     bool isAvailable(Product* product) {
//         return count[product] > 0;
//     }
// };

// class VendingMachineState {
// public:
//     virtual void selectProduct(Product* product) = 0;
//     virtual void insertCash(int money) = 0;
//     virtual void dispenseProduct() = 0;
//     virtual void returnChange() = 0;
// };

// class VendingMachine {
// public:
//     VendingMachineState* idleState;
//     VendingMachineState* readyState;
//     VendingMachineState* dispenseState;
//     VendingMachineState* returnState;
//     VendingMachineState* curState;
//     Inventory* inventory;
//     Product* selectedProduct;
//     int totalPayment;

//     VendingMachine() {
//         inventory = new Inventory();
//         idleState = new IdleState(this);
//         readyState = new ReadyState(this);
//         dispenseState = new DispenseState(this);
//         returnState = new ReturnState(this);
//         curState = idleState;
//     }
//     void addProduct(Product* product, int cnt) {
//         inventory->count[product] += cnt;
//     }
//     void selectProduct(Product* product) {
//         curState->selectProduct(product);
//     }
//     void insertCash(int money) {
//         curState->insertCash(money);
//     }
//     void dispenseProduct() {
//         curState->dispenseProduct();
//     }
//     void returnChange() {
//         curState->returnChange();
//     }
//     void setState(VendingMachineState* state) {
//         curState = state;
//     }
//     VendingMachineState* getIdleState() {
//         return idleState;
//     }
//     VendingMachineState* getReadyState() {
//         return readyState;
//     }
//     VendingMachineState* getDispenseState() {
//         return dispenseState;
//     }
//     VendingMachineState* getReturnState() {
//         return returnState;
//     }
// };

// class IdleState : public VendingMachineState {
// public:
//     VendingMachine* machine;
//     IdleState(VendingMachine* machine) {
//         this->machine = machine;
//     }
//     void selectProduct(Product* product) {
//         if (!machine->inventory->isAvailable(product)) {
//             cout << "Sorry, this product is not available\n";
//             return;
//         }
//         cout << "You have selected this product : " << product->productName << endl;
//         machine->selectedProduct = product;
//         machine->setState(machine->getReadyState());
//     }
//     void insertCash(int money) {
//         cout << "Please select a product first\n";
//     }
//     void dispenseProduct() {
//         cout << "Please select a product first\n";
//     }
//     void returnChange() {
//         cout << "Please select a product first\n";
//     }
// };

// class ReadyState : public VendingMachineState {
// public:
//     VendingMachine* machine;
//     ReadyState(VendingMachine* machine) {
//         this->machine = machine;
//     }
//     void selectProduct(Product* product) {
//         cout << "Please make a payment first\n";
//     }
//     void insertCash(int money) {
//         if (money < machine->selectedProduct->price) {
//             cout << "Insufficient payment\n";
//             return;
//         }
//         machine->totalPayment = money;
//         machine->setState(machine->getDispenseState());
//     }
//     void dispenseProduct() {
//         cout << "Please make a payment first\n";
//     }
//     void returnChange() {
//         cout << "Please make a payment first\n";
//     }
// };

// class DispenseState : public VendingMachineState {
// public:
//     VendingMachine* machine;
//     DispenseState(VendingMachine* machine) {
//         this->machine = machine;
//     }
//     void selectProduct(Product* product) {
//         cout << "Dispensing product, please wait\n";
//     }
//     void insertCash(int money) {
//         cout << "Dispensing product, please wait\n";
//     }
//     void dispenseProduct() {
//         machine->inventory->count[machine->selectedProduct]--;
//         cout << "Product dispensed\n";
//         machine->setState(machine->getReturnState());
//     }
//     void returnChange() {
//         cout << "Dispensing product, please wait\n";
//     }
// };

// class ReturnState : public VendingMachineState {
// public:
//     VendingMachine* machine;
//     ReturnState(VendingMachine* machine) {
//         this->machine = machine;
//     }
//     void selectProduct(Product* product) {
//         cout << "Returning change, please wait\n";
//     }
//     void insertCash(int money) {
//         cout << "Returning change, please wait\n";
//     }
//     void dispenseProduct() {
//         cout << "Returning change, please wait\n";
//     }
//     void returnChange() {
//         if (machine->totalPayment == machine->selectedProduct->price) {
//             cout << "No change to return\n";
//         } else {
//             cout << "Returning change : " << machine->totalPayment - machine->selectedProduct->price << endl;
//         }
//         machine->totalPayment = 0;
//         machine->selectedProduct = NULL;
//         machine->setState(machine->getIdleState());
//     }
// };

// int main() {
//     VendingMachine* m = new VendingMachine();
//     Product* apple = new Product("apple", 10);
//     Product* orange = new Product("orange", 5);
//     m->addProduct(apple, 1);
//     m->addProduct(orange, 3);
//     m->selectProduct(apple);
//     m->insertCash(20);
//     m->dispenseProduct();
//     m->returnChange();
// }
