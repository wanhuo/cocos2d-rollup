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

#ifndef _STORE_H_
#define _STORE_H_

#include "Game.h"

/**
 *
 *
 *
 */
#include "BackgroundScroll.h"

/**
 *
 *
 *
 */
class Store : public Popup
{
  /**
   *
   *
   *
   */
  public:
  class Element : public Button
  {
    /**
     *
     *
     *
     */
    public:
    enum State {
      STATE_LOCKED,
      STATE_NORMAL,
      STATE_SELECTED
    };

    enum Action {
      ACTION_NONE,
      ACTION_FACEBOOK,
      ACTION_TWITTER,
      ACTION_INSTAGRAM,
      ACTION_INAPP
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
    Text* currency;

    int index;
    int state;
    int action;
    int category;

    float price;

    TiledEntity* icon;

    /**
     *
     *
     *
     */
    public:
    Element();
   ~Element();

    virtual void onCreate() override;
    virtual void onDestroy(bool action = false) override;

    virtual void onAction();

    virtual void setIndex(int index);
    virtual void setState(int state);
    virtual void setAction(int action);
    virtual void setPrice(float price);
    virtual void setCategory(int category);

    virtual int getIndex();
    virtual int getState();
    virtual int getAction();
    virtual int getCategory();

    virtual Element* deepCopy() override;

    virtual bool containsTouchLocation(cocos2d::Touch* touch) override;
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

  public:
  enum Categories {
    CATEGORY_REGULAR = 1,
    CATEGORY_RARE = 2,
    CATEGORY_MYTHICAL = 3
  };

  struct State {
    int index;
    int category;
    int state;
    int action;

    float price;

    bool update;
  };

  vector<State> states;

  public:
  struct Buttons {
    ExtendedButton* menu;
    ExtendedButton* share;
    ExtendedButton* rate;
    ExtendedButton* video;
    ExtendedButton* present;
    ExtendedButton* next;
    ExtendedButton* announce;
  };

  struct Texts {
    Text* more1;
    Text* more2;

    Text* separator2;
    Text* separator3;

    Text* connect;
    Text* character;
  };

  Buttons buttons;
  Texts texts;

  Entity* separator2;
  Entity* separator3;

  BackgroundScroll* scroll;
  RenderTexture* texture;

  Node* current;

  /**
   *
   *
   *
   */
  private:
  static Store* instance;

  /**
   *
   *
   *
   */
  protected:
  Pool* elements;

  virtual void onMenu();
  virtual void onShare();
  virtual void onRate();
  virtual void onNext();

  /**
   *
   *
   *
   */
  public:
  static Store* getInstance();

  Store();
 ~Store();

  virtual void onEnter() override;
  virtual void onExit() override;

  virtual void show() override;
  virtual void hide() override;

  virtual void showButtons();
  virtual void hideButtons();

  virtual int count(int category, bool create = false);

  virtual State element(bool action = false);

  virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
};

#endif
