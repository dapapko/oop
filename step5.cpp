#include <exception>
#include <iostream>
#include <fstream>
using namespace std;


class SteamFaucetOpeningError : public exception {
public:
    const char * what () {
        return "Steam faucet opening error. Deg must be positive.";
    }
};

class CoffeeMachine{
private:
    bool canMakeCappuccino; // can make cappuccino or not
    int pressure; // pressure of pump
    int colour; // hexadecimal code of colour
    int price; // price of a machine (in roubles)
    int temperature; // current temperature of a coffee machine
    fstream file;
    class SteamFaucet {
    private:
        int deg;
    public:
        SteamFaucet(): deg(0) {}

        void setDeg(int deg){
            this->deg = deg;
        }

    };

    SteamFaucet faucet = CoffeeMachine::SteamFaucet();
    bool isStraitOpened;

public:
    CoffeeMachine(string filename) {
        file.open(filename);
        if(!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }
        file >> canMakeCappuccino;
        file >> pressure;
        file  this->price;
        file >> hex >> colour;
        temperature = 20;
        isStraitOpened = false;
        cout << "The default constructor was called" << endl;
    }
    ~CoffeeMachine() {
        if(file.is_open()) file.close();
    }

    CoffeeMachine(const CoffeeMachine& instance):
            canMakeCappuccino(instance.canMakeCappuccino),
            pressure(instance.pressure),
            colour(instance.colour),
            price(instance.price),
            temperature(instance.temperature),
            isStraitOpened(instance.isStraitOpened)
    {
        cout << "Copying constructor of coffee machine was called" << endl;
    }


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
        this->closeStrait();
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

    void printProperties() {
        cout << "Price: " << this->price << endl;
        cout << "Pressure: " << this->pressure << endl;
        cout << "Can make cappuccino: " << this->canMakeCappuccino << endl;
        cout << "Colour: " << hex << this-> colour << endl;
        cout << "Temperature: " << this->temperature << endl;
        cout << "Is strait opened: " << this->isStraitOpened << endl;
        cout << "Degree of opening of facet: " << this->faucet.getDeg() << endl;
    }

    void prepareToMakeMilkFoam(int deg) {
        this->warm(130);
    }

};

int main() {
    CoffeeMachine machine = CoffeeMachine("coffee.txt");
    cout << endl << "===========" << endl;
    // make espresso
   machine.printProperties();
   CoffeeMachine machine2 = CoffeeMachine(machine);
}
