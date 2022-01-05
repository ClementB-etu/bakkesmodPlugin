// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "Header.h"
#include "utils/parser.h"



BAKKESMOD_PLUGIN(TESTPlugin, "TESTPlugin", "0.1", PLUGINTYPE_FREEPLAY)


void TESTPlugin::onLoad() {

	touchMeasure = std::make_shared<bool>(false);

	cvarManager->registerCvar("startCounter", "0", "Turns on the count.", true, true, 0.0f, true, 1.0f, false).bindTo(touchMeasure);
	cvarManager->getCvar("startCounter").addOnValueChanged([this](std::string oldValue, CVarWrapper cvar)
		{
			if (cvar.getBoolValue())
			{
				gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput", std::bind(&TESTPlugin::BallHit, this));
			}
			else
			{
				gameWrapper->UnhookEvent("Function TAGame.Car_TA.SetVehicleInput");
			}
		});
}

void TESTPlugin::onUnload() {
}

void TESTPlugin::BallHit()
{	
	if (*touchMeasure)
	{	
		if (!gameWrapper->IsInFreeplay())
		{
			return;
		}

		auto server = gameWrapper->GetGameEventAsServer();
		if (server.IsNull())
		{
			return;
		}
		auto ball = server.GetBall();
		if (ball.IsNull())
			return;
		auto rb = ball.GetOldRBState();
		double new_speed_sq = rb.LinearVelocity.X * rb.LinearVelocity.X + rb.LinearVelocity.Y * rb.LinearVelocity.Y;

		if (old_speed_sq >= 0.0)
		{
			if (new_speed_sq > old_speed_sq)
			{	
				cpt += 1;
				//cvarManager->log("HIT : newspeed = " + std::to_string(new_speed_sq) + " oldspeed = "+  std::to_string(old_speed_sq));
				gameWrapper->LogToChatbox("HIT N° " + std::to_string(cpt),"COMPTEUR");
			}
		}
		old_speed_sq = new_speed_sq;
	}
}
