#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#pragma comment(lib, "winmm.lib")

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

int main()
{
    const char *filename = "./src/story.m";
    FILE *filePointer = fopen(filename, "r");

    if (!filePointer) {
        printf("Game Story could not be loaded.");
        return 0;
    }

    //PlaySound(".\\src\\sound\\song.wav", NULL, SND_ASYNC);

    int line_size = 1024;
    int nestLevel = 0;
    int inChoice = 0;
    char buffer[BUFFER_LENGTH];
    char name[MAX_STRING_CHARS];
    char location[MAX_STRING_CHARS];

    while (fgets(buffer, BUFFER_LENGTH, filePointer)) {
        char *str = buffer + (4 * nestLevel);

        if (inChoice == 1) {
            if (toupper(*(str + 1)) != choice[0]) {
                continue;
            } else {
                inChoice = 0;
            }
        }

        if (*str == '#' || (*str != '[' && *str != ' ')) continue;

        // Print line
        if (*(str + 1) == 'p') printf("%s", str + 3);

        // Quote line
        if (*(str + 1) == 'q') {
            char *q1, *q2;
            q1 = strstr(str, TYPE_START) + 1;

            if (q1) {
                q2 = strstr(q1, TYPE_END);

                char quoteBuffer[128];
                snprintf(quoteBuffer, sizeof(buffer), "%.*s", q2 - q1, q1);

                char *quote = str + (strlen(quoteBuffer) + 2);
                strrtn(quote);

                printnpcc(quoteBuffer + 2, quote);
            }
        }

        // Execute Function
        // TODO: Find better function execution method
        if (*(str + 1) == 'f') {
            char *f1, *f2;
            f1 = strstr(str, TYPE_START) + 1;

            if (f1) {
                f2 = strstr(f1, TYPE_END);

                char funcBuffer[128];
                snprintf(funcBuffer, sizeof(buffer), "%.*s", f2 - f1, f1);

                char *function = funcBuffer + 2;

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
        }

        // Increase Nest Level
        if (*(str + 1) == 'z' || (*(str + 1) == 'e' && *(str + 2) == 'x') || *(str + 1) == 'a' || *(str + 1) == 'b' || *(str + 1) == 'c') nestLevel++;

        // Activate Choice Mode
        if (*(str + 1) == 'z') {
            printsep();
            printf("---- What will you do? -----------------------------\n");

            // Separate Choices
            char *p1, *p2;
            p1 = strstr(str, CHOICE_START) + 1;

            if (p1) {
                p2 = strstr(p1, CHOICE_END);

                if (p2) {
                    char assignmentBuffer[128];
                    char choiceTypes[10];
                    snprintf(assignmentBuffer, sizeof(buffer), "%.*s\n", p2 - p1, p1);
                    char *choices = strtok(assignmentBuffer, CHOICE_SEPARATOR);

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

                        inChoice = 1;
                    }
                }
            }
        }

        // Init Endscreen
        if ((*(str + 1) == 'e' && *(str + 2) == 'n' && *(str + 3) == 'd')) {
            printf("The End");
            break;
        }
    }

    fclose(filePointer);
}
