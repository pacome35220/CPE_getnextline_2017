/*
** EPITECH PROJECT, 2018
** get_next_line
** File description:
** get_next_line
*/

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int my_strlen(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char *concat(char *recept, char *new)
{
	int i = 0;
	int j = 0;
	int len_recept = (recept) ? my_strlen(recept) : 0;
	int len_new = (new) ? my_strlen(new) : 0;
	char *new_str = malloc(sizeof(char) * (len_recept + len_new + 1));

	if (new_str == NULL)
		return (NULL);
	while (recept && i < len_recept) {
		new_str[i] = recept[i];
		i++;
	}
	while (j < len_new) {
		new_str[i] = new[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free(recept);
	return (new_str);
}

char *my_strdup(char *src, size_t n, char *tofree)
{
	size_t i = 0;
	char *new_str = malloc(sizeof(char) * (my_strlen(src) + 1));

	if (new_str == NULL)
		return (NULL);
	while (i < n && src[i] != '\0') {
		new_str[i] = src[i];
		i++;
	}
	new_str[i] = '\0';
	free(tofree);
	return (new_str);
}

ssize_t check_back_n(char *str)
{
	int j = 0;

	if (str == NULL)
		return (-1);
	while (str[j] != '\0') {
		if (str[j] == '\n')
			return (j);
		j++;
	}
	return (-1);
}

char *get_next_line(int fd)
{
	ssize_t size = 0;
	ssize_t pos_back_n = 0;
	char buffer[READ_SIZE + 1] = {0};
	static char *tmp = NULL;
	char *rest_line = NULL;

	if ((pos_back_n = check_back_n(tmp)) == -1) {
		if ((size = read(fd, buffer, READ_SIZE)) > 0) {
			buffer[size] = '\0';
			tmp = concat(tmp, buffer);
			return (*buffer == '\0' ? NULL : get_next_line(fd));
		}
		if (tmp == NULL || tmp[0] == '\0')
			return (free(tmp), NULL);
		rest_line = my_strdup(tmp, my_strlen(tmp), tmp);
		tmp = NULL;
		return (rest_line);
	}
	rest_line = my_strdup(tmp, pos_back_n, NULL);
	tmp = my_strdup(tmp + pos_back_n + 1, my_strlen(tmp + pos_back_n), tmp);
	return (rest_line);
}
