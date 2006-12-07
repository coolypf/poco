//
// BinaryWriter.h
//
// $Id: //poco/1.2/Foundation/include/Poco/BinaryWriter.h#1 $
//
// Library: Foundation
// Package: Streams
// Module:  BinaryReaderWriter
//
// Definition of the BinaryWriter class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_BinaryWriter_INCLUDED
#define Foundation_BinaryWriter_INCLUDED


#include "Poco/Foundation.h"
#include <ostream>


namespace Poco {


class Foundation_API BinaryWriter
	/// This class writes basic types in binary form into an output stream.
	/// It provides an inserter-based interface similar to ostream.
	/// The writer also supports automatic conversion from big-endian
	/// (network byte order) to little-endian and vice-versa.
	/// Use a BinaryReader to read from a stream created by a BinaryWriter.
	/// Be careful when exchanging data between systems with different
	/// data type sizes (e.g., 32-bit and 64-bit architectures), as the sizes
	/// of some of the basic types may be different. For example, writing a
	/// long integer on a 64-bit system and reading it on a 32-bit system
	/// may yield an incorrent result. Use fixed-size types (Int32, Int64, etc.)
	/// in such a case.
{
public:
	enum StreamByteOrder
	{
		NATIVE_BYTE_ORDER        = 1, /// the host's native byte-order
		BIG_ENDIAN_BYTE_ORDER    = 2, /// big-endian (network) byte-order
		NETWORK_BYTE_ORDER       = 2, /// big-endian (network) byte-order
		LITTLE_ENDIAN_BYTE_ORDER = 3  /// little-endian byte-order
	};
	
	BinaryWriter(std::ostream& ostr, StreamByteOrder byteOrder = NATIVE_BYTE_ORDER);
		/// Creates the BinaryWriter.

	~BinaryWriter();
		/// Destroys the BinaryWriter.

	BinaryWriter& operator << (bool value);
	BinaryWriter& operator << (char value);
	BinaryWriter& operator << (unsigned char value);
	BinaryWriter& operator << (signed char value);
	BinaryWriter& operator << (short value);
	BinaryWriter& operator << (unsigned short value);
	BinaryWriter& operator << (int value);
	BinaryWriter& operator << (unsigned int value);
	BinaryWriter& operator << (long value);
	BinaryWriter& operator << (unsigned long value);
	BinaryWriter& operator << (float value);
	BinaryWriter& operator << (double value);

#if defined(POCO_HAVE_INT64) && !defined(POCO_LONG_IS_64_BIT)
	BinaryWriter& operator << (Int64 value);
	BinaryWriter& operator << (UInt64 value);
#endif

	BinaryWriter& operator << (const std::string& value);
	BinaryWriter& operator << (const char* value);
	
	void write7BitEncoded(UInt32 value);
		/// Writes a 32-bit unsigned integer in a compressed format.
		/// The value is written out seven bits at a time, starting 
		/// with the seven least-significant bits. 
		/// The high bit of a byte indicates whether there are more bytes to be 
		/// written after this one.
		/// If value will fit in seven bits, it takes only one byte of space. 
		/// If value will not fit in seven bits, the high bit is set on the first byte and 
		/// written out. value is then shifted by seven bits and the next byte is written. 
		/// This process is repeated until the entire integer has been written.

#if defined(POCO_HAVE_INT64)
	void write7BitEncoded(UInt64 value);
		/// Writes a 64-bit unsigned integer in a compressed format.
		/// The value written out seven bits at a time, starting 
		/// with the seven least-significant bits. 
		/// The high bit of a byte indicates whether there are more bytes to be 
		/// written after this one.
		/// If value will fit in seven bits, it takes only one byte of space. 
		/// If value will not fit in seven bits, the high bit is set on the first byte and 
		/// written out. value is then shifted by seven bits and the next byte is written. 
		/// This process is repeated until the entire integer has been written.
#endif

	void writeRaw(const std::string& rawData);
		/// Writes the string as-is to the stream.

	void writeBOM();
		/// Writes a byte-order mark to the stream. A byte order mark is
		/// a 16-bit integer with a value of 0xFEFF, written in host byte-order. 
		/// A BinaryReader uses the byte-order mark to determine the byte-order 
		/// of the stream.

	void flush();
		/// Flushes the underlying stream.
		
	bool good();
		/// Returns _ostr.good();
		
	bool fail();
		/// Returns _ostr.fail();
	
	bool bad();
		/// Returns _ostr.bad();
		
	std::ostream& stream() const;
		/// Returns the underlying stream.
		
	StreamByteOrder byteOrder() const;
		/// Returns the byte ordering used by the writer, which is
		/// either BIG_ENDIAN_BYTE_ORDER or LITTLE_ENDIAN_BYTE_ORDER.

private:
	std::ostream& _ostr;
	bool          _flipBytes;
};


//
// inlines
//


inline std::ostream& BinaryWriter::stream() const
{
	return _ostr;
}


inline bool BinaryWriter::good()
{
	return _ostr.good();
}


inline bool BinaryWriter::fail()
{
	return _ostr.fail();
}


inline bool BinaryWriter::bad()
{
	return _ostr.bad();
}


inline BinaryWriter::StreamByteOrder BinaryWriter::byteOrder() const
{
#if defined(POCO_ARCH_BIG_ENDIAN)
	return _flipBytes ? LITTLE_ENDIAN_BYTE_ORDER : BIG_ENDIAN_BYTE_ORDER;
#else
	return _flipBytes ? BIG_ENDIAN_BYTE_ORDER : LITTLE_ENDIAN_BYTE_ORDER;
#endif
}


} // namespace Poco


#endif // Foundation_BinaryWriter_INCLUDED
