#include "mastermind.h"


int main(int argc, char** argv) {
    char* st_cd = calloc(sizeof(char), 4 + 1);
    int mx_atmp = 10;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            strncpy(st_cd, argv[i + 1], 4);
            st_cd[4] = '\0';
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            mx_atmp = atoi(argv[i + 1]);
        }
    }

    if (strlen(st_cd) == 0) {
        srand(time(NULL));
        random_code(st_cd);
    }

    char user_guess[4 + 1];
    int well_placed, misplaced;
    int rounds = 0;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    for (; rounds < mx_atmp; rounds++) {
        printf("---\nRound %d\n>", rounds);

        if (read(0, user_guess, 4 + 1) == -1) {
            printf("Error reading input.\n");
            return 1;
        }

        user_guess[4] = '\0';

        if (!is_input_valid(user_guess)) {
            printf("Wrong input!\n");
            continue;
        }

        evaluate_guess(user_guess, st_cd, &well_placed, &misplaced);

        if (well_placed == 4) {
            printf("Congratz! You did it!\n");
            return 0;
        }

        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
    }

    printf("---\nGame over. You didn't find the secret code.\n");

    return 0;
}
