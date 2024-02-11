#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>

template <typename Type>
class Stack {
private:
    std::vector<Type> items;
    int64_t top;

public:
    Stack() : top(-1) {}

    void push(const Type& value) {
        items.push_back(value);
        top++;
    }

    Type pop() {
        Type poppedValue = items[top];
        items.pop_back();
        top--;
        return poppedValue;
    }

    Type peek() {
        return items[top];
    }

    bool isEmpty() {
        return (top == -1);
    }
};

class Coverter {
public:
    std::string convert(const std::string &infix) {
        std::string postfix;
        Stack<std::string> operators;

        std::vector<std::string> parseStr = parseString(infix);

        for (std::string c : parseStr) {
            //std::cout << c << " ";
            if (isNumber(c)) {
                postfix += c + " ";
            } else if (c == "(") {
                operators.push(c);
            } else if (c == ")") {
                while (!operators.isEmpty() && operators.peek() != "(") {
                    postfix += operators.pop() + " ";
                }
                operators.pop();
            } else if (isOperator(c)) {
                while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(c)) {
                    postfix += operators.pop() + " ";
                }
                operators.push(c);
            }
        }

        while (!operators.isEmpty()) {
            postfix += operators.pop() + " ";
        }

        return postfix;
    }

private:
    std::vector<std::string> parseString(const std::string& input) {
        std::vector<std::string> v;
        std::string buff = "";

        for (char c : input) {
            if (std::isdigit(c)) {
                buff += c;
            } else {
                if (!buff.empty()) {
                    v.push_back(buff);
                    buff.clear();
                }
                buff.push_back(c);
                v.push_back(buff);
                buff.clear();
            }
        }

        if (!buff.empty()) {
            v.push_back(buff);
        }

        return v;
    }

    bool isNumber(std::string& str) {
        for (char c : str) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }

    bool isOperator(const std::string& c) {
        return (c == "+" || c == "-" || c == "*" || c == "/");
    }

    uint8_t precedence(std::string op) {
        if (op == "+" || op == "-")
            return 1;
        if (op == "*" || op == "/")
            return 2;
        return 0;
    }
};

class Solution {
public:
    int64_t solvePostfix(const std::string& input) {
        Stack<int64_t> operandStack;

        std::vector<std::string> postfix = parseString(input);

        for (std::string& element : postfix) {
            if (isOperand(element)) {
                operandStack.push(std::stoi(element));
            } else if (isOperator(element)) {
                int64_t operand2 = operandStack.peek();
                operandStack.pop();

                int64_t operand1 = operandStack.peek();
                operandStack.pop();

                int64_t result = performOperation(operand1, operand2, element);
                operandStack.push(result);
            }
        }

        return (!operandStack.isEmpty()) ? operandStack.peek() : 0;
    }

private:
    std::vector<std::string> parseString(const std::string& input) {
        std::vector<std::string> v;
        std::string buff = "";

        for (char c : input) {
            if (std::isalnum(c)) {
                buff += c;
            } else {
                if (!buff.empty()) {
                    v.push_back(buff);
                    buff.clear();
                }
                buff.push_back(c);
                v.push_back(buff);
                buff.clear();
            }
        }

        if (!buff.empty()) {
            v.push_back(buff);
        }

        return v;
    }

    bool isOperand(const std::string& element) {
        return std::isdigit(element[0]);
    }

    bool isOperator(const std::string& element) {
        return (element == "+" || element == "-" || element == "*" || element == "/");
    }

    int64_t performOperation(int64_t operand1, int64_t operand2, const std::string& op) {
        int64_t result = 0;

        switch (op[0]) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            default:
                break;
        }

        return result;
    }
};

int main() {
    Coverter converter;
    Solution solve;

    std::string input;
    std::cin >> input;

    std::cout << "Expression: \n" << input << std::endl;

    std::string postfix = converter.convert(input);
    std::cout << "Reverse Polish Notation: \n" << postfix << std::endl;

    int64_t result = solve.solvePostfix(postfix);
    std::cout << "Result: \n" << result << std::endl;

    return 0;
}