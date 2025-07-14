/**
 *
 * Retro
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2025 Retro Technique
 *
 * This software is a computer program whose purpose is to provide
 * minimalist "C with classes" functionalities.
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

namespace retro::tiled
{

	template<>
	void parser<tmx::data>::read(const boost::property_tree::ptree& pt)
	{
		m_element._encoding = pt.get<std::string>("<xmlattr>.encoding", "");
		m_element._compression = pt.get<std::string>("<xmlattr>.compression", "");

		std::string encoded_data = pt.get<std::string>("");

		encoded_data.erase(std::remove_if(encoded_data.begin(), encoded_data.end(),
								  [](std::uint8_t c)
								  {
									  return std::isspace(c);
								  }), encoded_data.end()
									  );

		tmx::data_parser(encoded_data, m_element._data).process(m_element._encoding, m_element._compression);
	}

	template<>
	void parser<tmx::layer>::read(const boost::property_tree::ptree& pt)
	{
		m_element._id = pt.get<std::int32_t>("<xmlattr>.id", 0);
		m_element._name = pt.get<std::string>("<xmlattr>.name", "");
		m_element._width = pt.get<std::int32_t>("<xmlattr>.width", 0);
		m_element._height = pt.get<std::int32_t>("<xmlattr>.height", 0);
		
		parser<tmx::data>(m_element._data).read(pt.get_child("data"));
	}

	template<>
	void parser<tmx::tileset>::read(const boost::property_tree::ptree& pt)
	{
		m_element._firstgid = pt.get<std::int32_t>("<xmlattr>.firstgid", 0);
		m_element._source = pt.get<std::string>("<xmlattr>.source", "");
	}

	template<>
	void parser<tmx::map>::read(const boost::property_tree::ptree& pt)
	{
		m_element._tiledversion = pt.get<std::string>("map.<xmlattr>.tiledversion", "");
		m_element._orientation = pt.get<std::string>("map.<xmlattr>.orientation", "");
		m_element._renderorder = pt.get<std::string>("map.<xmlattr>.renderorder", "");
		m_element._width = pt.get<std::int32_t>("map.<xmlattr>.width", 0);
		m_element._height = pt.get<std::int32_t>("map.<xmlattr>.height", 0);
		m_element._tilewidth = pt.get<std::int32_t>("map.<xmlattr>.tilewidth", 0);
		m_element._tileheight = pt.get<std::int32_t>("map.<xmlattr>.tileheight", 0);
		m_element._infinite = pt.get<std::int32_t>("map.<xmlattr>.infinite", 0);
		m_element._nextlayerid = pt.get<std::int32_t>("map.<xmlattr>.nextlayerid", 0);
		m_element._nextobjectid = pt.get<std::int32_t>("map.<xmlattr>.nextobjectid", 0);

		std::for_each(pt.get_child("map").begin(), pt.get_child("map").end(),
					  [this](const boost::property_tree::ptree::value_type& child_node)
					  {
						  if (child_node.first == "tileset")
						  {
							  tmx::tileset tileset;
							  parser<tmx::tileset>(tileset).read(child_node.second);
							  m_element._tilesets.push_back(tileset);
						  }
						  if (child_node.first == "layer")
						  {
							  tmx::layer layer;
							  parser<tmx::layer>(layer).read(child_node.second);
							  m_element._layers.push_back(layer);
						  }
					  }
		);
	}

}