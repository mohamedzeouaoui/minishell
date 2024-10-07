/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:56:19 by asodor            #+#    #+#             */
/*   Updated: 2024/10/07 06:56:51 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_TOKEN_LENGTH 1024

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_APPEND,
} TokenType;

typedef struct Token {
    char *value;
    TokenType type;
    struct Token *next;
} Token;

typedef struct Command {
    Token *tokens;
    struct Command *next;
} Command;

Token *create_token(char *value, TokenType type) {
    Token *token = malloc(sizeof(Token));
    token->value = strdup(value);
    token->type = type;
    token->next = NULL;
    return token;
}

void add_token(Token **head, char *value, TokenType type) {
    Token *new_token = create_token(value, type);
    if (*head == NULL) {
        *head = new_token;
    } else {
        Token *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_token;
    }
}

void free_tokens(Token *head) {
    Token *current = head;
    while (current != NULL) {
        Token *temp = current;
        current = current->next;
        free(temp->value);
        free(temp);
    }
}

Token *tokenize_input(char *input) {
    Token *head = NULL;
    char *token_start = input;
    char token_value[MAX_TOKEN_LENGTH];
    int in_quotes = 0;
    char quote_char = '\0';

    while (*input != '\0') {
        if (!in_quotes && (*input == ' ' || *input == '|' || *input == '<' || *input == '>')) {
            if (token_start != input) {
                strncpy(token_value, token_start, input - token_start);
                token_value[input - token_start] = '\0';
                add_token(&head, token_value, TOKEN_WORD);
            }

            if (*input != ' ') {
                token_value[0] = *input;
                token_value[1] = '\0';
                TokenType type = (*input == '|') ? TOKEN_PIPE :
                                 (*input == '<') ? TOKEN_REDIRECT_IN :
                                 (*(input + 1) == '>') ? TOKEN_REDIRECT_APPEND : TOKEN_REDIRECT_OUT;
                add_token(&head, token_value, type);
                if (type == TOKEN_REDIRECT_APPEND) {
                    input++;  // Skip the next '>' character
                }
            }

            token_start = input + 1;
        } else if (*input == '\'' || *input == '"') {
            if (!in_quotes) {
                in_quotes = 1;
                quote_char = *input;
            } else if (*input == quote_char) {
                in_quotes = 0;
            }
        }
        input++;
    }

    if (token_start != input) {
        strncpy(token_value, token_start, input - token_start);
        token_value[input - token_start] = '\0';
        add_token(&head, token_value, TOKEN_WORD);
    }

    return head;
}

void print_tokens(Token *head) {
    Token *current = head;
    while (current != NULL) {
        printf("Token: %s, Type: %d\n", current->value, current->type);
        current = current->next;
    }
}

int main() {
    char *input;
    while ((input = readline("minishell> ")) != NULL) {
        if (strlen(input) > 0) {
            add_history(input);
            Token *tokens = tokenize_input(input);
            print_tokens(tokens);
            free_tokens(tokens);
        }
        free(input);
    }
    return 0;
}
