//
// Created by nimsolated on 6/2/2025.
//
#include "../include/Maze.h"

Maze::Maze() {
    // Allocate the maze
    m_maze = new char*[m_mazeSizeY];
    for (size_t i = 0; i < m_mazeSizeY; ++i) {
        m_maze[i] = new char[m_mazeSizeX];
    }
    // Build the maze
    buildMaze();
    // Generate obstacles
    generateObstacles();
    // Generate NPCs
    generateNPCs();
}

Maze::Maze(const size_t sizeX, const size_t sizeY) {
    try {
        if (sizeX <= 1 || sizeX % 2 == 0) {
            throw std::runtime_error("Maze constructor failed: Bad sizeX.\n(constraints: sizeX > 1 && sizeX % 2 != 0)");
        }
        if (sizeY <= 1 || sizeY % 2 == 0) {
            throw std::runtime_error("Maze constructor failed: Bad sizeY.\n(constraints: sizeY > 1 && sizeY % 2 != 0)");
        }
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    m_mazeSizeX = sizeX;
    m_mazeSizeY = sizeY;
    // Allocate the maze
    m_maze = new char*[m_mazeSizeY];
    for (size_t i = 0; i < m_mazeSizeY; ++i) {
        m_maze[i] = new char[m_mazeSizeX];
    }
    // Build the maze
    buildMaze();
    // Generate obstacles
    generateObstacles();
    // Generate NPCs
    generateNPCs();
}

Maze::~Maze() {
    // deallocate the maze
    for (size_t i = 0; i < m_mazeSizeY; ++i) {
        delete[] m_maze[i];
    }
    delete[] m_maze;
}

void Maze::printMaze() const {
    // print the maze cell by cell, up to down, left to right
    for (size_t i = 0; i < m_mazeSizeY; ++i) {
        for (size_t j = 0; j < m_mazeSizeX; ++j) {
            std::cout << m_maze[i][j];
        }
        std::cout << std::endl;
    }
}

void Maze::updateMazeCell(const int x, const int y, const char ch) const {
    // updates the cell at the given coordinates
    m_maze[x][y] = ch;
}

char Maze::getMazeCell(const int x, const int y) const {
    // gets the cell at the given coordinates
    return m_maze[x][y];
}

void Maze::buildMaze() const {
    for (size_t i = 0; i < m_mazeSizeY; ++i) {
        if (i == 0 || i == m_mazeSizeY - 1) { // outer walls conditions
            for (size_t j = 0; j < m_mazeSizeX; ++j) {
                m_maze[i][j] = '#';
            }
        } else if (i % 2 != 0) { // inner walls conditions for odd rows
            for (size_t j = 0; j < m_mazeSizeX; ++j) {
                if (j == 0 || j == m_mazeSizeX - 1) {
                    m_maze[i][j] = '#';
                } else {
                    m_maze[i][j] = '_';
                }
            }
        } else { // inner walls conditions for even rows
            for (size_t j = 0; j < m_mazeSizeX; ++j) {
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
    for (size_t i = 0; i < m_mazeSizeY; ++i) {
        for (size_t j = 0; j < m_mazeSizeX; ++j) {
            if (m_maze[i][j] == '#' || m_maze[i][j] == 'o' || (i == SPAWN_X && j == SPAWN_Y)) {
                continue;
            }

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(
                0,
                static_cast<int>((m_mazeSizeY + m_mazeSizeX) / (std::max(m_mazeSizeX, m_mazeSizeY) / 2))
                );
            if (const int randNum = dis(gen); randNum == 0) {
                m_maze[i][j] = 'o';
            }
        }
    }
}

void Maze::generateNPCs() const {
    for (size_t i = 0; i < m_mazeSizeY; ++i) {
        for (size_t j = 0; j < m_mazeSizeX; ++j) {
            if (m_maze[i][j] == '#' || m_maze[i][j] == 'o' || (i == SPAWN_X && j == SPAWN_Y)) {
                continue;
            }

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(
                0,
                static_cast<int>((m_mazeSizeY + m_mazeSizeX) / (std::min(m_mazeSizeX, m_mazeSizeY) / 3))
                );
            if (const int randNum = dis(gen); randNum == 0) {
                m_maze[i][j] = 'E';
            }
        }
    }
}