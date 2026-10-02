#ifndef WORD_GAME_H
#define WORD_GAME_H

#include <string>

struct WordNode {
    std::string word;
    WordNode* next = nullptr;
};

struct WordGame {
    const std::string WORDS_FILENAME = "words.txt";
    WordNode* first = nullptr;
    int word_count = 0;

    std::string current_word = "";
    std::string guessed_mask = "";
    int attempts_left = 5;

    bool init_words_file(); 
    bool load_words();      
    void start_game();      
    void play_turn();       
    bool is_game_over() const;
    void clear_list();
};

#endif 