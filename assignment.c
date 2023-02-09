#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct magicianName { // names of team leaders, index means the number of team
    char uniqueMagicianName[1000];
};

struct player { // information about players
    char uniquePlayerName[1000];
    int teamNumber;
    int powerOfPlayer; // if equal to 0, then the player is frozen
    int visibilityOfPlayer; // 1 if visible, 0 if invisible
};

int main() {
    FILE *f1;
    FILE *f2;
    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    int numberOfTeams; // scan the number of teams and check whether it suits the restrictions, if not, we print "Invalid inputs"
    fscanf(f1,"%d", &numberOfTeams);
    if (numberOfTeams < 1 || numberOfTeams > 10) {
        fputs("Invalid inputs", f2);
        fputs("\n", f2);
        fclose(f1);
        fclose(f2);
        return 0;
    }

    // creat array of structures with names of team leaders, scan the names and check their validity
    struct magicianName MagicianNames[1000];

    for (int i = 0; i < numberOfTeams; ++i) {
        fscanf(f1, "%s", MagicianNames[i].uniqueMagicianName);
        // count the number of name letters
        int realLength = 0;
        int flag = 0;
        for (int j = 0; j < 1000; ++j) {
            if (MagicianNames[i].uniqueMagicianName[j] == '\0' || MagicianNames[i].uniqueMagicianName[j] == '\n') {
                break;
            }
            realLength++;
        }
        // check the length validity
        if (realLength < 2 || realLength > 20) {
            flag = 1;
        }

        // check letters validity (first is the capital, others should be from English alphabet
        if (MagicianNames[i].uniqueMagicianName[0] < 'A' || MagicianNames[i].uniqueMagicianName[0] > 'Z') {
            flag = 1;
        }
        for (int j = 1; j < realLength; ++j) {
            if (!isalpha(MagicianNames[i].uniqueMagicianName[j])) {
                flag = 1;
            }
        }

        // if some restriction is violated, we print "Invalid inputs" and stop our program
        if (flag == 1) {
            fputs("Invalid inputs", f2);
            fputs("\n", f2);
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }

    // scan the number of player, check if the value suits the game conditions. In case, when it is invalid, we print "Invalid inputs"
    int numberOfPlayers;
    fscanf(f1, "%d", &numberOfPlayers);
    if (numberOfPlayers < numberOfTeams || numberOfPlayers > 100) {
        fputs("Invalid inputs", f2);
        fputs("\n", f2);
        fclose(f1);
        fclose(f2);
        return 0;
    }

    // creat array of structures with information about players, scan the data and check it
    struct player Players[1000];

    for (int i = 0; i < numberOfPlayers; ++i) {
        fscanf(f1,"%s", Players[i].uniquePlayerName);
        // scan the name of player and count its length
        int realLength = 0;
        int flag = 0;
        for (int j = 0; j < 1000; ++j) {
            if (Players[i].uniquePlayerName[j] == '\0' || Players[i].uniquePlayerName[j] == '\n') {
                break;
            }
            realLength++;
        }
        //check whether the length suits the restrictions
        if (realLength < 2 || realLength > 20) {
            flag = 1;
        }
        // check if the first letter is capital and other letters are from English alphabet
        if (Players[i].uniquePlayerName[0] < 'A' || Players[i].uniquePlayerName[0] > 'Z') {
            flag = 1;
        }
        for (int j = 1; j < realLength; ++j) {
            if (!isalpha(Players[i].uniquePlayerName[j])) {
                flag = 1;
            }
        }
        // if the name is invalid we print it and finish the program
        if (flag == 1) {
            fputs( "Invalid inputs", f2);
            fputs("\n", f2);
            fclose(f1);
            fclose(f2);
            return 0;
        }
        // get the team number of the player and also check it
        fscanf(f1, "%d", &Players[i].teamNumber);
        if (Players[i].teamNumber < 0 || Players[i].teamNumber >= numberOfTeams) {
            flag = 1;
        }
        if (flag == 1) {
            fputs("Invalid inputs", f2);
            fputs("\n", f2);
            fclose(f1);
            fclose(f2);
            return 0;
        }
        // obtain the power of player and check the value validity
        fscanf(f1,"%d", &Players[i].powerOfPlayer);
        if (Players[i].powerOfPlayer < 0 || Players[i].powerOfPlayer > 1000) {
            flag = 1;
        }
        if (flag == 1) {
            fputs( "Invalid inputs", f2);
            fputs("\n", f2);
            fclose(f1);
            fclose(f2);
            return 0;
        }
        // scan the visibility of player, check its correctness and convert in into number representation
        char visibHero[1000];
        char visibTrue[] = "True";
        char visibFalse[] = "False";
        fscanf(f1, "%s", visibHero);
        if (strcmp(visibHero, visibTrue) == 0) {
            Players[i].visibilityOfPlayer = 1;
        }
        else if (strcmp(visibHero, visibFalse) == 0) {
            Players[i].visibilityOfPlayer = 0;
        }
        else {
            flag = 1;
        }
        if (flag == 1) {
            fputs( "Invalid inputs", f2);
            fputs("\n", f2);
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }


    int numberOfSuperPlayers = 0;
    int sequenceOfActions = -1; // create a variable to count actions, -1 is because the file contains '\n' after all actions, so the real amount of actions is one less
    while (!feof(f1)) {
        char action[1000];
        fscanf(f1, "%s", action);

        char checkActionSuper[] = "super";
        char checkActionFlip[] = "flip_visibility";
        char checkActionAttack[] = "attack";
        char checkActionHeal[] = "heal";

        // flip_visibility
        if (strcmp(action, checkActionFlip) == 0) {
            char nameForFlip[1000];
            fscanf(f1, "%s", nameForFlip);
            int indexOfPlayer = -1;
            // we go through all the players and look for the needed
            for (int i = 0; i < numberOfPlayers; ++i) {
                if (strcmp(nameForFlip, Players[i].uniquePlayerName) == 0) {
                    indexOfPlayer = i;
                }
            }
            if (indexOfPlayer == -1) { // if the player is not found, then the name is invalid, so we finish the game
                fclose(f2);
                FILE *f2;
                f2 = fopen("output.txt", "w");
                fputs("Invalid inputs", f2);
                fputs("\n", f2);
                fclose(f1);
                fclose(f2);
                return 0;
            }
            // if the player is found, then we check whether it can play
            else if (Players[indexOfPlayer].powerOfPlayer == 0) {
                fputs("This player is frozen", f2);
                fputs("\n", f2);
            }
            else {
                // if it can play we change its visibility
                if (Players[indexOfPlayer].visibilityOfPlayer == 1) {
                    Players[indexOfPlayer].visibilityOfPlayer = 0;
                }
                else if (Players[indexOfPlayer].visibilityOfPlayer == 0) {
                    Players[indexOfPlayer].visibilityOfPlayer = 1;
                }
            }
        }

        // attack
        if (strcmp(checkActionAttack, action) == 0) {
            char nameI[1000];
            char nameJ[1000];
            fscanf(f1, "%s", nameI);
            fscanf(f1, "%s", nameJ);
            int indexPlayerI = -1;
            int indexPlayerJ = -1;
            // look for the necessary players and remember their indexes
            for (int i = 0; i < numberOfPlayers; ++i) {
                if (strcmp(nameI, Players[i].uniquePlayerName) == 0) {
                    indexPlayerI = i;
                }
                if (strcmp(nameJ, Players[i].uniquePlayerName) == 0) {
                    indexPlayerJ = i;
                }
            }
            // if the player do not exist in the game, we stop the program
            if (indexPlayerI == -1 || indexPlayerJ == -1) {
                fclose(f2);
                FILE *f2;
                f2 = fopen("output.txt", "w");
                fputs("Invalid inputs", f2);
                fputs("\n", f2);
                fclose(f1);
                fclose(f2);
                return 0;
            }
            // now we check if these players can take part in attack
            else if (Players[indexPlayerI].visibilityOfPlayer == 0) {
                fputs("This player can't play", f2);
                fputs("\n", f2);
            }
            else if (Players[indexPlayerI].powerOfPlayer == 0) {
                fputs("This player is frozen", f2);
                fputs("\n", f2);
            }
            // and if the can we follow the rules of attack
            else if (Players[indexPlayerJ].visibilityOfPlayer == 0) {
                Players[indexPlayerI].powerOfPlayer = 0;
            }
            else if (Players[indexPlayerI].powerOfPlayer > Players[indexPlayerJ].powerOfPlayer) {
                Players[indexPlayerI].powerOfPlayer = (Players[indexPlayerI].powerOfPlayer + (Players[indexPlayerI].powerOfPlayer - Players[indexPlayerJ].powerOfPlayer));
                Players[indexPlayerJ].powerOfPlayer = 0;
                if (Players[indexPlayerI].powerOfPlayer > 1000) { // the power can't be more than 1000, we check it
                    Players[indexPlayerI].powerOfPlayer = 1000;
                }
            }
            else if (Players[indexPlayerI].powerOfPlayer < Players[indexPlayerJ].powerOfPlayer) {
                Players[indexPlayerJ].powerOfPlayer = (Players[indexPlayerJ].powerOfPlayer + (Players[indexPlayerJ].powerOfPlayer - Players[indexPlayerI].powerOfPlayer));
                Players[indexPlayerI].powerOfPlayer = 0;
                if (Players[indexPlayerJ].powerOfPlayer > 1000) { // the power can't be more than 1000, we check it
                    Players[indexPlayerJ].powerOfPlayer = 1000;
                }
            }
            else if (Players[indexPlayerI].powerOfPlayer == Players[indexPlayerJ].powerOfPlayer) {
                Players[indexPlayerI].powerOfPlayer = 0;
                Players[indexPlayerJ].powerOfPlayer = 0;
            }
        }

        // heal
        if (strcmp(action, checkActionHeal) == 0) {
            char nameOfI[1000];
            char nameOfJ[1000];
            int indexOfPlayerI = -1;
            int indexOfPlayerJ = -1;
            // scan the names of players to heal and find their indexes
            fscanf(f1, "%s", nameOfI);
            fscanf(f1, "%s", nameOfJ);
            for (int i = 0; i < numberOfPlayers; ++i) {
                if (strcmp(nameOfI, Players[i].uniquePlayerName) == 0) {
                    indexOfPlayerI = i;
                }
                if (strcmp(nameOfJ, Players[i].uniquePlayerName) == 0) {
                    indexOfPlayerJ = i;
                }
            }
            // if the names are invalid, we finish the game
            if (indexOfPlayerI == -1 || indexOfPlayerJ == -1) {
                fclose(f2);
                FILE *f2;
                f2 = fopen("output.txt", "w");
                fputs("Invalid inputs", f2);
                fputs("\n", f2);
                fclose(f1);
                fclose(f2);
                return 0;
            }
            // check whether the players can participate in heal
            else if (Players[indexOfPlayerI].visibilityOfPlayer == 0) {
                fputs("This player can't play", f2);
                fputs("\n", f2);
            }
            else if (Players[indexOfPlayerI].powerOfPlayer == 0) {
                fputs("This player is frozen", f2);
                fputs("\n", f2);
            }
            else if (Players[indexOfPlayerI].teamNumber != Players[indexOfPlayerJ].teamNumber) {
                fputs("Both players should be from the same team", f2);
                fputs("\n", f2);
            }
            else if (indexOfPlayerI == indexOfPlayerJ) {
                fputs("The player cannot heal itself", f2);
                fputs("\n", f2);
            }
            // and if they can, we do heal action
            else if (Players[indexOfPlayerI].powerOfPlayer % 2 == 0) {
                Players[indexOfPlayerJ].powerOfPlayer = Players[indexOfPlayerJ].powerOfPlayer + (Players[indexOfPlayerI].powerOfPlayer / 2);
                Players[indexOfPlayerI].powerOfPlayer = Players[indexOfPlayerI].powerOfPlayer / 2;
            }
            else if (Players[indexOfPlayerI].powerOfPlayer % 2 == 1) {
                Players[indexOfPlayerI].powerOfPlayer = Players[indexOfPlayerI].powerOfPlayer + 1;
                Players[indexOfPlayerJ].powerOfPlayer = Players[indexOfPlayerJ].powerOfPlayer + (Players[indexOfPlayerI].powerOfPlayer / 2);
                Players[indexOfPlayerI].powerOfPlayer = Players[indexOfPlayerI].powerOfPlayer / 2;
            }
            // the power of player still cannot increase 1000
            if (Players[indexOfPlayerJ].powerOfPlayer > 1000) {
                Players[indexOfPlayerJ].powerOfPlayer = 1000;
            }
            if (Players[indexOfPlayerI].powerOfPlayer > 1000) {
                Players[indexOfPlayerI].powerOfPlayer = 1000;
            }

        }

        // super
        if (strcmp(action, checkActionSuper) == 0) {
            char nameOfI[1000];
            char nameOfJ[1000];
            int indexOfI = -1;
            int indexOfJ = -1;
            // scan the names and check them in the array of players
            fscanf(f1, "%s", nameOfI);
            fscanf(f1, "%s", nameOfJ);
            for (int i = 0; i < numberOfPlayers; ++i) {
                if (strcmp(nameOfI, Players[i].uniquePlayerName) == 0) {
                    indexOfI = i;
                }
                if (strcmp(nameOfJ, Players[i].uniquePlayerName) == 0) {
                    indexOfJ = i;
                }
            }
            // if the players are not found, we stop the game and print "Invalid inputs"
            if (indexOfI == -1 || indexOfJ == -1) {
                fclose(f2);
                FILE *f2;
                f2 = fopen("output.txt", "w");
                fputs("Invalid inputs", f2);
                fputs("\n", f2);
                fclose(f1);
                fclose(f2);
                return 0;
            }
            // if the players exist, we check whether they can play
            else if (Players[indexOfI].visibilityOfPlayer == 0) {
                fputs("This player can't play", f2);
                fputs("\n", f2);
            }
            else if (Players[indexOfI].powerOfPlayer == 0) {
                fputs("This player is frozen", f2);
                fputs("\n", f2);
            }
            else if (Players[indexOfI].teamNumber != Players[indexOfJ].teamNumber) {
                fputs("Both players should be from the same team", f2);
                fputs("\n", f2);
            }
            else if (indexOfI == indexOfJ) {
                fputs("The player cannot do super action with itself", f2);
                fputs("\n", f2);
            }
            else {
                // we create the name of the new player
                char numberOfSuper[100];
                sprintf(numberOfSuper, "%d", numberOfSuperPlayers); // convert the int number of super player into char 
                char nameOfSuper[900];
                for (int k = 0; k < 900; ++k) {
                    nameOfSuper[k] = '\0';
                }
                nameOfSuper[0] = 'S';
                nameOfSuper[1] = '_';
                strcat(nameOfSuper, numberOfSuper);
                // create the power of the new super player from the two players
                int newPowerOfSuper = Players[indexOfI].powerOfPlayer + Players[indexOfJ].powerOfPlayer;
                if (newPowerOfSuper > 1000) {
                    newPowerOfSuper = 1000;
                }
                // on the index of indexOfI player participating in super, we create the new super player
                for (int k = 0; k < 1000; ++k) {
                    Players[indexOfI].uniquePlayerName[k] = '\0';
                }
                strcat(Players[indexOfI].uniquePlayerName, nameOfSuper);
                Players[indexOfI].powerOfPlayer = newPowerOfSuper;
                Players[indexOfI].visibilityOfPlayer = 1;

                numberOfSuperPlayers = numberOfSuperPlayers + 1; // increase the number of super players because of the new one
                // and we delete the indexOfJ player, participating in super, with the new, never existing name 
                char newNameOfDeletedPlayer[900];
                for (int k = 0; k < 900; ++k) {
                    Players[indexOfJ].uniquePlayerName[k] = '\0';
                    newNameOfDeletedPlayer[k] = 'A';
                }
                strcat(Players[indexOfJ].uniquePlayerName, newNameOfDeletedPlayer);
                Players[indexOfJ].powerOfPlayer = 0;
            }
        }
        // check whether the action name was correct, if not, this case is "Invalid inputs"
        if (strcmp(action, checkActionAttack) != 0 && strcmp(action, checkActionSuper) != 0 && strcmp(action, checkActionHeal) != 0 &&
            strcmp(action, checkActionFlip) != 0 && !feof(f1)) {
            fclose(f2);
            FILE *f2;
            f2 = fopen("output.txt", "w");
            fputs("Invalid inputs", f2);
            fputs("\n", f2);
            fclose(f1);
            fclose(f2);
            return 0;
        }

        for (int k = 0; k < 1000; ++k) { // erase the completed action
            action[k] = '\0';
        }
        // increase the number of done actions, if it increases 1000, we stop the program
        sequenceOfActions++;
        if (sequenceOfActions > 1000) {
            break;
        }
    }

    if (sequenceOfActions > 1000) { // check if the number of actions is correct
        fclose(f2);
        FILE *f2;
        f2 = fopen("output.txt", "w");
        fputs("Invalid inputs", f2);
        fputs("\n", f2);
        fclose(f1);
        fclose(f2);
        return 0;
    }

    int resultsOfPower[numberOfTeams]; // create array with the power results of game, index == team number
    for (int i = 0; i < numberOfTeams; ++i) {
        resultsOfPower[i] = 0;
    }
    for (int i = 0; i < numberOfPlayers; ++i) {
        resultsOfPower[Players[i].teamNumber] = resultsOfPower[Players[i].teamNumber] + Players[i].powerOfPlayer;
    }
    // search for the team with the best result and memorise its number
    int maxPowerLeft = -1;
    int teamWinner;
    for (int i = 0; i < numberOfTeams; ++i) {
        if (resultsOfPower[i] > maxPowerLeft) {
            maxPowerLeft = resultsOfPower[i];
            teamWinner = i;
        }
    }
    // also check whether there is only one best team
    int checkTie = 0;
    for (int i = 0; i < numberOfTeams; ++i) {
        if (resultsOfPower[i] == maxPowerLeft) {
            checkTie = checkTie + 1;
        }
    }
    // if more than one, then it is a tie
    if (checkTie > 1) {
        fputs("It's a tie", f2);
        fputs("\n", f2);
    }
    else { // if only one, we announce the winner
        fputs("The chosen wizard is ", f2);
        fputs(MagicianNames[teamWinner].uniqueMagicianName, f2);
        fputs("\n", f2);

    }
    fclose(f1);
    fclose(f2);
    return 0;
}
