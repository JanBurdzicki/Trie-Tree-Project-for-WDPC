#ifndef TRIE_TREE_H
#define TRIE_TREE_H

#include "Messages_Printing.h"
#include "Libraries_And_Macros.h"

#define TRIE_TREE_NULL ((void *) 0)

typedef void *Trie_Tree_Node_Value;

struct Trie_Tree_Node
{
	struct Trie_Tree_Node* next[ALPHABET_SIZE];

	int number_of_ending_words;
	int number_of_words_in_subtree;
};

typedef struct Trie_Tree_Node Trie_Tree_Node;

struct Trie_Tree
{
	Trie_Tree_Node* root;
};

typedef struct Trie_Tree Trie_Tree;

Trie_Tree* trie_tree_new();
void trie_tree_free(Trie_Tree* tree);
bool trie_tree_insert(Trie_Tree* tree, char* word);
int count_number_of_matching_words_in_trie_tree(Trie_Tree* tree, char* word);
bool is_word_in_trie_tree(Trie_Tree* tree, char* word);
bool trie_tree_remove(Trie_Tree* tree, char* value);

void print_trie_tree(Trie_Tree* tree);

#endif