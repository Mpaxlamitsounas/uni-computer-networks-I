#include <stdio.h>
#include <stdlib.h>

#define VERTICES 6
#define EDGES 8
#define INF INT_MAX
#define TRUE 1
#define FALSE 0

void dijkstra(int comm_arr[VERTICES+1][VERTICES+1], int start);
void bellmanFord(int comm_arr[VERTICES+1][VERTICES+1], int start);
void update_neighbours_dijkstra(int vertex, int comm_arr[VERTICES+1][VERTICES+1], int rout[], int from[], const int P[]);
int update_neighbours_BF(int vertex, int comm_arr[VERTICES+1][VERTICES+1], const int rout[], int temp_rout[], int from[]);
int find_minimum(const int rout[], const int P[]);
void print_table(int h, int rout[], int from[], const int P[], const char algorithm);
void copy(const int arr1[], int arr2[], int N);

int main (int argc, char **argv) {

    // Opens file for reading
    FILE *file = fopen("edges.txt", "r");

    int comm_arr[VERTICES+1][VERTICES+1]; // communication_array, πίνακα γειτνίασης
    // Initialises distanes between vertices to infinity
    for (int i = 0; i <= VERTICES; i++) {
        for (int j = 0; j <= VERTICES; j++)
            comm_arr[i][j] = INF; {
        }
    }
    
    // Reads from file the edges in the graph and updates comm_arr
    int vertex_1, vertex_2, weight;
    for (int i = 1; i <= EDGES; i++) {
        fscanf(file, "%d %d %d", &vertex_1, &vertex_2, &weight);
        comm_arr[vertex_1][vertex_2] = weight;
        comm_arr[vertex_2][vertex_1] = weight;
    }

    // Reads starting vertex from user
    int start;
    while (1) {
        printf("Input starting vertex:\n? ");
        scanf("%d", &start);
        puts("");
        if (start <= VERTICES && start > 0)
            break;
        else
            printf("Starting vertex must be between 1 and %d included\n", VERTICES);
    }

    // Reads which algorithm(s) to use
    int choice;
    puts("Select algorithm");
    puts("1 - Dijkstra");
    puts("2 - Bellman-Ford");
    puts("3 - Both");
    printf("? ");
    scanf("%d", &choice);
    // system("cls");

    switch(choice) {
        case 1: dijkstra(comm_arr, start); break;
        case 2: bellmanFord(comm_arr, start); break;
        case 3: dijkstra(comm_arr, start); bellmanFord(comm_arr, start); break;
        default: puts("Invalid selection"); return 1;
    }

    fclose(file);
    puts("");
    system("pause");
    return 0;
}

void dijkstra(int comm_arr[VERTICES+1][VERTICES+1], int start) {

    // rout == routing distances, from == previous in series vertex, P == set P that has been explored
    int rout[VERTICES+1], from[VERTICES+1], P[VERTICES+1];
    int h = 0;

    // Initialises distances from start to all vertices except start to infinity, previous in series "0", and not in set
    for (int i = 0; i <= VERTICES; i++) {
        rout[i] = INF;
        from[i] = 0;
        P[i] = FALSE; 
    }
    rout[start] = 0;
    from[start] = start; // The previous from start is start
    
    puts("");
    // Prints header info for table
    puts("Dijkstra");
    printf("h\t");
    for (int i = 1; i <= VERTICES; i++)
        printf("%d\t", i);
    printf("P\n");

    // Starts from start and while not all nodes have been visited
    int current = start;
    while (h != VERTICES) {
        print_table(h, rout, from, P, 'D'); // Prints how the current table looks like
        h++; // Moves to next phase
        P[current] = TRUE; // Adds current vertex to P
        update_neighbours_dijkstra(current, comm_arr, rout, from, P); // Update the cost of current's neighbours
        current = find_minimum(rout, P); // Find the next vertex to visit, which has the minimum weight
    }
    print_table(h, rout, from, P, 'D');

    // Prints header for routing table
    printf("\nRouting Table (%d)\n", start);
    puts("Dest\tNext\tCost");
    // For every vertex
    for (int i = 1; i <= VERTICES; i++) {
        int next = i;
        while (from[next] != start) // Moves back through the path to find next vertex from start
            next = from[next];
        printf("%d\t%d\t%d\n", i, next, rout[i]); // Prints Next and Cost based on Destination
    }   
}

void update_neighbours_dijkstra(int vertex, int comm_arr[VERTICES+1][VERTICES+1], int rout[], int from[], const int P[]) {

    for (int neighbour = 1; neighbour <= VERTICES; neighbour++) {
        if (comm_arr[vertex][neighbour] != INF) { // If it's not infinity (operations near max range may cause integer overflow)
            // If not in P, and the path from start to vertex plus vertex to neighbour is shorter than current best
            if (rout[vertex] + comm_arr[vertex][neighbour] < rout[neighbour] && P[neighbour] == FALSE) {
                rout[neighbour] = rout[vertex] + comm_arr[vertex][neighbour]; // Update best path length
                from[neighbour] = vertex; // Update previous vertex in series
            }
        }
    }
}

int find_minimum(const int rout[], const int P[]) {

    int min_weight = INF, min_vertex = -1;

    for (int i = 1; i <= VERTICES; i++) { // Searches for shortest path from star to vertex, while vertex has not been explored
        if (rout[i] < min_weight && P[i] == FALSE) {
            min_weight = rout[i];
            min_vertex = i;
        }
    }

    // Returns the index of closest not yet explored vertex
    return min_vertex;
}

void bellmanFord(int comm_arr[VERTICES+1][VERTICES+1], int start) {

    // rout == routing distances, from == previous in series vertex
    int rout[VERTICES+1], from[VERTICES+1];
    int h = 0;

    // Initialises distances from start to all vertices except start to infinity, previous in series "0"
    for (int i = 0; i <= VERTICES; i++) {
        rout[i] = INF;
        from[i] = 0;   
    }
    rout[start] = 0;
    from[start] = start; // The previous from start is start
    
    puts("");
    // Prints header info for table
    puts("Bellman-Ford");
    printf("h\t");
    for (int i = 1; i <= VERTICES; i++)
        printf("%d\t", i);
    printf("\n");

    // Loops until no change is made
    int changed = TRUE;
    while (changed) {

        // New distances are written to temp_rout then to rout
        int temp_rout[VERTICES+1];
        copy(rout, temp_rout, VERTICES);

        changed = FALSE;
        print_table(h, rout, from, 0, 'B');
        h++;

        // For every vertex, checks if there is a shorter path
        for (int vertex = 1; vertex <= VERTICES; vertex++) {
            int result = update_neighbours_BF(vertex, comm_arr, rout, temp_rout, from);
            changed = changed || result; // If a change is made, the flag is kept true
        }

        copy(temp_rout, rout, VERTICES);
    }
    print_table(h, rout, from, 0, 'B');

    printf("\nRouting Table (%d)\n", start);
    puts("Dest\tNext\tCost");
    for (int i = 1; i <= VERTICES; i++) {
        int next = i;
        while (from[next] != start)
            next = from[next];
        printf("%d\t%d\t%d\n", i, next, rout[i]);
    }
}

int update_neighbours_BF(int vertex, int comm_arr[VERTICES+1][VERTICES+1], const int rout[], int temp_rout[], int from[]) {

    int changed = FALSE;

    for (int neighbour = 1; neighbour <= VERTICES; neighbour++) {
        if (comm_arr[vertex][neighbour] != INF && rout[neighbour] != INF) { // If it's not infinity (operations near max range may cause integer overflow)
            // If the path from start to vertex plus vertex to neighbour is shorter than current best
            if (rout[neighbour] + comm_arr[neighbour][vertex] < rout[vertex]) {
                changed = TRUE;
                temp_rout[vertex] = rout[neighbour] + comm_arr[neighbour][vertex];
                from[vertex] = neighbour;
            }
        }
    }

    return changed;
}

void print_table(int h, int rout[], int from[], const int P[], const char algorithm) {

    // Prints phase/step
    printf("%d", h);

    // Prints distance from start to i, and the previous in series
    for (int i = 1; i <= VERTICES; i++) {
        if (rout[i] == INF)
            printf("\t∞(%d)", from[i]);
        else
            printf("\t%d(%d)", rout[i], from[i]);
    }

    // If Dijkstra's algorithm is used, also prints elements in set P
    if (algorithm == 'D') {
        int flag = 1;
        printf("\t");
        for (int i = 1; i <= VERTICES; i++) {
            if (P[i] != 0) {
                if (flag != 1)
                    printf(",");
                printf("%d", i);
                flag = 0; 
            }
        }
    }
    printf("\n");
}

void copy(const int arr1[], int arr2[], int N) {
    for (int i = 0; i <= N; i++)
        arr2[i] = arr1[i];
}