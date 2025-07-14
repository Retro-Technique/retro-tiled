#include <boost/test/unit_test.hpp>
#include <retro/tiled.h>

#define BOOST_TEST_MODULE TMXTestModule

BOOST_AUTO_TEST_CASE(TMXReadTest)
{
	retro::tiled::tmx::map map;

	try
	{
		retro::tiled::file(map).load_from_file("..\\..\\..\\..\\tests\\res\\room_01.tmx");
	}
	catch (const std::exception& e)
	{
		BOOST_ERROR(e.what());
	}

	BOOST_CHECK_EQUAL("1.11.2", map._tiledversion);
	BOOST_CHECK_EQUAL("orthogonal", map._orientation);
	BOOST_CHECK_EQUAL("right-down", map._renderorder);
	BOOST_CHECK_EQUAL(5, map._width);
	BOOST_CHECK_EQUAL(5, map._height);
	BOOST_CHECK_EQUAL(16, map._tilewidth);
	BOOST_CHECK_EQUAL(16, map._tileheight);
	BOOST_CHECK_EQUAL(0, map._infinite);
	BOOST_CHECK_EQUAL(4, map._nextlayerid);
	BOOST_CHECK_EQUAL(1, map._nextobjectid);
	BOOST_CHECK_EQUAL(1, map._tilesets.size());
	BOOST_CHECK_EQUAL(1, map._layers.size());
	BOOST_CHECK_EQUAL(1, map._tilesets[0]._firstgid);
	BOOST_CHECK_EQUAL("tileset_01.tsx", map._tilesets[0]._source);
	BOOST_CHECK_EQUAL(3, map._layers[0]._id);
	BOOST_CHECK_EQUAL("ground", map._layers[0]._name);
	BOOST_CHECK_EQUAL(5, map._layers[0]._width);
	BOOST_CHECK_EQUAL(5, map._layers[0]._height);
}