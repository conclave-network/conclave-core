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

#include "rpc_config.h"
#include "bitcoin_chain_config.h"
#include "conclave_chain_config.h"
#include "chainwatch_config.h"
#include <string>
#include <optional>

class Config
{
    public:
    explicit Config(const std::string&);
    [[nodiscard]] bool getTestnet() const;
    [[nodiscard]] const std::string& getDisplayName() const;
    [[nodiscard]] const std::string& getPrivateKey() const;
    [[nodiscard]] const RpcConfig& getRpcConfig() const;
    [[nodiscard]] const BitcoinChainConfig& getBitcoinChainConfig() const;
    [[nodiscard]] const ConclaveChainConfig& getConclaveChainConfig() const;
    [[nodiscard]] const ChainwatchConfig& getChainwatchConfig() const;
    private:
    bool testnet;
    std::string displayName;
    std::string privateKey;
    std::optional<RpcConfig> rpcConfig;
    std::optional<BitcoinChainConfig> bitcoinChainConfig;
    std::optional<ConclaveChainConfig> conclaveChainConfig;
    std::optional<ChainwatchConfig> chainwatchConfig;
};
