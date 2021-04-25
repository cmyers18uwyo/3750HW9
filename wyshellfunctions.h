#ifndef __WYSHELL_HELP_FUNCTION__
#define __WYSHELL_HELP_FUNCTION__
typedef struct node Node;
typedef struct word Word;
struct node {
 struct node *next, *prev;
 char *command;
 Word *arg_list;
 int input, output, error, amp;
 char *in_file, *out_file, *err_file;
};
struct word {
 struct word *next, *prev;
 char *string;
};

void addInFile(Node **head, char* infile);
void addOutFile(Node **head, char* outfile);
void addErrFile(Node **head, char* errfile);
void addCommand(Node **head, char* com);
void addArg(Word **head,char* arg);
void printArg(Word* head);
void printCom(Node* head);
void printInFile(Node* head);
int findarrsize(Word* head);
//char * argArray(Word* head, int arrsize);
void nodeStart(Node **head);
#endif



