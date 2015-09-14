//trie with “isowrd” only

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
      std::unique_ptr<TrieNode> children[AlphabetSize];
    };
    
  TrieNode root_;
    
public:
    
  Trie()
  {
  }
    
  void insert(std::vector<unsigned char> newWord)
  {
    size_t index = 0;
    TrieNode *currentNode = &root_;
    while(index < newWord.size()) {
      unsigned char &value = newWord[index];
      if(!currentNode->children[value]) {
	currentNode->children[value] = std::make_unique<TrieNode>();
      }
      ++(currentNode->prefixCount);
      currentNode = currentNode->children[value].get();
      ++index;
    }
        
    currentNode->isWord = true;
  }
    
  bool lookUp(std::vector<unsigned char> newWord)
  {
    using namespace std;
    size_t index = 0;
    TrieNode *currentNode = &root_;
    while(index < newWord.size()) {
      unsigned char &value = newWord[index];
      if(!currentNode->children[value]) {
	return false;
      }
            
      currentNode = currentNode->children[value].get();
      ++index;
    }
    return currentNode->isWord;
  }
};

std::vector<unsigned char> convert(std::string s)
{
  std::vector<unsigned char> retValue;
  //std::transform(begin(s), end(s), begin(s), std::tolower);
  for(auto c : s) {
    if(c >= 'a') {
      retValue.push_back(c - 'a');
    } else {
      retValue.push_back(c - 'A');
    }
  }
  return std::move(retValue);
}

int main()
{
  using namespace std;
    
  vector<string> inputs {"Foo", "Bar", "DongPing", "Lee", "Larrytheloafer"};
  vector<vector<unsigned char>> inputsConverted(inputs.size());
    
     
  vector<string> searchStrings {"Foo", "cat", "leeHowes"};
    
  std::transform(
		 begin(inputs), end(inputs), begin(inputsConverted), [](string s){return convert(s);});
    
  Trie<26> t;
    
  for(auto v : inputsConverted) {
    t.insert(v);
  }
    
  for(auto v : searchStrings) {
    cout << v << "; " << t.lookUp(convert(v)) << "\n";
  }
}
