#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int lines, width;
    char empty, obstacle, full;
    char **map;
} Map;

int min3(int a, int b, int c) {
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

Map* read_map(char *filename) {
    FILE *file = filename ? fopen(filename, "r") : stdin;
    if (!file) return NULL;
    
    Map *map = malloc(sizeof(Map));
    if (fscanf(file, "%d %c %c %c\n", &map->lines, &map->empty, &map->obstacle, &map->full) != 4) {
        free(map);
        if (filename) fclose(file);
        return NULL;
    }
    
    map->map = malloc(map->lines * sizeof(char*));
    map->width = 0;
    
    for (int i = 0; i < map->lines; i++) {
        char *line = NULL;
        size_t len = 0;
        if (getline(&line, &len, file) == -1) {
            free(map);
            if (filename) fclose(file);
            return NULL;
        }
        
        // Remove newline
        int line_len = strlen(line);
        if (line[line_len - 1] == '\n') line[line_len - 1] = '\0';
        
        if (i == 0) map->width = strlen(line);
        else if (strlen(line) != map->width) {
            free(map);
            if (filename) fclose(file);
            return NULL;
        }
        
        map->map[i] = line;
    }
    
    if (filename) fclose(file);
    return map;
}

int validate_map(Map *map) {
    if (!map || map->lines <= 0 || map->width <= 0) return 0;
    if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full) return 0;
    
    for (int i = 0; i < map->lines; i++) {
        for (int j = 0; j < map->width; j++) {
            char c = map->map[i][j];
            if (c != map->empty && c != map->obstacle) return 0;
        }
    }
    return 1;
}

void solve_bsq(Map *map) {
    // Create DP table
    int **dp = malloc(map->lines * sizeof(int*));
    for (int i = 0; i < map->lines; i++) {
        dp[i] = calloc(map->width, sizeof(int));
    }
    
    int max_size = 0, best_i = 0, best_j = 0;
    
    // Fill DP table
    for (int i = 0; i < map->lines; i++) {
        for (int j = 0; j < map->width; j++) {
            if (map->map[i][j] == map->obstacle) {
                dp[i][j] = 0;
            } else if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
            }
            
            if (dp[i][j] > max_size) {
                max_size = dp[i][j];
                best_i = i;
                best_j = j;
            }
        }
    }
    
    // Fill the square
    int start_i = best_i - max_size + 1;
    int start_j = best_j - max_size + 1;
    
    for (int i = start_i; i < start_i + max_size; i++) {
        for (int j = start_j; j < start_j + max_size; j++) {
            map->map[i][j] = map->full;
        }
    }
    
    // Free DP table
    for (int i = 0; i < map->lines; i++) {
        free(dp[i]);
    }
    free(dp);
}

void print_map(Map *map) {
    for (int i = 0; i < map->lines; i++) {
        printf("%s\n", map->map[i]);
    }
}

void free_map(Map *map) {
    if (!map) return;
    for (int i = 0; i < map->lines; i++) {
        free(map->map[i]);
    }
    free(map->map);
    free(map);
}

void process_file(char *filename) {
    Map *map = read_map(filename);
    if (!map || !validate_map(map)) {
        fprintf(stderr, "map error\n");
        if (map) free_map(map);
        return;
    }
    
    solve_bsq(map);
    print_map(map);
    free_map(map);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        process_file(NULL);  // Read from stdin
    } else {
        for (int i = 1; i < argc; i++) {
            process_file(argv[i]);
        }
    }
    return 0;
}