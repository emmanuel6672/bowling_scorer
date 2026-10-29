#include "queue.h"
#include "tpb.h"
#include <stdlib.h> /* you probably need this */
#include <stdio.h>  /* you definitely need this */
#include <ctype.h>
#include <string.h>

/* add other headers from the CSTDLIB needed */

/* define my boolean type */

#define true 1
#define false 0
typedef int bool;

#define FRAME_NUMBER 10 /* you may need this */

/* Accepted Tokens */
typedef enum {
  TOKEN_LITERAL,      /* Number 0-9 */
  TOKEN_SPARE,        /* / symbol */
  TOKEN_STRIKE,       /* X/x symbol */
  TOKEN_GUTTER,       /* - symbol */
  TOKEN_FAULT        /* F/f symbol */
} Token;

/* Struct for the lexical tokenization */
typedef struct
{
  Token token;
  char character;
  int lookahead;
  int pos;
} Lex;

/* I implement a few functions to help you */
void print_s(void *data);
void print_s2(void *data);
void print_linked_list2(LinkedList *list, void (*print_func)(void *));

void free_scoreboard(LinkedList *scoreboard)
{
  Node * next = scoreboard->head;
  while (next!=NULL)
  {
    free(next->data);
    next = next->next;
  }

  free_linked_list(scoreboard);
}

/* 
This function is not in the tpb.h, because it doesn't need to be externalised
Given a token of a roll, it return its value. prev_roll is the token of the
previous roll necessary to computer the spare
 */
int get_token_value(Lex* token, Lex * prev_roll)
{
  if (token!= NULL)
  {
    switch (token->token)
    {
      case TOKEN_STRIKE:
        return 10;
      case TOKEN_SPARE:
        if (prev_roll!= NULL)  return 10-get_token_value(prev_roll,NULL); 
        else break;
      case TOKEN_LITERAL:
        return token->character - '0';
      default: /* GUTTER / FAULT*/
        return 0;
    }

  }

  return -1; /* in case on an error */
}

/*
This function performs the tokenization
Also this one is not in the tpb.h as it's not needed to be seen outside

The purpose of this function is that, given a character, it makes the 
corresponding token. The struct Lex l is where the values are stored
because the function returns true in case of success, false otherwise.

*/

bool tokenization(char c, Lex *l)
{

    switch (c)
    {
      case 'x':
      case 'X':
        l->token = TOKEN_STRIKE;
        l->character = c;
        l->lookahead=2;
        break;
      case 'f':
      case 'F':
        l->token = TOKEN_FAULT;
        l->character = c;
        l->lookahead=0;
        break;
      case '-':
        l->token = TOKEN_GUTTER;
        l->character = c;
        l->lookahead=0;
        break;
      case '/':
        l->token = TOKEN_SPARE;
        l->character = c;
        l->lookahead=1; 
        break;
      default:
        if (isdigit(c) && (c!='0'))
        {
          l->token = TOKEN_LITERAL;
          l->character = c;
          l->lookahead=0;
        }
        else return false;
    }

    return true;
}




LinkedList *bowling_score_parser(const char *game_characters, int *err_position) 
{
  /* initialzation */
  LinkedList *list = initialise_linked_list();
  LinkedList *list_1 = initialise_linked_list();
  Queue *queue = initialise_queue();
  int i = 0;
  int tmp = 0;
  int tmp2 = 0;
  int game = 0;
  int score_num = 0;
  char score[6] = {"0"};
  char *copy, *copy2;
  int *LH, *score_n;
  Lex lex;
  Lex *cur, *prev;
  Node *next;

  /* Lexer */
  while (game_characters[i] != '\0' ) {
    tokenization(game_characters[i], &lex);
    lex.pos = i;
    push_queue(queue, &lex, sizeof(lex));
    i++;    
  }

  /* parser */
  i = 0;
  while (game_characters[i] != '\0' ) { /*this is used to go through each item in the input*/
    if (game == 9) { /*this is used to out input the rest of the characters in the input into the final frame*/
      score[4] = ' ';
      score[2] = ' ';
      game++;
      while (game_characters[i] != '\0' && tmp < 5) {
        tmp2++;
        score[tmp] = game_characters[i++];
        if (isalpha(score[tmp]) && !(score[tmp] == 'x' || score[tmp] == 'X' || score[tmp] == '-' 
            || score[tmp] == 'f' || score[tmp] == 'F' || score[tmp]   == '/')) { /*this is is used to check if it has the correct characters as an input*/
          *err_position = --i;
          free_queue(queue);
          free_scoreboard(list);
          free_scoreboard(list_1);
          return NULL;
        }
        
        if ((tmp2 == 1 && score[tmp] == '/') || (tmp2 == 2 && (score[tmp] == 'x' || score[tmp] == 'X'))) { /*this is is used to check if it has the correct characters as an input*/
          *err_position = --i;
          free_queue(queue);
          free_scoreboard(list);
          free_scoreboard(list_1);
          return NULL;
        }
        else if (score[tmp] == 'x' || score[tmp] == 'X' || score[tmp] == '/') { /*this is is used to check if it has the correct characters as an input*/
          tmp2 = 0;
        }

        if (tmp2 == 3) {
          *err_position = --i;
          free_queue(queue);
          free_scoreboard(list);
          free_scoreboard(list_1);
          return NULL;
        }
        tmp+=2;
      }
      score[1] = ' ';
      score[3] = ' ';
      score[6] = '\0';
      copy = malloc(strlen(score) + 1); /*these are used to copy the score and to append it*/
      strcpy(copy, score);              /*it needs a copy bc it will copy the pointer otherwise which will have the final value and to the data*/
      append_linked_list(list, copy);
      break; /*this is used to stop the loop*/
    }
    else if (game_characters[i] == 'x' || game_characters[i] == 'X') { /*this is used to format a strike*/
      score[0] = game_characters[i];
      i++;
      score[1] = ' ';
      score[2] = ' ';
      score[3] = '\0';
      game++;
      copy = malloc(strlen(score) + 1);
      strcpy(copy, score);
      append_linked_list(list, copy);
    }
    else{ /*this is used to format a anything else*/
      score[0] = game_characters[i];
      i++;
      if (score[0] == '/') { /*this is used to check that the / is placed correctly*/
        *err_position = --i;
        free_queue(queue);
        free_scoreboard(list);
        free_scoreboard(list_1);
        return NULL;
      }
      else if (isalpha(score[0]) && !(score[0] == 'x' || score[0] == 'X' || score[0] == '-' || score[0] == 'f' || score[0] == 'F' || score[0] == '/')) {
        *err_position = --i;
        free_queue(queue);
        free_scoreboard(list);
        free_scoreboard(list_1);
        return NULL;
      }
      score[1] = ' ';
      score[2] = game_characters[i];
      if (score[2] == '\0') {
        score[2] = ' ';
      }
      else {
        i++;
      }
      if (score[2] == 'x' || score[2] == 'X' || score[2] == '\0') { /*this is used to check that the x is placed correctly*/
        *err_position = --i;
        free_queue(queue);
        free_scoreboard(list);
        free_scoreboard(list_1);
        return NULL;
      }
      else if (isalpha(score[2]) && !(score[2] == 'x' || score[2] == 'X' || score[2] == '-' || score[2] == 'f' || score[2] == 'F' || score[2] == '/')) {
        *err_position = --i;
        free_queue(queue);
        free_scoreboard(list);
        free_scoreboard(list_1);
        return NULL;
      }
      score[3] = '\0';
      game++;
      copy = malloc(strlen(score) + 1);
      strcpy(copy, score);
      append_linked_list(list, copy);
    }
  }
  
  /* reducer */
  prev = NULL;
  next = queue->head;
  cur = next->data;
  tmp = 0;
  i = 0;
  if (!( LH = ( int *) calloc (64 , sizeof ( int ))) ||
      !( score_n = ( int *) calloc (64 , sizeof ( int )))) { /*this is used to make the dynamic variables*/
    free_queue(queue);
    free_scoreboard(list);
    free(LH);
    free(score_n);
    free_scoreboard(list_1);
    return NULL;
  }

  while (next != NULL) { /*this is used to variable that are needed from the queue*/
    tmp = get_token_value(cur, prev);
    prev = cur;
    LH[i] = cur->lookahead;
    score_n[i] = tmp;
    next = next->next;
    if (next != NULL) {
      cur = next->data;
    }
    else {
      cur = NULL;
    }
    i++;
  }

  if (game <= 10) { /*this is used to ensure that it prints of the correct amount of games*/
    game--;
  }

  i = 0;
  tmp2 = 0;
  while (LH[i] || LH[i] <= 0) {
    /*these are use to ensure that if the reach the end they have the correct data*/
    if (score_n[i+1]) {
      tmp = score_n[i+1];
    }
    else {
      tmp = 0;
    }

    if (score_n[i+2]) {
      tmp2 = score_n[i+2];
    }
    else {
      tmp2 = 0;
    }

    if (LH[i] == 2) { /*this is used to process a strike*/
      score_num += score_n[i] + tmp + tmp2;
      i++;
    }
    else if (LH[i] + LH[i+1] == 1) { /*this is used to process a spare*/
      score_num += score_n[i] + tmp + tmp2;
      i+=2;
    }
    else if (LH[i] + LH[i+1] == 0) { /*this is used to process a normal roll*/
      score_num += score_n[i] + score_n[i+1];
      i+=2;
    }
    if (game < 0) { /*this is used to make it process only ten games*/
      break;
    }
    /*these are used to push the data into a linked list*/
    copy2 = malloc(strlen(score) + 1);
    sprintf(copy2, "%d", score_num);
    append_linked_list(list_1, copy2);
    game--;
  }

  /*this is used to change how the code is compilied depending on the compilation command*/
  #ifdef SCOREBOARD /*this is if the command has -DSCOREBOARD*/
  printf("+-----------------------------------------+\n");
  printf("|");
  print_linked_list2(list, print_s2);
  printf("\n");
  #else
  printf("%s:", game_characters);
  #endif

  /* Garbage collection */
  free_scoreboard(list);
  free_queue(queue);
  free(LH);
  free(score_n);
  free(next);
  
  return list_1;
}

#ifdef SCOREBOARD
void print_scoreboard(LinkedList *scoreboard)/*this is used to print the bottom half of other vertion*/
{
  printf("|");
  print_linked_list2(scoreboard, print_s2);
  printf("\n");
  printf("+-----------------------------------------+\n");
}
#else
void print_scoreboard(LinkedList *scoreboard)
{
  print_linked_list(scoreboard, print_s);
  printf("\n");
}
#endif

void print_s(void *data) {
  char *str = data;
  printf(" %s", str);
}

void print_s2(void *data) { /*this is used to the answer in the correct format*/
  char *str = data;
  int len = strlen(str);
  int i;
  for (i = 3; i > len; i--) {
    printf(" ");
  }
  printf("%s|", str);
}

void print_linked_list2(LinkedList *list, void (*print_func)(void *)) { /*this is used to the answer in the correct format but for the other version*/
	Node *next = list->head;
  char str[16];
  int num = 0;

	while(next) {
    strcpy(str, next->data);
    if (str[1] != ' ') { /*this is used for formating for the second line*/
      if (strlen(str) < 5 && num == 9) {
        printf("  ");
      }
    }
		(*print_func)(next->data);
		next = next->next;
    num++;
	}

  /*these are use to fill in the space if its empty*/
  while (num < 9) {
    printf("   |");
    num++;
  }

  if (num == 9) {
    printf("     |");
  }
}
