#include <boost/test/unit_test.hpp>
#include <retro/tiled.h>

#define BOOST_TEST_MODULE TSXTestModule

BOOST_AUTO_TEST_CASE(TSXReadTest)
{
	try
	{
		const retro::tiled::tsx::tileset tileset = retro::tiled::load_from_file<retro::tiled::tsx::tileset>(TESTS_RESOURCE_DIRECTORY "\\" "tileset_01.tsx");

		BOOST_CHECK_EQUAL("1.11.2", tileset._tiledversion);
		BOOST_CHECK_EQUAL("tileset_01", tileset._name);
		BOOST_CHECK_EQUAL(16, tileset._tilewidth);
		BOOST_CHECK_EQUAL(16, tileset._tileheight);
		BOOST_CHECK_EQUAL(1, tileset._spacing);
		BOOST_CHECK_EQUAL(0, tileset._margin);
		BOOST_CHECK_EQUAL(968, tileset._tilecount);
		BOOST_CHECK_EQUAL(44, tileset._columns);
		BOOST_CHECK_EQUAL("tileset_01.png", tileset._image._source);
		BOOST_CHECK_EQUAL("ff00ff", tileset._image._trans);
		BOOST_CHECK_EQUAL(748, tileset._image._width);
		BOOST_CHECK_EQUAL(374, tileset._image._height);
	}
	catch (const std::exception& e)
	{
		BOOST_ERROR(e.what());
	}
}