#include "Trie.h"

Trie::Node::Node()
    : isWord(false)
{
}

Trie::Trie()
    : root(new Node()), wordCount(0)
{
}

Trie::Trie(const Trie& other)
{
    root = clone(other.root);
    wordCount = other.wordCount;
}

Trie::Trie(Trie&& other) noexcept
{
    root = other.root;
    wordCount = other.wordCount;

    other.root = new Node();
    other.wordCount = 0;
}

Trie& Trie::operator=(const Trie& other)
{
    if (this != &other)
    {
        clear();
        delete root;

        root = clone(other.root);
        wordCount = other.wordCount;
    }

    return *this;
}

Trie& Trie::operator=(Trie&& other) noexcept
{
    if (this != &other)
    {
        clear();
        delete root;

        root = other.root;
        wordCount = other.wordCount;

        other.root = new Node();
        other.wordCount = 0;
    }

    return *this;
}

Trie::~Trie()
{
    destroy(root);
}

void Trie::insert(const string& word)
{
    Node* current = root;

    for (char c : word)
    {
        if (current->children.find(c) == current->children.end())
            current->children[c] = new Node();

        current = current->children[c];
    }

    if (!current->isWord)
    {
        current->isWord = true;
        ++wordCount;
    }
}

bool Trie::contains(const string& word) const
{
    Node* node = findNode(word);
    return node && node->isWord;
}

bool Trie::startsWith(const string& prefix) const
{
    return findNode(prefix) != nullptr;
}

vector<string> Trie::autocomplete(const string& prefix, size_t limit) const
{
    vector<string> results;

    Node* node = findNode(prefix);

    if (!node)
        return results;

    collectWords(node, prefix, results, limit);

    return results;
}

bool Trie::erase(const string& word)
{
    if (!contains(word))
        return false;

    eraseHelper(root, word, 0);
    --wordCount;

    return true;
}

void Trie::clear()
{
    destroy(root);
    root = new Node();
    wordCount = 0;
}

bool Trie::empty() const
{
    return wordCount == 0;
}

size_t Trie::size() const
{
    return wordCount;
}

Trie::Node* Trie::findNode(const string& text) const
{
    Node* current = root;

    for (char c : text)
    {
        auto it = current->children.find(c);

        if (it == current->children.end())
            return nullptr;

        current = it->second;
    }

    return current;
}

void Trie::collectWords(Node* node,
    string currentWord,
    vector<string>& results,
    size_t limit) const
{
    if (results.size() >= limit)
        return;

    if (node->isWord)
        results.push_back(currentWord);

    for (const auto& child : node->children)
    {
        collectWords(child.second,
            currentWord + child.first,
            results,
            limit);

        if (results.size() >= limit)
            return;
    }
}

bool Trie::eraseHelper(Node* node,
    const string& word,
    size_t depth)
{
    if (depth == word.size())
    {
        node->isWord = false;
        return node->children.empty();
    }

    char c = word[depth];

    auto it = node->children.find(c);

    if (it == node->children.end())
        return false;

    Node* child = it->second;

    if (eraseHelper(child, word, depth + 1))
    {
        delete child;
        node->children.erase(c);
    }

    return !node->isWord && node->children.empty();
}

void Trie::destroy(Node* node)
{
    if (!node)
        return;

    for (auto& child : node->children)
        destroy(child.second);

    delete node;
}

Trie::Node* Trie::clone(Node* node) const
{
    if (!node)
        return nullptr;

    Node* copy = new Node();
    copy->isWord = node->isWord;

    for (const auto& child : node->children)
        copy->children[child.first] = clone(child.second);

    return copy;
}
