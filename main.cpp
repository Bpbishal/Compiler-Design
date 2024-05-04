#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

bool is_keyword(char buffer[])
{
    char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default",
                             "do", "double", "else", "enum", "extern", "float", "for", "goto",
                             "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef", "union",
                             "unsigned", "void", "volatile", "while"};
    int i;
    bool flag = false;

    for (i = 0; i < 32; ++i)
    {
        if (strcmp(keywords[i], buffer) == 0)
        {
            flag = true;
            break;
        }
    }
    return flag;
}

bool is_valid_identifier(char *ch)
{
    if (*ch == '_')
    {
        return true;
    }
    else if (*ch >= 'A' && *ch <= 'Z')
    {
        return true;
    }
    else if (*ch >= 'a' && *ch <= 'z')
    {
        return true;
    }
    return false;
}

bool is_numeric(char *buffer, int sz)
{
    bool has_decimal = false;
    for (int i = 0; i < sz; i++)
    {
        if (buffer[i] < '0')
        {
            return false;
        }
        else if (buffer[i] > '9')
        {
            if (buffer[i] == '.' && !has_decimal)
            {
                has_decimal = true;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

bool is_delimiter(char ch)
{
    char delimiters[] = ",;\t";
    for (int i = 0; i < strlen(delimiters); i++)
    {
        if (ch == delimiters[i])
        {
            return true;
        }
    }
    return false;
}

int strcmp(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] && str2[i])
    {
        if (str1[i] != str2[i])
        {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

int strln(const char *str)
{
    int len = 0;
    while (str[len])
    {
        len++;
    }
    return len;
}

int main()
{
    char ch, buffer[15], operators[] ="+-*/%=";
    ifstream MyReadFile("lex_input.txt");
    int i, j = 0;

    if (!MyReadFile.is_open())
    {
        cout << "Error opening the file\n";
        exit(0);
    }

    while (!MyReadFile.eof())
    {
        ch = MyReadFile.get();

        for (i = 0; i < 6; i++)
        {
            if (ch == operators[i])
            {
                cout << ch << " is operator\n";
            }
        }

        if (is_delimiter(ch))
        {
            cout << ch << " is delimiter\n";
        }
        else if (isalpha(ch) || ch == '_')
        {
            buffer[j++] = ch;
        }
        else if ((ch == ' ' || ch == '\n') && (j != 0))
        {
            buffer[j] = '\0';
            int len = strlen(buffer);

            if (is_keyword(buffer))
            {
                cout << buffer << " is keyword\n";
            }
            else if (is_valid_identifier(buffer))
            {
                cout << buffer << " is valid identifier\n";
            }
            else if (is_numeric(buffer, len))
            {
                cout << buffer << " is numeric\n";
            }
            else
            {
                cout << buffer << " is unknown\n";
            }
            j = 0;
        }
    }

    MyReadFile.close();
    return 0;
}
