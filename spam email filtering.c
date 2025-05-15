#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// node struct for linked list which handles collisions in hash table
struct node {
 char *word;
 struct node *next;
};

int tablesize;               // size of hash table
struct node **hashtable;     // pointer to hash table (array of node pointers)

// A simple hash function which returns sum of ascii values % tablesize
int hashfunction(char *word) {
 int sum = 0;
 for (int i = 0; word[i] != '\0'; i++) {
  sum += word[i];
 }
 return sum % tablesize;
}

// insert a word into hash table using chaining
void insert(char *word) {
 int index = hashfunction(word);
 struct node *newnode = (struct node*)malloc(sizeof(struct node));
 newnode->word = (char*)malloc(strlen(word) + 1);
 strcpy(newnode->word, word);
 newnode->next = hashtable[index];
 hashtable[index] = newnode;
}

// search for a word in the hash table and return true if found
bool search(char *word) {
 int index = hashfunction(word);
 struct node *temp = hashtable[index];
 while (temp) {
  if (strcmp(temp->word, word) == 0) {
   return true;
  }
  temp = temp->next;
 }
 return false;
}

// initialize hash table and load spam words into it
void loadspamwords(char **spamwords, int count) {
 tablesize = count * 2;  // choose size double spam list for less collisions
 hashtable = (struct node**)malloc(tablesize * sizeof(struct node*));
 for (int i = 0; i < tablesize; i++) {
  hashtable[i] = NULL;
 }
 for (int i = 0; i < count; i++) {
  insert(spamwords[i]);
 }
}

// convert a word to lowercase (for case-insensitive matching)
void tolowercase(char *word) {
 for (int i = 0; word[i] != '\0'; i++) {
  if (word[i] >= 'A' && word[i] <= 'Z') {
   word[i] = word[i] - 'A' + 'a';
  }
 }
}

// check if email contains any spam words (no realloc, no fixed-size defines)
bool isspam(char *email) {
 char *word = (char *)malloc(1);
 int wordlen = 0;

 for (int i = 0; email[i] != '\0'; i++) {
  char ch = email[i];

  if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
   if (ch >= 'A' && ch <= 'Z') {
    ch = ch - 'A' + 'a';
   }
   // allocate new buffer and copy old word + new char
   char *temp = (char *)malloc(wordlen + 2);
   for (int j = 0; j < wordlen; j++) {
    temp[j] = word[j];
   }
   temp[wordlen++] = ch;
   temp[wordlen] = '\0';
   free(word);
   word = temp;
  } else {
   if (wordlen > 0) {
    if (search(word)) {
     free(word);
     return true;
    }
    free(word);
    word = (char *)malloc(1);
    word[0] = '\0';
    wordlen = 0;
   }
  }
 }
 if (wordlen > 0) {
  if (search(word)) {
   free(word);
   return true;
  }
 }
 free(word);
 return false;
}

// free all dynamically allocated memory in the hash table
void freehashtable() {
 for (int i = 0; i < tablesize; i++) {
  struct node *temp = hashtable[i];
  while (temp) {
   struct node *next = temp->next;
   free(temp->word);
   free(temp);
   temp = next;
  }
 }
 free(hashtable);
}

int main() {
 char *spamlist[] = {"lottery", "free", "money", "win", "offer", "lucky"};
 int spamcount = sizeof(spamlist) / sizeof(spamlist[0]);

 loadspamwords(spamlist, spamcount);

 char *email = NULL;
 size_t size = 0;
 printf("enter email content:\n");
 getline(&email, &size, stdin);

 if (isspam(email)) {
  printf("result: spam\n");
 } 
 else {
  printf("result: not spam\n");
 }

 free(email);
 freehashtable();

 return 0;
}

