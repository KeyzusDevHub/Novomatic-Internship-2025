#include "Trie.hpp"
#include <gtest/gtest.h>
#include <fstream>

bool comp(std::string a, std::string b) {
    if (a.size() != b.size()){
        return a.size() < b.size();
    }
    return a < b;
}

std::string runWithInput(const std::string& inputFilePath) {
    std::string output;

    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        exit(-1);
    }

    auto wordTrie = std::make_unique<Trie<char>>();
    auto sentenceTrie = std::make_unique<Trie<std::string>>();

    while (true) {
        std::string line;
        std::getline(inputFile, line);

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string request;
        ss >> request;

        std::string data;
        std::getline(ss, data);

        if (!data.empty()){
            data.erase(0, data.find_first_not_of(' '));
        }

        std::istringstream iss(data);
        std::vector<std::string> sentence;
        std::string word;

        if (request == "new:") {
            data.erase(data.find_last_not_of(" \t\n\r\f\v") + 1);
            std::ranges::for_each(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), [&](const std::string& word) {
                sentence.push_back(word);
                wordTrie->insert(std::vector<char>(word.begin(), word.end()));
            });
            sentenceTrie->insert(sentence);
        } 
        else if (request == "ask:") {
            std::ranges::find_if(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), [&](const std::string& word) {
                std::pair<std::string, bool> isWordFull = wordTrie->isFullPrefix(std::vector<char>(word.begin(), word.end()));
                
                if (isWordFull.second) {
                    sentence.push_back(word);
                } else {
                    sentence.push_back(isWordFull.first);
                }
                return !isWordFull.second;
            });

            std::vector<std::vector<std::string>> allPrefixes;

            if (data.back() != ' ') {
                std::string lastWord = sentence.back();
                sentence.pop_back();
                std::list<std::string> matchingWords = wordTrie->searchStartingWith(std::vector<char>(lastWord.begin(), lastWord.end()));
                std::ranges::for_each(matchingWords, [&](const std::string& mWord) {
                    sentence.push_back(mWord);
                    allPrefixes.push_back(sentence);
                    sentence.pop_back();
                });
            } 
            else {
                allPrefixes.push_back(sentence);
            }

            std::list<std::string> askResults;
            std::ranges::for_each(allPrefixes, [&](const auto& prefix) {
                std::list<std::string> askResult = sentenceTrie->searchStartingWith(prefix);
                askResults.insert(askResults.end(), askResult.begin(), askResult.end());
            });

            askResults.sort(comp);
            std::ranges::for_each(askResults, [&](const std::string& result) {
                output += "result: " + result + '\n';
            });
        }
        else if (request == "end"){
            break;
        }
        else {
            output += "Unknown command: " + request + '\n';
        }
    }

    return output;
}

void UnitTest(std::string inputPath, std::string outputPath){

    std::string actualOutput = runWithInput(inputPath);
    
    std::ifstream expectedFile(outputPath);
    
    if (!expectedFile.is_open()) {
        std::cerr << "Error: Could not open output file!" << std::endl;
        exit(-1);
    }

    std::stringstream expectedBuffer;
    expectedBuffer << expectedFile.rdbuf();

    EXPECT_EQ(actualOutput, expectedBuffer.str());
}

TEST(TrieIOTest, TaskExample) {
    UnitTest("tests/test1_input.txt", "tests/output1.txt");
}

TEST(TrieIOTest, PartialInput) {
    UnitTest("tests/test2_input.txt", "tests/output2.txt");
}

TEST(TrieIOTest, WrongCommands) {
    UnitTest("tests/test3_input.txt", "tests/output3.txt");
}

TEST(TrieIOTest, TypoAsk) {
    UnitTest("tests/test4_input.txt", "tests/output4.txt");
}

TEST(TrieIOTest, MixedInput) {
    UnitTest("tests/test5_input.txt", "tests/output5.txt");
}