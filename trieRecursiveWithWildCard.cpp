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
    
public:
  TrieNode root_;
    
  Trie()
  {
  }
    
  void insert(std::string newWord)
  {
        
    TrieNode *currentNode = &root_;
    insertUtil(currentNode, newWord);
  }

       
  void insertUtil(TrieNode* currentNode, std::string newWord)
  {
    if(newWord.size() == 0 ) {
      currentNode->isWord = true;
      ++(currentNode->prefixCount);
    } else {
      unsigned char value = newWord[0]-'a';
      if(!currentNode->children[value]) {
	currentNode->children[value] = std::make_unique<TrieNode>();
      }
      ++(currentNode->prefixCount);
      currentNode = currentNode->children[value].get();
      std::cout<<"newword[index] "<<0<<" "<<newWord[0]<<std::endl;
            
      insertUtil(currentNode, newWord.substr(1));
    }
  }
    
    
  bool lookUp(std::string newWord)
  {
    using namespace std;
        
    return lookupUtil(root_, newWord);
  }
    
  /*  bool lookupUtil(const TrieNode& currentNode, std::string input)
    {
        using namespace std;
        
        if(input.size()==0) {
            return currentNode.isWord;
        } else
        {
            unsigned char value = input[0]-'a';
            if(!currentNode.children[value]) {
                return false; 
            } else 
            {
                TrieNode &nextNode = *(currentNode.children[value]); 
                std::string suffix = input.substr(1);
                return lookupUtil(nextNode, suffix);
            }
        }
	}*/
  /*
    //lookupUtil takes ? into account. 
    bool lookupUtil(const TrieNode& currentNode, std::string input)
    {
        using namespace std;
        
        if(input.size()==0) {
            return currentNode.isWord;
        } else
        {
            if(input[0]!='?')
            {
                unsigned char value = input[0]-'a';
                if(!currentNode.children[value]) {
                    return false; 
                } else 
                {
                    TrieNode &nextNode = *(currentNode.children[value]); 
                    std::string suffix = input.substr(1);
                    return lookupUtil(nextNode, suffix);
                }
                
            }else
            {
                bool find = false;
                for(int i = 0; i<AlphabetSize; i++)
                {
                    
                    if(!find&&currentNode.children[i])
                        {
                            TrieNode &nextNode = *(currentNode.children[i]); 
                            std::string suffix = input.substr(1);
                            find = lookupUtil(nextNode, suffix);
                        }
                }
                return find;
                
            }
        }
    }
  */
  bool lookupUtil(const TrieNode& currentNode, std::string input)
  {
    using namespace std;
        
    if(input.size()==0) {
      return currentNode.isWord;
    } else
      {
	if(input[0]=='*'||input[0]=='?') {
	  bool find = false;
	  for(int i = 0; i<AlphabetSize; i++)
	    {
	      if(!find&&currentNode.children[i])
		{
		  TrieNode &nextNode = *(currentNode.children[i]); 
		  std::string suffix = input.substr(1);
		  find = lookupUtil(nextNode, suffix);
		  if(input[0]=='*') {
		    find |= lookupUtil(nextNode, input);
		  }
		}
	    }
	  return find;
	} else {
	  unsigned char value = input[0]-'a';
	  if(!currentNode.children[value]) {
	    return false; 
	  } else 
	    {
	      TrieNode &nextNode = *(currentNode.children[value]); 
	      std::string suffix = input.substr(1);
	      return lookupUtil(nextNode, suffix);
	    }
	}
      }
  }
    
  std::pair<size_t, std::string>
  lookUpWithPrefix(std::string newWord)
  {
    using namespace std;
    size_t index = 0;
    TrieNode *currentNode = &root_;
    while(index < newWord.size()) {
      unsigned char value = newWord[index] - 'a';
      if(!currentNode->children[value]) {
	return {currentNode->prefixCount, std::string(begin(newWord), begin(newWord) + index)};
      }
            
      currentNode = currentNode->children[value].get();
      ++index;
    }
    return {currentNode->prefixCount, newWord};
  }    
};

int main()
{
  using namespace std;
    
  vector<string> inputs {"Foo", "Bar", "DongPing", "Lee", "Larrytheloafer"};
  vector<string> searchStrings {"Foo", "cat", "leeHowes", "b*r", "?ee", "Larry*", "*e", "L*", "", "*"};
  //vector<string> searchStrings {"Foo", "cat", "leeHowes", "b?r", "?ee", "Larry?", "?e"};
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
    cerr<<"v = "<<v<<endl;
    cout << v << "; " << t.lookUp(v) << "\n";
    cerr<<"t.lookup(v) = "<<t.lookUp(v)<<endl;
  }
    
  /* cout << "Partial words:\n";
    for(auto v : searchStrings) {
        auto p = t.lookUpWithPrefix(v);
        cout << v << "; " << p.first << ", " << p.second << "\n";
    }
  */
}
