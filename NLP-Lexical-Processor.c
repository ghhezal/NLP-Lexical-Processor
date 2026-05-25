#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define wordLen 50

typedef struct WordNode
{
    char word[wordLen];
    struct WordNode *next;
} WordNode;

typedef struct repeatedWords
{
    char word[wordLen];
    int frequency;
    struct repeatedWords *next;
} repeatedWords;

WordNode *head = NULL;
WordNode *tail = NULL;
repeatedWords *repeatedWordshead = NULL;





void addWord(char *str)
{
    WordNode *newNode = malloc(sizeof(WordNode));
    if (!newNode)
        return;
    strncpy(newNode->word, str, wordLen - 1);
    newNode->word[wordLen - 1] = '\0';
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

void tokenisation(char *text)
{
    char *token = strtok(text, " ,.!?\n\r");
    while (token != NULL)
    {
        addWord(token);
        token = strtok(NULL, " ,.!?\n\r");
    }
    printf("\ndone!\n\n");
}









bool isStopWord(char *word)
{
    char *stopWords[] = {
        "a", "an", "and", "are", "as", "at", "be", "but", "by",
        "for", "if", "in", "is", "it", "no", "not", "of", "on",
        "or", "such", "that", "the", "their", "then", "there",
        "these", "they", "this", "to", "was", "will", "with"};
    int stopWordsSize = sizeof(stopWords) / sizeof(char *);
    for (int i = 0; i < stopWordsSize; i++)
    {
        if (strcasecmp(word, stopWords[i]) == 0)
        {
            return true;
        }
    }
    return false;
}







void removeWord(WordNode **prev, WordNode **cur)
{
    WordNode *temp = *cur;
    if (*prev == NULL)
    {
        head = (*cur)->next;
    }
    else
    {
        (*prev)->next = (*cur)->next;
    }
    *cur = (*cur)->next;
    free(temp);
}

void removeStopWords()
{
    WordNode *cur = head, *prev = NULL;
    while (cur != NULL)
    {
        if (isStopWord(cur->word))
        {
            removeWord(&prev, &cur);
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
    printf("\ndone!\n\n");
}










void printWords()
{
    WordNode *pointer = head;
    if (pointer == NULL)
    {
        printf("\nList is empty!\n\n");
        return;
    }
    printf("\n| ");
    while (pointer != NULL)
    {
        printf("%s | ", pointer->word);
        pointer = pointer->next;
    }
    printf("\n\n");
}








void addWordSorted(char *word)
{
    repeatedWords *node = malloc(sizeof(repeatedWords));
    if (!node)
        return;

    strncpy(node->word, word, wordLen - 1);
    node->word[wordLen - 1] = '\0';
    node->frequency = 1;

    if (repeatedWordshead == NULL)
    {
        node->next = NULL;
        repeatedWordshead = node;
    }
    else
    {
        repeatedWords *cur = repeatedWordshead;
        repeatedWords *prev = NULL;
        while (cur != NULL && strcasecmp(word, cur->word) > 0)
        {
            prev = cur;
            cur = cur->next;
        }

        if (prev == NULL)
        {
            node->next = repeatedWordshead;
            repeatedWordshead = node;
        }
        else
        {
            node->next = prev->next;
            prev->next = node;
        }
    }
}

repeatedWords *existInrepeatedWords(char *word)
{
    repeatedWords *temp = repeatedWordshead;
    while (temp != NULL)
    {
        if (strcasecmp(temp->word, word) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void calculateRepeatedWords()
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    WordNode *temp = head;
    while (temp != NULL)
    {
        repeatedWords *found = existInrepeatedWords(temp->word);
        if (found != NULL)
        {
            found->frequency++;
        }
        else
        {
            addWordSorted(temp->word);
        }
        temp = temp->next;
    }
    printf("\ndone!\n\n");
}

void printFrequencies()
{
    repeatedWords *temp = repeatedWordshead;

    printf("\n%-20s | %s\n", "Word", "Frequency");
    printf("-------------------------------------\n");

    while (temp != NULL)
    {
        printf("%-20s | %d\n", temp->word, temp->frequency);
        temp = temp->next;
    }
    printf("-------------------------------------\n");
}








int main()
{
    int choice1, choice2;
    char text[1000] = {0};

    printf("1 for Read from 'input.txt'\n");
    printf("2 for Read from terminal\n");
    printf("Enter your choice: ");

    scanf("%d", &choice1);
    getchar();

    switch (choice1)
    {
    case 1:{
        FILE *file = fopen("input.txt", "r");
        if (file == NULL)
        {
            printf("Error.\n");
            return 0;
        }
        size_t stringLen = fread(text, sizeof(char), sizeof(text) - 1, file);
        text[stringLen] = '\0';
        fclose(file);
        printf("\ndone reading!.\n\n");
        break;
    } 
    case 2:{
         printf("Enter the text: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = 0;
        break;
    }
    default:
        printf("Invalid choice.\n");
        break;
    }

    sleep(1);
    system("cls");

    while (true)
    {
        printf("1 for Tokenisation\n2 for Removing Stop Words\n3 for Showing Words\n4 for Calculate and show Frequencies\n5 for Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice2);
        getchar();
        switch (choice2)
        {
        case 1:
            tokenisation(text);
            sleep(1);
            system("cls");
            break;
        case 2:
            removeStopWords();
            sleep(1);
            system("cls");
            break;
        case 3:
            system("cls");
            printWords();
            break;
        case 4:
            system("cls");
            calculateRepeatedWords();
            printFrequencies();
            break;
        case 5:
            system("cls");
            printf("goodbye\n");
            return 0;
        default:
            printf("Wrong input!\n");
            break;
        }
    }

    return 0;
}