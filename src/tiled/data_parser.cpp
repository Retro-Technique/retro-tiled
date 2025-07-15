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

#include "pch.h"
#include "data_parser.h"

namespace retro::tiled::tmx
{

	data_parser::data_parser(const std::string_view& input_data, std::vector<std::uint32_t>& output_data)
		: m_input_data(input_data), m_output_data(output_data)
	{
	}

	void data_parser::process(const std::string_view& encoding, const std::string_view& compressing)
	{
		BOOST_ASSERT_MSG(m_output_data.empty(), "Output data vector should be empty before processing.");
			 
		// si XML (obsolète) : vide + vide
		// si Base64 (non compressé) : "base64" + vide
		// si Base64 (compressé par gzip) : "base64" + "gzip"
		// si Base64 (compressé par zlib) : "base64" + "zlib"
		// si Base64 (compressé par Zstandard) : "base64" + "zstd"
		// si CSV : "csv" + vide

		if (encoding.empty())
		{
			BOOST_ASSERT_MSG(compressing.empty(), "Invalid data encoding and compression combination.");

			decode_xml_data();
		}

		if (encoding == "base64")
		{
			decode_base64_data(compressing);
		}

		if (encoding == "csv")
		{
			BOOST_ASSERT_MSG(compressing.empty(), "Invalid data encoding and compression combination.");

			decode_csv_data();
		}
	}

	void data_parser::decode_xml_data()
	{

	}

	void data_parser::decode_base64_data(const std::string_view& compressing)
	{
		std::vector<char> decoded_data;

		const std::size_t decoded_size = boost::beast::detail::base64::decoded_size(m_input_data.size());
		decoded_data.resize(decoded_size);

		const std::pair<std::size_t, std::size_t> pair = boost::beast::detail::base64::decode(decoded_data.data(), m_input_data.data(), m_input_data.size());

		decoded_data.resize(pair.first);

		if (!compressing.empty())
		{
			uncompress_data(compressing, decoded_data);
		}

		const std::uint32_t* buffer = reinterpret_cast<const std::uint32_t*>(decoded_data.data());

		m_output_data.assign(buffer, buffer + (decoded_data.size() / sizeof(std::uint32_t)));
	}

	void data_parser::decode_csv_data()
	{
		std::vector<std::string> decoded_strings;

		boost::split(decoded_strings, m_input_data, boost::is_any_of(","));

		std::transform(decoded_strings.begin(), decoded_strings.end(), std::back_inserter(m_output_data),
					   [](const std::string& str)
					   {
						   return static_cast<std::uint32_t>(std::stoul(str));
					   });
	}

	void data_parser::uncompress_data(const std::string_view& compressing, std::vector<char>& compressed_data) const
	{
		boost::iostreams::filtering_ostream decompressor;

		if (compressing == "zlib")
		{
			decompressor.push(boost::iostreams::zlib_decompressor());
		}
		else if (compressing == "gzip")
		{
			decompressor.push(boost::iostreams::gzip_decompressor());
		}
		else if (compressing == "zstd")
		{
			decompressor.push(boost::iostreams::zstd_decompressor());
		}

		decompressor.push(boost::iostreams::back_inserter(compressed_data));
		decompressor.write(compressed_data.data(), compressed_data.size());
		decompressor.reset();
	}

}