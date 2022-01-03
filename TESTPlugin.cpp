// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "Header.h"


BAKKESMOD_PLUGIN(TESTPlugin, "TESTPlugin", "0.1", PLUGINTYPE_FREEPLAY)


void TESTPlugin::onLoad() {
	printf("test");
	cvarManager->registerNotifier("startCounter", [&gw = this->gameWrapper](std::vector<std::string> commands) {
		//START VERIF FREEPLAY
		if (!gw->IsInFreeplay())
			return;
		ServerWrapper tutorial = gw->GetGameEventAsServer();


		if (tutorial.GetGameBalls().Count() == 0)
			return;

		BallWrapper ball = tutorial.GetGameBalls().Get(0);
		CarWrapper car = tutorial.GetGameCar();
		if (ball.IsNull() || car.IsNull())
			return;
		//END VERIF FREEPLAY

		printf("test");

	}, "Count how many time you hit the ball", PERMISSION_FREEPLAY | PERMISSION_PAUSEMENU_CLOSED);
}

void TESTPlugin::onUnload() {

}
