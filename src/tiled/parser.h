/**
 *
 * Retro
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2025 Retro Technique
 *
 * This software is a computer program whose purpose is to provide
 * minimalist modern C++ functionalities for 2D game development.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 */

#pragma once

#include "data_parser.h"

namespace retro::tiled
{	

	template<typename T>
	T read(const boost::property_tree::ptree& pt);

	template<>
	tmx::property read<tmx::property>(const boost::property_tree::ptree& pt)
	{
		return
		{
			._name = pt.get<std::string>("<xmlattr>.name", ""),
			._type = pt.get<std::string>("<xmlattr>.type", ""),
			._value = pt.get<std::string>("<xmlattr>.value", "")
		};
	}

	std::vector<tmx::property> parse_properties(const boost::property_tree::ptree& pt)
	{
		std::vector<tmx::property> properties;

		if (auto props = pt.get_child_optional("properties"))
		{
			for (const auto& [tag, child] : *props)
			{
				if (tag == "property")
				{
					properties.emplace_back(read<tmx::property>(child));
				}
			}
		}

		return properties;
	}

	template<>
	tmx::data read<tmx::data>(const boost::property_tree::ptree& pt)
	{
		tmx::data element
		{
			._encoding = pt.get<std::string>("<xmlattr>.encoding", ""),
			._compression = pt.get<std::string>("<xmlattr>.compression", "")
		};

		std::string encoded_data = pt.get<std::string>("");

		encoded_data.erase(std::remove_if(encoded_data.begin(), encoded_data.end(),
										  [](std::uint8_t c)
										  {
											  return std::isspace(c);
										  }), encoded_data.end()
											  );

		tmx::data_parser(encoded_data, element._data).process(element._encoding, element._compression);

		return element;
	}

	template<>
	tmx::layer read<tmx::layer>(const boost::property_tree::ptree& pt)
	{
		return
		{
			._id = pt.get<std::int32_t>("<xmlattr>.id", 0),
			._name = pt.get<std::string>("<xmlattr>.name", ""),
			._class = pt.get<std::string>("<xmlattr>.class", ""),
			._width = pt.get<std::int32_t>("<xmlattr>.width", 0),
			._height = pt.get<std::int32_t>("<xmlattr>.height", 0),
			._data = read<tmx::data>(pt.get_child("data")),
			._properties = parse_properties(pt)
		};
	}

	template<>
	tmx::tileset read<tmx::tileset>(const boost::property_tree::ptree& pt)
	{
		return
		{
			._firstgid = pt.get<std::int32_t>("<xmlattr>.firstgid", 0),
			._source = pt.get<std::string>("<xmlattr>.source", "")
		};
	}

	template<>
	tmx::object read<tmx::object>(const boost::property_tree::ptree& pt)
	{
		return
		{
			._id = pt.get<std::int32_t>("<xmlattr>.id", 0),
			._name = pt.get<std::string>("<xmlattr>.name", ""),
			._type = pt.get<std::string>("<xmlattr>.type", ""),
			._x = pt.get<std::int32_t>("<xmlattr>.x", 0),
			._y = pt.get<std::int32_t>("<xmlattr>.y", 0),
			._width = pt.get<std::int32_t>("<xmlattr>.width", 0),
			._height = pt.get<std::int32_t>("<xmlattr>.height", 0),
			._properties = parse_properties(pt)
		};
	}

	template<>
	tmx::object_group read<tmx::object_group>(const boost::property_tree::ptree& pt)
	{
		std::vector<tmx::object> objects;

		for (const auto& [tag, child] : pt)
		{
			if (tag == "object")
			{
				objects.emplace_back(read<tmx::object>(child));
			}
		}

		return 
		{
			._id = pt.get<std::int32_t>("<xmlattr>.id", 0),
			._name = pt.get<std::string>("<xmlattr>.name", ""),
			._class = pt.get<std::string>("<xmlattr>.class", ""),
			._objects = std::move(objects),
			._properties = parse_properties(pt)
		};
	}

	template<>
	tmx::map read<tmx::map>(const boost::property_tree::ptree& pt)
	{
		std::vector<tmx::tileset> tilesets;
		std::vector<tmx::layer> layers;
		std::vector<tmx::object_group> object_groups;

		for (const auto& [tag, child] : pt)
		{
			if (tag == "tileset")
			{
				tilesets.emplace_back(read<tmx::tileset>(child));
			}
			else if (tag == "layer")
			{
				layers.emplace_back(read<tmx::layer>(child));
			}
			else if (tag == "objectgroup")
			{
				object_groups.emplace_back(read<tmx::object_group>(child));
			}
		}

		return
		{
			._tiledversion = pt.get<std::string>("<xmlattr>.tiledversion", ""),
			._orientation = pt.get<std::string>("<xmlattr>.orientation", ""),
			._renderorder = pt.get<std::string>("<xmlattr>.renderorder", ""),
			._width = pt.get<std::int32_t>("<xmlattr>.width", 0),
			._height = pt.get<std::int32_t>("<xmlattr>.height", 0),
			._tilewidth = pt.get<std::int32_t>("<xmlattr>.tilewidth", 0),
			._tileheight = pt.get<std::int32_t>("<xmlattr>.tileheight", 0),
			._infinite = pt.get<std::int32_t>("<xmlattr>.infinite", 0),
			._nextlayerid = pt.get<std::int32_t>("<xmlattr>.nextlayerid", 0),
			._nextobjectid = pt.get<std::int32_t>("<xmlattr>.nextobjectid", 0),
			._tilesets = std::move(tilesets),
			._layers = std::move(layers),
			._object_groups = std::move(object_groups),
		};
	}

	template<>
	tsx::image read<tsx::image>(const boost::property_tree::ptree& pt)
	{
		return
		{
			._source = pt.get<std::string>("<xmlattr>.source", ""),
			._trans = pt.get<std::string>("<xmlattr>.trans", ""),
			._width = pt.get<std::int32_t>("<xmlattr>.width", 0),
			._height = pt.get<std::int32_t>("<xmlattr>.height", 0)
		};
	}

	template<>
	tsx::tileset read<tsx::tileset>(const boost::property_tree::ptree& pt)
	{
		return
		{
			._tiledversion = pt.get<std::string>("<xmlattr>.tiledversion", ""),
			._name = pt.get<std::string>("<xmlattr>.name", ""),
			._tilewidth = pt.get<std::int32_t>("<xmlattr>.tilewidth", 0),
			._tileheight = pt.get<std::int32_t>("<xmlattr>.tileheight", 0),
			._spacing = pt.get<std::int32_t>("<xmlattr>.spacing", 0),
			._margin = pt.get<std::int32_t>("<xmlattr>.margin", 0),
			._tilecount = pt.get<std::int32_t>("<xmlattr>.tilecount", 0),
			._columns = pt.get<std::int32_t>("<xmlattr>.columns", 0),
			._image = pt.get_child_optional("image")
				? read<tsx::image>(pt.get_child("image"))
				: tsx::image{}
		};
	}

}