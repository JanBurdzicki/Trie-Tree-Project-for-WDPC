#include "Trie_Tree.h"

Trie_Tree* trie_tree_new()
{
	Trie_Tree* tree = NULL;

	tree = (Trie_Tree*) malloc(sizeof(Trie_Tree));

	if(tree == NULL)
	{
		print_error(stderr, "", "\n-----------------------------------\n");
		print_error(stderr, "ERROR", "Blad alokacji pamieci za pomoca funkcji malloc()!\n");
		print_error(stderr, "", "-----------------------------------\n\n");

		exit(EXIT_FAILURE);
	}

	tree->root = NULL;

	return tree;
}

static void trie_tree_free_subtree(Trie_Tree_Node* node)
{
	if(node == NULL)
	{
		return;
	}

	FOR(i, ALPHABET_SIZE)
	{
		trie_tree_free_subtree(node->next[i]);
	}

	free(node);
}

void trie_tree_free(Trie_Tree* tree)
{
	trie_tree_free_subtree(tree->root);

	free(tree);
}

Trie_Tree_Node* trie_tree_node_new()
{
	Trie_Tree_Node* node = NULL;

	node = (Trie_Tree_Node*) malloc(sizeof(Trie_Tree_Node));

	if(node == NULL)
	{
		print_error(stderr, "", "\n-----------------------------------\n");
		print_error(stderr, "ERROR", "Blad alokacji pamieci za pomoca funkcji malloc()!\n");
		print_error(stderr, "", "-----------------------------------\n\n");

		exit(EXIT_FAILURE);
	}

	FOR(i, ALPHABET_SIZE)
	{
		node->next[i] = NULL;
	}

	node->number_of_ending_words = 0;
	node->number_of_words_in_subtree = 0;

	return node;
}

int get_index(char sign)
{
	return sign - 'a';
}

void string_to_lower_case(char word[])
{
	FOR(i, strlen(word))
	{
		word[i] = tolower(word[i]);
	}
}

bool is_correct_index(int index)
{
	return (0 <= index && index < ALPHABET_SIZE);
}

bool trie_tree_insert(Trie_Tree* tree, char* word)
{
	string_to_lower_case(word);

	int size = strlen(word);

	FOR(i, size)
	{
		int index = get_index(word[i]);

		if(!is_correct_index(index))
		{
			return EXIT_FAILURE;
		}
	}

	Trie_Tree_Node** node = &tree->root;

	if(*node == NULL)
	{
		*node = trie_tree_node_new();
	}

	FOR(i, size)
	{
		int index = get_index(word[i]);

		if((*node)->next[index] == NULL)
		{
			(*node)->next[index] = trie_tree_node_new();
		}

		(*node)->number_of_words_in_subtree++;

		node = &((*node)->next[index]);
	}

	(*node)->number_of_words_in_subtree++;
	(*node)->number_of_ending_words++;

	return EXIT_SUCCESS;
}

Trie_Tree_Node* trie_tree_search_node(Trie_Tree* tree, char* word)
{
	string_to_lower_case(word);

	int size = strlen(word);

	Trie_Tree_Node* node = tree->root;

	if(node == NULL)
	{
		return NULL;
	}

	FOR(i, size)
	{
		int index = get_index(word[i]);

		if(!is_correct_index(index))
		{
			return NULL;
		}

		if(node->next[index] == NULL)
		{
			return NULL;
		}

		node = node->next[index];
	}

	return node;
}

int count_number_of_matching_words_in_trie_tree(Trie_Tree* tree, char* word)
{
	Trie_Tree_Node* node = trie_tree_search_node(tree, word);

	if(node == NULL)
	{
		return 0;
	}

	else
	{
		return node->number_of_ending_words;
	}
}

bool is_word_in_trie_tree(Trie_Tree* tree, char* word)
{
	return (count_number_of_matching_words_in_trie_tree(tree, word) > 0);
}

void trie_tree_remove_node(Trie_Tree_Node* node, char* word, int depth)
{
	if(word[depth] != '\0')
	{
		int index = get_index(word[depth]);

		Trie_Tree_Node* new_node = node->next[index];

		trie_tree_remove_node(new_node, word, depth + 1);

		if(new_node->number_of_words_in_subtree == 0)
		{
			node->next[index] = NULL;

			free(new_node);
		}
	}

	else
	{
		node->number_of_ending_words--;
	}

	node->number_of_words_in_subtree--;
}

bool trie_tree_remove(Trie_Tree* tree, char* word)
{
	Trie_Tree_Node* node_search = trie_tree_search_node(tree, word);

	if(node_search == NULL || node_search->number_of_ending_words == 0)
	{
		return EXIT_FAILURE;
	}

	string_to_lower_case(word);

	Trie_Tree_Node* node = tree->root;

	trie_tree_remove_node(node, word, 0);

	return EXIT_SUCCESS;
}

static void print_trie_subtree(Trie_Tree_Node* node, char word[], int depth)
{
	if(node->number_of_ending_words > 0)
	{
		print_text(stdout, "Slowo", "");
		printf("%s\t", word);
		print_text(stdout, "Ilosc", "");
		printf("%d\n", node->number_of_ending_words);
	}

	FOR(i, ALPHABET_SIZE)
	{
		if(node->next[i] != NULL)
		{
			word[depth] = i + 'a';

			print_trie_subtree(node->next[i], word, depth + 1);
		}
	}

	word[depth] = '\0';
}

void print_trie_tree(Trie_Tree* tree)
{
	Trie_Tree_Node* node = tree->root;

	if(node == NULL)
	{
		return;
	}

	char word[MAX_N];

	print_trie_subtree(node, word, 0);
}