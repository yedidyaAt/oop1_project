#include "FileManager.h"
#include <iostream>
#include <limits> // בשביל numeric_limits

FileManager::FileManager(const std::string& fileName)
  : m_fileName(fileName)
{
  scanFileForLevels();
}

void FileManager::scanFileForLevels() {
  std::ifstream file(m_fileName);
  if (!file.is_open()) {
    std::cerr << "Error: Cannot open level file!" << std::endl;
    exit(1);
  }

  int rows = 0, cols = 0;

  while (true) {

    // jump whit spac space/endl
    file >> std::ws;

    if (file.eof()) break;

    // save begin level
    std::streampos currentPos = file.tellg();

    if (!(file >> rows >> cols)) {
      break; 
    }
    // push begin level
    m_levelOffsets.push_back(currentPos);

    // move after the first line
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

     for (int i = 0; i < rows; ++i) {
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

  }

  file.close();
}

std::vector<std::string> FileManager::getLevel(int levelIndex) const {
  if (levelIndex < 0 || levelIndex >= m_levelOffsets.size()) {
    return {};
  }

  std::ifstream file(m_fileName);
  if (!file.is_open()) return {};

  file.seekg(m_levelOffsets[levelIndex]);

  int rows = 0, cols = 0;
  file >> rows >> cols; 

  // move after the first line
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::vector<std::string> board;
  board.reserve(rows);

  std::string line;
  for (int i = 0; i < rows; ++i) {
    if (std::getline(file, line)) {
      if (line.size() < cols) {
        line.resize(cols, ' ');
      }
      board.push_back(line);
    }
  }

  return board;
}

int FileManager::getTotalLevels() const {
  return static_cast<int>(m_levelOffsets.size());
}

sf::Vector2u FileManager::getSizeBoard(int levelIndex) const
{
  auto board = getLevel(levelIndex);

  if (!board.size())
    return { 0,0 };

  return sf::Vector2u{ static_cast<unsigned int>(board[0].size()), 
                       static_cast<unsigned int>(board.size()) };
}
