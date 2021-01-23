#include "Entity.h"
#include "Log.h"
#include "Render.h"
#include "Scene.h"

Entity::Entity(const fPoint& position, const char* name, EntityType type) 
	:position(position), name(name), type(type)
{
	this->position = position;
	pugi::xml_document config_file;
	pugi::xml_node ret;

	pugi::xml_parse_result result = config_file.load_file("config.xml");

	if (result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config").child("entities");

	switch (type)
	{
	case EntityType::NO_ENTITY:
		break;
	case EntityType::PLAYER:
		entNode = ret.child("player");

		break;
	case EntityType::ASTEROID:
		entNode = ret.child("asteroid");

		break;
	case EntityType::MOON:
		entNode = ret.child("moon");

		break;
	case EntityType::EARTH:
		entNode = ret.child("earth");

		break;
	case EntityType::BULLET:
		entNode = ret.child("shot");

		break;
	default:
		break;
	}



}

Entity::~Entity()
{

}


void Entity::Draw()
{
	if (currentAnim != nullptr) 
		app->render->DrawTexture(characterTex, position.x, position.y, &currentAnim->GetCurrentFrame(), 1.0f);
	else 
		app->render->DrawTexture(characterTex, position.x, position.y);
}



void Entity::AwakeEntity(pugi::xml_node& playerNode)
{
	size.x = playerNode.child("position").attribute("w").as_int();
	size.y = playerNode.child("position").attribute("h").as_int();

	speed.x = playerNode.child("speed").attribute("x").as_int();
	speed.y = playerNode.child("speed").attribute("y").as_int();

	//pugi::xml_node node = playerNode.child("spawnPosition");
	spawnPos.x = playerNode.child("spawnPosition").attribute("x").as_int();
	spawnPos.y = playerNode.child("spawnPosition").attribute("y").as_int();

	for (pugi::xml_node node = playerNode.child("animation"); node; node = node.next_sibling("animation"))
	{

		for (pugi::xml_node node_iterator = node.child("frame"); node_iterator; node_iterator = 
			node_iterator.next_sibling("frame")) 
		{
			SDL_Rect frame;
			frame.x = node_iterator.attribute("x").as_int();
			frame.y = node_iterator.attribute("y").as_int();
			frame.w = node_iterator.attribute("w").as_int();
			frame.h = node_iterator.attribute("h").as_int();

			SString name = node.attribute("name").as_string();
			if (name == "idle")
			{
				idleAnim.PushBack(frame);
				idleAnim.speed = node.attribute("speed").as_float();
				idleAnim.loop = node.attribute("loop").as_bool();
			}

			else if (name == "fly")
			{
				flyAnim.PushBack(frame);
				flyAnim.speed = node.attribute("speed").as_float();
				flyAnim.loop = node.attribute("loop").as_bool();
			}

			else if (name == "dead")
			{
				deathAnim.PushBack(frame);
				deathAnim.speed = node.attribute("speed").as_float();
				deathAnim.loop = node.attribute("loop").as_bool();
			}

			else if (name == "shot")
			{
				fireAnim.PushBack(frame);
				fireAnim.speed = node.attribute("speed").as_float();
				fireAnim.loop = node.attribute("loop").as_bool();
			}

			else if (name == "asteroid")
			{
				asteroidAnim.PushBack(frame);
				asteroidAnim.speed = node.attribute("speed").as_float();
				asteroidAnim.loop = node.attribute("loop").as_bool();
			}

			else if (name == "moon")
			{
				moonAnim.PushBack(frame);
				moonAnim.speed = node.attribute("speed").as_float();
				moonAnim.loop = node.attribute("loop").as_bool();
			}

			else if (name == "earth")
			{
				earthAnim.PushBack(frame);
				earthAnim.speed = node.attribute("speed").as_float();
				earthAnim.loop = node.attribute("loop").as_bool();
			}
		}

	}

}



