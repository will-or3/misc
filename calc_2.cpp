#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>

// 2nd version, add AST & ex^ponent, include file input

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

// structs

enum token_type {
  NUMBER,
  PLUS,
  MINUS,
  ASTERISK,
  DIV,
  EXPONENT,
  LEFT_PAREN,
  RIGHT_PAREN,
  END
};

struct token {
  token_type type;

  int num;
};

std::vector<token> tokens;
size_t i = 0;

struct expr {
  virtual ~expr() = default;
};

struct num_expr : expr {
  int value;
  num_expr(int x) : value(x) {}
};

struct binary_expr : expr {
  token_type op;

  expr* left;
  expr* right;

  binary_expr(token_type o, expr* l, expr* r)
      : op(o), left(l), right(r) {}
};

// code
std::vector<token> tokenize(std::string input){
  std::vector<token> tokens;

  int index=0;
  while (index < input.size()) { //'string.size()'!!! that's so cool
    char c = input[index];

    if (std::isdigit(c)) {
      int value = 0;

      while (index < input.size() && std::isdigit(input[index])) {
        value = value * 10 + (input[index] - '0');
        index++;
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
      case '^': t.type = EXPONENT; break;

      default:
      std::cout << "invalid char: " << c << "\n";
      exit(1);
    }

    tokens.push_back(t);
    index++;
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

expr* parse_expression();
expr* parse_term();
expr* parse_factor();

expr* parse_factor() {
  token t = current();

  if (t.type == NUMBER){
    advance();
    return new num_expr(t.num);
  }

  if (t.type == LEFT_PAREN) {
    advance();

    expr* value = parse_expression();

    if (current().type != RIGHT_PAREN){
      std::cout << "missing ')'\n";
      exit(1);
    }

    advance();
    return value;
  }

  std::cout << "token err\n";
  exit(1);
}


// 2^3^2 == 2^9; you have to move it to the right
expr* parse_power(){
  expr* left = parse_factor();

  if (current().type == EXPONENT) {
    advance();

    expr* right = parse_power();

    return new binary_expr(EXPONENT, left, right);
  }

  return left;
}

expr* parse_term(){
  expr* left = parse_power();

  while (current().type == ASTERISK ||
          current().type == DIV){
    token_type op = current().type;
    advance();

    expr* right = parse_power();

    left = new binary_expr(op, left, right);
  }
  return left;
}

expr* parse_expression(){
  expr* left = parse_term();

  while (current().type == PLUS ||
          current().type == MINUS) {
    token_type op = current().type;
    advance();

    expr* right = parse_term();

    left = new binary_expr(op, left, right);
  }

  return left;
}

void free_ast(expr* node){
  if (!node) return;

  if (auto bin = dynamic_cast<binary_expr*>(node)) {
    free_ast(bin->left);
    free_ast(bin->right);
  }

  delete node;
}

double eval_tree(expr* expr){
  if (auto num = dynamic_cast<num_expr*>(expr)){
      return num->value;
  }

  if (auto bin = dynamic_cast<binary_expr*>(expr)) {
    double left = eval_tree(bin->left);
    double right = eval_tree(bin->right);

    switch (bin->op){
      case PLUS:
        return left + right;
      case MINUS:
        return left - right;
      case ASTERISK:
        return left * right;
      case DIV:
        if (right == 0) {std::cout << "division by 0 err :(\n"; exit(1);}
        else {return left / right;}
      case EXPONENT:
        return std::pow(left, right);
      
      default:
        std::cout << "operator syntax err\n";
        exit(1); 
    }
  }
  std::cout << "if theres an err all the way down here im sad :(\n";
  exit(1);
}

void print_calc(double x){
  const double eps = 1e-10;

  double intpart;
  double frac = std::modf(x, &intpart);

  if (std::abs(frac) < eps) {
    std::cout << (long long)intpart << "\n";
  } else {
    std::cout << std::fixed << std::setprecision(10);
    std::cout << x << "\n";
  }
}

int main(int argc, char* argv[]){
  std::string input;

  std::cout << "baby's f̶i̶r̶s̶t̶ '2nd' c++ calculator\n";
  
  if (argc > 1) {
    std::ifstream file(argv[1]);

    if (!file) {
      std::cout << "could not open file : " << argv[i] << "\n";
      return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
      input += line;
    }

    file.close();
    } 
    else { 
      std::cout << "  >: ";
      std::getline(std::cin, input);
    }

  input = rm_whitespace(input);

  tokens = tokenize(input);

  // ast = advanced syntax tree btw, if you did know btw, btw
  expr* ast  = parse_expression();
  double x = eval_tree(ast);
  free_ast(ast);
  
  std::cout << "\n";
  print_calc(x);
  
  return 0;  
}
