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

#pragma once

#include "../../../../util/json.h"
#include "../../../../structs/destination.h"
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;
namespace conclave
{
    namespace rpc
    {
        namespace methods
        {
            namespace make_entry_tx
            {
                struct Destinations final
                {
                    // JSON keys
                    const static std::string JSONKEY_BITCOIN;
                    const static std::string JSONKEY_CONCLAVE;
                    // Constructors
                    Destinations(const std::vector<Destination>&, const std::vector<Destination>&);
                    Destinations(const pt::ptree&);
                    // Operators
                    explicit operator pt::ptree() const;
                    explicit operator std::string() const;
                    bool operator==(const Destinations&) const;
                    bool operator!=(const Destinations&) const;
                    friend std::ostream& operator<<(std::ostream&, const Destinations&);
                    // Properties
                    std::vector<Destination> bitcoinDestinations;
                    std::vector<Destination> conclaveDestinations;
                };
            }
        }
    }
}
