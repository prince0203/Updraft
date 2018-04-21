#pragma once

#include "Graphics/Font.hpp"
#include "Graphics/Line.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Circle.hpp"
#include "Player.hpp"

class Stage
{
  const Font m_font;

  const Vec2 m_stageSize;

  const Vec2 m_playerInitialPos;

  const Circle m_goal;

  int m_goalCount;

  Point m_scrollPos;

  Player m_player;

  Array<Line> m_lines;

  Array<Rect> m_updrafts;

public:
  Stage(const Vec2 stageSize)
    : m_font(L"Fonts\\MisakiGothic.fnt")
    , m_stageSize(stageSize)
    , m_playerInitialPos(100, 0)
    , m_goal(2560, 215, 25)
    , m_goalCount(-1)
    , m_scrollPos(0, 0)
    , m_player(m_playerInitialPos, this)
  { }

  Vec2 size();

  Point& scrollPos();

  Array<Line>& lines();

  const Array<Line>& lines() const;

  Array<Rect>& updrafts();

  const Array<Rect>& updrafts() const;

  bool isInStage(const Vec2 pos);

  bool isInUpdraft(const Vec2 pos);

  void update(const PlayerParams playerParams);

  void draw() const;
};
