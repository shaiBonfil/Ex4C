#include <stdlib.h>

#define NUM_LETTERS ((int)26)

typedef enum
{
   FALSE = 0,
   TRUE = 1
} boolean;

#ifndef Node
#define Node

typedef struct node
{

   char letter;
   long unsigned int count;
   struct node *children[NUM_LETTERS];
   boolean isEndOfWord;
   boolean hasChild;

} node;
#endif

//The function prints an error in case of memory allocation error
void alloctionError()
{

   printf("Memory allocation ERROR!\n");
   exit(1);
}

//The function allocates space in memory for the node
node *newNode()
{
   node *n;
   if (!(n = (node *)malloc(sizeof(node))))
      alloctionError();

   return n;
}

//The function initializing the node
node *resetNode(node *n, char ch)
{
   int i;
   n->letter = ch;
   n->count = 0;
   n->hasChild = FALSE;
   n->isEndOfWord = FALSE;
   for (i = 0; i < NUM_LETTERS; i++)
   {
      (n->children)[i] = NULL;
   }
   return n;
}

//The function creates a new node
node *createNode(char ch)
{
   node *createdNode;
   createdNode = newNode();
   return resetNode(createdNode, ch);
}

//The function free the memory of the node
void freeNode(node *n)
{
   int i;
   if (n == NULL)
   {
      return;
   }
   if ((n->hasChild) != 0)
   {
      for (i = 0; i < NUM_LETTERS; i++)
      {
         freeNode((n->children)[i]);
      }
   }
   free(n);
   return;
}

#ifndef Trie
#define Trie

typedef struct trie
{

   node *children[NUM_LETTERS];
   node *topical;
   char *word;
   int MaxWordLen;
   boolean empty;

} trie;
#endif

trie *newTrie();
trie *resetTrie(trie *t);
trie *createTrie();
void freeTrie(trie *t);
boolean isEmpty(trie *root);
int readL(trie *root, int c);
trie *readTxt();
void printWordsRev(trie *root);
void printTrieRev(trie *root);
void printW(trie *root);
void printT(trie *root);
