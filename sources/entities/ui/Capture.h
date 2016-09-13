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

#ifndef _CAPTURE_H_
#define _CAPTURE_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Capture : public ExtendedButton
{

  /**
   *
   *
   *
   */
  public:
  class Element : public Entity {

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

    /**
     *
     *
     *
     */
    public:
    Element();
   ~Element();

    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
  };

  /**
   * Tooflya Inc. Development
   *
   * @author Igor Mats from Tooflya Inc.
   * @copyright (c) by Igor Mats
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
  private:
  struct Buttons {
    AnnounceButton* announce;
  };

  Buttons buttons;

  /**
   *
   *
   *
   */
  protected:
  Entity* element;

  Pool* elements;

  /**
   *
   *
   *
   */
  public:
  Capture();
 ~Capture();

  int index;

  virtual void onCreate() override;
  virtual void onDestroy(bool action = false) override;

  virtual void onAdd() override;
  virtual void onRemove() override;

  virtual void update(float time) override;
};

#endif
