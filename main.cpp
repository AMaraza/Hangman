#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

void clear(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void ChooseWord(std::vector<std::string> &words, std::vector<char> &wordChars, std::vector<char> &blankWord);
void DrawGame(std::vector<char> &wordChars, std::vector<char> &blankWord, int guesses);

int main(){
    std::vector<std::string> words;
    std::vector<char> wordChars;
    std::vector<char> blankWord;
    int guesses = 0;

    ChooseWord(words, wordChars, blankWord);
    DrawGame(wordChars, blankWord, guesses);

    return 0;
}

void ChooseWord(std::vector<std::string> &words, std::vector<char> &wordChars, std::vector<char> &blankWord){
    std::string word;
    std::string chosenWord;

    std::ifstream hangmanWords("hangman.txt");

    while (getline (hangmanWords, word)){
        words.push_back(word);
    }

    srand(time(0));
    int randomWord = rand() % words.size() + 1;
    
    chosenWord = words.at(randomWord);

    for (int i = 0; chosenWord[i]; i++){
        wordChars.push_back(chosenWord[i]);
        blankWord.push_back(' ');
    }

    /*for (char element : wordChars){
        std::cout << element << " ";
    }*/
}

void DrawGame(std::vector<char> &wordChars, std::vector<char> &blankWord, int guesses){
    guesses = 5;
    char guess;
    int fill = 0;
    bool win = false;
    bool wrongGuess = false;
    char blank;

    do {
        wrongGuess = false;
        if (fill == wordChars.size()){
            win = true;
            break;
        }
        for (int i = 0; i < blankWord.size(); i++){
            std::cout << blankWord.at(i) << " ";
        }
    
        std::cout << "\n";
    
        for (char element : blankWord){
            std::cout << "_ ";
        }
    
        std::cout << "\n\n";
    
        std::cout << "Guesses: " << guesses << "\n";
        std::cout << "Make a Guess: ";
        std::cin >> guess;
        std::cout << "\n";
    
        for (int i = 0; i < wordChars.size(); i++){
            if (guess == wordChars[i] && guess != blankWord[i]){
                blankWord.at(i) = guess;
                fill++;
            }
        }

        for (char element : wordChars){
            if (guess != element){
                wrongGuess = true;
            }
            else{
                wrongGuess = false;
                break;
            }
        }

        if (wrongGuess){
            guesses--;
        }

        std::cin.clear();
        std::cin.ignore();
        clear();

    } while (guesses > 0 || win);

    if (win){
        std::cout << "You Win! The Word Was: ";
        for (char element : wordChars){
            std::cout << element;
        }
        std::cout << "\n";
    } else if (guesses == 0){
        std::cout << "You Lose! The Word Was: ";
        for (char element : wordChars){
            std::cout << element;
        }
        std::cout << "\n";
    }
    
    std::cin >> blank;
}