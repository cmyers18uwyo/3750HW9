#include"wyshellfunctions.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>
void addInFile(Node **head, char* infile) {
  //Node *new_node = (Node*)malloc(sizeof(Node));
  //new_node->in_file = infile;
  if(*head == NULL) {
    return;
  }
  else {
    Node *last_node = *head;
    while(last_node->next != NULL) {
      last_node = last_node->next;
      
    }
    last_node->in_file = infile;
  }
  return;

}
void addOutFile(Node **head, char* outfile) {
  if(*head == NULL) {
    return;
  }
  else {
    Node *last_node = *head;
    while(last_node->next != NULL) {
      last_node = last_node->next;
      
    }
    last_node->out_file = outfile;
  }
  return;

}
void addErrFile(Node **head, char* errfile) {
  //Node *new_node = (Node*)malloc(sizeof(Node));
  //new_node->in_file = infile;
  if(*head == NULL) {
    return;
  }
  else {
    Node *last_node = *head;
    while(last_node->next != NULL) {
      last_node = last_node->next;
      
    }
    last_node->err_file = errfile;
  }
  return;

}
void nodeStart(Node **head) {
  
  Node *tmp = *head;

  while(tmp->prev != NULL) {
    tmp = tmp->prev;
    printf("while loop ran \n");
  }
}
void addCommand(Node **head, char* com) {
  
  Node *new_node = (Node*)malloc(sizeof(Node));
  Node * temp = *head;
  new_node->command = com;
  new_node->next = NULL;
  if(temp->command == NULL) {
    *head = new_node;
  }
  else {
    Node *last_node = *head;
    while(last_node->next != NULL) {
      last_node = last_node->next;
      
    }
    last_node->next = new_node;
  }
  return;
}
void addArg(Word **head,char* arg) {
  Word *new_word = (Word*)malloc(sizeof(Word));
  new_word->string = arg;
  int i = 0;
  new_word->next = NULL;
  if(*head == NULL) {
    *head = new_word;
    return;
  }
  else {
    Word *last_word = *head;
    while(last_word->next != NULL) {
      last_word = last_word->next;
      i++;
      
    }
    last_word->next = new_word;
  }
  return;
}
void printArg(Word* head) {
  Word* temp = head;
  int i = 0;
  while(temp != NULL) {
    i++;
    printf("%s", temp->string);
    
    printf("\n");
    temp = temp->next;
    }
}
void printCom(Node* head) {
  Node* temp = head;
  while(temp != NULL) {
   
    printf("%s", temp->command);
    printf("\n");
    temp = temp->next;
    }

}
void printInFile(Node* head) {
  Node* temp = head;
  while(temp != NULL) {
   
    printf("%s", temp->in_file);
    printf("\n");
    temp = temp->next;
    }

}
int findarrsize(Word* head) {
  int i = 1;
  Word * tmp = head;
  while(tmp->next != NULL) {
    i++;
    tmp = tmp->next;
  }
  return i;
}
/*char * argArray(Word* head, int arrsize) {
  
  char *argarr[arrsize];
  
  Word * tmp = head;
  int i = 0;
  while(tmp != NULL) {
    argarr[i] = tmp->string;
    tmp = tmp->next;
    i++;
  
  }

  
  return argarr;
}
*/
