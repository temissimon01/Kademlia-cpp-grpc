#include "Identifier.h"

Identifier::Identifier() : __val(0) {}
Identifier::Identifier(Identifier::numeric_type val) : __val(val) {}
Identifier::~Identifier(){}

Identifier Identifier::FromString(std::string src)
{
    try {
        Identifier::numeric_type val = boost::lexical_cast<boost::multiprecision::cpp_int>(src).convert_to<Identifier::numeric_type>();

        return Identifier(val);
    }
    catch(...){}

    return Identifier();
}

Identifier::numeric_type Identifier::value() const
{
    return __val;
}

Identifier::numeric_type Identifier::Distance(const Identifier::numeric_type& A, const Identifier::numeric_type& B)
{
    // Kademlia distance function A xor B
    return A ^ B;
}

Identifier::numeric_type Identifier::distance(const Identifier::numeric_type& OtherID) const
{
    // Kademlia distance function A xor B
    return __val ^ OtherID;
}

Identifier::numeric_type Identifier::bucketOf(const Identifier::numeric_type& OtherID) const
{
    // Get the distance to the other node
    Identifier::numeric_type dist = this->distance(OtherID);

    // Get subtree in which the node should be stored (K-Bucket)
    for (int j = 0; j < Kademlia::GUID_SPACE; j++) {
        if ((dist >> (Kademlia::GUID_SPACE - 1 - j) & 0x1) != 0) {
            return Kademlia::GUID_SPACE - j;
        }
    }

    // The distance between the two nodes are 0 (OtherID == this->__val)
    return 0;
}

Identifier::operator Identifier::numeric_type() const
{
    return __val;
}

Identifier::operator std::string() const
{
    return __val.str();
}

std::vector<Identifier> Identifier::GetDirectReferenceIds(const Identifier& id)
{
    std::vector<Identifier> ret;

    for (unsigned int i = 0; i < Kademlia::GUID_SPACE; i++) {
        Identifier::numeric_type id_value = boost::multiprecision::pow((Identifier::numeric_type)2, i);
        ret.push_back(Identifier(id_value));
    }

    return ret;
}

bool operator==(const Identifier& A, const Identifier& B)
{
    return A.__val == B.__val;
}

bool operator!=(const Identifier& A, const Identifier& B)
{
    return A.__val != B.__val;
}
