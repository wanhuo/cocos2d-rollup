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
void Generator::create()
{
  auto yy = SIZE;
  if(probably(10)) yy -= 0.5;

  auto plate = static_cast<Plate*>(Application->environment->plates->_create());

  plate->setPosition3D(Vec3(this->x, this->y, this->z));
  plate->setRotation3D(Vec3(0, 0, 0));
  plate->setIndex(this->index);
  plate->syncNodeToPhysics();
  plate->runAction(
    ScaleTo::create(0.5, 1.0, yy, 1.0)
  );

  if(this->direction)
  {
    if(this->x == POSITION_MAX || (this->x > 0 && probably(10)))
    {
      this->direction = !this->direction;
      this->z--;
    }
    else
    {
      this->x++;
      this->y += 1.0 / HEIGHT;
    }
  }
  else
  {
    if(this->x == POSITION_MIN || (this->x < 0 && probably(10)))
    {
      this->direction = !this->direction;
      this->z--;
    }
    else
    {
      this->x--;
      this->y += 1.0 / HEIGHT;
    }
  }

  this->index++;
}

void Generator::destroy()
{
}

/**
 *
 *
 *
 */
float Color::tt = 0.0;
void Generator::reset()
{
  Application->environment->plates->clear();

  /**
   *
   *
   *
   */
  this->direction = true;

  this->index = 0;

  this->x = -3;
  this->y = 0;
  this->z = 0;

  /**
   *
   *
   *
   */
  Application->environment->runAction(
    Repeat::create(
      Sequence::create(
        CallFunc::create([=] () {
          this->create();
        }),
        DelayTime::create(0.02),
        nullptr
      ),
      COUNT_START
    )
  );
}
