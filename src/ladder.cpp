#include "ladder.h"

void error(string word1, string word2, string msg) {

}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int m = str1.length();
    int n = str2.length();

    if (abs(m - n) > d) return false;

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

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    
}

void load_words(set<string> & word_list, const string& file_name) {

}

void print_word_ladder(const vector<string>& ladder) {

}

void verify_word_ladder() {

}