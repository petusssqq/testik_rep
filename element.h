#ifndef ELEMENT_H
#define ELEMENT_H

#define MAX_NAME_LEN 50
#define MAX_SYMBOL_LEN 10

typedef struct Element {
    char name[MAX_NAME_LEN];
    char symbol[MAX_SYMBOL_LEN];
    float atomic_mass;
    int nuclear_charge;
} Element;

typedef struct Node {
    Element data;
    struct Node* next;
} Node;

// Прототипы функций
Node* create_node(Element elem);
void push_back(Node** tail, Element elem);
void print_list(Node* head);
void free_list(Node* head);
void save_to_file(Node* head, const char* filename);
Node* load_from_file(const char* filename);
Element* find_by_symbol(Node* head, const char* symbol);
Element* find_max_mass_by_first_letter(Node* head, char letter);
void delete_last(Node** head, Node** tail);
void print_element_header();
void print_element_row(Element elem, int row_num);

#endif