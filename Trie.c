#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_LETTERS ((int)26)

typedef enum
{
    FALSE,
    TRUE
} boolean;
typedef struct node
{
    char letter;
    boolean endOfword;
    char *word;
    long unsigned int count;
    struct node *children[NUM_LETTERS];
} node;

node *addNode(char l)
{
    node *n = (node *)malloc(sizeof(node));
    if (n != NULL)
    {
        for (int i = 0; i < NUM_LETTERS; i++)
        {
            n->children[i] = NULL;
        }
        n->count = 0;
        n->endOfword = FALSE;
        n->word = NULL;
        //adds a letter to the trie as a new node
        n->letter = l;
        return n;
    }
    exit(1);
}

node *addWord(node *root, char w)
{
    int num = 'a';
    char currentNode = tolower(w);
    int place = currentNode - num;
    if (root->children[place] == NULL)
    {
        node *nw = addNode(currentNode);
        if (root->word != NULL)
        {
            int place1 = strlen(root->word);
            nw->word = (char *)malloc(place1 + 2);
            if (nw->word == NULL)
                exit(1);
            for (int i = 0; i < place1; i++)
                nw->word[i] = root->word[i];
            //adds a new word to the trie
            nw->word[place1] = currentNode;
            nw->word[(place1 + 1)] = 0;
        }
        else
        {
            nw->word = (char *)malloc(2);
            if (nw->word == NULL)
                exit(1);
            nw->word[0] = currentNode;
            nw->word[1] = 0;
        }
        root->children[place] = nw;
        return root->children[place];
    }
    else
    {
        return root->children[place];
    }
}

void printTrie(node *root)
{
    if (root == NULL)
        return;
    if (root->endOfword != 0)
    {
        printf("%s %ld\n", root->word, root->count);
    }
    for (int i = 0; i < NUM_LETTERS; i++)
    //prints the trie in dictionary order
    {
        printTrie(root->children[i]);
    }
    //releases the memory that allocated to word
    free(root->word);
}

void printReversedTrie(node *root)
{
    if (root == NULL)
        return;

    for (int i = NUM_LETTERS - 1; i >= 0; i--)
    //prints the reverse trie
    {
        printReversedTrie(root->children[i]);
    }
    if (root->endOfword != 0)
    {

        printf("%s %ld\n", root->word, root->count);
    }
    //releases the memory that allocated to word
    free(root->word);
}
void freeRoot(node *root)
{
    if (root == NULL)
        return;
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        freeRoot(root->children[i]);
    }
    //releases the memory that allocated to root
    free(root);
}

int main(int argc, char *argv[])
{
    int counter;
    char w;
    node *root = (node *)malloc(sizeof(node));
    if (root == NULL)
        exit(1);
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        root->children[i] = NULL;
    }
    root->endOfword = FALSE;
    root->word = NULL;
    root->count = 0;
    node *poinRoo = root;

    while ((w = getchar()) != EOF)
    {
        counter = 0;
        poinRoo = root;
        while (!isspace(w))
        {
            if (isalpha(w))
            {
                poinRoo = addWord(poinRoo, tolower(w));
                counter++;
            }

            w = getchar();
        }
        if (counter != 0)
        {
            poinRoo->endOfword = TRUE;
            poinRoo->count++;
        }
    }

    if (argc == 1)
        printTrie(root);
    else if (argc == 2 && strcmp(argv[1], "r") == 0)
        printReversedTrie(root);

    freeRoot(root);
    return 0;
}
