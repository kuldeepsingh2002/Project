#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class SentimentAnalyzer {
public:
    void loadPositiveWords(const string& filename) {
        loadWords(filename, positiveWords_);
    }

    void loadNegativeWords(const string& filename) {
        loadWords(filename, negativeWords_);
    }

    string analyzeSentiment(const string& userInput) const {
        unordered_set<string> userWords = extractWords(userInput);

        int positiveCount = countMatchingWords(userWords, positiveWords_);
        int negativeCount = countMatchingWords(userWords, negativeWords_);

        if (positiveCount > negativeCount) {
            return "Positive Experience";
        } else if (negativeCount > positiveCount) {
            return "Negative Experience";
        } else {
            return "Neutral Experience";
        }
    }

private:
    unordered_set<string> positiveWords_;
    unordered_set<string> negativeWords_;

    void loadWords(const string& filename, unordered_set<string>& wordSet) const {
        ifstream file(filename);
        if (file.is_open()) {
            string word;
            while (file >> word) {
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                wordSet.insert(word);
            }
            file.close();
        } else {
            cerr << "Error opening file: " << filename << endl;
        }
    }

    unordered_set<string> extractWords(const string& text) const {
        unordered_set<string> words;
        istringstream iss(text);
        string word;

        while (iss >> word) {
            
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

            
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            words.insert(word);
        }

        return words;
    }

    int countMatchingWords(const unordered_set<string>& userWords, const unordered_set<string>& lexicon) const {
        int count = 0;
        for (const auto& word : userWords) {
            if (lexicon.count(word)) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    SentimentAnalyzer analyzer;

    
    analyzer.loadPositiveWords("positive words.txt");
    analyzer.loadNegativeWords("negative words.txt");

    
    cout << "Enter text for sentiment analysis: ";
    string userInput;
    getline(cin, userInput);

    
    string sentiment = analyzer.analyzeSentiment(userInput);

   
    cout << "Sentiment: " << sentiment << endl;

    return 0;
}