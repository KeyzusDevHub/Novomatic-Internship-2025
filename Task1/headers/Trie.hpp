#ifndef _TRIE_HPP_
#define _TRIE_HPP_

#include "config.hpp"

// Concept to restrict T to char or std::string
template<typename T>
concept CharOrString = std::is_same_v<T, char> || std::is_same_v<T, std::string>;

template <CharOrString T>
struct TrieNode {
    std::map<T, std::shared_ptr<TrieNode<T>>> connections;
    bool isFullPhrase;

    TrieNode() : isFullPhrase(false) {}
};

template <CharOrString T>
class Trie {
private:
    std::shared_ptr<TrieNode<T>> root;
    std::string delimiter;

public:
    Trie() {
        root = std::make_shared<TrieNode<T>>();
        delimiter = std::is_same<T, char>::value ? "" : " ";
    }

    void insert(std::vector<T> phrase) {
        std::shared_ptr<TrieNode<T>> node = root;
        std::ranges::for_each(phrase, [&](const T& part){
            if (!node->connections.count(part)) {
                node->connections[part] = std::make_shared<TrieNode<T>>();
            }
            node = node->connections[part];
        });
        node->isFullPhrase = true;
    }

    std::list<std::string> searchStartingWith(std::vector<T> prefix) {
        std::shared_ptr<TrieNode<T>> node = root;
        std::list<std::string> found;

        auto it = std::ranges::find_if(prefix, [&](const T& part) {
            if (!node->connections.count(part)) {
                return true;
            }
            node = node->connections[part];
            return false;
        });

        if (it != prefix.end()) {
            return found;
        }

        std::queue<std::pair<std::shared_ptr<TrieNode<T>>, std::string>> queue;
        std::string fullPrefix;
        std::ranges::for_each(prefix, [&](const T& prefixPart) {
            fullPrefix += prefixPart + delimiter;
        });
        fullPrefix.erase(fullPrefix.find_last_not_of(" ") + 1);
        queue.push({ node, fullPrefix });

        while (!queue.empty()) {
            auto [currentNode, currentPhrase] = queue.front();
            queue.pop();

            if (currentNode->isFullPhrase) {
                found.push_back(currentPhrase);
            }

            std::ranges::for_each(currentNode->connections, [&](const auto& pair) {
                queue.push({ pair.second, currentPhrase + delimiter + pair.first });
            });
        }

        return found;
    }

    std::pair<std::string, bool> isFullPrefix(std::vector<T> prefix) {
        std::string found;
        std::shared_ptr<TrieNode<T>> node = root;

        auto it = std::ranges::find_if(prefix, [&](const T& part) {
            if (!node->connections.count(part)) {
                found.erase(found.find_last_not_of(" ") + 1);
                return true;
            }
            found += part + delimiter;
            node = node->connections[part];
            return false;
        });

        if (it != prefix.end()) {
            return { found, false };
        }

        found.erase(found.find_last_not_of(" ") + 1);
        return { found, true };
    }

    void remove(std::vector<T> phrase) {
        std::shared_ptr<TrieNode<T>> node = root;
        for (const T& part : phrase) {
            if (!node->connections.count(part)) {
                return;
            }
            node = node->connections[part];
        }
        if (node->isFullPhrase) {
            node->isFullPhrase = false;
        }
    }

    ~Trie() = default;
};

#endif
