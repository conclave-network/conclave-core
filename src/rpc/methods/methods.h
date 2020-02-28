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

#include <string>
#include <stdexcept>

namespace conclave
{
    namespace rpc
    {
        // Order matters!
        enum RpcMethod
        {
            NodeInfo,
            SendTx,
            GetAddressBalance,
            MakeEntryTx
        };
        // Order matters!
        static const std::string RPC_METHOD_NAMES[] = {
            "NodeInfo",
            "SendTx",
            "GetAddressBalance",
            "MakeEntryTx"
        };
        static const size_t NUM_RPC_METHODS = sizeof(RPC_METHOD_NAMES) / sizeof(std::string);
        
        inline RpcMethod stringToRpcMethod(const std::string str)
        {
            for (size_t i = 0; i < NUM_RPC_METHODS; i++) {
                if (str == RPC_METHOD_NAMES[i]) {
                    return (RpcMethod) i;
                }
            }
            throw std::runtime_error("Unknown RPC method: " + str);
        }
        
        inline static const std::string& rpcMethodToString(const RpcMethod rpcMethod)
        {
            return RPC_METHOD_NAMES[rpcMethod];
        }
    }
}
