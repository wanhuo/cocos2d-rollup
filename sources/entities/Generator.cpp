/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 *
 * License: Tooflya Inc. Software License v1.
 *
 * Licensee may not use this software for commercial purposes. For the purpose of this license,
 * commercial purposes means that a 3rd party has to pay in order to access Software or that
 * the Website that runs Software is behind a paywall. In consideration of the License granted
 * under clause 2, Licensee shall pay Licensor a fee, via Credit-Card, PayPal or any other
 * mean which Licensor may deem adequate. Failure to perform payment shall construe as material
 * breach of this Agreement. This software is provided under an AS-IS basis and without any support,
 * updates or maintenance. Nothing in this Agreement shall require Licensor to provide Licensee with
 * support or fixes to any bug, failure, mis-performance or other defect in The Software.
 *
 * @cocos2d
 *
 */

#include "Game.h"

/**
 *
 *
 *
 */
Generator::Generator()
{
}

Generator::~Generator()
{
}

/**
 *
 *
 *
 */
static int TEST_BACK_DIRECTION;
static int TEST_BACK_LENGTH_X;
static int TEST_BACK_LENGTH_Z;
static int TEST_BACK_MIN_Z;
void Generator::create()
{
  auto element = this->element();

  /**
   *
   * Принимаем решение.
   *
   */
  switch((int) this->direction.x)
  {
    case LEFT:
    if(this->x <= POSITION_MIN || (this->moves.x >= this->min.x && probably(25)))
    {
      ///////////////
      bool test = true;
      int length = random(2, 5);

      // проверяем назад
      int x = this->x;
      int z = this->z;

      for(int i = 0; i < length; i++)
      {
        if(this->element(x, z + i + 3).active || z > 0)
        {
          test = false;
        }
      }

      // проверяем справа
      x = this->x + 1;
      z = this->z;

      for(int i = 0; i < length; i++)
      {
        if(this->element(x, z + i + 1).active || z > 0)
        {
          test = false;
        }
      }

      // проверяем слева
      x = this->x - length;
      z = this->z;

      for(int i = 0; i < length; i++)
      {
        if(this->element(x, z + i + 1).active || z > 0 || x < POSITION_MIN)
        {
          test = false;
        }
      }

      if(test)
      {
        if(element.element)
        {
          element.element->setColor(Color3B::BLUE);
        }

        TEST_BACK_DIRECTION = LEFT;
      }
      /////////////////

      this->direction.x = NONE;
      this->direction.z = test ? BACK : FORWARD;

      this->moves.x = 0;
      this->moves.z = 0;
      

  this->min.x = MOVES_MIN_X;
  this->min.z = MOVES_MIN_Z;

      if(test)
      {
        TEST_BACK_MIN_Z = length;
      }
    }
    break;
    case RIGHT:
    if(this->x >= POSITION_MAX || (this->moves.x >= this->min.x && probably(25)))
    {
      this->direction.x = NONE;
      this->direction.z = FORWARD;

      this->moves.x = 0;
      this->moves.z = 0;

  this->min.x = MOVES_MIN_X;
  this->min.z = MOVES_MIN_Z;
    }
    break;
  }

  switch((int) this->direction.z)
  {
    case FORWARD:
    if(this->moves.z >= this->min.z + TEST_BACK_MIN_Z)
    {
      this->direction.x = (this->x > 0) ? LEFT : RIGHT;
      this->direction.z = NONE;

      this->moves.x = 0;
      this->moves.z = 0;

  this->min.x = MOVES_MIN_X;
  this->min.z = MOVES_MIN_Z;

      TEST_BACK_MIN_Z = 0;
    }
    break;
    case BACK:
    if(this->moves.z >= this->min.z)
    {
      this->direction.x = TEST_BACK_DIRECTION;
      this->direction.z = NONE;

      this->moves.x = 0;
      this->moves.z = 0;

  this->min.x = MOVES_MIN_X;
  this->min.z = MOVES_MIN_Z;
    }
    break;
  }

  /**
   *
   * Обрабатываем принятое решение.
   *
   */
  switch((int) this->direction.x)
  {
    case LEFT:
    this->x--;
    this->moves.x++;
    break;
    case RIGHT:
    this->x++;
    this->moves.x++;
    break;
  }

  switch((int) this->direction.z)
  {
    case FORWARD:
    this->z--;
    this->moves.z++;
    break;
    case BACK:
    this->z++;
    this->moves.z++;
    break;
  }
}

void Generator::destroy()
{
}

/**
 *
 *
 *
 */
void Generator::reset()
{
  this->special = COUNT_SPECIAL;
  this->index = 0;

  this->x = 0;
  this->y = 0;
  this->z = 0;

  this->direction.x = RIGHT;
  this->direction.z = NONE;

  this->moves.x = 0;
  this->moves.z = 0;

  this->min.x = MOVES_MIN_X;
  this->min.z = MOVES_MIN_Z;

  /**
   *
   *
   *
   */
  for(int i = 0; i < COUNT_START; i++)
  {
    this->create();
  }
}

/**
 *
 *
 *
 */
Generator::Element Generator::element()
{
  Vec3 index;

  index.x = this->x + POSITION_MAX;
  index.z = this->z * -1;

  /**
   *
   *
   *
   */
  this->special--;

  auto plate = static_cast<Plate*>(Application->environment->plates->_create());

  plate->setPosition(this->x, this->y, this->z);
  plate->setRotation(0, 0, 0);
  //plate->setIndex(?);

  if(this->special < 0 && probably(50))
  {
    
  this->special = COUNT_SPECIAL;
    plate->setNormal(false);
  }
  else
  {
    plate->setNormal(true);

  Element element;

  element.active = true;
  element.normal = plate->getNormal();
  element.element = plate;

  this->elements[(int) index.x][(int) index.z] = element;

  return this->elements[(int) index.x][(int) index.z];
  }

  //return nullptr;
}

Generator::Element Generator::element(int x, int z)
{
  Vec3 index;

  index.x = x + POSITION_MAX;
  index.z = z * -1;

  /**
   *
   *
   *
   */
  return this->elements[(int) index.x][(int) index.z];
}
