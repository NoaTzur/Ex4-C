#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
//#include <aclapi.h>
#include <stdlib.h>

#define end_of_word 36 //represents $ in ASCII
#define num_of_chars 26
int maxLen = 0;

typedef struct node{
    char letter;
    long unsigned int num_of_appearance;
    struct node *children[num_of_chars];
    char end; //remark if this node is a leaf (means that there is a word that ends here)
    int num_of_children;
}node;

node* new_node(char c){
    struct node* n = (node*)malloc(sizeof (struct node));
    n -> num_of_appearance =0;
    n -> letter = c;
    n -> num_of_children =0;
    for (int i = 0; i < num_of_chars; i++) {
        n -> children[i] = NULL;
    }
    return n;
}

void clean_trie(node** root){
    if (*root){
        for (int i = 0; i < num_of_chars; i++) {
            if((*root) -> children[i]){ //not null - there is a children in index i
                clean_trie(&((*root)->children[i]));
            }
            else {
                continue;
            }
        }
        free(*root); //we can free the whole node because the array in it is not allocated with malloc
    }
}

void printAllWords(node **root, char words[maxLen], int index, int reverse) {
    if((*root) == NULL){
        return;
    }

    if(((*root)->end) == end_of_word && reverse==0){
        if(strlen(words)> index){
            words[index] = '\0';
        }
        if(strlen(words) !=0){
        printf("%s\t%lu\n", words, (*root)->num_of_appearance);
        }
    }

    if(reverse) {
        for (int i = num_of_chars - 1; i >= 0; i--) {
            if ((*root)->children[i] != NULL) {
                words[index] = (*root)->children[i]->letter;
                printAllWords(&((*root)->children[i]), words, index + 1, reverse);
            }
        }
    }
    else{ //reverse == 0
        for (int i = 0; i < num_of_chars; i++) {
            if((*root)->children[i] != NULL){
                words[index] = (*root)->children[i]->letter;
                printAllWords(&((*root)->children[i]), words, index+1, reverse);
            }
        }
    }

    if(((*root)->end) == end_of_word && reverse==1){
        if(strlen(words)> index){
            words[index] = '\0';
        }
         if(strlen(words) !=0){
        printf("%s\t%lu\n", words, (*root)->num_of_appearance);
        }
    }
}


int main(int argc, char *argv[]) {
    struct node* root = new_node('h');

   struct node* fixTheRoot = &(*root);
    int reverse=0;

    if (argc >1 && strcmp("r", argv[1]) == 0){
        reverse = 1;
    }

    char letter='y';
    int wordLen=0;
    while (scanf("%c", &letter) != EOF) {
        if(letter == ' ' || letter == '\n'){
            wordLen =0;
            root -> end = end_of_word;
            root -> num_of_appearance++;
            root = fixTheRoot; //turn back to the head, now ready for new word to insert
        }
        else{
            int index_of_letter = 0;
            if(letter > 96 && letter < 123){
                wordLen++;
                index_of_letter = (int)letter - 'a';

            }
            else if(letter > 64 && letter < 91){
                wordLen++;
                index_of_letter = (int) (letter + ' ') - 'a';
            }
            else{
                continue;
            }
            if ((root->children[index_of_letter]) == NULL) { //there is no "char child" in the array
                root->children[index_of_letter] = new_node(letter);
                root->num_of_children++;
            }
            root = root->children[index_of_letter]; //brings the next child that will holds the next char in word

            if (wordLen > maxLen)
                maxLen = wordLen;
        }

    }
    root -> end = end_of_word;
    root -> num_of_appearance++;
    root = fixTheRoot;
    char words[maxLen];
    printAllWords(&root, words, 0, reverse);
    clean_trie(&root);
    return 0;

}
