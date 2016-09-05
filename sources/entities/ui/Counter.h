/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @version of cocos2d is 3.5
 *
 */

#ifndef _COUNTER_H_
#define _COUNTER_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Counter : public Entity
{
  /**
   *
   *
   *
   */
  public:
  struct Coins {
    Entity* background;
    Entity* icon;

    Text* text;
  };

  struct Value {
    int count;
  };

  struct Values {
    Value score;
    Value coins;
  };

  struct Animation {
    int count;
  };

  Coins coins;
  Values values;
  Animation animation;

  /**
   *
   *
   *
   */
  private:
  virtual int numbers(int number, int *elements);

  /**
   *
   *
   *
   */
  protected:
  Pool* elements;

  /**
   *
   *
   *
   */
  public:
  Counter();
 ~Counter();

  virtual void onCreate() override;
  virtual void onDestroy(bool action = false) override;

  virtual void onCount(int count = 1);
  virtual void onCoin(int count = 1);

  virtual void reset();

  virtual void updateData();

  virtual void updateScoreData();
  virtual void updateCoinsData();

  virtual void update(float time) override;
};

#endif
