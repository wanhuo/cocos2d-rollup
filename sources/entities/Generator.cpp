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
Plate* Generator::element(int index)
{
}

/**
 *
 *
 *
 */
void Generator::create()
{
  if(true)
  {
    auto elements = Application->environment->plates;

    /**
     *
     *
     *
     */
    if(elements->count)
    {
      auto previous = elements->last();

      auto px = previous->getPosition3D().x;
      auto py = previous->getPosition3D().y;
      auto pz = previous->getPosition3D().z;

      auto rx = previous->getRotation3D().x;
      auto ry = previous->getRotation3D().y;
      auto rz = previous->getRotation3D().z;

      /**
       *
       *
       *
       */
      auto current = static_cast<Plate*>(elements->_create());

      auto rotation = 180+random(0.0, 45.0);
      auto r = 0.9;

      auto x =  r * sin(CC_DEGREES_TO_RADIANS(rotation)) + px;
      auto z =  r * cos(CC_DEGREES_TO_RADIANS(rotation)) + pz;
      auto y = 0;

      current->setPosition(x, y, z);
      current->setRotation(0, - (22.5 - rotation * 2) - ry, 0);
    }
    else
    {
      auto current = static_cast<Plate*>(elements->_create());

      current->setPosition(0, 0, 0);
      current->setRotation(0, 0, 0);
    }
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
  this->index = 0;

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
