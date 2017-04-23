#include <stdio.h>

// TODO: comment the line below to start debugging
// #define NDEBUG
#include <assert.h>


unsigned char RUNTIME_STATUS;

void main(void) {

    // published release
    #ifdef NDEBUG
    puts("Logged in as user-group!\n");
    #else
    puts("Welcome back, hacker!\n");
    #endif


    while (1) {

        printf("Enter RUNTIME_STATUS (1 for good, 0 for bad, otherwise generates UB): ");
        scanf("%hhu", &RUNTIME_STATUS); getchar();

        // alpha verson
        #if !(defined(NDEBUG))
        puts("\n============================================================");
        printf("[DEBUG_LOG] RUNTIME_STATUS = %hhu\n", RUNTIME_STATUS);
        puts("============================================================\n");
        #endif

        switch(RUNTIME_STATUS) {
            case 1: {
                puts("Rolling al' well!\n");
                break;
            }
            case 0: {
                puts("Somethings gone wrong...\n");
                break;
            }
            default: {
                // will show debug log
                assert(RUNTIME_STATUS==1 || RUNTIME_STATUS==0);
                // will not show debug log
                puts("Sorry to inform you that the programme has crashed...");
                return;
                // the following will not exec
                puts("Aftermath will be avoided! So this will not show!");
            }
        }
    }


}
