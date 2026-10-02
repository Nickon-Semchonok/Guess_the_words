#include <iostream>
#include <conio.h>
#include "word_game.h"

int main() {
    WordGame game;
    game.init_words_file();
    game.load_words();

    while (true) {
        std::cout << "\nChoose an action:\n"
            << "1: Start game\n"
            << "2: Start new game\n"
            << "0: Exit game\n";

        int choice = _getch();

        switch (choice) {
        case 49: 
            game.start_game();
            while (!game.is_game_over()) {
                game.play_turn();
            }
            break;

        case 50: 
            game.start_game();
            while (!game.is_game_over()) {
                game.play_turn();
            }
            break;

        case 48: 
            std::cout << "\nThank you for playing! Goodbye." << std::endl;
            game.clear_list();
            return 0;

        default:
            std::cout << "\nInvalid choice. Please try again." << std::endl;
            break;
        }
    }

    return 0;
}