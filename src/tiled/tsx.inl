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
	void parser<tsx::image>::read(const boost::property_tree::ptree& pt)
	{
		m_element._source = pt.get<std::string>("<xmlattr>.source", "");
		m_element._trans = pt.get<std::string>("<xmlattr>.trans", "");
		m_element._width = pt.get<std::int32_t>("<xmlattr>.width", 0);
		m_element._height = pt.get<std::int32_t>("<xmlattr>.height", 0);
	}

	template<>
	void parser<tsx::tileset>::read(const boost::property_tree::ptree& pt)
	{
		m_element._tiledversion = pt.get<std::string>("tileset.<xmlattr>.tiledversion", "");
		m_element._name = pt.get<std::string>("tileset.<xmlattr>.name", "");
		m_element._tilewidth = pt.get<std::int32_t>("tileset.<xmlattr>.tilewidth", 0);
		m_element._tileheight = pt.get<std::int32_t>("tileset.<xmlattr>.tileheight", 0);
		m_element._spacing = pt.get<std::int32_t>("tileset.<xmlattr>.spacing", 0);
		m_element._margin = pt.get<std::int32_t>("tileset.<xmlattr>.margin", 0);
		m_element._tilecount = pt.get<std::int32_t>("tileset.<xmlattr>.tilecount", 0);
		m_element._columns = pt.get<std::int32_t>("tileset.<xmlattr>.columns", 0);

		std::for_each(pt.get_child("tileset").begin(), pt.get_child("tileset").end(),
					  [this](const boost::property_tree::ptree::value_type& child_node)
					  {
						  if (child_node.first == "image")
						  {
							  tsx::image image;
							  parser<tsx::image>(image).read(child_node.second);
							  m_element._image = image;
						  }
					  }
		);
	}

}