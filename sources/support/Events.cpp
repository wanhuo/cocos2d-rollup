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

#include "Events.h"
#include "Game.h"

/**
 *
 *
 *
 */
void Events::onStart()
{//Storage::clear();
  Text::FONT = "Bangla Sangam MN";

  new Game;
  new Menu;
  new Unlock;
  new Settings;
  new Store;
  new Users;
  new Tutorial;

  Director::getInstance()->runWithScene(Application);

  Analytics::sendEvent("Application", "application.events.onStart", "Application onStart event");
}

/**
 *
 *
 *
 */
void Events::onStop()
{
  Analytics::sendEvent("Application", "application.events.onStop", "Application onStop event");
}

/**
 *
 *
 *
 */
void Events::onPause()
{
  Analytics::sendEvent("Application", "application.events.onPause", "Application onPause event");
}

/**
 *
 *
 *
 */
void Events::onResume()
{
  Analytics::sendEvent("Application", "application.events.onResume", "Application onResume event");
}

/**
 *
 *
 *
 */
void Events::onLeaderboards()
{
  Analytics::sendEvent("Application", "application.events.onLeaderboards", "Application onLeaderboards event");

  Modal::show();
  Services::showLeaderboards();
}

/**
 *
 *
 *
 */
void Events::onAchievements()
{
  Analytics::sendEvent("Application", "application.events.onAchievements", "Application onAchievements event");

  Modal::show();
  Services::showAchievements();
}

/**
 *
 *
 *
 */
void Events::onServices()
{
  Modal::hide();
}

/**
 *
 *
 *
 */
void Events::onRate()
{
  Analytics::sendEvent("Application", "application.events.onRate", "Application onRate event");

  Media::openStore();
}

/**
 *
 *
 *
 */
void Events::onShare()
{
  Analytics::sendEvent("Application", "application.events.onShare", "Application onShare event");
}

/**
 *
 *
 *
 */
void Events::onSound()
{
  Analytics::sendEvent("Application", "application.events.onSound", "Application onSound event");

  if(!Music->enabled || !Sound->enabled)
  {
    Music->changeState(true);
    Sound->changeState(true);
  }
  else
  {
    Music->changeState(false);
    Sound->changeState(false);
  }
}

/**
 *
 *
 *
 */
bool Events::onFacebookLike()
{
  Analytics::sendEvent("Application", "application.events.onFacebookLike", "Application onFacebookLike event");
  Analytics::sendSocial("Facebook", "Open publisher view from application", "503287153144438");

  return Media::openFacebook("503287153144438");
}

bool Events::onTwitterLike()
{
  Analytics::sendEvent("Application", "application.events.onTwitterLike", "Application onTwitterLike event");
  Analytics::sendSocial("Twitter", "Open publisher view from application", "2869168750");

  return Media::openTwitter("2869168750");
}

bool Events::onInstagramLike()
{
  Analytics::sendEvent("Application", "application.events.onInstagramLike", "Application InstagramLike event");
  Analytics::sendSocial("Instagram", "Open publisher view from application", "ketchapp");

  return Media::openInstagram("ketchapp");
}

/**
 *
 *
 *
 */
bool Events::onTwitter()
{
  Analytics::sendEvent("Application", "application.events.onTwitter", "Application onTwitter event");
  Analytics::sendSocial("Twitter", "Open developer view from application", "");

  return Media::openTwitter();
}

bool Events::onFacebook()
{
  Analytics::sendEvent("Application", "application.events.onFacebook", "Application onFacebook event");
  Analytics::sendSocial("Facebook", "Open developer view from application", "386292514777918");

  return Media::openFacebook();
}

bool Events::onInstagram()
{
  Analytics::sendEvent("Application", "application.events.onInstagram", "Application onInstagram event");
  Analytics::sendSocial("Instagram", "Open developer view from application", "tooflya");

  return Media::openInstagram();
}

void Events::onMail()
{
  Analytics::sendEvent("Application", "application.events.onMail", "Application onMail event");

  Media::openMail();
}

/**
 *
 *
 *
 */
void Events::onScreenChanged(const char* name)
{
  Analytics::sendScreen(name);
}

/**
 *
 *
 *
 */
void Events::onRestorePurchases()
{
  Analytics::sendEvent("Application", "application.events.onRestorePurchases", "Application onRestorePurchases event");

  Purchase::restorePurchases();
}

/**
 *
 *
 *
 */
void Events::onPurchaseSuccess(const char* id, const char* name, float revenue)
{
  Modal::hide();

  Analytics::sendEvent("Application", "application.events.onPurchaseSuccess", "Application onPurchaseSuccess event");
  Analytics::sendTransaction(id, name, revenue);
}

/**
 *
 *
 *
 */
void Events::onPurchaseRestored(const char* id)
{
  if(strncmp(id, "com.ketchapp.exodus.remove.ads", 100) == 0)
  {
    //Application->onNoadAction();
  }
}

/*
 *
 *
 *
 */
void Events::updateMissions()
{
}

void Events::onMissionComplete(int id)
{
}
