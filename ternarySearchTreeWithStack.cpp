// C program to demonstrate Ternary Search Tree (TST) insert, travese 
// and search operations
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

#define MAX 50
 
// A node of ternary search tree
struct Node
{
  char data;
 
  // True if this character is last character of one of the words
  unsigned isEndOfString: 1;
 
  struct Node *left, *eq, *right;
};
 
// A utility function to create a new ternary search tree node
struct Node* newNode(char data)
{
  struct Node* temp = (struct Node*) malloc(sizeof( struct Node ));
  temp->data = data;
  temp->isEndOfString = 0;
  temp->left = temp->eq = temp->right = NULL;
  return temp;
}
 
// Function to insert a new word in a Ternary Search Tree
void insert(struct Node** root, char *word)
{
  // Base Case: Tree is empty
  if (!(*root))
    *root = newNode(*word);
 
  // If current character of word is smaller than root's character,
  // then insert this word in left subtree of root
  if ((*word) < (*root)->data)
    insert(&( (*root)->left ), word);
 
  // If current character of word is greate than root's character,
  // then insert this word in right subtree of root
  else if ((*word) > (*root)->data)
    insert(&( (*root)->right ), word);
 
  // If current character of word is same as root's character,
  else
    {
      if (*(word+1))
	insert(&( (*root)->eq ), word+1);
 
      // the last character of the word
      else
	(*root)->isEndOfString = 1;
    }
}
 
// A recursive function to traverse Ternary Search Tree
void traverseTSTUtil(struct Node* root, std::vector<char> &stringStack)
{
  if (root)
    {
      // First traverse the left subtree
  traverseTSTUtil(root->left, stringStack);
  
// Store the character of this node
  stringStack.push_back(root->data);
 if (root->isEndOfString)
   {
     stringStack.push_back('\0'); 
     printf( "%s\n", stringStack.data());
     stringStack.pop_back();
   }
 
 // Traverse the sub tree using equal pointer (middle subtree)
   traverseTSTUtil(root->eq, stringStack);
   stringStack.pop_back();
  
 // Finally Traverse the right subtree
   traverseTSTUtil(root->right, stringStack);
    }
}
 
// The main function to traverse a Ternary Search Tree.
// It mainly uses traverseTSTUtil()
void traverseTST(struct Node* root)
{
  std::vector<char> stringStack;
  stringStack.reserve(MAX);
  traverseTSTUtil(root, stringStack);
}
 
// Function to search a given word in TST
int searchTST(struct Node *root, char *word)
{
  if (!root)
    return 0;
 
  if (*word < (root)->data)
    return searchTST(root->left, word);
 
  else if (*word > (root)->data)
    return searchTST(root->right, word);
 
  else
    {
      if (*(word+1) == '\0')
	return root->isEndOfString;
 
      return searchTST(root->eq, word+1);
    }
}
 
// Driver program to test above functions
int main()
{
  struct Node *root = NULL;
 
  insert(&root, "cat");
  insert(&root, "cats");
  insert(&root, "up");
  insert(&root, "bug");
 
  printf("Following is traversal of ternary search tree\n");
  traverseTST(root);
 
  printf("\nFollowing are search results for cats, bu and cat respectively\n");
  searchTST(root, "cats")? printf("Found\n"): printf("Not Found\n");
  searchTST(root, "bu")?   printf("Found\n"): printf("Not Found\n");
  searchTST(root, "cat")?  printf("Found\n"): printf("Not Found\n");
 
  return 0;
}
