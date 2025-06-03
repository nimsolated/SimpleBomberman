//
// Created by nimsolated on 6/2/2025.
//

#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <random>

class Maze {
public:
    Maze();
    explicit Maze(size_t sizeX, size_t sizeY);
    ~Maze();

    void printMaze() const;
    void updateMazeCell(int x, int y, char ch) const;
    [[nodiscard]] char getMazeCell(int x, int y) const;
private:
    void buildMaze() const;
    void generateObstacles() const;
    void generateNPCs() const;
private:
    char** m_maze{nullptr};
    size_t m_mazeSizeX{11};
    size_t m_mazeSizeY{7};
    const int SPAWN_X{1};
    const int SPAWN_Y{1};
    int m_playerPosX{1};
    int m_playerPosY{1};
};

#endif //MAZE_H
