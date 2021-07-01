#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

template <typename T>
struct STACK
{
    T value;
    STACK* next;
};

template <typename T>
void push (STACK<T>* &stack, T value)
{
    STACK<T>* new_node = new STACK<T>;
    new_node->value = value;
    new_node->next = stack;
    stack = new_node;
}

template <typename T>
T pop(STACK<T>* &stack)
{
    STACK<T>* new_node = stack;
    T value = new_node->value;
    stack = stack->next;
    delete (new_node);
    return value;
}

int prior(char zn)
{
    if (zn == '=')
        return 1;
    if (zn == '(')
        return 2;
    if (zn == '-' || zn == '+')
        return 3;
    if (zn == '*' || zn == '/')
        return 4;
    if (zn == '1' || zn == '2' || zn == '3'|| zn == '4' || zn == '5' || zn == '6' || zn == '7' || zn == '8' || zn == '9' || zn == '0')
        return 0;
    else return -1;
}

char s[100];
int i = 0;

int gran()
{
    int j = i;
    if (s[j] == '+' || s[j] == '-')
        j++;
    while (prior(s[j]) == 0)
        j++;
    if (s[j] == '.')
        j++;
    while (prior(s[j]) == 0)
        j++;
    if (s[j] == 'e')
        j += 2;
    while (prior(s[j]) == 0)
        j++;
    return (j - 1);
}

STACK<double>* X = NULL;
STACK<char>* Y = NULL;

int main()
{
    double a, b;
    int k, j;
    char n[100];
    ifstream fin("input.txt");
    fin.getline(s, 100);
    fin.close();
    cout << s << endl;
    cout << endl;
    k = gran();
    for (j = i; j <= k; j++)
        n[j - i] = s[j];
    n[k - i + 1] = '\0';
    cout << n << " ";
    i = k + 1;
    push(X, atof(n));
    while (s[i] != '\0')
    {
        if (prior(s[i]) == 0 || (prior(s[i]) == 3 && s[i - 1] == '('))
        {
            k = gran();
            for (j = i; j <= k; j++)
                n[j - i] = s[j];
            n[k - i + 1] = '\0';
            i = k + 1;
            push(X, atof(n));
            cout << n << " ";
        }
        if(s[i] == '(')
        {
            push(Y, s[i]);
            i++;

        }
        if(s[i] == ')')
        {
            while (Y->value != '(')
            {
                a = pop(X);
                b = pop(X);
                cout << Y-> value << " ";
                if (Y->value == '/' && a == 0)
                {
                    cout << endl;
                    cout << endl;
                    cout << "error" << endl;
                    return 0;
                }
                if (Y->value == '+')
                    push(X, b + a);
                if (Y->value == '-')
                    push(X, b - a);
                if (Y->value == '*')
                    push(X, b * a);
                if (Y->value == '/')
                    push(X, b / a);
                pop(Y);
            }
            pop(Y);
            i++;
        }
        if (prior(s[i]) >= 1 && s[i - 1] != '(')
        {
            if (Y == NULL)
                push(Y, s[i]);
            else
            {
                if (prior(Y->value) < prior(s[i]))
                    push(Y, s[i]);
                else
                {
                    while (Y != NULL && prior(Y->value) >= prior(s[i]))
                    {
                        a = pop(X);
                        b = pop(X);
                        cout << Y->value << " ";
                        if (Y->value == '/' && a == 0)
                        {
                            cout << endl;
                            cout << endl;
                            cout << "error" << endl;
                            return 0;
                        }
                        if (Y->value == '+')
                            push(X, b + a);
                        if (Y->value == '-')
                            push(X, b - a);
                        if (Y->value == '*')
                            push(X, b * a);
                        if (Y->value == '/')
                            push(X, b / a);
                        pop(Y);

                    }
                    push(Y, s[i]);
                }

            }
            i++;
        }
    }
    cout << endl;
    cout << endl;
    cout << X->value << endl;
    cout << endl;
    cout << endl;
    return 0;
}
