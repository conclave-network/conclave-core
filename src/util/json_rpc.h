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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdexcept>
#include <string>

namespace pt = boost::property_tree;
namespace conclave
{
    const static std::string JSON_RPC_DEFAULT_ERROR_MESSAGE = "JSON-RPC Error";
    
    const pt::ptree buildRequest(const std::string& methodName)
    {
        pt::ptree request;
        request.add("jsonrpc", "2.0");
        request.add("id", 0);
        request.add("method", methodName);
        return request;
    }
    
    const pt::ptree getResultOrThrowError(const pt::ptree& response)
    {
        /**
         * TODO - remove this god-awful code when we get a new and better JSON library
         */
        try {
            const std::optional<std::string> resultStr = getOptionalPrimitiveFromJson<std::string>(response, "result");
            if (resultStr.has_value()) {
                if (resultStr->length() > 0) {
                    pt::ptree res;
                    res.add("result", *resultStr);
                    return res;
                }
            }
        } catch (...) {}
        try {
            const boost::optional<const pt::ptree&> resultPtree = response.get_child_optional("result");
            if (resultPtree.has_value()) {
                return *resultPtree;
            }
        } catch (...) {}
        const boost::optional<const pt::ptree&> error = response.get_child_optional("error");
        std::string errMsg =
            error.has_value() ?
            error.get().get<std::string>("message", JSON_RPC_DEFAULT_ERROR_MESSAGE)
                              : JSON_RPC_DEFAULT_ERROR_MESSAGE;
        throw std::runtime_error(errMsg);
    }
}
