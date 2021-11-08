#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int getValueFromKey(FILE *iniFile, char *section, char *key);
int findValue(FILE *iniFile, char *key);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Expects file name as input argument\r\n");
        return 0;
    }
    FILE *fptr = fopen(argv[1], "r");
    int val = getValueFromKey(fptr, "section 1", "name");
    printf("value = %d\r\n", val);
    /* char line[50];
    while(fgets(line, 50, fptr) != NULL && fptr != NULL)
    {
        printf("%s", line);
    } */
    /* char c;
    while(!feof(fptr))
    {
        fscanf(fptr, "%c", &c);
        if(feof(fptr))
            break;
        if(c == '[')
        {
            printf("Found a key");
        }
        printf("%c", c);
    } */
    return 0;
}

int getValueFromKey(FILE *iniFile, char *section, char *key)
{
    FILE *fptr = iniFile;
    char *str = malloc(sizeof(char) * 50);
    while(fgets(str, 50, fptr) != NULL)
    {
        //puts(str);
        if(str[0] == '[')
        {
            //printf("found a key\r\n");
            str++;
            str[strlen(str) - 3] = '\0';
            //puts(str);
            if(strcmp(section, str) == 0)
            {
                return findValue(fptr, key);
            }
        }
    }
    return 0;
}

int findValue(FILE *iniFile, char *key)
{
    FILE *fptr = iniFile;
    char *str = malloc(sizeof(char) *50);
    char *token;
    while(fgets(str, 50, fptr) != NULL && str[0] != '[')
    {
        //puts(str);    //debugging
        token = strtok(str, "=");
        if(strcmp(token, key) == 0)
        {
            token = strtok(NULL, "=");
            int val;
            sscanf(token, "%d", &val);
            return val;
        }
    }
    return -1;
}