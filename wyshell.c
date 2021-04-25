#include"wyscanner.h"
#include"wyshellfunctions.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include<sys/wait.h>
/*
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
*/
int main(int argc, char* argv[]) {
 Node *head = NULL;
 Node *current = NULL;
 char *tokens[]={ "QUOTE_ERROR", "ERROR_CHAR", "SYSTEM_ERROR",
                "EOL", "REDIR_OUT", "REDIR_IN", "APPEND_OUT",
                "REDIR_ERR", "APPEND_ERR", "REDIR_ERR_OUT", "SEMICOLON",
                "PIPE", "AMP", "WORD" };
 char msg[1024];
 char *rpt;
 int parseLineInt = 0;
 int first,end ,outputredir, inputredir, errorredir, amp,amploc, pipe, pipeloc, lastgo;

 
 while(1) {
  head = NULL;
  current = NULL;
  int i =0;
  first = 0;
  end = 0;
  outputredir = 0;
  inputredir = 0;
  errorredir = 0;
  amp = 0;
  amploc = 0;
  pipe = 0;
  pipeloc = 0;
  lastgo = 0;
  end = 0;
  printf("$> ");
  rpt = fgets(msg,1024,stdin);
  //Error checking for user input
  if(rpt == NULL) {
   if(feof(stdin)) {
    return 0;
   }
    else {
     perror("fgets from stdin");
     return 1;
    }
   }
   //Parse the user input
   parseLineInt = parse_line(msg);
   
   while(parseLineInt != EOL && end != 1){ 
   i++;
   if(head == NULL) {
     //head = calloc(1,sizeof(Node));
     //head = malloc(sizeof(Node));
     current = head;
   }
   
   
      switch(parseLineInt) {
      	case APPEND_OUT:
      	//If there is no command before anything other then a ; give an error and stop reading
      	if(first == 0) {
   	    printf("ERROR NO COMMAND \n");
   	    end = 1;
     	  }
     	else {
          lastgo = 3;
        }
        break;
        case WORD:
           if(first == 0) {

            Node *firsttmp = (Node*)malloc(sizeof(Node));
            firsttmp->command = strdup(lexeme);
            firsttmp->next = NULL;
            if(head == NULL) {
              head = firsttmp;
              current = head;
            }
            else {
              current = head;
              while(current->next != NULL) {
                current = current->next;
              }
              current->next = firsttmp;
              current = firsttmp;
            }
            first = 1;
            lastgo = 1;
          }
          else if(outputredir == 1) {
            //current->out_file = lexeme;
            addOutFile(&current, strdup(lexeme));
            outputredir = 2;
            lastgo = 1;
          } 
          else if(inputredir == 1) {
            //current->in_file = lexeme;
            addInFile(&current, strdup(lexeme));
            inputredir = 2;
            lastgo = 1;
          }
          else if(errorredir == 1) {
            //current->err_file = lexeme;
            addErrFile(&current, strdup(lexeme));
            errorredir = 2;
            lastgo = 1;
          }
          else {
            if(current->arg_list == NULL) {
              
              addArg(&current->arg_list, strdup(lexeme));
            }
            else {
              addArg(&current->arg_list, strdup(lexeme));
            }
            
          }
        
        break;      
        case PIPE:
          if(first == 0) {
   	    printf("ERROR NO COMMAND \n");
   	    end = 1;
     	  }
     	  else {
          
          pipe++;
          //first = 0;
          lastgo = 2;
          pipeloc = i;
        }
        break;
        case SEMICOLON:
          
          current->output = 1;
          first = 0;
        break;
        case REDIR_IN:
          if(first == 0) {
            printf("ERROR NO COMMAND \n");
   	    end = 1;
     	  }  
     	  else if (inputredir != 1 && inputredir != 2){
            inputredir = 1;
            lastgo = 3;
          }
          else {
            printf("TO MANY INPUT REDIR \n");
            end = 1;
          }
        break;
        case REDIR_OUT:
        if(first == 0) {
   	    printf("ERROR NO COMMAND \n");
   	    end = 1;
     	}
     	else if(outputredir != 1 && outputredir != 2){
          outputredir = 1;
          lastgo = 3;
        }
        else {
          printf("TO MANY OUTPUT REDIR \n");
          end = 1;
        }
        break;
        case REDIR_ERR:
        if(first == 0) {
   	    printf("ERROR NO COMMAND \n");
   	    end = 1;
     	}
     	else if(errorredir != 1 && errorredir != 2){
          errorredir = 1;
          lastgo = 3;
        }
        else {
          printf("TO MANY ERR REDIR \n");
          end = 1;
        }
        break;
        case APPEND_ERR:
        if(first == 0) {
   	    printf("ERROR NO COMMAND \n");
   	    end = 1;
     	}
     	else {
          lastgo = 3;
        }
        break;
        case AMP:
        if(first == 0) {
   	    printf("ERROR NO COMMAND \n");
   	    end = 1;
     	} 
     	else if (amp != 1){
          current->amp = 1;
          lastgo = 4;
          amploc = i;
        }
        break;
        case SYSTEM_ERROR:
          perror("system error");
          return -1;
        break;
        case ERROR_CHAR:
          printf("%d: %s\t =%d\n",parseLineInt,tokens[parseLineInt%96],error_char);
          
        break;
        case QUOTE_ERROR:
          printf("%d: %s\t \n",parseLineInt,tokens[parseLineInt%96]);
        break;
        default:
          printf("%d: %s\n",parseLineInt,tokens[parseLineInt%96]); 
      }
     
      parseLineInt=parse_line(NULL);
    }
    
    //printArg(current->arg_list);
    //printCom(current);
    
    //If the last thing in the string was a word its fine
    if(lastgo == 1) {
    
    }
    //If the last thing in the string was a | then return a semantic error
    else if(lastgo == 2) {
     printf("ERROR: Must have a command after | \n");
    }
    //If the last thing in the string was a redir then return a semantic error
    else if(lastgo == 3) {
     printf("ERROR: Must have a filename after a redir / append \n");
    }
    //If there was an & before the | return a semantic error
    else if(amploc != 0 && pipeloc != 0 && amploc < pipeloc) {
     printf("ERROR: Background task must be the last task");
    }
      Node *temp = NULL;
      temp = head;
      while(temp != NULL) {
        
        if(temp->command == NULL) {
          printf("temp com was NULL");
          temp = temp->next;
        }
        else {
        int rtn;
        int arsize = findarrsize(current->arg_list);
        Word* p = temp->arg_list;
        char **argarr;
        argarr = calloc(arsize+2,sizeof(char*));
        int k = 1;
        argarr[0] = temp->command;
        while(p != NULL) {
          argarr[k] = p->string;
          
          k++;
          p = p->next;
        
        }
        argarr[arsize+1] = NULL;
          int pid = fork();
          if(pid == -1) {
            perror("Bad Fork");
            return -1;
          }
          else if(pid == 0) {
            execvp(temp->command, argarr);
          }
          else if(lastgo != 4 || current->amp != 1){
            rtn=waitpid(-1,NULL,0);
            while(rtn > 0) {
              rtn = waitpid(-1,NULL,0);
            }
          }
          
        }
        temp = temp->next;
      }
 }
}
