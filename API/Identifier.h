#pragma once

#pragma region NOSTDINCLUDE

#include <API/SysDef.h>
#include <boost/multiprecision/cpp_int.hpp>

#pragma endregion

class Identifier
{
public:
	typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<Kademlia::GUID_SPACE, Kademlia::GUID_SPACE, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>  numeric_type;

	Identifier();
	Identifier(Identifier::numeric_type val);
	~Identifier();

	static Identifier FromString(std::string src);

	Identifier::numeric_type value() const;

	static Identifier::numeric_type Distance(const Identifier::numeric_type& A, const Identifier::numeric_type& B);
	Identifier::numeric_type distance(const Identifier::numeric_type& OtherID) const;

	Identifier::numeric_type bucketOf(const Identifier::numeric_type &OtherID) const;

	friend bool operator==(const Identifier& A, const Identifier& B);
	friend bool operator!=(const Identifier& A, const Identifier& B);

	operator Identifier::numeric_type() const;
	operator std::string() const;

	static std::vector<Identifier> GetDirectReferenceIds(const Identifier& id);

private:
	Identifier::numeric_type __val;
};

