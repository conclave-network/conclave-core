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

#define BOOST_TEST_MODULE Bitcoin_Tx_Test

#include <boost/test/included/unit_test.hpp>
#include "../../src/structs/bitcoin_input.h"
#include "../../src/structs/bitcoin_output.h"
#include <cstdint>

namespace conclave
{
    const static std::vector<BitcoinInput> INPUTS_1 = {
        BitcoinInput(
            Outpoint("0000000000000000000000000000000000000000000000000000000000000000", 5),
            Script(),
            66
        )
    };
    const static std::vector<BitcoinOutput> OUTPUTS_1 = {
        //TODO
    };
    const static uint32_t VERSION_1 = 1;
    const static uint32_t VERSION_2 = 2;
    const static uint32_t LOCKTIME_1 = 0;
    const static uint32_t LOCKTIME_2 = 0xffffffff;
    
    BOOST_AUTO_TEST_CASE(BitcoinTxConstructorsTest)
    {
        BOOST_TEST(true); // Dummy test because no tests will fail
    }
}
