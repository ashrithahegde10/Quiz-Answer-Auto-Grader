#include "quizgrader.h"

Entry *hashTable[HASH_SIZE] = {NULL};
 
// -------------------- BASIC UTILS --------------------
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

void trimNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// -------------------- TRIE FUNCTIONS --------------------
TrieNode *createTrieNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->isEndOfWord = 0;
    for (int i = 0; i < 26; i++)
        node->children[i] = NULL;
    return node;
}

void insertTrie(TrieNode *root, char *word) {
    TrieNode *curr = root;
    for (int i = 0; word[i]; i++) {
        if (isalpha(word[i])) {
            int idx = tolower(word[i]) - 'a';
            if (!curr->children[idx])
                curr->children[idx] = createTrieNode();
            curr = curr->children[idx];
        }
    }
    curr->isEndOfWord = 1;
}

int searchTrie(TrieNode *root, char *word) {
    TrieNode *curr = root;
    for (int i = 0; word[i]; i++) {
        if (isalpha(word[i])) {
            int idx = tolower(word[i]) - 'a';
            if (!curr->children[idx])
                return 0;
            curr = curr->children[idx];
        }
    }
    return curr->isEndOfWord;
}

// -------------------- HASH FUNCTIONS --------------------
unsigned int hashFunction(char *str) {
    unsigned int hash = 0;
    for (int i = 0; str[i]; i++)
        hash = (hash * 31) + str[i];
    return hash % HASH_SIZE;
}

void insertHash(char *q, char *a) {
    unsigned int hash = hashFunction(q);
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    strcpy(newEntry->question, q);
    strcpy(newEntry->answer, a);
    newEntry->next = hashTable[hash];
    hashTable[hash] = newEntry;
}

char *searchHash(char *q) {
    unsigned int hash = hashFunction(q);
    Entry *temp = hashTable[hash];
    while (temp) {
        if (strcmp(temp->question, q) == 0)
            return temp->answer;
        temp = temp->next;
    }
    return NULL;
}

// -------------------- MATCHING USING TRIE --------------------
float matchScoreUsingTrie(char *modelAns, char *studAns) {
    TrieNode *root = createTrieNode();
    char temp[MAX_LINE];
    strcpy(temp, modelAns);
    toLowerCase(temp);

    char *word = strtok(temp, " ");
    int totalWords = 0, matched = 0;
    while (word) {
        insertTrie(root, word);
        totalWords++;
        word = strtok(NULL, " ");
    }

    char studTemp[MAX_LINE];
    strcpy(studTemp, studAns);
    toLowerCase(studTemp);
    word = strtok(studTemp, " ");
    while (word) {
        if (searchTrie(root, word))
            matched++;
        word = strtok(NULL, " ");
    }

    return totalWords ? (float)matched / totalWords : 0.0;
}

// -------------------- FEEDBACK FUNCTION --------------------
const char *generateFeedback(float score) {
    if (score >= 0.9)
        return "Excellent";
    else if (score >= 0.7)
        return "Good";
    else if (score >= 0.5)
        return "Average";
    else
        return "Poor";
}

