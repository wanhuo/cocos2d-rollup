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

#ifndef _PLATE_H_
#define _PLATE_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Plate : public Element
{
  /**
   *
   *
   *
   */
  public:
  enum State {
    STATE_NONE,
    STATE_NORMAL,
    STATE_COIN
  };

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
  int index;

  Node* coin = nullptr;

  /**
   *
   *
   *
   */
  public:
  Plate();
 ~Plate();

  int state = STATE_NONE;

  int stage;
  int rotation;
  int flushed;
  int dusts;

  float common;

  virtual void onEnter() override;
  virtual void onExit() override;

  virtual void onCreate() override;
  virtual void onDestroy(bool action = false) override;

  virtual void onAction();

  virtual void onNormal();
  virtual void onCoin();

  virtual void setIndex(int index);

  virtual int getIndex();

  virtual void start(bool animation = false, float time = 0.0);
  virtual void finish();

  virtual void flush();

  virtual void changeState(int state);

  virtual void update();

  virtual void updateStates(float time);
  virtual void update(float time) override;

  virtual Plate* deepCopy() override;
};

#endif
