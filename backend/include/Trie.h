#pragma once
#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * @brief Trie data structure for efficient prefix searching and autocomplete.
 *
 * Supports:
 * - Insert words
 * - Search complete words
 * - Prefix search
 * - Autocomplete
 * - Word deletion
 *
 * The class follows the Rule of Five and performs deep copies.
 */
class Trie
{
public:
    /**
     * @brief Default constructor.
     */
    Trie();

    /**
     * @brief Copy constructor.
     *
     * Creates a deep copy of another Trie.
     */
    Trie(const Trie& other);

    /**
     * @brief Move constructor.
     */
    Trie(Trie&& other) noexcept;

    /**
     * @brief Copy assignment operator.
     */
    Trie& operator=(const Trie& other);

    /**
     * @brief Move assignment operator.
     */
    Trie& operator=(Trie&& other) noexcept;

    /**
     * @brief Destructor.
     */
    ~Trie();

    /**
     * @brief Insert a new word into the trie.
     *
     * Duplicate words are ignored.
     *
     * @param word Word to insert.
     */
    void insert(const string& word);

    /**
     * @brief Remove a word from the trie.
     *
     * @param word Word to remove.
     * @return true if the word existed and was removed.
     * @return false otherwise.
     */
    bool erase(const string& word);

    /**
     * @brief Check whether a complete word exists.
     *
     * @param word Word to search.
     * @return true if found.
     * @return false otherwise.
     */
    bool contains(const string& word) const;

    /**
     * @brief Check whether any word starts with a prefix.
     *
     * @param prefix Prefix to search.
     * @return true if the prefix exists.
     * @return false otherwise.
     */
    bool startsWith(const string& prefix) const;

    /**
     * @brief Return autocomplete suggestions.
     *
     * Suggestions are returned in lexicographical order.
     *
     * @param prefix Prefix entered by the user.
     * @param limit Maximum number of returned words.
     * @return Vector containing matching words.
     */
    vector<string> autocomplete(
        const string& prefix,
        size_t limit = SIZE_MAX
    ) const;

    /**
     * @brief Remove every stored word.
     */
    void clear();

    /**
     * @brief Check whether the trie is empty.
     */
    bool empty() const;

    /**
     * @brief Return the number of stored words.
     */
    size_t size() const;

private:

    /**
     * @brief Represents a single trie node.
     */
    struct Node
    {
        bool isWord;
        unordered_map<char, Node*> children;

        Node();
    };

    Node* root;
    size_t wordCount;

    /**
     * @brief Recursively delete an entire subtree.
     */
    void destroy(Node* node);

    /**
     * @brief Recursively clone a subtree.
     */
    Node* clone(Node* node) const;

    /**
     * @brief Recursive helper used by erase().
     *
     * @return true if the current node should be deleted.
     */
    bool eraseHelper(
        Node* node,
        const string& word,
        size_t depth
    );

    /**
     * @brief Collect all words below a node.
     *
     * Used internally by autocomplete().
     */
    void collectWords(
        Node* node,
        string currentWord,
        vector<string>& results,
        size_t limit
    ) const;

    /**
     * @brief Traverse the trie and return the node
     * corresponding to a given prefix.
     *
     * Returns nullptr if the prefix does not exist.
     */
    Node* findNode(const string& text) const;
};

#endif // TRIE_H