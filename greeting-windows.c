#include <stdio.h>
#include <strings.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

void art()
{
    printf("\t\t############################################\n");
    printf("\t\t#__        __   _                          #\n");
    printf("\t\t#\\ \\      / /__| | ___ ___  _ __ ___   ___ #\n");
    printf("\t\t# \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\#\n");
    printf("\t\t#  \\ V  V /  __/ | (_| (_) | | | | | |  __/#\n");
    printf("\t\t#   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|#\n");
    printf("\t\t############################################\n");
}

void clearScreen()
{
    system("cls");
}

void systemTime()
{
    time_t now;
    time(&now);

    printf("The computer thinks it's %ld\n", now);
    printf("%s", ctime(&now));
}

int menuOption()
{
    int userInput;
    printf("\t====MENU====\n");
    printf("1) vscode\n2) browser\n>");
    scanf("%d", &userInput);

    switch (userInput)
    {
    case 1:
        system("code");
        break;
    case 2:
        system("start brave");
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    Sleep(1000);
    if (argc > 1 && strcmp(argv[1], "-run") == 0)
    {
        art();
        Sleep(1000);
        clearScreen();
        menuOption();
        return 0;
    }
    
    char modulePath[MAX_PATH];
    GetModuleFileNameA(NULL, modulePath, MAX_PATH);

    char commandLine[1024];
    snprintf(commandLine, sizeof(commandLine), "powershell.exe -NoExit -Command \"& '%s' -run\"", modulePath);

    STARTUPINFO startUp = {0};
    PROCESS_INFORMATION pInfo = {0};
    startUp.cb = sizeof(startUp);

    BOOL winPS = CreateProcessA(
        NULL,
        commandLine,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &startUp,
        &pInfo
    );
    
    if (!winPS)
    {
        printf("Failed to lauch PowerShell. Error: %lu\n", GetLastError());
        return 1;
    }

    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);
    return 0;

}
