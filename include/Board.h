#pragma once
#pragma once
#include <vector>
#include <memory>
#include "Object.h"

#include <string>


class Board
{
public:

  void draw()const;

  void loadFromData(const std::vector<std::string>& data);
  const std::vector<std::vector<std::unique_ptr<Object>>>& getBoard()const;

private:
  void setSizeBoard(const std::vector<std::string>& data);
  void setBoard(const std::vector<std::string>& data);

  std::vector<std::vector<std::unique_ptr<Object>>> m_board;
};