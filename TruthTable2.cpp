#include <iostream>
using namespace std;

char condition(char, char);
char conjunction(char, char);
char disjunction(char, char);
char biconditional(char, char);
void evaluatebinary();

char stack1[20];
char stack2[20];
char usedchars[2][20];
bool charfound = false;
string input;
int top1 = -1, top2 = -1, i = 0, m = 0;
bool run = true;
int main()
{
    cout << "Boolean Evaluation using 2 stacks" << endl;
    cout << "Rules:" << endl;
    cout << "1.Spaces not allowed" << endl;
    cout << "2.Symbols-" << endl;
    cout << "3.Case sensitive" << endl;
    cout << "~=negation" << endl;
    cout << "0=false" << endl;
    cout << "1=true" << endl;
    cout << "A=conjunction" << endl;
    cout << "V=disjunction" << endl;
    cout << ">=conditional" << endl;
    cout << "<=bi-condtional" << endl;

    cout << "Enter Expression  : ";
    cin >> input;

    while (input[i] != '\0')
    {
        if (input[i] == '(' || input[i] == '<' || input[i] == '>' || input[i] == 'A' || input[i] == 'V' || input[i] == '~')
        {
            top1++;
            stack1[top1] = input[i];
        }
        else if (input[i] == ')' || input[i + 1] == '\0')
        {
            evaluatebinary();
        }
        else
        {
            top2++;
            int k;
            char temp;
            for (k = 0; usedchars[0][k] != '\0'; k++)
            {
                if (usedchars[0][k] == input[i])
                {
                    charfound = true;
                    break;
                }
            }
            if (charfound)
            {
                temp = usedchars[1][k];
            }
            else
            {
                cout << "Enter Value Of " << input[i] << ":";
                cin >> temp;
                usedchars[0][m] = input[i];
                usedchars[1][m] = temp;
                m++;
            }
            charfound = false;

            stack2[top2] = temp;
            // stack2[top2] = input[i];
        }
        i++;
    }
    while (top1 > -1 && top2 > 0)
    {
        evaluatebinary();
    }
    cout << top1 << endl;
    cout << top2 << endl;
    cout << "Final Result : ";
    if (stack2[top2] == '1')
        cout << "True1";
    else
        cout << "False";
    return 0;
}
void evaluatebinary()
{
    while (run)
    {
        switch (stack1[top1])
        {
        case '~':
            stack2[top2] = !(stack2[top2]);
            top2++;
            break;
        case 'A':
            stack2[top2 - 1] = conjunction(stack2[top2], stack2[top2 - 1]);
            break;
        case 'V':
            stack2[top2 - 1] = disjunction(stack2[top2], stack2[top2 - 1]);
            break;
        case '<':
            stack2[top2 - 1] = condition(stack2[top2], stack2[top2 - 1]);
            break;
        case '>':
            stack2[top2 - 1] = biconditional(stack2[top2], stack2[top2 - 1]);
            break;
        }
        top2--;
        top1--;
        if (stack1[top1] == '(' || top1 < 0)
        {
            top1--;
            run = false;
        }
    }
    run = true;

    if (top1 == -1 && top2 == 0 && i == input.length())
    {
        cout << "Final Result : ";
        if (stack2[top2] == '1')
            cout << "True2";
        else
            cout << "False";
    }
}
char conjunction(char a, char b)
{
    if (a == '1' && b == '1')
        return '1';
    else
        return '0';
}
char disjunction(char a, char b)
{
    if (a == '0' && b == '0')
        return '0';
    else
        return '1';
}
char condition(char a, char b)
{
    if (b == '1' && a == '0')
        return '0';
    else
        return '1';
}
char biconditional(char a, char b)
{
    if (b == a)
        return '1';
    else
        return '0';
}