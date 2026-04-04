/* Construct an expression tree from the given prefix
   and traverse it using post order traversal and then
   delete the entire tree */

#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;

struct node
{
    char data;
    node *left;
    node *right;
};

class stack1
{
    node *data[30];
    int top;

public:
    stack1()
    {
        top = -1;
    }

    int empty()
    {
        if (top == -1)
            return 1;
        return 0;
    }

    void push(node *p)
    {
        data[++top] = p;
    }

    node *pop()
    {
        return data[top--];
    }
};

class tree
{
    char prefix[20];

public:
    node *top;

    void expression(char[]);
    void display(node *);
    void non_rec_postorder(node *);
    void del(node *);
    void printTree(node *, int);   // NEW FUNCTION
};

void tree::expression(char prefix[])
{
    stack1 s;
    node *t1, *t2;

    int len, i;
    len = strlen(prefix);

    for (i = len - 1; i >= 0; i--)
    {
        top = new node;
        top->left = NULL;
        top->right = NULL;

        if (isalpha(prefix[i]))
        {
            top->data = prefix[i];
            s.push(top);
        }
        else if (prefix[i] == '+' || prefix[i] == '*' ||
                 prefix[i] == '-' || prefix[i] == '/')
        {
            t2 = s.pop();
            t1 = s.pop();

            top->data = prefix[i];
            top->left = t2;
            top->right = t1;

            s.push(top);
        }
    }

    top = s.pop();
}

void tree::display(node *root) // preorder
{
    if (root != NULL)
    {
        cout << root->data;
        display(root->left);
        display(root->right);
    }
}

void tree::non_rec_postorder(node *top)
{
    stack1 s1, s2;
    node *T = top;

    cout << "\n";

    s1.push(T);

    while (!s1.empty())
    {
        T = s1.pop();
        s2.push(T);

        if (T->left != NULL)
            s1.push(T->left);

        if (T->right != NULL)
            s1.push(T->right);
    }

    while (!s2.empty())
    {
        top = s2.pop();
        cout << top->data;
    }
}

/* FUNCTION TO PRINT EXPRESSION TREE */
void tree::printTree(node *root, int space)
{
    if (root == NULL)
        return;

    space += 5;

    printTree(root->right, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";

    cout << root->data << "\n";

    printTree(root->left, space);
}

void tree::del(node *node)
{
    if (node == NULL)
        return;

    del(node->left);
    del(node->right);

    cout << endl << "Deleting node : " << node->data << endl;
    free(node);
}

int main()
{
    char expr[20];
    tree t;

    cout << "Enter prefix Expression : ";
    cin >> expr;

    t.expression(expr);

    cout << "\nExpression (Preorder) : ";
    t.display(t.top);

    cout << "\nPostorder of the expression is : ";
    t.non_rec_postorder(t.top);

    cout << "\n\nExpression Tree:\n";
    t.printTree(t.top, 0);   // PRINT TREE

    t.del(t.top);

    cout << "\nTree deleted.";
}
