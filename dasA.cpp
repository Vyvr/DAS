#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Alfabet
const string alphabet = "ab";

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
public:
    DeterministicAutomaton()
    {
        states = {0, 1, 2}; // Stany: 0 - początkowy, 1 - napotkano 'a', 2 - napotkano 'b' po 'a'
        initialState = 0;
        acceptingStates = {2};
        transitions = {
            {0, 'a', 1},
            {0, 'b', 0},
            {1, 'a', 1},
            {1, 'b', 2},
            {2, 'a', 1},
            {2, 'b', 2}};
    }

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

private:
    vector<int> states;
    int initialState;
    vector<int> acceptingStates;
    vector<Transition> transitions;

    // przejscie do nastepnego stanu
    int getNextState(int currentState, char symbol)
    {
        for (const Transition &transition : transitions)
        {
            if (transition.state == currentState && transition.symbol == symbol)
            {
                return transition.nextState;
            }
        }
        return -1; // brak przejścia dla danego symbolu
    }

    // czy stan akceptujacy
    bool isAcceptingState(int state)
    {
        return find(acceptingStates.begin(), acceptingStates.end(), state) != acceptingStates.end();
    }
};

int main()
{
    DeterministicAutomaton automaton;
    string input;
    cout << "Enter a string: ";
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
