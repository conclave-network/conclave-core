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

#include "conclave_output.h"
#include "../util/json.h"

namespace conclave
{
    const std::string ConclaveOutput::JSONKEY_SCRIPTPUBKEY = "scriptPubKey";
    const std::string ConclaveOutput::JSONKEY_VALUE = "value";
    const std::string ConclaveOutput::JSONKEY_PREDESESSOR = "predesessor";
    
    ConclaveOutput::ConclaveOutput(const Script& scriptPubKey, const uint64_t value)
        : scriptPubKey(scriptPubKey), value(value), predesessor(std::nullopt)
    {
    }
    
    ConclaveOutput::ConclaveOutput(const Script& scriptPubKey, const uint64_t value, const Outpoint& predesessor)
        : scriptPubKey(scriptPubKey), value(value), predesessor(predesessor)
    {
    }
    
    ConclaveOutput::ConclaveOutput(const pt::ptree& tree)
        : ConclaveOutput(getObjectFromJson<Script>(tree, JSONKEY_SCRIPTPUBKEY),
                         getPrimitiveFromJson<uint64_t>(tree, JSONKEY_VALUE),
                         *getOptionalObjectFromJson<Outpoint>(tree, JSONKEY_PREDESESSOR))
    {
    }
    
    ConclaveOutput::operator pt::ptree() const
    {
        pt::ptree tree;
        tree.add_child(JSONKEY_SCRIPTPUBKEY, (pt::ptree) scriptPubKey);
        tree.add<uint64_t>(JSONKEY_VALUE, value);
        if (predesessor.has_value()) {
            tree.add_child(JSONKEY_PREDESESSOR, static_cast<pt::ptree>(*predesessor));
        }
        return tree;
    }
    
    ConclaveOutput::operator std::string() const
    {
        return jsonToString(static_cast<pt::ptree>(*this));
    }
    
    bool ConclaveOutput::operator==(const ConclaveOutput& other) const
    {
        return (scriptPubKey == other.scriptPubKey) && (value == other.value) && (predesessor == other.predesessor);
    }
    
    bool ConclaveOutput::operator!=(const ConclaveOutput& other) const
    {
        return (scriptPubKey != other.scriptPubKey) || (value != other.value) || (predesessor != other.predesessor);
    }
    
    std::ostream& operator<<(std::ostream& os, const ConclaveOutput& conclaveOutput)
    {
        os << static_cast<std::string>(conclaveOutput);
        return os;
    }
}