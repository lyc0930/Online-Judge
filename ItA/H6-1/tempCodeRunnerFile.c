
    while(1)
    {
        scanf("%c %d", &command, &k);
        getchar();
        if (command == 'I')
            RB_Insert_Key(T, k);
        else if (command == 'D')
            RB_Delete_Key(T, k);
        else if (command == 'K')
            printf("%d\n", OS_Select(T, k)->key);
        RB_Print(T, T->root, 0);
    }