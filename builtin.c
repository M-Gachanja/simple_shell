#include "shell.h"

/**
 * _exitShell - Exits the shell.
 *
 * @info: Structure containing potential arguments.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int _exitShell(info_t *info)
{
	int exitCheck;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exitCheck = _erratoi(info->argv[1]);
		if (exitCheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _changeDirectory - Changes the current directory of the process.
 *
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _changeDirectory(info_t *info)
{
	char *currentDir, *targetDir, buffer[1024];
	int chdirRet;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		targetDir = _getenv(info, "HOME=");
		if (!targetDir)
			chdirRet = chdir((targetDir = _getenv(info, "PWD=")) ? targetDir : "/");
		else
			chdirRet = chdir(targetDir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirRet = chdir((targetDir = _getenv(info, "OLDPWD=")) ? targetDir : "/");
	}
	else
		chdirRet = chdir(info->argv[1]);

	if (chdirRet == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _showHelp - Displays help information.
 *
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _showHelp(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	_puts("Help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray); /* Temporarily unused, workaround to avoid compiler warning */
	return (0);
}

