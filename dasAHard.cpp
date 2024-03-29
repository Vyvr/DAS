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
    vector<int> states;
    int initialState;
    vector<int> acceptingStates;
    vector<Transition> transitions;
    string alphabet;

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

public:
    DeterministicAutomaton() {}

    // Wczytanie automatu z pliku
    void loadFromFile(const string &fileName)
    {
        ifstream file(fileName);
        string line;

        // alfabet
        getline(file, line);
        alphabet = line;

        // stany
        getline(file, line);
        stringstream ssStates(line);
        int state;
        while (ssStates >> state)
        {
            states.push_back(state);
        }

        // stany koncowe
        getline(file, line);
        stringstream ssAccepting(line);
        while (ssAccepting >> state)
        {
            acceptingStates.push_back(state);
        }

        // funkcje przejscia
        while (getline(file, line))
        {
            int s, ns;
            char sym;
            stringstream ssTrans(line);
            ssTrans >> s >> sym >> ns;
            transitions.push_back({s, sym, ns});
        }

        initialState = states.front();
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
};

int main()
{
    DeterministicAutomaton automaton;
    automaton.loadFromFile("dasAHardData.txt");

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
