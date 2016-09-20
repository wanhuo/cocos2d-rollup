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
  private:

  /**
   *
   *
   *
   */
  protected:
  struct Length {
    int current;

    int max;
    int min;
  };

  struct Parameters {
    float escarpment;
    float pullement;
    float probability;

    float rotation;

    Length length;
  };
  
  struct Previous {
    Vec3 position;
    Vec3 rotation;

    int stage;

    bool next;
  };

  /**
   *
   *
   *
   */
  public:
  const static int COUNT_START = 8;

  const static int PROBABILITY_NEXT = 50;
  const static int PROBABILITY_STAGE = 50;

  Generator();
 ~Generator();

  int index;
  int rotation;
  int direction;
  int tutorial;

  Parameters parameters;
  Previous previous;

  virtual Plate* element(int index);

  virtual void create(bool animation = false, float time = 0.0);
  virtual void destroy();

  virtual void reset();
};

#endif
