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

#ifndef _USERS_H_
#define _USERS_H_

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
class Users : public Popup
{
  /**
   *
   *
   *
   */
  public:
  class Element : public TiledEntity
  {
    /**
     *
     *
     *
     */
    public:
    enum Type {
      TYPE_USER,
      TYPE_INVITE
    };

    struct Buttons {
      ExtendedButton* add;
      ExtendedButton* remove;
    };

    struct Texts {
      Text* name;
      Text* score;
    };

    Buttons buttons;
    Texts texts;

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
    Entity* element;

    /**
     *
     *
     *
     */
    public:
    Element();
   ~Element();

    int type;

    virtual void onCreate() override;
    virtual void onDestroy(bool action = false) override;

    virtual void onEnter() override;
    virtual void onExit() override;

    virtual void onAdd();
    virtual void onRemove();

    virtual void setType(int type);
    virtual void setData(FacebookFriend* element, float time = 0.0);

    virtual Element* deepCopy() override;
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
  struct Buttons {
    ExtendedButton* menu;
    ExtendedButton* share;
    ExtendedButton* rate;
    ExtendedButton* video;
    ExtendedButton* present;
    ExtendedButton* services;
    FacebookButton::Invite* invite;
  };

  Buttons buttons;

  BackgroundScroll* scroll;
  Background* container;

  RenderTexture* texture;

  Entity* animation;
  Entity* separator;

  bool listen;

  float x;
  float y;

  float time;

  vector<Element*> invitations;

  /**
   *
   *
   *
   */
  private:
  static Users* instance;

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
  virtual void onServices();

  /**
   *
   *
   *
   */
  public:
  static Users* getInstance();

  Users();
 ~Users();

  virtual void onEnter() override;
  virtual void onExit() override;

  virtual void show() override;
  virtual void hide() override;

  virtual void showButtons();
  virtual void hideButtons();

  virtual void invitationsCreate(Element* element);
  virtual void invitationsDestroy(Element* element);
  virtual void invitationsUpdate();

  virtual void update(bool reset = false);

  virtual void update(float time) override;
  virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
};

#endif
