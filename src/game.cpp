#include "game.h"
#include <random>

Game::Game()
{
  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  level = 1;
  linesClearedTotal = 0;
  delay = 0.2;
  InitAudioDevice();
  music = LoadMusicStream("Audio/music.mp3");
  PlayMusicStream(music);
  rotateSound = LoadSound("Audio/rotate.mp3");
  clearSound = LoadSound("Audio/clear.mp3");
}

Game::~Game()
{
  UnloadSound(rotateSound);
  UnloadSound(clearSound);
  UnloadMusicStream(music);
  CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
  if(blocks.empty())
  {
    blocks = GetAllBlocks();
  }
  int randomIndex = rand() % blocks.size();
  Block block = blocks[randomIndex];
  statistics[block.id-1]++;
  blocks.erase(blocks.begin() + randomIndex);
  return block;
}

std::vector<Block> Game::GetAllBlocks()
{
  return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
  grid.Draw();
  currentBlock.Draw(211, 11);
  switch(nextBlock.id)
  {
    case 3:
      nextBlock.Draw(455, 290);
      break;
    case 4:
      nextBlock.Draw(455, 280);
      break;
    default:
      nextBlock.Draw(470, 270);
      break;
  }

  DrawAllBlocks();
}

void Game::DrawAllBlocks()
{
  std::vector<Block> blockList = GetAllBlocks();
  int offsetY = 0;
  for(Block block: blockList)
  {
    block.Draw(-50, 70 + offsetY);
    switch(block.id)
    {
      case 2:
        offsetY += 85;
        break;
      case 3:
        offsetY -= 10;
      default:
        offsetY += 75;
    }

  }
}

void Game::HandleInput()
{
  int keyPressed = GetKeyPressed();
  if(gameOver && keyPressed != 0)
  {
    gameOver = false;
    Reset();
  }
  switch(keyPressed)
  {
    case KEY_LEFT:
      MoveBlockLeft();
      break;

    case KEY_RIGHT:
      MoveBlockRight();
      break;

    case KEY_DOWN:
      MoveBlockDown();
      UpdateScore(0, 1);
      break;

    case KEY_UP:
      RotateBlock();
      break;
  }
}

void Game::MoveBlockLeft()
{
  if(!gameOver)
  {
    currentBlock.Move(0, -1);
    if(IsBlockOutside() || BlockFits() == false)
    {
      currentBlock.Move(0, 1);
    }
  }
}

void Game::MoveBlockRight()
{
  if(!gameOver)
  {
    currentBlock.Move(0, 1);
    if(IsBlockOutside() || BlockFits() == false)
    {
      currentBlock.Move(0, -1);
    }
  }
}

void Game::MoveBlockDown()
{
  if(!gameOver)
  {
    currentBlock.Move(1, 0);
    if(IsBlockOutside() || BlockFits() == false) 
    {
      currentBlock.Move(-1, 0);
      LockBlock();
    }
  }
}

bool Game::IsBlockOutside()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for(Position tile: tiles)
  {
    if(grid.IsCellOutside(tile.row, tile.col))
    {
      return true;
    }
  }
  return false;
}

void Game::RotateBlock()
{
  if(!gameOver)
  {
    currentBlock.Rotate();
    if(IsBlockOutside() || BlockFits() == false)
    {
      currentBlock.UndoRotation();
    }
    else
    {
      PlaySound(rotateSound);
    }
  }
}

void Game::LockBlock()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for(Position tile: tiles)
  {
    grid.grid[tile.row][tile.col] = currentBlock.id;
  }
  currentBlock = nextBlock;
  if(BlockFits() == false)
  {
    gameOver = true;
  }
  nextBlock = GetRandomBlock();
  int rowsCleared = grid.ClearFullRows();
  if(rowsCleared > 0)
  {
    PlaySound(clearSound);
    UpdateScore(rowsCleared, 0);
  }
}

bool Game::BlockFits()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for(Position tile: tiles)
  {
    if(!grid.IsCellEmpty(tile.row, tile.col))
    {
      return false;
    }
  }
  return true;
}

void Game::Reset()
{
  grid.Initalize();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  level = 1;
  delay = 0.2;
  linesClearedTotal = 0;

  statistics.clear();
  statistics[currentBlock.id-1]++;
  statistics[nextBlock.id-1]++;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
  switch(linesCleared)
  {
    case 1:
      score += 100;
      break;

    case 2:
      score += 300;
      break;

    case 3:
      score += 500;
      break;

    case 4:
      score += 800;
      break;

    default:
      break;
  }

  score += moveDownPoints;
}
