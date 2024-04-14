#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10
#define MIN_SIZE 5

// Global variables
char room[MAX_SIZE][MAX_SIZE];
int character_x, character_y;
int door_x, door_y;
char direction[4] = {'a', 'd', 'w', 's'};

// Function prototypes
void draw_room(int size);
int is_game_over();
void print_room(int size);
void move_character(char move);
void game_menu();

// Main function
int main() {
    int choice, size;
    char move;

    srand(time(NULL)); // Seed the random number generator

    printf("Welcome to the 2D Puzzle Game!\n");

    do {
        game_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Get the size of the room from the user
                do {
                    printf("Enter the size of the room (%d-%d): ", MIN_SIZE, MAX_SIZE);
                    scanf("%d", &size);
                } while (size < MIN_SIZE || size > MAX_SIZE);

                // Draw the room and randomly place the character and door
                draw_room(size);
                character_x = rand() % size;
                character_y = rand() % size;
                room[character_y][character_x] = 'C';
                do {
                    door_x = rand() % size;
                    door_y = rand() % size;
                } while (door_x == character_x && door_y == character_y);
                room[door_y][door_x] = 'D';

                // Print the initial state of the room
                print_room(size);

                // Play the game until it's over
                int move_count = 0;
                while (!is_game_over()) {
                    printf("Enter your move (a=left, d=right, w=up, s=down): ");
                    scanf(" %c", &move);
                    move_character(move);
                    print_room(size);
                    move_count++;
                }


                // Check if the door and character have the same coordinates
                if (character_x == door_x && character_y == door_y) {
                    printf("Congratulations, you won the game in %d moves!\n" , move_count);
                } else {
                    printf("The door and character have the same coordinates. Starting over.\n");
                }
                break;
            case 2:
                printf("Instructions:\n");
                printf("The objective of the game is to lead the character (C) to the door (D).\n");
                printf("Use the following keys to move the character:\n");
                printf("a - move left\n");
                printf("d - move right\n");
                printf("w - move up\n");
                printf("s - move down\n");
                printf("The game ends when the character reaches the door.\n");
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}

// Function to draw the room
void draw_room(int size) {
    int x, y;
    for (y = 0; y < size; y++) {
        for (x = 0; x < size; x++) {
            room[y][x] = '|';
        }
    }
}

// Function to check if the game is over
int is_game_over() {
    if (character_x == door_x && character_y == door_y) {
        return 1;
    } else {
        return 0;
    }
}
// Function to print the room
void print_room(int size) {
    int x, y;
    for (y = 0; y < size; y++) {
        for (x = 0; x < size; x++) {
            printf("%c ", room[y][x]);
        }
        printf("\n");
    }
}

// Function to move the character
void move_character(char move) {
    int i;

    // Check if the move is valid
    for (i = 0; i < 4; i++) {
        if (move == direction[i]) {
            break;
        }
    }

    if (i == 4) {
        printf("Invalid move, please try again.\n");
        return;
    }

    // Update the character's position
    switch (move) {
        case 'a':
            if (character_x > 0) {
                room[character_y][character_x] = '|';
                character_x--;
                room[character_y][character_x] = 'C';
            }
            break;
        case 'd':
            if (character_x < MAX_SIZE - 1) {
                room[character_y][character_x] = '|';
                character_x++;
                room[character_y][character_x] = 'C';
            }
            break;
        case 'w':
            if (character_y > 0) {
                room[character_y][character_x] = '|';
                character_y--;
                room[character_y][character_x] = 'C';
            }
            break;
        case 's':
            if (character_y < MAX_SIZE - 1) {
                room[character_y][character_x] = '|';
                character_y++;
                room[character_y][character_x] = 'C';
            }
            break;
    }
}

// Function to display the game menu
void game_menu() {
    printf("\nPlease choose an option:\n");
    printf("1. Play the game\n");
    printf("2. Instructions\n");
    printf("3. Quit\n");
    printf("Enter your choice: ");
}
