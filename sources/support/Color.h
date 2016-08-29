/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * @copyright (c) 2016 by Igor Mats
 * http://www.tooflya.com/development/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @cocos2d
 *
 */

#ifndef _COLOR_H_
#define _COLOR_H_

#include "Macros.h"

/**
 *
 *
 *
 */
class Color
{
  /**
   *
   *
   *
   */
  public:
  static cocos2d::Color3B random() {
    return cocos2d::Color3B(cocos2d::random(0, 255), cocos2d::random(0, 255), cocos2d::random(0, 255));
  }

  static float tt;
  static cocos2d::Color3B t() {
    tt += 0.001;

    if(tt > 1)
    {
      tt = 0;
    }

    float r = 0;
    float g = 0;
    float b = 0;

    float h = tt;
    float s = 0.8;
    float v = 0.95;

    int hi = floor(h*6);
    float f = h*6 - hi;
    float p = v * (1 - s);
    float q = v * (1 - f*s);
    float t = v * (1 - (1 - f) * s);
  
    switch(hi) {
      case 0:
      r = v;
      g = t;
      b = p;
      break;
      case 1:
      r = q;
      g = v;
      b = p;
      break;
      case 2:
      r = p;
      g = v;
      b = t;
      break;
      case 3:
      r = p;
      g = q;
      b = v;
      break;
      case 4:
      r = t;
      g = p;
      b = v;
      break;
      case 5:
      r = v;
      g = p;
      b = q;
      break;
    }

    r *= 256;
    g *= 256;
    b *= 256;

    return cocos2d::Color3B(r, g, b);
  }
};

#endif
