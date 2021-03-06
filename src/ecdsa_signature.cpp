/*
 * CONCLAVE - Scaling Bitcoin Simply.
 * Copyright (C) 2019-2021 Conclave development team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ecdsa_signature.h"
#include <bitcoin/system.hpp>

namespace bc_system = libbitcoin::system;
namespace conclave
{
    ///
    /// Factories
    ///
    
    EcdsaSignature EcdsaSignature::deserialize(const std::vector<BYTE>& data, size_t& pos)
    {
        // DER deserialization
        const auto derSig =
            std::vector<BYTE>(data.cbegin() + pos, data.cbegin() + pos + ECDSA_SIGNATURE_DER_MAX_SIZE_BYTES);
        bc_system::ec_signature sig;
        bc_system::parse_signature(sig, derSig, false);
        return static_cast<EcdsaSignature>(sig);
    }
    
    EcdsaSignature EcdsaSignature::deserialize(const std::vector<BYTE>& data)
    {
        size_t pos = 0;
        return deserialize(data, pos);
    }
    
    ///
    /// Constructors
    ///
    
    EcdsaSignature::EcdsaSignature(const EcdsaSignature& other) = default;
    
    EcdsaSignature::EcdsaSignature(EcdsaSignature&& other) noexcept
        : r(std::move(other.r)), s(std::move(other.s))
    {
    }
    
    EcdsaSignature::EcdsaSignature(Hash256 r, Hash256 s)
        : r(std::move(r)), s(std::move(s))
    {
    }
    
    EcdsaSignature::EcdsaSignature(const std::array<BYTE, ECDSA_SIGNATURE_SIZE_BYTES>& data)
        : r(&data[0]), s(&data[0] + SECP256K1_SCALAR_SIZE_BYTES)
    {
    }
    
    EcdsaSignature::EcdsaSignature(const std::string& hex)
        : EcdsaSignature(hexStringToByteArray<ECDSA_SIGNATURE_SIZE_BYTES>(hex))
    {
    }
    
    EcdsaSignature::EcdsaSignature(const char* hex)
        : EcdsaSignature(std::string(hex))
    {
    }
    
    ///
    /// Public Functions
    ///
    
    std::vector<BYTE> EcdsaSignature::serialize() const
    {
        // DER Serialization
        bc_system::der_signature der;
        bc_system::encode_signature(der, static_cast<const std::array<BYTE, ECDSA_SIGNATURE_SIZE_BYTES>>(*this));
        return der;
    }
    
    ///
    /// Conversions
    ///
    
    EcdsaSignature::operator std::array<BYTE, ECDSA_SIGNATURE_SIZE_BYTES>() const
    {
        std::array<BYTE, ECDSA_SIGNATURE_SIZE_BYTES> arr{};
        std::copy(r.begin(), r.end(), arr.begin());
        std::copy(s.begin(), s.end(), arr.begin() + SECP256K1_SCALAR_SIZE_BYTES);
        return arr;
    }
    
    EcdsaSignature::operator std::vector<BYTE>() const
    {
        const auto array = static_cast<std::array<BYTE, ECDSA_SIGNATURE_SIZE_BYTES>>(*this);
        std::vector<BYTE> vector(ECDSA_SIGNATURE_SIZE_BYTES);
        std::copy(array.begin(), array.end(), vector.begin());
        return vector;
    }
    
    EcdsaSignature::operator std::string() const
    {
        return byteArrayToHexString(static_cast<std::array<BYTE, ECDSA_SIGNATURE_SIZE_BYTES>>(*this));
    }
    
    ///
    /// Operator Overloads
    ///
    
    EcdsaSignature& EcdsaSignature::operator=(const EcdsaSignature& other) = default;
    
    EcdsaSignature& EcdsaSignature::operator=(EcdsaSignature&& other) noexcept
    {
        r = std::move(other.r);
        s = std::move(other.s);
        return *this;
    }
    
    bool EcdsaSignature::operator==(const EcdsaSignature& other) const
    {
        return (r == other.r) && (s == other.s);
    }
    
    bool EcdsaSignature::operator!=(const EcdsaSignature& other) const
    {
        return (r != other.r) || (s != other.s);
    }
    
    std::ostream& operator<<(std::ostream& os, const EcdsaSignature& ecdsaSignature)
    {
        os << static_cast<std::string>(ecdsaSignature);
        return os;
    }
}
