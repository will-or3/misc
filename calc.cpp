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
  OPERATOR
};

struct token {
  token_type type;

  int num;
  char op;
};

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

    if (c == '+' || c == '-' ||
        c == '*' || c == '/' ||
         c == '('|| c == ')') {
      token t;
      t.type = OPERATOR;
      t.op = c;

      tokens.push_back(t);

      i++;
      continue;
    }

    std::cout << "err: invalid char [" << c << "]\n";
    break;
  }

  return tokens;
}



int main(){
  std::string input;
  std::getline(std::cin, input);

  std::cout << ">:" << input << "\n";

  input = rm_whitespace(input);

  tokenize(input);
  
  return 0;  
}
