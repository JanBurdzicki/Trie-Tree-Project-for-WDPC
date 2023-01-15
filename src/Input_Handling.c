#include "Input_Handling.h"

#define NUMBER_OF_OPERATIONS 6

char* operations[NUMBER_OF_OPERATIONS] = {
	"insert WARTOSC",
	"delete WARTOSC",
	"search WARTOSC",
	"count WARTOSC",
	"print",
	"quit"
};

char* operation_description[NUMBER_OF_OPERATIONS] = {
	"wstawia WARTOSC do drzewa Trie\n",
	"usuwa WARTOSC z drzewa Trie (jesli WARTOSC znajduje sie w drzewie Trie)\n",
	"sprawdza czy WARTOSC znajduje sie w drzewie Trie (\"NIE\" jesli nie ma WARTOSCI w drzewie Trie, \"TAK\" jesli WARTOSC jest w drzewie Trie)\n",
	"zwraca ilosc wystapien WARTOSCI w drzewie Trie\n",
	"wypisuje wszystkie slowa (ktore wystepuja w drzewie Trie) i ich ilosci\n",
	"konczy wczytywanie danych\n"
};

void print_operations(FILE* stream)
{
	print_text(stream, "", "Mozliwe polecenia:\n");

	FOR(i, NUMBER_OF_OPERATIONS)
	{
		print_text(stream, operations[i], operation_description[i]);
	}

	print_text(stream, "", "\n");
	print_text(stream, "UWAGA!", "WARTOSC musi zawierac tylko litery alfabetu angielskiego, wielkosc liter nie ma znaczenia\n\n");
}

void read_data(Trie_Tree* tree, int argc, char* argv[])
{
	print_operations(stdout);

	FOR(i, 1, argc - 1)
	{
		FILE* file = fopen(argv[i], "r");

		if(file == NULL)
		{
			print_error(stderr, "", "\n-----------------------------------\n");
			print_error(stderr, "ERROR", "Blad podczas otwieraniu pliku!\nSciezka do pliku: ");
			print_error(stderr, "", argv[i]);
			print_error(stderr, "", "\n");
			print_error(stderr, "", "-----------------------------------\n\n");

			continue;
		}

		char word[MAX_N];

		while(fscanf(file, "%s", word) == 1)
		{
			fprintf(stderr, "%s\n", word);

			bool is_insert_failed = trie_tree_insert(tree, word);

			if(is_insert_failed)
			{
				print_error(stderr, "", "\n-----------------------------------\n");
				print_error(stderr, "ERROR", "Niepoprawny format slowa (w slowie moga wystepowac tylko litery alfabetu angielskiego)!\n");
				print_error(stderr, "", "-----------------------------------\n\n");
			}
		}

		fprintf(stderr, "\n");

		fclose(file);
	}

	while(true)
	{
		char operation[100];
		scanf("%s", operation);

		if(strcmp(operation, "insert") == 0)
		{
			char word[MAX_N];
			scanf("%s", word);

			bool is_insert_failed = trie_tree_insert(tree, word);

			if(is_insert_failed)
			{
				print_error(stderr, "", "\n-----------------------------------\n");
				print_error(stderr, "ERROR", "Niepoprawny format slowa (w slowie moga wystepowac tylko litery alfabetu angielskiego)!\n");
				print_error(stderr, "", "-----------------------------------\n\n");
			}
		}

		else if(strcmp(operation, "delete") == 0)
		{
			char word[MAX_N];
			scanf("%s", word);

			bool is_delete_failed = trie_tree_remove(tree, word);

			if(is_delete_failed)
			{
				print_error(stderr, "", "\n-----------------------------------\n");
				print_error(stderr, "ERROR", "W Trie_Tree nie ma podanej wartosci!\n");
				print_error(stderr, "", "-----------------------------------\n\n");
			}
		}

		else if(strcmp(operation, "count") == 0)
		{
			char word[MAX_N];
			scanf("%s", word);

			printf("%d\n", count_number_of_matching_words_in_trie_tree(tree, word));
		}

		else if(strcmp(operation, "search") == 0)
		{
			char word[MAX_N];
			scanf("%s", word);

			if(is_word_in_trie_tree(tree, word))
			{
				printf("TAK\n");
			}

			else
			{
				printf("NIE\n");
			}
		}

		else if(strcmp(operation, "print") == 0)
		{
			print_trie_tree(tree);
		}

		else if(strcmp(operation, "quit") == 0)
		{
			break;
		}

		else
		{
			system("clear");

			print_error(stderr, "", "\n-----------------------------------\n");
			print_error(stderr, "ERROR", "Bledne polecenie!\n");
			print_error(stderr, "", "Wpisz poprawne polecenie!\n");
			print_error(stderr, "", "-----------------------------------\n\n");

			print_operations(stderr);
		}
	}
}