#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#pragma comment(lib, "winmm.lib")

#define MAX_SOURCE_SIZE (0x100000)
#define BUFFER_LENGTH 1024
#define MAX_STRING_CHARS 20
#define CHOICE_MAX_ATTEMPTS 10
#define CON_DELAY 500

#define CHOICE_START "{"
#define CHOICE_END "}"
#define TYPE_START "["
#define TYPE_END "]"
#define CHOICE_SEPARATOR ";"
#define CHOICETYPE_SEPARATOR ":"

char choice[15];

// String Remove Trailing Newline
void strrtn(char str[])
{
    str[strcspn(str, "\n")] = 0;
}

// Print Separator
void printsep()
{
    printf("----------------------------------------------------\n");
}

// Print NPC Conversation
void printnpcc(char npc[], char str[])
{
    printf("%s: \"%s\"\n", npc, str);
}

void wait()
{
    #ifdef _WIN32
    Sleep(CON_DELAY);
    #else
    usleep(CON_DELAY*1000);
    #endif
}

// Create a choice
void init_choice()
{
    int choiceAttempts = 0;

    while (choiceAttempts < CHOICE_MAX_ATTEMPTS)
    {
        fgets(choice, 10, stdin);
        strrtn(choice);

        if (strcmp(choice, "A") == 0 || strcmp(choice, "B") == 0 || strcmp(choice, "C") == 0) {
            choiceAttempts = CHOICE_MAX_ATTEMPTS;
        } else {
            printf("Invalid choice, %d attempts remaining...\n", CHOICE_MAX_ATTEMPTS - (choiceAttempts + 1));
        }

        choiceAttempts++;

        if (choiceAttempts == CHOICE_MAX_ATTEMPTS) {
            printf("Max choices reached. Game Over!");
            exit(0);
        }
    }
}

// Initialize End Screen
void init_end_screen()
{
    printf("\n");
    printsep();
    printf("Thank you for playing!\n");
    printf("---- CREDITS -----------------------------\n");
    printf("Story: Maarten Wolfsen\n");
    printf("Programming: Maarten Wolfsen\n");
    printf("Music: 8 Bit Presentation (Free music for non-commercial use from https://www.fesliyanstudios.com)\n");
    printsep();
    printf("\n");
}

// Replace words in a string
char *replace_str(char *str, char *orig, char *rep)
{
  static char buffer[4096];
  char *p;

  if (!(p = strstr(str, orig))) return str;

  strncpy(buffer, str, p - str);
  buffer[p - str] = '\0';

  sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));

  return buffer;
}

// Get string between symbols
char *get_str_between(char *str, char *startsym, char *endsym)
{
    char buffer[BUFFER_LENGTH];
    char *p1, *p2;

    p1 = strstr(str, startsym) + 1;

    if (p1) {
        p2 = strstr(p1, endsym);
        snprintf(buffer, sizeof(buffer), "%.*s", p2 - p1, p1);
    }

    return buffer;
}

int main()
{
    FILE *filePointer = fopen("./src/script.tee", "r");

    if (!filePointer) {
        printf("Game Story could not be loaded.");
        return 0;
    }

    PlaySound(".\\src\\sound\\bg_track.wav", NULL, SND_LOOP | SND_ASYNC);

    int nestLevel = 0;
    char buffer[BUFFER_LENGTH];
    char name[MAX_STRING_CHARS];
    char location[MAX_STRING_CHARS];

    while (fgets(buffer, BUFFER_LENGTH, filePointer)) {
        char *str = buffer + (4 * nestLevel);

        if (*str == '#' || (*str != '[' && *str != ' ')) continue;
        
        str = replace_str(str, "$name", name);
        str = replace_str(str, "$location", location);

        // Print line
        if (*(str + 1) == 'p') printf("%s", str + 3);

        // Quote line
        if (*(str + 1) == 'q') {
            char *quoteBuffer = get_str_between(str, TYPE_START, TYPE_END);
            char *quote = str + (strlen(quoteBuffer) + 2);

            strrtn(quote);
            printnpcc(quoteBuffer + 2, quote);
        }

        // Execute Function
        // TODO: Find better function execution method
        if (*(str + 1) == 'f') {
            char *function = get_str_between(str, TYPE_START, TYPE_END) + 2;

            if (strcmp(function, "setName") == 0) {
                fgets(name, MAX_STRING_CHARS, stdin);
                strrtn(name);
                printnpcc(name, name);
            } else if (strcmp(function, "setLocation") == 0) {
                fgets(location, MAX_STRING_CHARS, stdin);
                strrtn(location);
                printnpcc(location, location);
            }
        }

        // Increase Nest Level
        if (*(str + 1) == 'z' || (*(str + 1) == 'e' && *(str + 2) == 'x') || *(str + 1) == 'a' || *(str + 1) == 'b' || *(str + 1) == 'c') nestLevel++;

        // Activate Choice Mode
        if (*(str + 1) == 'z') {
            printsep();
            printf("---- What will you do? -----------------------------\n");

            // Separate Choices            
            char *assignmentBuffer = get_str_between(str, CHOICE_START, CHOICE_END);
            char *choices = strtok(assignmentBuffer, CHOICE_SEPARATOR);
            char choiceTypes[10];

            while (choices != NULL) {
                printf("[%c] %s\n", toupper(choices[0]), choices + 2);
                choices = strtok(NULL, CHOICE_SEPARATOR);
            }

            free(choices);
            printsep();
            init_choice();
            printf("Choosing %s\n", choice);
            printsep();
            wait();

            for (int i = 0; i < strlen(choiceTypes); i++) {
                if (choice[0] == choiceTypes[i]) {
                    continue;
                }
            }
        }

        // Init Endscreen
        if ((*(str + 1) == 'e' && *(str + 2) == 'n' && *(str + 3) == 'd')) {
            init_end_screen();
            break;
        }
    }

    fclose(filePointer);
}
