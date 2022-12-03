/*************************************************************
 * 1. Name:
 *      The Key
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POSITION
#include "howitzer.h"   // for HOWITZER
#include "test.h"
#include "testProjectile.h"
#include "testPhysics.h"
#include "testGround.h"
#include "testPosition.h"
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Game
{
public:
   Game(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      ground(ptUpperRight),
      howitzer(ptUpperRight),
      time(0.0)
   {
       // Pass howitzer position to ground so that
       // it's Y position can be set to the correct
       // height.
       ground.reset(*howitzer.getPosition());
       // set projectile position equal to position of howitzer
       projectile.setPosition(*howitzer.getPosition());

      // This is to make the bullet travel across the screen. Notice how there are 
      // 20 pixels, each with a different age. This gives the appearance
      // of a trail that fades off in the distance.
      for (int i = 0; i < 20; i++)
      {
         projectilePath[i].setPixelsX((double)i * 2.0);
         projectilePath[i].setPixelsY(ptUpperRight.getPixelsY() / 1.5);
      }
   }

   void reset() {
       howitzer.getPosition()->setPixelsX(rand() % (int)ptUpperRight.getPixelsX() + 1);
       ground.reset(*howitzer.getPosition());
       projectile.setPosition(*howitzer.getPosition());
       
       for (int i = 1; i < 20; i++)
       {
           projectilePath[i].setPixelsX(0.0);
           projectilePath[i].setPixelsY(0.0);
       }

   }

   Ground ground;                 // the ground
   Position  projectilePath[20];  // path of the projectile
   Howitzer  howitzer;          // location of the howitzer
   Projectile projectile;        // the projectile
   Physics physics = Physics(&projectile);              // physics engine
   Position  ptUpperRight;        // size of the screen
   double time;                   // amount of time since the last firing
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Game* pGame = (Game*)p;

   //
   // accept input
   //

   // move a large amount
   if (pUI->isRight())
      pGame->howitzer.rotate(0);
   if (pUI->isLeft())
      pGame->howitzer.rotate(1);
   if (pUI->isUp())
      pGame->howitzer.rotate(2);
   if (pUI->isDown())
      pGame->howitzer.rotate(3);

   // fire that gun
   if (pUI->isSpace() && !pGame->projectile.getIsFlying() && !pGame->projectile.getHitGround()) {
       // Call physics engine to calculate projectile's new position.
       pGame->physics.initialCalculations(pGame->howitzer.getAngleRadians());
       pGame->howitzer.resetTimeSinceLastShot();
       pGame->projectile.setIsFlying(true);
   }

    if (pGame->projectile.getIsFlying()) {
        // Call physics engine to calculate projectile's new position.
        pGame->projectile.setPrevV(pGame->projectile.getV());
        pGame->projectile.setPrevAge(pGame->projectile.getAge());
        pGame->projectile.setPrevAltitude(pGame->projectile.getPosition()->getMetersY());
        pGame->projectile.updateTrail(*pGame->projectile.getPosition());
        pGame->physics.updateProjectile();
        pGame->howitzer.incrementTimeSinceLastShot();
        pGame->projectile.updateAge(0.5);
    }

    if (pUI->isSpace() && pGame->projectile.getHitGround()) {
        // Call physics engine to calculate projectile's new position.
        pGame->projectile.setHitGround(false);
        pGame->projectile.setDX(0.0);
        pGame->projectile.setDY(0.0);
        pGame->projectile.setPosition(*pGame->howitzer.getPosition());
        pGame->projectile.setAge(0.0);
        pGame->projectile.setV(0.0);
    }

    if (pGame->projectile.getPosition()->getMetersY() - pGame->ground.getElevationMeters(*pGame->projectile.getPosition()) < 0) {
        pGame->projectile.setIsFlying(false);
        pGame->projectile.setHitGround(true);

        pGame->projectile.setV(pGame->physics.linearlyInterpolate(pGame->ground.getElevationMeters(*pGame->projectile.getPosition()),
            pGame->projectile.getPrevAltitude(),
            pGame->projectile.getPosition()->getMetersY(),
            pGame->projectile.getPrevV(),
            pGame->projectile.getV()));

        pGame->projectile.setAge(pGame->physics.linearlyInterpolate(pGame->ground.getElevationMeters(*pGame->projectile.getPosition()),
            pGame->projectile.getPrevAltitude(),
            pGame->projectile.getPosition()->getMetersY(),
            pGame->projectile.getPrevAge(),
            pGame->projectile.getAge()));

        pGame->projectile.getPosition()->setMetersY(pGame->ground.getElevationMeters(*pGame->projectile.getPosition()));
    }
    
    if (pGame->projectile.getHitTarget(pGame->ground.getTarget())) {
        pGame->reset();
    }

    // Print projectiles elevation in relation to the ground.
//    cout << "Projectile elevation: " << pGame->projectile.getPosition()->getMetersY() - pGame->ground.getElevationMeters(*pGame->projectile.getPosition()) << endl;

  
   ogstream gout(Position(10.0, pGame->ptUpperRight.getPixelsY() - 20.0));

   // draw the ground first
   // pGround->draw(gout);
   pGame->ground.draw(gout);

   // draw the howitzer
   //gout.drawHowitzer(pHowitzer->*getPosition(), pHowitzer->getAngle(), pHowitzer.getTimeSinceLastShot())
   gout.drawHowitzer(*pGame->howitzer.getPosition(), pGame->howitzer.getAngleRadians(), pGame->projectile.getIsFlying() ? pGame->howitzer.getTimeSinceLastShot() : 2);

   // draw the projectile
   for (int i = 0; i < 20; i++) {
        gout.drawProjectile(pGame->projectile.getTrail()[i], 0.5 * i);
   }

   // draw some text on the screen
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(1);

   Position drawPos = Position();
   drawPos.setPixelsX(425);
   drawPos.setPixelsY(480);

   gout.setPosition(drawPos);
   gout << "Howitzer Angle: " << pGame->howitzer.getAngleDegrees() << " degrees";

    drawPos.setPixelsX(425);
    drawPos.setPixelsY(455);

    gout.setPosition(drawPos);
    gout << "Projectile Altitude: " << pGame->projectile.getPosition()->getMetersY() - pGame->ground.getElevationMeters(*pGame->projectile.getPosition()) << " meters";

    drawPos.setPixelsX(425);
    drawPos.setPixelsY(430);

    gout.setPosition(drawPos);
    gout << "Projectile Speed: " << pGame->projectile.getV() << " m/s";

    drawPos.setPixelsX(425);
    drawPos.setPixelsY(405);

    gout.setPosition(drawPos);
    gout << "Hang Time: " << pGame->projectile.getAge() << " s";
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);

   testRunner();

   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "Artillery Simulator",   /* name on the window */
      ptUpperRight);

   // Initialize the game
   Game game(ptUpperRight);

   // set everything into action
   ui.run(callBack, &game);

   return 0;
}
