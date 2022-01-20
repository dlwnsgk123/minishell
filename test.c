/*
void	print_cmd(t_list *cmds)
{
	t_list	*start;
	t_list	*rdi_lst;
	t_rdi	*rdi;
	t_cmd	*cmd;

	int i;
	
	start = cmds;
	while (start)
	{
		cmd = start->content;
		i = 0;
		printf("argv : ");
		while (cmd->argv[i])
			printf("%s ",cmd->argv[i++]);
		printf("\n");
		if (cmd->redirect != NULL)
		{
			rdi_lst = cmd->redirect;
			while(rdi_lst)
			{
			rdi = rdi_lst->content;
			printf("type : %d target : %s,\n", rdi->type, rdi->target);
			rdi_lst = rdi_lst->next;
			}
		}
		start = start->next;
	}
}
*/