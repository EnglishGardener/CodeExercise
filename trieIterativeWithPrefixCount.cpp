//trie with prefix count

#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <iostream>

template<int AlphabetSize>
class Trie
{
private:
    
    struct TrieNode 
    {
      bool isWord = {false};
      size_t prefixCount = {0};
      std::unique_ptr<TrieNode> children[AlphabetSize];
    };
    
  TrieNode root_;
    
public:
    
  Trie()
  {
  }
    
  void insert(std::string newWord)
  {
    size_t index = 0;
    TrieNode *currentNode = &root_;
    while(index < newWord.size()) {
      unsigned char value = newWord[index]-'a';
      if(!currentNode->children[value]) {
	currentNode->children[value] = std::make_unique<TrieNode>();
      }
      ++(currentNode->prefixCount);
      currentNode = currentNode->children[value].get();
      ++index;
    }
        
    currentNode->isWord = true;
  }
    
  bool lookUp(std::string newWord)
  {
    using namespace std;
    size_t index = 0;
    TrieNode *currentNode = &root_;
    while(index < newWord.size()) {
      unsigned char value = newWord[index] - 'a';
      if(!currentNode->children[value]) {
	return false;
      }
            
      currentNode = currentNode->children[value].get();
      ++index;
    }
    return currentNode->isWord;
  }
    
  std::pair<bool, std::string>
  lookUpWithPrefix(std::string newWord)
  {
    using namespace std;
    size_t index = 0;
    TrieNode *currentNode = &root_;
    while(index < newWord.size()) {
      unsigned char value = newWord[index] - 'a';
      if(!currentNode->children[value]) {
	return {false, std::string(begin(newWord), begin(newWord) + index)};
      }
            
      currentNode = currentNode->children[value].get();
      ++index;
    }
    return {currentNode->isWord, newWord};
  }    
};

int main()
{
  using namespace std;
    
  vector<string> inputs {"Foo", "Bar", "DongPing", "Lee", "Larrytheloafer"};
  vector<string> searchStrings {"Foo", "cat", "leeHowes"};
    
  for(auto &s : inputs) {
    std::transform(begin(s), end(s), begin(s), ::tolower);
  }
  for(auto &s : searchStrings) {
    std::transform(begin(s), end(s), begin(s), ::tolower);
  }
    
    
  Trie<26> t;
    
  for(auto v : inputs) {
    t.insert(v);
  }
    
  cout << "Whole words:\n";
  for(auto v : searchStrings) {
    cout << v << "; " << t.lookUp(v) << "\n";
  }
    
  cout << "Partial words:\n";
  for(auto v : searchStrings) {
    auto p = t.lookUpWithPrefix(v);
    cout << v << "; " << p.first << ", " << p.second << "\n";
  }
}
