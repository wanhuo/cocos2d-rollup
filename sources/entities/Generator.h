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

#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Generator : public Ref
{
  /**
   *
   *
   *
   */
  public:
  enum Direction {
    NONE,
    LEFT,
    RIGHT,
    FORWARD,
    BACK
  };

  const static int COUNT_START = 15;
  const static int COUNT_SPECIAL = 10;

  const static int MOVES_MIN_X = 3;
  const static int MOVES_MIN_Z = 3;

  const static int POSITION_MIN = -10;
  const static int POSITION_MAX = 10;

  const static int POSITION_SIZE = POSITION_MAX * 2 + 1;

  /**
   *
   *
   *
   */
  public:
  struct Element {
    bool active = false;
    bool normal = true;

    Plate* element;
  };

  Element elements[POSITION_SIZE][10000];

  /**
   *
   *
   *
   */
  public:
  Generator();
 ~Generator();

  int index;
  int special;

  int x;
  int y;
  int z;

  Vec3 direction;
  Vec3 moves;
  Vec3 min;

  virtual void create();
  virtual void destroy();

  virtual void reset();

  virtual Element element();
  virtual Element element(int x, int z);
};

#endif
