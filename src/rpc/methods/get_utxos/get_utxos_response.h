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

#include "../response.h"
#include "../../../structs/bitcoin_rich_output.h"
#include "../../../structs/conclave_rich_output.h"
#include "../../../util/json.h"
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;
namespace conclave
{
    namespace rpc
    {
        namespace methods
        {
            namespace get_utxos
            {
                class GetUtxosResponse : public Response
                {
                    public:
                    GetUtxosResponse(const std::vector<BitcoinRichOutput>& bitcoinRichOutputs)
                        : bitcoinRichOutputs(bitcoinRichOutputs), conclaveRichOutputs({})
                    {
                    }
                    
                    GetUtxosResponse(const std::vector<ConclaveRichOutput>& conclaveRichOutputs)
                        : bitcoinRichOutputs({}), conclaveRichOutputs(conclaveRichOutputs)
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
                        if (bitcoinRichOutputs.size() > 0) {
                            tree.add_child("BitcoinRichOutputs",
                                           vectorOfObjectsToArray(bitcoinRichOutputs));
                        }
                        if (conclaveRichOutputs.size() > 0) {
                            tree.add_child("ConclaveRichOutputs",
                                           vectorOfObjectsToArray(conclaveRichOutputs));
                        }
                        serializedJson = ptreeToString(tree);
                    }
                    
                    const static RpcMethod rpcMethod = RpcMethod::GetUtxos;
                    const std::vector<BitcoinRichOutput> bitcoinRichOutputs;
                    const std::vector<ConclaveRichOutput> conclaveRichOutputs;
                };
            }
        }
    }
}
