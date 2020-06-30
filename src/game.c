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

    PlaySound(".\\src\\sound\\song.wav", NULL, SND_ASYNC);

    int line_size = 1024;
    char buffer[100];
    int nestLevel = 0;
    int inChoice = 0;

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

                printf("%s: \"%s\"\n", quoteBuffer + 2, quote);
            }
        }

        // Execute Function
        if (*(str + 1) == 'f') {
            char *f1, *f2;
            f1 = strstr(str, TYPE_START) + 1;

            if (f1) {
                f2 = strstr(f1, TYPE_END);

                char funcBuffer[128];
                snprintf(funcBuffer, sizeof(buffer), "%.*s", f2 - f1, f1);

                printf("%s", funcBuffer + 2);
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
                    char* choices = strtok(assignmentBuffer, CHOICE_SEPARATOR);

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
    
    /*
    char name[MAX_STRING_CHARS];
    char location[MAX_STRING_CHARS];
    char choiceAnswer[50];

    // printf(node);

    printsep();
    printf("  ________            ______                      __         \n");
    printf(" /_  __/ /_  ___     /_  __/________ __   _____  / /__  _____\n");
    printf("  / / / __ \\/ _ \\     / / / ___/ __ `/ | / / _ \\/ / _ \\/ ___/\n");
    printf(" / / / / / /  __/    / / / /  / /_/ /| |/ /  __/ /  __/ /    \n");
    printf("/_/ /_/ /_/\\___/    /_/ /_/   \\__,_/ |___/\\___/_/\\___/_/     \n");
    printf("                      A Short Story by Maarten Wolfsen\n\n");
    printf("---- Main Menu -------------------------------------\n");
    printf("[A] Start Game.\n");
    printf("[B] Exit.\n");
    printsep();

    init_choice();

    if (strcmp(choice, "B") == 0) {
        printf("Exiting Game...\n");
        exit(0);
    } else {
        printnpcc("Bartender", "Hello weary Traveler. You have been on quite the Journey, what is your name?");

        fgets(name, MAX_STRING_CHARS, stdin);
        strrtn(name);
        printnpcc(name, name);
        wait();

        sprintf(buffer, "So %s... I have never seen you before...", name);
        printnpcc("Bartender", buffer);
        printnpcc("Bartender", "Where are you from?");

        fgets(location, MAX_STRING_CHARS, stdin);
        strrtn(location);
        printnpcc(name, location);
        wait();

        sprintf(buffer, "Ah... %s... From afar I see...", location);
        printnpcc("Bartender", buffer);
        printnpcc("Bartender", "Make yourself at home, ask me if you need anything.");

        printsep();
        printf("---- What will you do? -----------------------------\n");
        printf("[A] Grab a drink and sit at the bar.\n");
        printf("[B] Grab a drink and sit at a empty table.\n");
        printf("[C] Grab a drink and sit at a table beside someone.\n");
        printsep();

        init_choice();
        
        if (strcmp(choice, "A") == 0) {
            printf("You order a drink and go sit at the bar.\n");
            printf("After a short while, a stranger sits right next to you and orders a beer.\n");
            printf("You notice his hand is torn open and bleeding.\n");
            printnpcc("Bartender", "How are you going to pay for that beer, stranger?");
            printf("It seems that the stranger does not have enough money to pay for the beer.\n");

            printsep();
            printf("---- What will you do? -----------------------------\n");
            printf("[A] Pay for his beer.\n");
            printf("[B] Don't pay for his beer.\n");
            printsep();

            init_choice();
            
            if (strcmp(choice, "A") == 0) {
                printnpcc("Stranger", "Thank you Traveler...");
            }
        }
    }*/
}
