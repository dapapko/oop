#include <iostream>
#include <exception>
#include <string>
using namespace std;


class SteamFaucetOpeningError : public exception {
public:
    const char * what () {
        return "Steam faucet opening error. Deg must be positive.";
    }
};

class ConsumerElectronics {
private:
    int price; // price (in russian roubles)
    double weight; // weight (in kg)
    double width; // width (in metres)
    double height; // height (in metres)
    double depth; // depth (in metres)
    int voltage; // preferable voltage

public:
    ConsumerElectronics(int price = 5000, double weight = 1.0, double width = 1.7, double height = 4.6, double depth = 0.46, int voltage = 220) {
        this->price = price;
        this->weight = weight;
        this->width = width;
        this->height = height;
        this->depth = depth;
        this->voltage = voltage;
        cout << "Calling default constructor for consumer electronics" << endl;
    }

    virtual ~ConsumerElectronics() {
        cout << "Calling virtual destructor of consumer electronics" << endl;
    }

    ConsumerElectronics(const ConsumerElectronics &instance) {
        this->price = instance.price;
        this->weight = instance.weight;
        this->width = instance.width;
        this->height = instance.height;
        this->depth = instance.depth;
        this->voltage = instance.voltage;
        cout << "Calling copying constructor for consumer electronics" << endl;
    }


};

class CoffeeMaker: public ConsumerElectronics {
private:
    bool canWorkWithCapsules;
    bool canWorkWithGroundCoffee;
    bool canMakeCappuccino;
    int pressure;
public:
    CoffeeMaker(bool canWorkWithCapsules, bool canWorkWithGroundCoffee, bool canMakeCappuccino,
            int pressure, int price, double weight, double width, double height, double depth, int voltage)
    : ConsumerElectronics(price, weight, width, height, depth, voltage) {
        this->pressure = pressure;
        this->canWorkWithCapsules = canWorkWithCapsules;
        this->canWorkWithGroundCoffee = canWorkWithGroundCoffee;
        this->canMakeCappuccino = canMakeCappuccino;
        cout << "Calling default constructor for coffee maker" << endl;
    }

    CoffeeMaker(const CoffeeMaker &instance): ConsumerElectronics(instance) {
        this->pressure = instance.pressure;
        this->canWorkWithCapsules = instance.canWorkWithCapsules;
        this->canMakeCappuccino = instance.canMakeCappuccino;
        cout << "Calling copying constructor for coffee maker" << endl;
    }
    ~CoffeeMaker() override {
        cout << "Calling virtual destructor of coffee maker" << endl;
    }
};





class CoffeeMachine: public CoffeeMaker {
private:
    class SteamFaucet {
    private:
        int deg;
    public:
        SteamFaucet() {
            this->deg = 0;
        }

        void setDeg(int deg){
            this->deg = deg;
        }

    };
    SteamFaucet faucet = CoffeeMachine::SteamFaucet();
    bool isStraitOpened;
    int temperature = 20;

    void warm(int temp) {
        while(this->temperature < temp) {
            this->temperature++;
            cout << "Warming. Current temperature: " << this->temperature << endl;
        };
    }

    void openStrait(){
        if(!this->isStraitOpened) this->isStraitOpened = true;
    }


public:

    void makeCoffee(){
        this->warm(100);
        this->openStrait();
    }

    void closeStrait() {
        if(this->isStraitOpened) this->isStraitOpened = false;
    }

    void openStreamFaucet(int deg){
        if (deg <= 0) throw SteamFaucetOpeningError();
        faucet.setDeg(deg);
    }

    void closeStreamFaucet(){
        faucet.setDeg(-1);
    }

    void prepareToMakeMilkFoam(int deg) {
        this->warm(130);
    }

    CoffeeMachine(bool canWorkWithCapsules = false, bool canWorkWithGroundCoffee = true, bool canMakeCappuccino = true,
                  int pressure = 15, int price = 5000, double weight = 52.0, double width = 23.5,
                  double height = 1.2, double depth = 1.3, int voltage = 230)
                  : CoffeeMaker(canWorkWithCapsules, canWorkWithGroundCoffee, canMakeCappuccino,
                          pressure, price, weight, width, height, depth, voltage)
    {
        this->isStraitOpened = false;
        cout << "Calling default constructor for coffee machine" << endl;
    }

    CoffeeMachine(const CoffeeMachine &instance) : CoffeeMaker(instance) {
        this->isStraitOpened = instance.isStraitOpened;
        cout << "Calling copying constructor for coffee machine" << endl;
    }

    virtual ~CoffeeMachine() {
        cout << "Calling virtual destructor of coffee machine" << endl;
    }

};



int main() {
    CoffeeMachine machine = CoffeeMachine();
    cout << endl << "===========" << endl;
    // make espresso
    machine.makeCoffee();
    cout << endl << "===========" << endl;
    // make milk foam
    try {
        machine.prepareToMakeMilkFoam(20);
        machine.openStreamFaucet(7);
    } catch (SteamFaucetOpeningError e) {
        cerr << e.what();
        exit(1);
    }
    machine.closeStreamFaucet();
    CoffeeMachine machine2 = CoffeeMachine(machine);
}