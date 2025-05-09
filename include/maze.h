#ifndef MAZE_H
#define MAZE_H

#ifdef __cplusplus
extern "C" {
#endif

#define T Maze_T
typedef struct T *T;

T Maze_create(int n, int m);
void Maze_destroy(T maze);
void Maze_display(T maze, char wall);
void Maze_solution(T maze, char wall, char path);

#ifdef __cplusplus
}
#endif

#undef T
#endif // MACE_H
