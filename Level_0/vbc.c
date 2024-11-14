#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
    enum{
        ADD,
        MULTI,
        VAL,
    } type;
    int val;
    struct node *l;
    struct node *r;
} node ;


node    *parse_expr(char **s);
node    *parse_term(char **s);
node    *parse_primary(char **s);

node    *new_node(node n)
{
    node*ret = calloc(1, sizeof(node));
    if (!ret)
        return NULL;
    *ret = n;
    return ret;
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c, int i)
{
    if (c)
        printf("unexpected %c\n", c);
    else
        printf("unexpected EOF\n");
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return 1;
    }
    return 0;
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return 1;
    unexpected(**s, **s == '\0');
    return 0;
}

// ... 
// ...

// node    *parse_expr(char **s)
// {
//     // ...

//     if (*s)
//     {
//         destroy_tree(ret);
//         return NULL;
//     }
//     return (ret);
// }


node    *parse_expr(char **s)
{
    node *ret = parse_term(s);
    if (!ret)
        return NULL;
    while (accept(s, '+'))
    {
        node *r = parse_term(s);
        if (!r)
        {
            destroy_tree(ret);
            return NULL;
        }
        node n = {.type = ADD, .l = ret, .r = r};
        ret = new_node(n);
        if (!ret)
        {
            destroy_tree(r);
            return NULL;
        }
    }
    if (**s && **s != ')')
    {
        unexpected(**s, 0);
        destroy_tree(ret);
        return NULL;
    }
    return ret;
}

node    *parse_primary(char **s)
{
    node *ret;
    if (accept(s, '('))
    {
        ret = parse_expr(s);
        if (!ret)
        {
            return NULL;
        }
        if (!accept(s, ')'))
        {
            unexpected(**s, **s == '\0');
            destroy_tree(ret);
            return NULL;
        }
        return ret;
    }
    if (isdigit(**s))
    {
        node ret = {.type = VAL, .val = **s - '0'};
        (*s)++;
        return new_node(ret);
    }
    unexpected(**s, **s == '\0');
    return NULL;
}

node    *parse_term(char **s)
{
    node *ret = parse_primary(s);
    if (!ret)
        return NULL;
    while (accept(s, '*'))
    {
        node *r = parse_primary(s);
        if (!r)
        {
            destroy_tree(ret);
            return NULL;
        }
        node n = {.type = MULTI, .l = ret, .r = r};
        ret = new_node(n);
        if (!ret)
        {
            destroy_tree(r);
            return NULL;
        }
    }
    return ret;
}


int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return eval_tree(tree->l) + eval_tree(tree->r);
        case MULTI:
            return eval_tree(tree->l) * eval_tree(tree->r);
        case VAL:
            return tree->val;
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    char *input = av[1];
    node *tree = parse_expr(&input);
    if (!tree)
        return 1;
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    return 0;
}