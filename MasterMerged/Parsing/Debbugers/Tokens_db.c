#include "../minishell.h"

void debbuger_tk(t_token *id_class)
{
    t_token *trav = id_class;
    printf("***************************************\n");
    while (trav != NULL)
    {
        printf("RE_identity> %s\n", trav->identity);
        if (trav->tok == 0)
        {
            printf("ID-> PIPE\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 1)
        {
            printf("ID-> RED_IN_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 2)
        {
            printf("ID-> RED_OUT_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 3)
        {
            printf("ID-> RED_APP_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 4)
        {
           printf("ID-> HERE_DOC_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 5)
        {
            printf("ID-> AND_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 6)
        {
            printf("ID-> OR_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 7)
        {
            printf("ID-> BRACE_O_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 8)
        {
            printf("ID-> BRACE_C_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 9)
        {
            printf("ID-> S_QUOTE_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 10)
        {
            printf("ID-> D_QUOTE_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 11)
        {
            printf("ID-> STRING_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 12)
        {
            printf("ID-> DEL_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
            if (trav->here_doc_fd != -1)
                printf("File Descriptor Stored [fd %d]\n", trav->here_doc_fd);
            else if (trav->here_doc_fd == -1)
                printf("File desciptor Unsaved\n");
        }
        else if (trav->tok == 13)
        {
            printf("ID-> INPUT_FILE_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 14)
        {
            printf("ID-> OUTPUT_FILE_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 15)
        {
            printf("ID-> INPUT_APP_FILE_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 16)
        {
            printf("ID-> COMMAND_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
            if (trav->end == true)
                printf("End Marked\n");
            if (trav->here_document_act == true)
                printf("HERE_DOC_INPUT\n");
            if (trav->red)
                printer_red(trav->red, "Red ");
            if (trav->arg)
                printer_arg(trav->arg, "Ags ");
            if (trav->was_single_quote == 1)
                printf("       └─ Was s quoted\n");
            else
                printf("       └─ Not Quoted\n");
            if (trav->fake == true)
                printf("       └─ FAKE CMD\n");

        }
        else if (trav->tok == 17)
        {
            printf("ID-> ARG_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
            if (trav->end == true)
                printf("End Marked\n");
        }
        trav = trav->next;
        printf("****************\n");
    }
    printf("***************************************\n");
}