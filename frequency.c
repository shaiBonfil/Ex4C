#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "frequency.h"

#define NUM_LETTERS ((int)26)

//The function allocates space in memory for the trie
trie *newTrie()
{
   trie *t;
   if (!(t = (trie *)malloc(sizeof(trie))))
      alloctionError();
   return t;
}

//The function initializing the trie
trie *resetTrie(trie *t)
{
   int i;
   for (i = 0; i < NUM_LETTERS; i++)
   {
      t->children[i] = NULL;
   }
   t->topical = NULL;
   t->empty = TRUE;
   t->MaxWordLen = 0;

   return t;
}

//The function creates a new trie
trie *createTrie()
{
   trie *createdTrie;
   createdTrie = newTrie();
   return resetTrie(createdTrie);
}

//The function free the memory of the trie
void freeTrie(trie *t)
{
   int i;
   if (t == NULL)
      return;
   for (i = 0; i < NUM_LETTERS; i++)
   {
      freeNode(t->children[i]);
   }
   free(t->word);
   free(t);
}

boolean isEmpty(trie *root)
{
   return root->empty;
}

//The function gets trie and character, checks if the character is alphabetic and build the trie.
//Returns the word length.
int readL(trie *root, int c)
{
   int index;
   int wordLen = 0;
   if (!(isalpha(c)))
   {
      if (c != ' ' && c != '\t' && c != '\n')
         return wordLen;
      if (root->topical == NULL)
         return wordLen;
      root->topical->count++;
      root->topical->isEndOfWord = TRUE;
      root->topical = NULL;
      return wordLen;
   }
   wordLen++;
   c = tolower(c);
   index = c - 'a';

   if (root->topical == NULL)
   {
      if (root->children[index] == NULL)
         root->children[index] = createNode(c);
      root->topical = root->children[index];
      root->empty = FALSE;
   }
   else
   {
      root->topical->hasChild = TRUE;
      if (root->topical->children[index] == NULL)
         root->topical->children[index] = createNode(c);
      root->topical = root->topical->children[index];
   }
   return wordLen;
}

//The function reads the list of words read in the input
trie *readTxt()
{
   int c;
   int wordLen;
   trie *root;
   root = createTrie();
   while ((c = getchar()) != EOF)
   {
      wordLen = readL(root, c);
      if (wordLen > root->MaxWordLen)
         root->MaxWordLen = wordLen;
   }
   free(root->word);
   if (!(root->word = (char *)malloc(1 + sizeof(char) * (root->MaxWordLen))))
      alloctionError();
   return root;
}

//The function print the list of words read in the input along with
//the number of occurrences per word sorted in descending lexicographic order
void printWordsRev(trie *root)
{
   int i;
   static int tmp = 0;
   node *topical;
   root->word[tmp++] = root->topical->letter;

   if (root->topical->hasChild)
   {
      for (i = NUM_LETTERS - 1; i >= 0; i--)
      {
         if (root->topical->children[i] == NULL)
            continue;
         topical = root->topical;
         root->topical = root->topical->children[i];
         printWordsRev(root);
         root->topical = topical;
      }
   }
   else
   {
      if (root->topical->isEndOfWord)
      {
         root->word[tmp] = '\0';
         printf("%s\t%ld\n", root->word, root->topical->count);
      }
      --tmp;
      return;
   }
   if (root->topical->isEndOfWord)
   {
      root->word[tmp] = '\0';
      printf("%s\t%ld\n", root->word, root->topical->count);
   }
   --tmp;
}

//The function print the list of words read in the input along with
//the number of occurrences per word sorted in descending lexicographic order
void printTrieRev(trie *root)
{
   int i;
   if (root == NULL)
      return;
   if (isEmpty(root))
      return;
   for (i = NUM_LETTERS - 1; i >= 0; i--)
   {
      if (root->children[i] == NULL)
         continue;
      root->topical = root->children[i];
      printWordsRev(root);
   }
}

//The function print the list of words read in the input
void printW(trie *root)
{
   int i;
   static int tmp = 0;
   node *topical;
   root->word[tmp++] = root->topical->letter;
   if (root->topical->isEndOfWord)
   {
      root->word[tmp] = '\0';
      printf("%s\t%ld\n", root->word, root->topical->count);
   }
   if (root->topical->hasChild)
   {
      for (i = 0; i < NUM_LETTERS; i++)
      {
         if (root->topical->children[i] == NULL)
            continue;
         topical = root->topical;
         root->topical = root->topical->children[i];
         printW(root);
         root->topical = topical;
      }
   }
   else
   {
      --tmp;
      return;
   }
   --tmp;
}

//The function prints the trie
void printT(trie *root)
{
   int i;
   if (root == NULL)
      return;
   if (isEmpty(root))
      return;
   for (i = 0; i < NUM_LETTERS; i++)
   {
      if (root->children[i] == NULL)
         continue;
      root->topical = root->children[i];
      printW(root);
   }
}

int main(int argc, char *argv[])
{
   trie *root;
   root = readTxt();

   if (argc > 1 && *(argv[1]) == 'r')
      printTrieRev(root);
   else if (argc == 1)
      printT(root);
   else
   {
      printf("Invalid input\n");
      exit(1);
   }
   freeTrie(root);
}