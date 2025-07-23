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

#ifndef __RETRO_TILED_H_INCLUDED__
#error "Do not include this file directly, include <retro/tiled.h> instead."
#endif

namespace retro::tiled::tmx
{

	struct property
	{
		std::string _name;
		std::string _type;
		std::string _value;
	};

	struct tileset
	{
		std::int32_t _firstgid = 0;
		std::string _source;
	};

	struct data
	{
		std::string _encoding;
		std::string _compression;
		std::vector<std::uint32_t> _data;
	};

	struct layer
	{
		std::int32_t _id = 0;
		std::string _name;
		std::string _class;
		std::int32_t _width = 0;
		std::int32_t _height = 0;
		tmx::data _data;
		std::vector<tmx::property> _properties;
	};

	struct object
	{
		std::int32_t _id = 0;
		std::string _name;
		std::string _type;
		std::int32_t _x = 0;
		std::int32_t _y = 0;
		std::int32_t _width = 0;
		std::int32_t _height = 0;
		std::vector<tmx::property> _properties;
	};

	struct object_group
	{
		std::int32_t _id = 0;
		std::string _name;
		std::string _class;
		std::vector<tmx::object> _objects;
		std::vector<tmx::property> _properties;
	};

	struct map
	{
		std::string _tiledversion;
		std::string _orientation;
		std::string _renderorder;
		std::int32_t _width = 0;
		std::int32_t _height = 0;
		std::int32_t _tilewidth = 0;
		std::int32_t _tileheight = 0;
		std::int32_t _infinite = 0;
		std::int32_t _nextlayerid = 0;
		std::int32_t _nextobjectid = 0;
		std::vector<tmx::tileset> _tilesets;
		std::vector<tmx::layer> _layers;
		std::vector<tmx::object_group> _object_groups;
	};

}