#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if (map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

	p2List_item<TilesetInfo>* item;
	item = tilesetList.start;

	int i = 0;

	if (load_tex) {

		tile = new SDL_Texture*[tilesetList.count()];

		while (item != NULL)
		{
			tile[i] = App->tex->Load(item->data.name.GetString());
			i++;
			item = item->next;
		}

		item = tilesetList.start;
		i = 0;

		load_tex = false;
	}

	App->render->Blit(tile[i], 0, 0);
	item = item->next;
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map

	if (tilesetList.start != nullptr)
		tilesetList.clear();

	if (layerList.start != nullptr)
		layerList.clear();

	layerInfo.name.Clear();
	tilesetInfo.name.Clear();

	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if (ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data

		if (LoadMap()) {
			LOG("Successfully parsed map XML file: %s", file_name);
			LOG("width: %i", mapInfo.width);
			LOG("height: %i", mapInfo.height);
			LOG("tile_width: %i", mapInfo.tilewidth);
			LOG("tile_height: %i", mapInfo.tileheight);
			
			map_loaded = ret;
		}
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	
	if (map_loaded == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything

		if (LoadTilesets()) {

			p2List_item<TilesetInfo>* item;
			item = tilesetList.start;

			while (item != NULL)
			{
				LOG("Tileset ----");
				LOG("name: %s", item->data.name.GetString());
				LOG("firstgid: %i", item->data.firstgid);
				LOG("tile_width: %i", item->data.tilewidth);
				LOG("tile_height: %i", item->data.tileheight);
				LOG("spacing: %i", item->data.spacing);
				LOG("margin: %i", item->data.margin);

				item = item->next;
			}

			tilesets_loaded = ret;
		}
	}

	if (tilesets_loaded == true) {

		if (LoadLayers()) {

			p2List_item<LayerInfo>* item;
			item = layerList.start;

			while (item != NULL)
			{
				LOG("Layer ----");
				LOG("name: %s", item->data.name.GetString());
				LOG("width: %i", item->data.width);
				LOG("height: %i", item->data.height);

				item = item->next;
			}

			layers_loaded = ret;
		}
	}

	tmp.Clear();

	return ret;
}

bool j1Map::LoadMap() {

	bool ret = true;

	pugi::xml_node map = map_file.child("map");

	p2SString temp_orientation = map.attribute("orientation").as_string();

	if (temp_orientation == "orthogonal")
		mapInfo.o = orthogonal;
	else if (temp_orientation == "isometric")
		mapInfo.o = isometric;
	else if (temp_orientation == "staggered")
		mapInfo.o = staggered;
	else if (temp_orientation == "hexagonal")
		mapInfo.o = hexagonal;

	p2SString temp_renderorder = map.attribute("orientation").as_string();

	if (temp_renderorder == "right_down")
		mapInfo.r = right_down;
	else if (temp_renderorder == "right_up")
		mapInfo.r = right_up;
	else if (temp_renderorder == "left_down")
		mapInfo.r = left_down;
	else if (temp_renderorder == "left_up")
		mapInfo.r = left_up;

	mapInfo.width = map.attribute("width").as_uint();
	mapInfo.height = map.attribute("height").as_uint();
	mapInfo.tilewidth = map.attribute("tilewidth").as_uint();
	mapInfo.tileheight = map.attribute("tileheight").as_uint();
	mapInfo.nextobjectid = map.attribute("nextobjectid").as_uint();

	temp_orientation.Clear();
	temp_renderorder.Clear();

	return ret;
}

bool j1Map::LoadTilesets() {

	bool ret = true;

	for (pugi::xml_node tileset = map_file.child("map").child("tileset"); tileset; tileset = tileset.next_sibling("tileset")) {

		tilesetInfo.firstgid = tileset.attribute("firstgid").as_uint();
		
		p2SString temp_name("%s%s%s", folder.GetString(), tileset.attribute("name").as_string(), ".png");
		
		tilesetInfo.name = temp_name;
		
		tilesetInfo.tilewidth = tileset.attribute("tilewidth").as_uint();
		tilesetInfo.tileheight = tileset.attribute("tileheight").as_uint();
		tilesetInfo.spacing = tileset.attribute("spacing").as_uint();
		tilesetInfo.margin = tileset.attribute("margin").as_uint();

		tilesetList.add(tilesetInfo);

		temp_name.Clear();
	}

	return ret;
}

bool j1Map::LoadLayers() {

	bool ret = true;

	for (pugi::xml_node layer = map_file.child("map").child("layer"); layer; layer = layer.next_sibling("layer")) {

		layerInfo.name = layer.attribute("name").as_string();
		layerInfo.width = layer.attribute("width").as_uint();
		layerInfo.height = layer.attribute("height").as_uint();

		layerList.add(layerInfo);
	}

	return ret;
}
