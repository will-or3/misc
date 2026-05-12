#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>


std::string rm_whitespace(std::string s) {
  s.erase(
    std::remove_if(s.begin(), s.end(),
                   [](unsigned char c){
                     return std::isspace(c);
                   }),
    s.end()
  );

  return s;
}

enum token_type {
  NUMBER,
  PLUS,
  MINUS,
  ASTERISK,
  DIV,
  LEFT_PAREN,
  RIGHT_PAREN,
  END
};

struct token {
  token_type type;

  int num;
  char op;
};

std::vector<token> tokens;
size_t i = 0;

std::vector<token> tokenize(std::string input){
  std::vector<token> tokens;

  int i=0;
  while (i < input.size()) { //'string.size()'!!! that's so cool
    char c = input[i];

    if (std::isdigit(c)) {
      int value = 0;

      while (i < input.size() && std::isdigit(input[i])) {
        value = value * 10 + (input[i] - '0');
        i++;
      }
      token t;
      t.type = NUMBER;
      t.num = value;

      tokens.push_back(t);

      continue;
    }

    token t;

    switch (c) {
      case '+': t.type = PLUS; break;
      case '-': t.type = MINUS; break;
      case '*': t.type = ASTERISK; break;
      case '/': t.type = DIV; break;
      case '(': t.type = LEFT_PAREN; break;
      case ')': t.type = RIGHT_PAREN; break;

      default:
      std::cout << "invalid char: " << c << "\n";
      exit(1);
    }

    tokens.push_back(t);
    i++;
  }

  token eof;
  eof.type = END;

  tokens.push_back(eof);
  return tokens;
}

token current(){
  return tokens[i];
}


void advance(){
  i++;
}

int parse_expression();
int parse_term();
int parse_factor();

int parse_factor() {
  token t = current();

  if (t.type == NUMBER){
    advance();
    return t.num;
  }

  if (t.type == LEFT_PAREN) {
    advance();

    int value = parse_expression();

    if (current().type != RIGHT_PAREN){
      std::cout << "missing ')'\n";
    }

    advance();
    return value;
  }

  std::cout << "token err\n";
  exit(1);
}

int parse_term(){
  int left = parse_factor();

  while (current().type == ASTERISK ||
          current().type == DIV){
    token_type op = current().type;
    advance();

    int right = parse_factor();

    if (op == ASTERISK) {left *= right;}
    else {left /= right;}

  }
  return left;
}

int parse_expression(){
  int left = parse_term();

  while (current().type == PLUS ||
          current().type == MINUS) {
    token_type op = current().type;
    advance();

    int right = parse_term();

    if (op == PLUS){ left += right;}
    else {left -= right;}

  }

  return left;
}
int main(){
  std::string input;

  std::cout << "baby's first c++ calculator\n";
  std::cout << ">: ";
  
  std::getline(std::cin, input);

  input = rm_whitespace(input);

  tokens = tokenize(input);

  int x = parse_expression();
  std::cout << x << "\n";
  
  return 0;  
}
