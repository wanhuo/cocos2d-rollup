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

#ifndef _TIME_BUTTON_H_
#define _TIME_BUTTON_H_

#include "Game.h"

/**
 *
 *
 *
 */
class TimeButton : public ExtendedButton
{
  /**
   *
   *
   *
   */
  private:
  long long time;

  /**
   *
   *
   *
   */
  protected:
  enum State {
    STATE_NORMAL,
    STATE_WAIT
  };

  string id;

  int count;

  Entity* icon;
  Text* text;

  /**
   *
   *
   *
   */
  public:
  TimeButton(const char* textureFileName, int horizontalFramesCount, int verticalFramesCount, Node* parent, bool autocreate = false);
 ~TimeButton();

  int state;

  virtual void onCreate() override;
  virtual void onDestroy(bool action = false) override;

  virtual void onEnter() override;
  virtual void onExit() override;

  virtual void onAdd() override;
  virtual void onRemove() override;

  virtual void onNormal();
  virtual void onWait();

  virtual void onAction();
  virtual void onAction(int count, Node* element);

  virtual void changeState(int state);

  virtual void updateState();
  virtual void updateTime(int time);

  virtual void update(float time) override;
};

#endif
