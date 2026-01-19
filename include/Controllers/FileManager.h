#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Const.h"
#include <SFML/System/Vector2.hpp>


class FileManager {
public:
  FileManager(const std::string& fileName = WindowConfig::DEFAULT_FILE_NAME);

  std::vector<std::string> getLevel(int levelIndex) const;

  int getTotalLevels() const;
  sf::Vector2u getSizeBoard(int levelIndex) const;
private:
  void scanFileForLevels();
  
  std::string m_fileName;
  std::vector<std::streampos> m_levelOffsets;
};