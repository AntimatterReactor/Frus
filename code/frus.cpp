#include <iostream>
#include <vector>
#include <string>

//Pre-Lexing
int isbracket(int);
std::vector<std::string> LetterReformer(std::string);

// Lexing
enum class TokenType;
struct Token;
std::vector<Token> Tokenizer(std::vector<std::string>);

// Parsing to Binary Tree
class BinaryTree;
BinaryTree TreeBuilder(std::vector<Token>);

int main(int argc, char const *argv[])
{
    for (auto i : LetterReformer(argv[1]))
    {
        std::cout << i << "\n";
    }
    return 0;
}

int isbracket(int x)
{
    if (x == '(' || x == ')' || x == '[' || x == ']' || x == '{' || x == '}')
        return 1;
    return 0;
}

std::vector<std::string> LetterReformer(std::string input_str)
{
    std::vector<std::string> result;
    int PastType = 0; //0 = Nothing; 1 = Codes; 2 = Operators; 3 = Digits; 4 = Strings/Chars
    std::string CurrentString;

    for (size_t i = 0; i < input_str.length(); i++)
    {
        if (isalpha(input_str[i]) || input_str[i] == '_')
        {
            PastType != 4 ? PastType = 1 : PastType = 4;
            CurrentString.push_back(input_str[i]);
            continue;
        }
        else if (isdigit(input_str[i]))
        {
            PastType == 4 ? PastType = 4 : (PastType == 1 ? PastType = 1 : PastType = 3);
            CurrentString.push_back(input_str[i]);
            continue;
        }
        else
        {

            if (isblank(input_str[i]))
            {
                if (PastType != 4)
                {
                    PastType = 0;
                    result.push_back(CurrentString);
                    CurrentString = "";
                }
                else
                {
                    CurrentString.push_back(input_str[i]);
                }

                continue;
            }
            else if (input_str[i] == '\"' || input_str[i] == '\'')
            {
                PastType == 4 ? PastType = 0 : PastType = 4;
                result.push_back(CurrentString);
                CurrentString = "";

                CurrentString.push_back(input_str[i]);
                result.push_back(CurrentString);
                CurrentString = "";
                continue;
            }
            else
            {
                if (PastType != 2)
                {
                    result.push_back(CurrentString);
                    CurrentString = "";
                }

                CurrentString.push_back(input_str[i]);

                if (input_str[i + 1] != input_str[i] || isbracket(input_str[i]))
                {
                    result.push_back(CurrentString);
                    CurrentString = "";
                    PastType = 0;
                    continue;
                }
                else
                {
                    PastType = 2;
                    continue;
                }
            }
        }
    }

    std::vector<std::string> true_result;

    //Remove empty strings
    for (auto i : result)
        if (i != "")
            true_result.push_back(i);

    return true_result;
}

enum class TokenType
{
    id,
    t_integer,
    t_float,
    t_char,
    t_string,

    sqr_bracket_a,
    sqr_bracket_b,
    curl_bracket_a,
    curl_bracket_b,
    angle_bracket_a,
    angle_bracket_b,
    parenthesis_a,
    parenthesis_b,

    op_plus,
    op_min,
    op_mult,
    op_div,
    op_mod,

    op_inc,
    op_dec,

    op_assign,
    op_eq,
    op_not,
    op_not_eq,
    op_more,
    op_more_eq,
    op_less,
    op_less_eq,
    op_and,
    op_or,

    op_semi,
    op_colon,
    op_comma,

    op_backslash,
};

struct Token
{
    TokenType type;
    std::string val;
};

std::vector<Token> Tokenizer(std::vector<std::string>)
{
}
