#pragma once

#include "Utils/Vec2.hpp"

struct PlayerParams
{
  Vec2 acceleration;
  double maxFallSpeed;
  double maxSlideSpeed;
  double walkSpeed;
};

struct Player
{
  Vec2 pos;
  Vec2 speed = {0.0, 0.0};

  const uint8 r = 15;

  constexpr Player(const Vec2 _pos)
    : pos(_pos)
  { }

  void draw() const;
};
