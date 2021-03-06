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

#include "database/database_client.h"
#include "structs/conclave_block.h"
#include "bitcoin_chain.h"
#include "../config/conclave_chain_config.h"
#include "../structs/conclave_tx.h"
#include "../structs/conclave_rich_output.h"
#include "../address.h"
#include "../hash256.h"
#include <cstdint>
/***
 * Abstraction layer over the Conclave blockchain. All interaction with the Conclave chain
 * such as getting blocks, transactions, wallet balances, as well as submitting new transactions,
 * must be done through this class.
 */

namespace conclave
{
    namespace chain
    {
        using namespace database;
        
        class ConclaveChain
        {
            public:
            // Genesis
            const static ConclaveBlock GENESIS_BLOCK;
            // Collection Names
            const static std::string COLLECTION_CHAIN_TIP;
            const static std::string COLLECTION_CLAIMS;
            const static std::string COLLECTION_SPENDS;
            const static std::string COLLECTION_SPEND_TIPS;
            const static std::string COLLECTION_FUND_TIPS;
            // Constructors
            explicit ConclaveChain(const ConclaveChainConfig&, BitcoinChain& bitcoinChain);
            // Public Functions
            const uint64_t getAddressBalance(const Address&);
            const std::vector<ConclaveRichOutput> getUtxos(const Address&);
            const Hash256 submitTx(const ConclaveTx&);
            const Hash256 getChainTipHash();
            const ConclaveBlock getChainTip();
            private:
            // Private Functions
            const uint64_t countFundTotal(const Hash256& walletHash);
            const uint64_t countSpendTotal(const Hash256& walletHash);
            const bool txIsOnBlockchain(const Hash256&);
            const Hash256 processClaimTx(ConclaveTx);
            const Hash256 processTx(ConclaveTx);
            const void withdrawOutputs(const std::vector<BitcoinOutput>&);
            // Properties
            BitcoinChain& bitcoinChain;
            DatabaseClient databaseClient;
        };
    }
}
