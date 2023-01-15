#include "Messages_Printing.h"
#include "Input_Handling.h"
#include "Trie_Tree.h"
#include "Libraries_And_Macros.h"

int main(int argc, char* argv[])
{
	// color_messages_printing_test();

	Trie_Tree* tree = trie_tree_new();

	read_data(tree, argc, argv);

	trie_tree_free(tree);

	return 0;
}