#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_HEALTH 100

typedef struct {
    char name[30];
    int health;
    int power;
} Fighter;

void print_health_bar(Fighter f) {
    printf("%-10s [", f.name);
    int bars = (f.health * 20) / MAX_HEALTH;
    for (int i = 0; i < 20; i++) {
        if (i < bars) printf("=");
        else printf(" ");
    }
    printf("] %d/%d HP\n", f.health > 0 ? f.health : 0, MAX_HEALTH);
}

int main() {
    srand((unsigned int)time(NULL));

    Fighter player = {"Jin Kazama", MAX_HEALTH, 15};
    Fighter opponent = {"Kazuya Mishima", MAX_HEALTH, 15};

    printf("==========================================\n");
    printf("        TEKKEN: C ARENA TOURNAMENT        \n");
    printf("==========================================\n\n");
    printf("Match: %s VS %s\n\n", player.name, opponent.name);

    int round = 1;

    while (player.health > 0 && opponent.health > 0) {
        printf("--- ROUND %d ---\n", round);
        print_health_bar(player);
        print_health_bar(opponent);
        printf("\nChoose your move:\n");
        printf("1. Left Jab (Quick, Safe - 10-15 DMG)\n");
        printf("2. Electric Wind God Fist (Heavy High - 20-30 DMG, 30%% Miss Chance)\n");
        printf("3. Parry & Counter (Defensive - Block & Strike back)\n");
        printf("Select (1-3): ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear invalid input
            choice = 1;
        }

        int player_dmg = 0;
        int opp_dmg = 0;
        int opp_choice = (rand() % 3) + 1; // 1: Quick, 2: Heavy, 3: Parry

        printf("\n");

        // Player Move Processing
        switch (choice) {
            case 1: // Quick Attack
                player_dmg = 10 + (rand() % 6);
                printf("> You executed a swift Left Jab!\n");
                break;
            case 2: // Heavy Attack
                if ((rand() % 100) < 70) {
                    player_dmg = 20 + (rand() % 11);
                    printf("> CRITICAL! Electric Wind God Fist connected!\n");
                } else {
                    player_dmg = 0;
                    printf("> You whiffed the EWGF!\n");
                }
                break;
            case 3: // Parry
                printf("> You took a defensive parry stance.\n");
                break;
            default:
                player_dmg = 8;
                printf("> Basic kick delivered.\n");
                break;
        }

        // Opponent Move & Interaction Processing
        if (opp_choice == 3 && choice != 3) {
            // Opponent parried player
            printf("> %s PARRIED your attack and countered!\n", opponent.name);
            player.health -= 18;
        } else if (choice == 3 && opp_choice != 3) {
            // Player parried opponent
            printf("> You successfully PARRIED %s's attack!\n", opponent.name);
            opponent.health -= 18;
        } else {
            // Normal damage resolution
            if (opp_choice == 1) {
                opp_dmg = 10 + (rand() % 6);
                printf("> %s strikes with a Demon Scissors kick!\n", opponent.name);
            } else if (opp_choice == 2) {
                if ((rand() % 100) < 65) {
                    opp_dmg = 22 + (rand() % 10);
                    printf("> %s lands a brutal Hellsweep!\n", opponent.name);
                } else {
                    opp_dmg = 0;
                    printf("> %s missed his heavy strike!\n", opponent.name);
                }
            } else {
                printf("> %s braced for impact.\n", opponent.name);
            }

            opponent.health -= player_dmg;
            player.health -= opp_dmg;
        }

        printf("------------------------------------------\n\n");
        round++;
    }

    // Match Result
    printf("==========================================\n");
    if (player.health > 0 && opponent.health <= 0) {
        printf("           YOU WIN! KO!          \n");
        printf("   %s defeated %s!   \n", player.name, opponent.name);
    } else if (opponent.health > 0 && player.health <= 0) {
        printf("           YOU LOST! KO!         \n");
        printf("   %s was defeated...    \n", player.name);
    } else {
        printf("           DOUBLE KO! DRAW!       \n");
    }
    printf("==========================================\n");

    return 0;
}
