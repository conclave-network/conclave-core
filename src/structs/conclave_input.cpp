/*
 * CONCLAVE - Making Bitcoin Scale And Be Useful
 * Copyright (C) 2019-2020 Noel P. O'Donnell <noel.odonnell.2020@mumail.ie>
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

#include "conclave_input.h"
#include "../util/json.h"
#include "../util/serialization.h"

namespace conclave
{
    const std::string ConclaveInput::JSONKEY_OUTPOINT = "outpoint";
    const std::string ConclaveInput::JSONKEY_SCRIPTSIG = "scriptSig";
    const std::string ConclaveInput::JSONKEY_SEQUENCE = "sequence";
    
    ConclaveInput::ConclaveInput(const Outpoint& outpoint, const Script& scriptSig, const uint32_t sequence)
        : outpoint(outpoint), scriptSig(scriptSig), sequence(sequence)
    {
    }
    
    ConclaveInput::ConclaveInput(const pt::ptree& tree)
        : ConclaveInput(getObjectFromJson<Outpoint>(tree, JSONKEY_OUTPOINT),
                        getObjectFromJson<Script>(tree, JSONKEY_SCRIPTSIG),
                        getPrimitiveFromJson<uint32_t>(tree, JSONKEY_SEQUENCE))
    {
    }
    
    const std::vector<BYTE> ConclaveInput::serialize() const
    {
        const std::vector<BYTE> outpointSerialized = outpoint.serialize();
        const std::vector<BYTE> scriptSigSerialized = scriptSig.serialize();
        const std::vector<BYTE> sequenceSerialized = serializeU32(sequence);
        std::vector<BYTE> serialized(
            outpointSerialized.size() + scriptSigSerialized.size() + sequenceSerialized.size());
        size_t pos = writeToByteVector(serialized, outpointSerialized);
        pos += writeToByteVector(serialized, scriptSigSerialized, pos);
        writeToByteVector(serialized, sequenceSerialized, pos);
        return serialized;
    }
    
    ConclaveInput::operator pt::ptree() const
    {
        pt::ptree tree;
        tree.add_child(JSONKEY_OUTPOINT, static_cast<pt::ptree>(outpoint));
        tree.add_child(JSONKEY_SCRIPTSIG, static_cast<pt::ptree>(scriptSig));
        tree.add<uint32_t>(JSONKEY_SEQUENCE, sequence);
        return tree;
    }
    
    ConclaveInput::operator std::string() const
    {
        return jsonToString(static_cast<pt::ptree>(*this));
    }
    
    bool ConclaveInput::operator==(const ConclaveInput& other) const
    {
        return (outpoint == other.outpoint) && (scriptSig == other.scriptSig) && (sequence == other.sequence);
    }
    
    bool ConclaveInput::operator!=(const ConclaveInput& other) const
    {
        return (outpoint != other.outpoint) || (scriptSig != other.scriptSig) || (sequence != other.sequence);
    }
    
    std::ostream& operator<<(std::ostream& os, const ConclaveInput& ConclaveInput)
    {
        os << static_cast<std::string>(ConclaveInput);
        return os;
    }
}