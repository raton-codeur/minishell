static void tree_print_rec(t_tree *tree, int depth, char* path)
{
    if (tree == NULL)
        return ;

    path[depth] = 0;

    if(tree->left)
    {
        path[depth] = '1';
        tree_print_rec(tree->left, depth + 1, path);
    }

    path[depth] = 0;

    printf("\n");
    for(int i = 0; i < depth; i++)
    {
        if(path[i] == '1')
            printf("--->");
        else
            printf("    ");
    }

    list_print(tree->content, print_token_line);

    if(tree->right)
    {
        path[depth] = '1';
        tree_print_rec(tree->right, depth + 1, path);
    }

    path[depth] = 0;
}

void    tree_print(t_tree *tree)
{
    char path[1024];
    tree_print_rec(tree, 0, path);
}