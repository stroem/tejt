#include "menu.hpp"

Menu::Menu(const std::string& msg)
{
	eye.position = Point(2.0, 2.0, 5.0);
    rotation_speed = 0.01;

	Letter style(Size(0.08, 0.06, 0), 0.02, 2.5, Color(0.3,0.3,1));	//

	world.push_back(object_ptr(new Body(Point(2, 2, 0), Size(2,2,2), Color(1,1,1), CUBE_BORDERED)));	// Huvudkuben

	// Den text vi vill ha på menyn läggs till i vår värld.
	world.push_back(object_ptr(new Text("NEW GAME", style, Point(2, 2.9, 1+MILLI), Size())));

	world.push_back(object_ptr(new Text("DIRECT IP", style,
		Point(-2, 2.9, 1+MILLI), Size(0,0,0), Color(0.6,0.6,0.6), Rotation(0,0,-90))));

	world.push_back(object_ptr(new Text("QUIT", style, Point(2, 1.1, 1+MILLI))));

	world.push_back(object_ptr(new Text("TEJTPUCK V.1337", Letter(Size(0.1, 0.07, 0.5), 0.03, 2.5),
		Point(2, -1.1, 1+MILLI), Size(2,0,0), Color(0.6,0.6,0.6), Rotation(0,0,90), false)));

	world.push_back(object_ptr(new Text(msg, Letter(Size(0.07,0.15,0.0), 0.03, 2.5, Color(0,0,0)),
		Point(2, 2, 1+MILLI), Size(0.75))));
}

Menu::~Menu()
{

}

void Menu::Think(unsigned int elapsed_time)
{
    if(eye.rotation.z > 5.0)
       rotation_speed = -0.01;

    if(eye.rotation.z < -5.0)
       rotation_speed = 0.01;

    eye.rotation.z += rotation_speed*elapsed_time;
}
void Menu::OnKeyDown(const ::SDL_KeyboardEvent& key)
{
	switch(key.keysym.sym)
	{
		// Hantera knapptryckningar och initiera de motsvarande aktiviteterna
		case SDLK_UP:
			SetNextActivity(new Fade(new Login, world, eye), true);
			break;
		case SDLK_RIGHT:
			//SetNextActivity(new Fade(new DirectIP, world, eye), true);
			break;
		case SDLK_ESCAPE:
			SetNextActivity(new Fade(0, world, eye), true);
			break;
		case SDLK_DOWN:
			SetNextActivity(new Fade(0, world, eye), true);
			break;
		default:
			break;
	}
}
