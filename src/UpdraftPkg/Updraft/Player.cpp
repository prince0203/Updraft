#include "Player.hpp"

#include "System/Input.hpp"
#include "Utils/Utility.hpp"
#include "Graphics/Circle.hpp"
#include "Graphics/ColorPalette.hpp"
#include "Stage.hpp"

bool Player::isGliding() const
{
  return walkingLine == nullptr;
}

bool Player::isWalking() const
{
  return !isGliding();
}

void Player::clampSpeed(const PlayerParams playerParams)
{
  if (isGliding())
  {
    speed.x = Clamp(speed.x, playerParams.minGlideSpeed.x, playerParams.maxGlideSpeed.x);
    speed.y = Clamp(speed.y, playerParams.minGlideSpeed.y, playerParams.maxGlideSpeed.y);
  }
}

void Player::jump(const PlayerParams playerParams)
{
  speed.y = playerParams.jumpSpeed;
}

void Player::processInput(const PlayerParams playerParams)
{
  if (isWalking())
  {
    speed = {0, 0};

    if (Input::KeyRight.pressed())
    {
      speed.x += playerParams.walkSpeed;
    }
    if (Input::KeyLeft.pressed())
    {
      speed.x -= playerParams.walkSpeed;
    }
    if (Input::KeySpace.pressed())
    {
      walkingLine = nullptr;
      jump(playerParams);
    }
  }
  else
  {
    if (Input::KeyRight.pressed())
    {
      speed.x += playerParams.glideAcceleration.x;
    }
    if (Input::KeyLeft.pressed())
    {
      speed.x -= playerParams.glideAcceleration.x;
    }

    speed.y += playerParams.glideAcceleration.y;
  }
}

void Player::processCollision(const PlayerParams playerParams, const Vec2 oldPos)
{
  if (isWalking())
  {
    const Line line = *walkingLine;

    if ((pos - line.begin).dot(line.vector()) <= 0 || (pos - line.end).dot(line.vector()) >= 0)
    {
      walkingLine = nullptr;
      return;
    }

    const double distance = line.distanceFrom(pos) - r;

    if (distance <= playerParams.walkSpeed)
    {
      const Vec2 normalizedVec = line.vector().normalized();
      const double angle = (line.begin.x < line.end.x) ? Math::Pi * 3 / 2 : Math::Pi / 2;

      pos += normalizedVec.rotated(angle) * -distance;
    }
  }
  else
  {
    for (auto &line : m_stage->lines())
    {
      const double oldDistance = line.distanceFrom(oldPos) - r;
      const double distance = line.distanceFrom(pos) - r;

      if (oldDistance > 0 && distance <= 0 && speed.y >= 0)
      {
        const Vec2 normalizedVec = line.vector().normalized();
        const double angle = (line.begin.x < line.end.x) ? Math::Pi * 3 / 2 : Math::Pi / 2;

        pos += normalizedVec.rotated(angle) * -distance;
        walkingLine = &line;
      }
    }
  }
}

void Player::reset()
{
  pos = initialPos;
  speed = {0.0, 0.0};
}

void Player::update(const PlayerParams playerParams)
{
  processInput(playerParams);

  if (isGliding() && m_stage->isInUpdraft(pos))
    speed.y += playerParams.updraftAcceleration;

  if (isGliding())
    clampSpeed(playerParams);

  const auto oldPos = pos;
  pos += speed;

  processCollision(playerParams, oldPos);
}

void Player::draw() const
{
  Circle(pos.asPoint(), r).draw(Palette::Chocolate);
}
