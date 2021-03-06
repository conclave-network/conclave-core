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

#include "../config/bitcoin_chain_config.h"
#include "electrumx/electrumx_client.h"
#include "../structs/bitcoin_tx.h"
#include "../structs/bitcoin_rich_output.h"
#include "../structs/outpoint.h"
#include "../address.h"
#include "../hash256.h"
#include <cstdint>
/***
 * Abstraction layer over the Bitcoin blockchain. All interaction with the bitcoin base chain
 * such as getting blocks, transactions, wallet balances, as well as submitting new transactions,
 * must be done through this class.
 *
 * Currently, a single electrumx (electrum-server) instance is used as the source of truth for all
 * blockchain stuff, but this may not be the case in the future.
 */

namespace conclave
{
    namespace chain
    {
        using namespace electrumx;
        
        class BitcoinChain
        {
            public:
            // Constructors
            explicit BitcoinChain(const BitcoinChainConfig&);
            // Public Functions
            const uint64_t getAddressBalance(const Address&);
            const std::vector<BitcoinRichOutput> getUtxos(const Address&);
            const std::optional<BitcoinTx> getTx(const Hash256&);
            const Hash256 submitTx(const BitcoinTx&);
            const bool txIsConfirmed(const Hash256&);
            const bool outputIsConclaveOwned(const Outpoint& outpoint);
            const Hash256 getLatestBlockHash();
            const uint64_t getLatestBlockHeight();
            private:
            // Properties
            ElectrumxClient electrumxClient;
        };
    }
}
