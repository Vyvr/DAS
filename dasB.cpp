#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

// Funkcja przejscia
struct Transition
{
    int state;
    char symbol;
    int nextState;
};

// Automat
class DeterministicAutomaton
{
private:
    vector<int> states = {0, 1, 2};
    int initialState = 0;
    vector<int> acceptingStates = {0};
    string alphabet = "0123456789";

    // przejscie do nastepnego stanu
    int getNextState(int currentState, char symbol)
    {
        int digit = symbol - '0';
        int newState = (currentState + digit) % 3;
        return newState;
    }

    // czy stan akceptujacy
    bool isAcceptingState(int state)
    {
        return find(acceptingStates.begin(), acceptingStates.end(), state) != acceptingStates.end();
    }

public:
    DeterministicAutomaton() {}

    bool isNumberAccepted(const string &input)
    {
        int currentState = initialState;
        for (char symbol : input)
        {
            if (alphabet.find(symbol) == string::npos)
            {
                cout << "Invalid symbol: " << symbol << endl;
                return false; // zly symbol
            }
            currentState = getNextState(currentState, symbol);
            if (currentState == -1)
                return false; // zle przejscie
        }
        return isAcceptingState(currentState);
    }
};

int main()
{
    DeterministicAutomaton automaton;

    string input;
    cout << "Enter a number: ";
    cin >> input;

    if (automaton.isNumberAccepted(input))
    {
        cout << "Accepted" << endl;
    }
    else
    {
        cout << "Rejected" << endl;
    }

    return 0;
}
