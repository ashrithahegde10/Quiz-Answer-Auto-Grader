#ifndef QUIZGRADER_H
#define QUIZGRADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 512
#define MAX_Q 100
#define HASH_SIZE 101

// -------------------- STRUCTURES --------------------
typedef struct TrieNode {
    struct TrieNode *children[26];
    int isEndOfWord;
} TrieNode;

typedef struct Entry {
    char question[MAX_LINE];
    char answer[MAX_LINE];
    struct Entry *next;
} Entry;

// -------------------- GLOBAL --------------------
extern Entry *hashTable[HASH_SIZE];

// -------------------- FUNCTION DECLARATIONS --------------------
void toLowerCase(char *str);
void trimNewline(char *str);

TrieNode *createTrieNode();
void insertTrie(TrieNode *root, char *word);
int searchTrie(TrieNode *root, char *word);

unsigned int hashFunction(char *str);
void insertHash(char *q, char *a);
char *searchHash(char *q);

float matchScoreUsingTrie(char *modelAns, char *studAns);
const char *generateFeedback(float score);   // NEW FUNCTION

#endif

