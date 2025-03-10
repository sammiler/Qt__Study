//
// NameValueCollection.h
//
// Library: Net
// Package: Messages
// Module:  NameValueCollection
//
// Definition of the NameValueCollection class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_NameValueCollection_INCLUDED
#define Net_NameValueCollection_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/String.h"
#include "Poco/ListMap.h"
#include <cstddef>


namespace Poco {
namespace Net {


class Net_API NameValueCollection
	/// A collection of name-value pairs that are used in
	/// various internet protocols like HTTP and SMTP.
	///
	/// The name is case-insensitive.
	///
	/// There can be more than one name-value pair with the
	/// same name.
{
public:
	using HeaderMap = Poco::ListMap<std::string, std::string>;
	using Iterator = HeaderMap::Iterator;
	using ConstIterator = HeaderMap::ConstIterator;

	NameValueCollection();
		/// Creates an empty NameValueCollection.

	NameValueCollection(const NameValueCollection& nvc);
		/// Creates a NameValueCollection by copying another one.

	NameValueCollection(NameValueCollection&& nvc) noexcept;
		/// Creates a NameValueCollection by moving another one.

	virtual ~NameValueCollection();
		/// Destroys the NameValueCollection.

	NameValueCollection& operator = (const NameValueCollection& nvc);
		/// Assigns the name-value pairs of another NameValueCollection to this one.

	NameValueCollection& operator = (NameValueCollection&& nvc) noexcept;
		/// Moves the name-value pairs of another NameValueCollection to this one.

	void swap(NameValueCollection& nvc) noexcept;
		/// Swaps the NameValueCollection with another one.

	const std::string& operator [] (const std::string& name) const;
		/// Returns the value of the (first) name-value pair with the given name.
		///
		/// Throws a NotFoundException if the name-value pair does not exist.

	void set(const std::string& name, const std::string& value);
		/// Sets the value of the (first) name-value pair with the given name.

	void add(const std::string& name, const std::string& value);
		/// Adds a new name-value pair with the given name and value.

	const std::string& get(const std::string& name) const;
		/// Returns the value of the first name-value pair with the given name.
		///
		/// Throws a NotFoundException if the name-value pair does not exist.

	const std::string& get(const std::string& name, const std::string& defaultValue) const;
		/// Returns the value of the first name-value pair with the given name.
		/// If no value with the given name has been found, the defaultValue is returned.

	bool has(const std::string& name) const;
		/// Returns true if there is at least one name-value pair
		/// with the given name.

	ConstIterator find(const std::string& name) const;
		/// Returns an iterator pointing to the first name-value pair
		/// with the given name.

	Iterator find(const std::string& name);
		/// Returns an iterator pointing to the first name-value pair
		/// with the given name.

	ConstIterator begin() const;
		/// Returns an iterator pointing to the begin of
		/// the name-value pair collection.

	Iterator begin();
		/// Returns an iterator pointing to the begin of
		/// the name-value pair collection.

	ConstIterator end() const;
		/// Returns an iterator pointing to the end of
		/// the name-value pair collection.

	Iterator end();
		/// Returns an iterator pointing to the end of 
		/// the name-value pair collection.

	bool empty() const;
		/// Returns true iff the header does not have any content.

	std::size_t size() const;
		/// Returns the number of name-value pairs in the
		/// collection.

	void erase(const std::string& name);
		/// Removes all name-value pairs with the given name.

	void erase(Iterator it);
		/// Removes the name-value pair referenced by the given iterator.

	void secureErase(const std::string& name);
		/// Securely erases all name-value pairs with the given name,
		/// by first overwriting the value with zeroes before
		/// removing the value.

	void secureErase(Iterator it);
		/// Securely erases the name-value pair referenced by the given iterator,
		/// by first overwriting the value with zeroes before
		/// removing the value.

	void clear();
		/// Removes all name-value pairs and their values.

	void secureClear();
		/// Removes all name-value pairs and their values. 
		/// Additionally, all values are also overwritten with zeroes.

private:
	HeaderMap _map;
};


//
// inlines
//
inline void swap(NameValueCollection& nvc1, NameValueCollection& nvc2) noexcept
{
	nvc1.swap(nvc2);
}


inline NameValueCollection::ConstIterator NameValueCollection::find(const std::string& name) const
{
	return _map.find(name);
}


inline NameValueCollection::Iterator NameValueCollection::find(const std::string& name)
{
	return _map.find(name);
}

	
inline NameValueCollection::ConstIterator NameValueCollection::begin() const
{
	return _map.begin();
}


inline NameValueCollection::Iterator NameValueCollection::begin()
{
	return _map.begin();
}

	
inline NameValueCollection::ConstIterator NameValueCollection::end() const
{
	return _map.end();
}


inline NameValueCollection::Iterator NameValueCollection::end()
{
	return _map.end();
}

	
inline bool NameValueCollection::empty() const
{
	return _map.empty();
}


inline std::size_t NameValueCollection::size() const
{
	return _map.size();
}


} } // namespace Poco::Net


#endif // Net_NameValueCollection_INCLUDED
