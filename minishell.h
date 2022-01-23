#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
# include <termios.h>
#include <errno.h>
#include <sys/wait.h>
#include "Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#define R_RDR			1
#define RR_RDR			2
#define L_RDR			3
#define LL_RDR			4
#define	BUILTIN_ECHO	1
#define	BUILTIN_CD		2
#define	BUILTIN_EXPORT	3
#define	BUILTIN_UNSET	4
#define	BUILTIN_ENV		5
#define	BUILTIN_EXIT	6
#define	BUILTIN_PWD		7

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef struct s_rdi
{
	int				type;
	char			*target;
}				t_rdi;

typedef struct s_cmd
{
	char			*tmp;
	char			**argv;
	t_list			*redirect;
}				t_cmd;

extern int	g_status;

void	env_setting(t_env **env, char **envp);
t_env	*env_last(t_env *env);
void	print_env(t_env *env);
void	env_add_back(t_env **env, t_env *new);
char	*env_get_value(t_env **env, char *key);
void	env_change_value(t_env **env, char *key, char *value);
void	env_delete_node(char *key, t_env **env);
t_env	*ft_envnew(char *envp);


char	*skip_quote(char *input);
int		check_input(char *input);
int		check_empty(char *input);

/*---------------------------- parse ------------------------------*/

void	parse_pipe(char *input, t_list **cmds);
void	parse(char *input, t_list **cmds, t_env *env);
void	parse_redirection(t_list **cmds);
char	*parse_env_start(char *str, t_env *env, bool in_dquote);
void	*parse_env(t_list *cmds, t_env *env);
char	*delete_quote(char	*str);
char	*get_last(char *str);
char	*get_middle(char *str, t_env *env);
char	*get_key(char *str);

/*-----------------------------------------------------------------*/

void	execute(t_list *cmds, t_env **env);
void	pipe_execute(t_list *cmds, t_env **env);

int		exec_redirect(t_list *redirect);
void	run_rdr_cmd(t_list *cmds, t_env **env);
int		exec_builtin(t_cmd *cmd, t_env **env);

void	rdr_right(char *target);
void	rdr_double_right(char *target);
int		rdr_left(char *target);
void	rdr_double_left(char *target);


void	echoctl_on(void);
void	echoctl_off(void);

void	sig_newline(int	signum);
void	sig_endl(int signum);

int		ft_echo(char **argv);
int		ft_cd(char **argv, t_env **env);
int		ft_pwd(void);
int		ft_env(t_env **env);
int		ft_export(char **argv, t_env **env);
int		ft_exit();
int		ft_unset(char **argv, t_env **env);
int		get_argc(char **argv);

void	exit_error(char	*str);