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

#pragma once

#include "../address.h"
#include "../config/conclave_chain_config.h"

/***
 * Abstraction layer over the Conclave blockchain. All interaction with the Conclave chain
 * such as getting blocks, transactions, wallet balances, as well as submitting new transactions,
 * must be done through this class.
 */

namespace conclave
{
    namespace chain
    {
        class ConclaveChain
        {
            public:
            explicit ConclaveChain(const ConclaveChainConfig&);
            const uint64_t getAddressBalance(const Address&);
            private:
        };
    }
}