#include "ladder.h"
#include <unordered_set>


void error(string word1, string word2, string msg) {
    std::cerr << word1 + word2 + msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int m = str1.length();
    int n = str2.length();

    if (abs(m - n) > d) return false;

    // optimized approach for just m == n
    if (m == n) {
        int difference = 0;
        for (int i = 0; i < m; ++i) {
            if (str1[i] != str2[i]) {
                ++difference;
                if (difference > 1) 
                    return false;
            }
        }
        return difference <= 1;
    } else {
        // levenshtien 
        vector<vector<int>> subproblems(m + 1, vector<int>(n + 1));

        for (int i = 0; i <= m; i++) 
            subproblems[i][0] = i;
        for (int j = 0; j <= n; j++) 
            subproblems[0][j] = j; 

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1[i - 1] == str2[j - 1])
                    subproblems[i][j] = subproblems[i - 1][j - 1];
                else
                    subproblems[i][j] = 1 + min({subproblems[i][j - 1],  
                                    subproblems[i - 1][j],   
                                    subproblems[i - 1][j - 1]});
            }
        }

        return subproblems[m][n] <= d;
    }
}     

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) return vector<string>();
    if (begin_word == end_word) return vector<string>();

    unordered_set<string> visited;
    visited.insert(begin_word);

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for (auto word: word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);

                    auto new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        // print_word_ladder(new_ladder);
                        return new_ladder;
                    }
                    
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return vector<string>();
}

void load_words(set<string> & word_list, const string& file_name) {
    std::ifstream file(file_name);
    std::string word;
    while (getline(file, word)) 
        word_list.insert(word);
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        std::cout << "No word ladder found." << std::endl;
    } else {
        std::cout << "Word ladder found: ";
        for (auto word: ladder)
            std::cout << word << " ";
        std::cout << std::endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}