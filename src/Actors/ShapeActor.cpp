#include <Actors/ShapeActor.h>


Simulation::ShapeActor::ShapeActor()
{

}

Simulation::ShapeActor::~ShapeActor()
{
	delete this->actorShape;
	delete this->fillColor;
	delete this->actorText;
}
