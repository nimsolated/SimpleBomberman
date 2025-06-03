//
// Created by nimsolated on 6/2/2025.
//
#include "../include/Maze.h"

Maze::Maze() {
    // Allocate the maze
    m_maze = new char*[m_mazeSizeX];
    for (size_t i = 0; i < m_mazeSizeX; ++i) {
        m_maze[i] = new char[m_mazeSizeY];
    }
    // Build the maze
    buildMaze();
    // Generate obstacles
    generateObstacles();
    // Generate NPCs
    generateNPCs();
}

Maze::Maze(const size_t sizeX, const size_t sizeY) {
    m_mazeSizeX = sizeX;
    m_mazeSizeY = sizeY;
    // Allocate the maze
    m_maze = new char*[m_mazeSizeX];
    for (size_t i = 0; i < m_mazeSizeX; ++i) {
        m_maze[i] = new char[m_mazeSizeY];
    }
    // Build the maze
    buildMaze();
    // Generate obstacles
    generateObstacles();
    // Generate NPCs
    generateNPCs();
}

Maze::~Maze() {
    for (size_t i = 0; i < m_mazeSizeX; ++i) {
        delete[] m_maze[i];
    }
    delete[] m_maze;
}

void Maze::printMaze() const {
    for (size_t i = 0; i < m_mazeSizeX; ++i) {
        for (size_t j = 0; j < m_mazeSizeY; ++j) {
            std::cout << m_maze[i][j];
        }
        std::cout << std::endl;
    }
}

void Maze::updateMazeCell(const int x, const int y, const char ch) const {
    m_maze[x][y] = ch;
}

char Maze::getMazeCell(const int x, const int y) const {
    return m_maze[x][y];
}

void Maze::buildMaze() const {
    for (size_t i = 0; i < m_mazeSizeX; ++i) {
        if (i == 0 || i == m_mazeSizeX - 1) {
            for (size_t j = 0; j < m_mazeSizeY; ++j) {
                m_maze[i][j] = '#';
            }
        } else if (i % 2 != 0) {
            for (size_t j = 0; j < m_mazeSizeY; ++j) {
                if (j == 0 || j == m_mazeSizeY - 1) {
                    m_maze[i][j] = '#';
                } else {
                    m_maze[i][j] = '_';
                }
            }
        } else {
            for (size_t j = 0; j < m_mazeSizeY; ++j) {
                if (j % 2 == 0) {
                    m_maze[i][j] = '#';
                } else {
                    m_maze[i][j] = '_';
                }
            }
        }
    }
    m_maze[SPAWN_X][SPAWN_Y] = 'P';
}

void Maze::generateObstacles() const {
    for (size_t i = 0; i < m_mazeSizeX; ++i) {
        for (size_t j = 0; j < m_mazeSizeY; ++j) {
            if (m_maze[i][j] == '#' || m_maze[i][j] == 'o' || (i == SPAWN_X && j == SPAWN_Y)) {
                continue;
            }

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, (m_mazeSizeX + m_mazeSizeY) / 4);
            if (const int randNum = dis(gen); randNum == 0) {
                m_maze[i][j] = 'o';
            }
        }
    }
}

void Maze::generateNPCs() const {
    for (size_t i = 0; i < m_mazeSizeX; ++i) {
        for (size_t j = 0; j < m_mazeSizeY; ++j) {
            if (m_maze[i][j] == '#' || m_maze[i][j] == 'o' || (i == SPAWN_X && j == SPAWN_Y)) {
                continue;
            }

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, (m_mazeSizeX + m_mazeSizeY) / 2);
            if (const int randNum = dis(gen); randNum == 0) {
                m_maze[i][j] = 'E';
            }
        }
    }
}