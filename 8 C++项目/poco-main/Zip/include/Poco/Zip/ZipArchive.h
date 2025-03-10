//
// ZipArchive.h
//
// Library: Zip
// Package: Zip
// Module:  ZipArchive
//
// Definition of the ZipArchive class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Zip_ZipArchive_INCLUDED
#define Zip_ZipArchive_INCLUDED


#include "Poco/Zip/Zip.h"
#include "Poco/Zip/ZipLocalFileHeader.h"
#include "Poco/Zip/ZipFileInfo.h"
#include "Poco/Zip/ZipArchiveInfo.h"
#include <istream>
#include <map>


namespace Poco {
namespace Zip {


class ParseCallback;
class Compress;


class Zip_API ZipArchive
	/// A ZipArchive contains information on the content of a zip file
{
public:
	using FileHeaders = std::map<std::string, ZipLocalFileHeader>;
	using FileInfos = std::map<std::string, ZipFileInfo>;
	using DirectoryInfos = std::map<Poco::UInt16, ZipArchiveInfo>;
	using DirectoryInfos64 = std::map<Poco::UInt32, ZipArchiveInfo64>;

	ZipArchive(std::istream& in);
		/// Creates the ZipArchive from a file. Note that the in stream will be in state failed after the constructor is finished

	ZipArchive(std::istream& in, ParseCallback& callback);
		/// Creates the ZipArchive from a file or network stream. Note that the in stream will be in state failed after the constructor is finished

	~ZipArchive();
		/// Destroys the ZipArchive.

	void checkConsistency();
		/// Check archive's consistency

	FileInfos::const_iterator fileInfoBegin() const;

	FileInfos::const_iterator fileInfoEnd() const;

	FileHeaders::const_iterator findHeader(const std::string& fileName) const;

	FileHeaders::const_iterator headerBegin() const;

	FileHeaders::const_iterator headerEnd() const;

	const std::string& getZipComment() const;

private:
	void parse(std::istream& in, ParseCallback& pc);

	ZipArchive(const FileHeaders& entries, const FileInfos& infos, const DirectoryInfos& dirs, const DirectoryInfos64& dirs64 );

private:
	FileHeaders    _entries;
		/// Info generated by parsing the data block of the zip file
	FileInfos      _infos;
		/// Info generated by parsing the directory block of the zip file
	DirectoryInfos _disks;
		/// Stores directory info for all found disks
	DirectoryInfos64 _disks64;
		/// Stores directory info for all found disks

	static const std::string EMPTY_COMMENT;

	friend class Compress;
};


inline ZipArchive::FileInfos::const_iterator ZipArchive::fileInfoBegin() const
{
	return _infos.begin();
}


inline ZipArchive::FileInfos::const_iterator ZipArchive::fileInfoEnd() const
{
	return _infos.end();
}


inline ZipArchive::FileHeaders::const_iterator ZipArchive::findHeader(const std::string& fileName) const
{
	return _entries.find(fileName);
}


inline ZipArchive::FileHeaders::const_iterator ZipArchive::headerBegin() const
{
	return _entries.begin();
}


inline ZipArchive::FileHeaders::const_iterator ZipArchive::headerEnd() const
{
	return _entries.end();
}


} } // namespace Poco::Zip


#endif // Zip_ZipArchive_INCLUDED
