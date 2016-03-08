/* rewrite for deal with num of length > 1 */

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int priority(char c='\0', bool coming=true){
  switch(c){
    case '(': return coming?5:0;
    case 'N': return 4;
    case '%': return 3;
    case '*':
    case '/': return 2;
    case '+':
    case '-': return 1;
    case 'B':
    default:  return 0;
  }
}

void neg_to_n(string &exp){
  bool has_lhs = false;
  for(int i=0; i<exp.length(); i++){
    if(!has_lhs && exp[i]=='-')
      exp[i] = 'N';
    else if(isdigit(exp[i]) || exp[i]==')')
      has_lhs = true;
    else 
      has_lhs = false;
  }
}

void to_postfix(string &exp){
  stack<char> op;
  op.push('B');
  string postfix;
  for(int i=0; i<exp.length(); i++){
    if(isdigit(exp[i]))
      postfix += exp[i];
    else if(exp[i] == ')'){
      while(op.top() != '(' && op.top() != 'B'){
        postfix += op.top();
        op.pop();
      }
      if(op.top() == '(')
        op.pop();
    }
    else if(priority(exp[i]) > priority(op.top(), false))
      op.push(exp[i]);
    else{
      while(priority(op.top(), false) >= priority(exp[i]) && op.top()!='B'){
        postfix += op.top();
        op.pop();
      }
      op.push(exp[i]);
    }
  }
  while(op.top()!='B'){
    postfix += op.top();
    op.pop();
  }
  exp = postfix;
}

int main(){
  string exp;
  while(getline(cin, exp)){
    neg_to_n(exp);
    to_postfix(exp);
    cout << exp;
    evalute_print(exp);
  }
  return 0;
}
