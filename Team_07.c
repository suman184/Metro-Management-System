#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATIONS 100
#define MAX_LINES 10
#define MAX_NAME_LENGTH 20

typedef struct {
    char source[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
    int cost;
} Edge_connection;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int line_count;
    char lines[MAX_LINES][MAX_NAME_LENGTH];
} Station;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int station_count;
    char stations[MAX_STATIONS][MAX_NAME_LENGTH];
} Line;

typedef struct {
    int edge_count;
    Edge_connection edges[MAX_STATIONS];
    int station_count;
    Station stations[MAX_STATIONS];
    int line_count;
    Line lines[MAX_LINES];
} MetroNetwork;

void initialize_metro(MetroNetwork *metro);
void dfs_find_routes(MetroNetwork *metro, const char *current, const char *destination, bool visited[], char path[][MAX_NAME_LENGTH], int path_index, int total_cost);
void find_routes(MetroNetwork *metro, const char *source, const char *destination);
void display_station_info(MetroNetwork *metro, const char *station_name);
void display_intersections(MetroNetwork *metro);
void display_terminal_stations(MetroNetwork *metro);
void find_nearest_intersection(MetroNetwork *metro, const char *station_name);

void initialize_metro(MetroNetwork *metro) {
    int n, m;
    printf("Enter the number of edges: ");
    scanf("%d", &n);
    metro->edge_count = n;

    for (int i = 0; i < n; i++) {
        int cost;
        printf("Enter source, destination, and cost: ");
        while (scanf("%s %s %d", metro->edges[i].source, metro->edges[i].destination, &cost) != 3 || cost < 0) {
            printf("Invalid input. Please enter valid source, destination, and non-negative integer cost: ");
            while (getchar() != '\n');
        }
        metro->edges[i].cost = cost;
    }

    printf("Enter the number of lines: ");
    scanf("%d", &m);
    metro->line_count = m;

    for (int i = 0; i < m; i++) {
        printf("Enter line name: ");
        scanf("%s", metro->lines[i].name);
        printf("Enter the number of stations in %s: ", metro->lines[i].name);
        scanf("%d", &metro->lines[i].station_count);

        for (int j = 0; j < metro->lines[i].station_count; j++) {
            printf("Enter station name: ");
            scanf("%s", metro->lines[i].stations[j]);

            int found = 0;
            for (int k = 0; k < metro->station_count; k++) {
                if (strcmp(metro->stations[k].name, metro->lines[i].stations[j]) == 0) {
                    strcpy(metro->stations[k].lines[metro->stations[k].line_count++], metro->lines[i].name);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(metro->stations[metro->station_count].name, metro->lines[i].stations[j]);
                strcpy(metro->stations[metro->station_count].lines[0], metro->lines[i].name);
                metro->stations[metro->station_count++].line_count = 1;
            }
        }
    }
}

void dfs_find_routes(MetroNetwork *metro, const char *current, const char *destination, bool visited[], char path[][MAX_NAME_LENGTH], int path_index, int total_cost) {

    if (strcmp(current, destination) == 0) {
        for (int i = 0; i < path_index; i++) {
            printf("%s", path[i]);
            if (i < path_index - 1) printf(" -> ");
        }
        printf(", Cost: %d\n", total_cost);
        return;
    }
    
    for (int i = 0; i < metro->station_count; i++) {
        if (strcmp(metro->stations[i].name, current) == 0) {
            visited[i] = true;
            break;
        }
    }

    for (int i = 0; i < metro->edge_count; i++) {
        if (strcmp(metro->edges[i].source, current) == 0 || strcmp(metro->edges[i].destination, current) == 0) {
            const char *next_station = (strcmp(metro->edges[i].source, current) == 0) ? metro->edges[i].destination : metro->edges[i].source;
            bool already_visited = false;
            for (int j = 0; j < metro->station_count; j++) {
                if (visited[j] && strcmp(metro->stations[j].name, next_station) == 0) {
                    already_visited = true;
                    break;
                }
            }

            if (!already_visited) {
                strcpy(path[path_index], next_station);
                dfs_find_routes(metro, next_station, destination, visited, path, path_index + 1, total_cost + metro->edges[i].cost);
            }
        }
    }

    for (int i = 0; i < metro->station_count; i++) {
        if (strcmp(metro->stations[i].name, current) == 0) {
            visited[i] = false;
            break;
        }
    }
}

void find_routes(MetroNetwork *metro, const char *source, const char *destination) {
    bool visited[MAX_STATIONS] = {false};
    char path[MAX_STATIONS][MAX_NAME_LENGTH];
    strcpy(path[0], source);
    
    dfs_find_routes(metro, source, destination, visited, path, 1, 0);
}

void display_station_info(MetroNetwork *metro, const char *station_name) {
    for (int i = 0; i < metro->station_count; i++) {
        if (strcmp(metro->stations[i].name, station_name) == 0) {
            printf("Station Name: %s\nLines: ", metro->stations[i].name);
            for (int j = 0; j < metro->stations[i].line_count; j++) {
                printf("%s ", metro->stations[i].lines[j]);
            }
            printf("\nAdjacent Stations:\n");
            for (int k = 0; k < metro->edge_count; k++) {
                if (strcmp(metro->edges[k].source, station_name) == 0) {
                    printf("%s, Cost: %d\n", metro->edges[k].destination, metro->edges[k].cost);
                } else if (strcmp(metro->edges[k].destination, station_name) == 0) {
                    printf("%s, Cost: %d\n", metro->edges[k].source, metro->edges[k].cost);
                }
            }
            return;
        }
    }
    printf("Station %s not found.\n", station_name);
}

void display_intersections(MetroNetwork *metro) {
    printf("Stations serving multiple lines:\n");
    for (int i = 0; i < metro->station_count; i++) {
        if (metro->stations[i].line_count > 1) {
            printf("%s, %d\n", metro->stations[i].name, metro->stations[i].line_count);
        }
    }
}

void display_terminal_stations(MetroNetwork *metro) {
    printf("Terminal stations for each line:\n");
    for (int i = 0; i < metro->line_count; i++) {
        printf("%s: %s, %s\n", metro->lines[i].name,
               metro->lines[i].stations[0],
               metro->lines[i].stations[metro->lines[i].station_count - 1]);
    }
}

typedef struct QueueNode {
    char station[20];
    int cost;
    char path[MAX_STATIONS][20];
    int path_length;
} QueueNode;

void find_nearest_intersection(MetroNetwork *metro, const char *station_name) {
    printf("Finding nearest intersection to %s...\n", station_name);
    bool visited[MAX_STATIONS] = {false};
    QueueNode queue[MAX_STATIONS];
    int front = 0, rear = 0;

    QueueNode start = {.cost = 0, .path_length = 1};
    strcpy(start.station, station_name);
    strcpy(start.path[0], station_name);
    queue[rear++] = start;

    while (front < rear) {
        QueueNode current = queue[front++];
        for (int i = 0; i < metro->station_count; i++) {
            if (strcmp(metro->stations[i].name, current.station) == 0) {
                if (metro->stations[i].line_count > 1 && strcmp(current.station, station_name) != 0) {
                    printf("Nearest Intersection found at %s\n", current.station);
                    for (int j = 0; j < current.path_length; j++) {
                        printf("%s", current.path[j]);
                        if (j < current.path_length - 1) printf(" -> ");
                    }
                    printf(", Total Cost: %d\n", current.cost);
                    return;
                }
                visited[i] = true;
                break;
            }
        }
        for (int i = 0; i < metro->edge_count; i++) {
            if (strcmp(metro->edges[i].source, current.station) == 0 || strcmp(metro->edges[i].destination, current.station) == 0) {
                const char *neighbor = (strcmp(metro->edges[i].source, current.station) == 0) ? metro->edges[i].destination : metro->edges[i].source;
                if (!visited[i]) {
                    QueueNode next = current;
                    strcpy(next.station, neighbor);
                    strcpy(next.path[next.path_length], neighbor);
                    next.path_length++;
                    next.cost += metro->edges[i].cost;
                    queue[rear++] = next;
                }
            }
        }
    }
}

int main() {
    MetroNetwork metro;
    initialize_metro(&metro);

    int choice;
    do {
        printf("\nMetro Network Management\n");
        printf("1. Find routes\n");
        printf("2. Display station info\n");
        printf("3. Display intersections\n");
        printf("4. Display terminal stations\n");
        printf("5. Find nearest intersection\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        char source[MAX_NAME_LENGTH], destination[MAX_NAME_LENGTH];
        switch (choice) {
            case 1:
                printf("Enter source station: ");
                scanf("%s", source);
                printf("Enter destination station: ");
                scanf("%s", destination);
                find_routes(&metro, source, destination);
                break;
            case 2:
                printf("Enter station name: ");
                scanf("%s", source);
                display_station_info(&metro, source);
                break;
            case 3:
                display_intersections(&metro);
                break;
            case 4:
                display_terminal_stations(&metro);
                break;
            case 5:
                printf("Enter station name: ");
                scanf("%s", source);
                find_nearest_intersection(&metro, source);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
