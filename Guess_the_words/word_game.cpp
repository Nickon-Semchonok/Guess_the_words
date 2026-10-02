#include "word_game.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

bool WordGame::init_words_file() {
    std::ofstream file(WORDS_FILENAME);
    if (!file.is_open()) {
        std::cout << "File open error for writing!" << std::endl;
        return false;
    }

    const std::string words[100] = {
        "game", "code", "book", "word", "tree", "park", "river", "sun", "water", "sky",
        "earth", "flower", "forest", "bird", "fish", "cat", "dog", "bread", "milk", "apple",
        "city", "town", "house", "window", "door", "table", "chair", "desk", "sofa", "spoon",
        "fork", "knife", "plate", "cup", "coffee", "tea", "sugar", "salt", "pepper", "oil",
        "cheese", "meat", "plant", "fruit", "banana", "lemon", "pear", "plum", "cherry", "berry",
        "melon", "grape", "squash", "carrot", "beet", "potato", "onion", "garlic", "cucumber", "tomato",
        "cabbage", "peas", "beans", "rice", "wheat", "flour", "dough", "pie", "cake", "cookie",
        "candy", "chocolate", "juice", "drink", "frost", "snow", "rain", "wind", "cloud", "storm",
        "heat", "summer", "autumn", "winter", "spring", "morning", "day", "evening", "night", "time",
        "minute", "second", "year", "month", "week", "holiday", "school", "class", "student", "paper"
    };

    for (int i = 0; i < 100; ++i) {
        file << words[i] << "\n";
    }

    file.close();
    return true;
}

bool WordGame::load_words() {
    clear_list();
    std::ifstream file(WORDS_FILENAME);
    if (!file.is_open()) {
        return false;
    }

    std::string w;
    WordNode* last = nullptr;
    while (file >> w) {
        WordNode* new_node = new WordNode{ w, nullptr };
        if (first == nullptr) {
            first = last = new_node;
        }
        else {
            last->next = new_node;
            last = new_node;
        }
        word_count++;
    }
    file.close();
    return word_count > 0;
}

void WordGame::clear_list() {
    while (first) {
        WordNode* temp = first;
        first = first->next;
        delete temp;
    }
    word_count = 0;
}

void WordGame::start_game() {
    if (word_count == 0) {
        std::cout << "Word list is empty! Please load words first." << std::endl;
        return;
    }

    srand(static_cast<unsigned int>(time(0)));
    int random_index = rand() % word_count;

    WordNode* curr = first;
    for (int i = 0; i < random_index && curr; ++i) {
        curr = curr->next;
    }

    if (curr) {
        current_word = curr->word;
        attempts_left = 5;

        guessed_mask = std::string(current_word.length(), '_');

        std::cout << "\n=== New game started! ===" << std::endl;
        std::cout << "Word: " << guessed_mask << std::endl;
        std::cout << "You have " << attempts_left << " attempts left." << std::endl;
    }
}

void WordGame::play_turn() {
    if (current_word.empty()) {
        std::cout << "Game has not started. Choose an option from the menu." << std::endl;
        return;
    }

    if (attempts_left <= 0) {
        std::cout << "No attempts left! The word was: " << current_word << std::endl;
        return;
    }

    std::cout << "\nEnter letter(s) [or '2' to restart, '0' to exit to menu]: ";
    std::string input;
    std::cin >> input;

    if (input == "2") {
        start_game();
        return;
    }

    if (input == "0") {
        std::cout << "Exiting current game." << std::endl;
        current_word = "";
        return;
    }

    std::string matching_letters = "";
    for (size_t i = 0; i < input.length(); ++i) {
        if (current_word.find(input[i]) != std::string::npos) {
            if (matching_letters.find(input[i]) == std::string::npos) {
                matching_letters += input[i];
            }
        }
    }

    if (input == current_word) {
        guessed_mask = current_word;
    }
    else {
        for (size_t i = 0; i < current_word.length() && i < input.length(); ++i) {
            if (current_word[i] == input[i]) {
                guessed_mask[i] = input[i];
            }
        }
    }

    if (!matching_letters.empty()) {
        if (matching_letters.length() == 1) {
            std::cout << "letter ( " << matching_letters << " ) is in the word" << std::endl;
        }
        else {
            std::cout << "these ( letters " << matching_letters << " ) are in the word" << std::endl;
        }
    }
    else {
        std::cout << "Entered character(s) not in the word." << std::endl;
    }

    attempts_left--;

    if (guessed_mask == current_word) {
        std::cout << "\nCongratulations! You guessed the word: " << current_word << std::endl;
        current_word = "";
    }
    else if (attempts_left > 0) {
        std::cout << "Current state: " << guessed_mask << std::endl;
        std::cout << "Attempts remaining: " << attempts_left << std::endl;
    }
    else {
        std::cout << "\nGame over! You lost. The hidden word was: " << current_word << std::endl;
        current_word = "";
    }
}

bool WordGame::is_game_over() const {
    return current_word.empty() || attempts_left <= 0;
}