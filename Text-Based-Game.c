#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROOMS 5
#define MAX_ITEMS 10
#define MAX_INVENTORY 5

typedef struct {
    int id;
    char name[50];
    char description[200];
    int exits[4]; // north, south, east, west
    int item_id;
} Room;

typedef struct {
    int id;
    char name[50];
    char description[100];
} Item;

typedef struct {
    int items[MAX_INVENTORY];
    int count;
} Inventory;

Room rooms[MAX_ROOMS];
Item items[MAX_ITEMS];
Inventory inventory = {0};

void init_game() {
    // Room 0: Entrance
    rooms[0].id = 0;
    strcpy(rooms[0].name, "Entrance");
    strcpy(rooms[0].description, "You stand at the entrance of an ancient mansion.");
    rooms[0].exits[0] = 1; // north
    rooms[0].exits[1] = -1;
    rooms[0].exits[2] = -1;
    rooms[0].exits[3] = -1;
    rooms[0].item_id = 0;

    // Room 1: Hallway
    rooms[1].id = 1;
    strcpy(rooms[1].name, "Hallway");
    strcpy(rooms[1].description, "A long hallway with portraits on the walls.");
    rooms[1].exits[0] = 2; // north
    rooms[1].exits[1] = 0; // south
    rooms[1].exits[2] = 3; // east
    rooms[1].exits[3] = -1;
    rooms[1].item_id = 1;

    // Room 2: Library
    rooms[2].id = 2;
    strcpy(rooms[2].name, "Library");
    strcpy(rooms[2].description, "Shelves of dusty books surround you.");
    rooms[2].exits[0] = -1;
    rooms[2].exits[1] = 1; // south
    rooms[2].exits[2] = -1;
    rooms[2].exits[3] = -1;
    rooms[2].item_id = 2;

    // Room 3: Kitchen
    rooms[3].id = 3;
    strcpy(rooms[3].name, "Kitchen");
    strcpy(rooms[3].description, "An old kitchen with a rusty stove.");
    rooms[3].exits[0] = 4; // north
    rooms[3].exits[1] = -1;
    rooms[3].exits[2] = -1;
    rooms[3].exits[3] = 1; // west
    rooms[3].item_id = 3;

    // Room 4: Treasure Room
    rooms[4].id = 4;
    strcpy(rooms[4].name, "Treasure Room");
    strcpy(rooms[4].description, "Golden artifacts line the shelves! You found the treasure!");
    rooms[4].exits[0] = -1;
    rooms[4].exits[1] = 3; // south
    rooms[4].exits[2] = -1;
    rooms[4].exits[3] = -1;
    rooms[4].item_id = 4;

    // Items
    strcpy(items[0].name, "Rusty Key");
    strcpy(items[0].description, "A key that might open something.");
    strcpy(items[1].name, "Torch");
    strcpy(items[1].description, "A lit torch for illumination.");
    strcpy(items[2].name, "Book");
    strcpy(items[2].description, "A mysterious book with strange symbols.");
    strcpy(items[3].name, "Bread");
    strcpy(items[3].description, "Old bread, still edible.");
    strcpy(items[4].name, "Golden Crown");
    strcpy(items[4].description, "The legendary treasure of the mansion!");
}

void display_room(int room_id) {
    if (room_id < 0 || room_id >= MAX_ROOMS) return;
    
    printf("\n=== %s ===\n", rooms[room_id].name);
    printf("%s\n", rooms[room_id].description);
    
    if (rooms[room_id].item_id >= 0) {
        printf("You see: %s\n", items[rooms[room_id].item_id].name);
    }
    
    printf("\nExits: ");
    if (rooms[room_id].exits[0] != -1) printf("[N]orth ");
    if (rooms[room_id].exits[1] != -1) printf("[S]outh ");
    if (rooms[room_id].exits[2] != -1) printf("[E]ast ");
    if (rooms[room_id].exits[3] != -1) printf("[W]est ");
    printf("\n");
}

void take_item(int room_id) {
    if (rooms[room_id].item_id == -1) {
        printf("Nothing to take here.\n");
        return;
    }
    
    if (inventory.count >= MAX_INVENTORY) {
        printf("Inventory full!\n");
        return;
    }
    
    inventory.items[inventory.count++] = rooms[room_id].item_id;
    printf("Took: %s\n", items[rooms[room_id].item_id].name);
    rooms[room_id].item_id = -1;
}

void show_inventory() {
    if (inventory.count == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    
    printf("\n=== Inventory ===\n");
    for (int i = 0; i < inventory.count; i++) {
        printf("%d. %s - %s\n", i + 1, items[inventory.items[i]].name, 
               items[inventory.items[i]].description);
    }
}

int main() {
    init_game();
    int current_room = 0;
    char input[50];
    int running = 1;

    printf("Welcome to the Mansion Adventure!\n");
    printf("Type 'help' for commands.\n");

    while (running) {
        display_room(current_room);
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "n") == 0 && rooms[current_room].exits[0] != -1) {
            current_room = rooms[current_room].exits[0];
        } else if (strcmp(input, "s") == 0 && rooms[current_room].exits[1] != -1) {
            current_room = rooms[current_room].exits[1];
        } else if (strcmp(input, "e") == 0 && rooms[current_room].exits[2] != -1) {
            current_room = rooms[current_room].exits[2];
        } else if (strcmp(input, "w") == 0 && rooms[current_room].exits[3] != -1) {
            current_room = rooms[current_room].exits[3];
        } else if (strcmp(input, "take") == 0) {
            take_item(current_room);
        } else if (strcmp(input, "i") == 0) {
            show_inventory();
        } else if (strcmp(input, "quit") == 0) {
            running = 0;
        } else if (strcmp(input, "help") == 0) {
            printf("Commands: n/s/e/w (move), take (item), i (inventory), quit\n");
        } else {
            printf("Unknown command.\n");
        }

        if (current_room == 4) {
            printf("\n*** You found the treasure! You win! ***\n");
            running = 0;
        }
    }

    return 0;
}