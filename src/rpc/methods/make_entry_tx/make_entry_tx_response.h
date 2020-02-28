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

#include "../response.h"
#include "../../../util/json.h"
#include "../../../structs/bitcoin_tx.h"
#include "../../../structs/conclave_entry_tx.h"
#include <iostream>
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
                class MakeEntryTxResponse : public Response
                {
                    public:
                    MakeEntryTxResponse(const BitcoinTx& bitcoinTx, const ConclaveEntryTx& conclaveEntryTx)
                        : bitcoinTx(bitcoinTx), conclaveEntryTx(conclaveEntryTx)
                    {
                    }
                    
                    RpcMethod getMethod() const override
                    {
                        return rpcMethod;
                    }
                    
                    const std::string& getMethodName() const override
                    {
                        return rpcMethodToString(rpcMethod);
                    }
                    
                    private:
                    void serialize()
                    {
                        pt::ptree tree;
                        tree.add_child("bitcoinTx", static_cast<pt::ptree>(bitcoinTx));
                        tree.add_child("conclaveEntryTx", static_cast<pt::ptree>(conclaveEntryTx));
                        serializedJson = jsonToString(tree);
                    }
                    
                    const static RpcMethod rpcMethod = RpcMethod::MakeEntryTx;
                    const BitcoinTx bitcoinTx;
                    const ConclaveEntryTx conclaveEntryTx;
                };
            }
        }
    }
}
