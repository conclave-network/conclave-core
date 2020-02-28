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

#define BOOST_TEST_MODULE Script_Test

#include <boost/test/included/unit_test.hpp>
#include <boost/property_tree/ptree.hpp>
#include "../src/address.h"
#include "../src/script.h"
#include "../src/util/hex.h"
#include "../src/util/json.h"

namespace pt = boost::property_tree;
using namespace bc::system;
using namespace bc::system::machine;
using namespace conclave;
const std::string ADDRESS_HASH_HEXSTR = "39a95df3c155a9c017c2099723a0a70ef85721b0";
const std::string P2PKH_SCRIPT_HEXSTR = "76a91439a95df3c155a9c017c2099723a0a70ef85721b088ac";
const std::string P2SH_SCRIPT_HEXSTR = "a91439a95df3c155a9c017c2099723a0a70ef85721b087";
const std::vector<BYTE> ADDRESS_HASH_BYTES = hexStringToByteVector(ADDRESS_HASH_HEXSTR);
const std::vector<BYTE> P2PKH_SCRIPT_BYTES = hexStringToByteVector(P2PKH_SCRIPT_HEXSTR);
const std::vector<BYTE> P2SH_SCRIPT_BYTES = hexStringToByteVector(P2SH_SCRIPT_HEXSTR);
const std::vector<std::string> P2PKH_SCRIPT_STRVEC = {
    "dup",
    "hash160",
    "[" + ADDRESS_HASH_HEXSTR + "]",
    "equalverify",
    "checksig"
};
const std::vector<std::string> P2SH_SCRIPT_STRVEC = {
    "hash160",
    "[" + ADDRESS_HASH_HEXSTR + "]",
    "equal"
};
const std::string P2PKH_SCRIPT_STR = "dup hash160 [" + ADDRESS_HASH_HEXSTR + "] equalverify checksig";
const std::string P2SH_SCRIPT_STR = "hash160 [" + ADDRESS_HASH_HEXSTR + "] equal";
const char* P2PKH_SCRIPT_CSTR = P2PKH_SCRIPT_STR.c_str();
const char* P2SH_SCRIPT_CSTR = P2SH_SCRIPT_STR.c_str();
const pt::ptree P2PKH_SCRIPT_PTREE = vectorOfPrimitivesToArray(P2PKH_SCRIPT_STRVEC);
const pt::ptree P2SH_SCRIPT_PTREE = vectorOfPrimitivesToArray(P2SH_SCRIPT_STRVEC);
const std::array<BYTE, SMALL_HASH_SIZE_BYTES> P2PKH_SCRIPT_HASH160 =
    hexStringToByteArray<SMALL_HASH_SIZE_BYTES>("7f4c795117569c94ea98b5617b42828be0dda062");
const std::array<BYTE, LARGE_HASH_SIZE_BYTES> P2PKH_SCRIPT_HASH256 =
    hexStringToByteArray<LARGE_HASH_SIZE_BYTES>("f2495adae6132c0cd807dae2b71edfcd69c81d11c70fde47822d9ff856f9239b");
const std::array<BYTE, LARGE_HASH_SIZE_BYTES> P2PKH_SCRIPT_SHA256 =
    hexStringToByteArray<LARGE_HASH_SIZE_BYTES>("6c758eb1fb7d743a3c86c3e955b0affeda40025db4ebe860061e7390b0b2e8b6");

BOOST_AUTO_TEST_CASE(ScriptFactoriesTest)
{
    //TODO
}

BOOST_AUTO_TEST_CASE(ScriptConstructorsTest)
{
    Script emptyScript;
    Script p2pkhScriptFromBytes(P2PKH_SCRIPT_BYTES);
    Script p2pkhScriptFromStrVec(P2PKH_SCRIPT_STRVEC);
    Script p2pkhScriptFromStr(P2PKH_SCRIPT_STR);
    Script p2pkhScriptFromCStr(P2PKH_SCRIPT_CSTR);
    Script p2pkhScriptFromPtree(P2PKH_SCRIPT_PTREE);
}

BOOST_AUTO_TEST_CASE(ScriptCastToByteVectorTest)
{
    BOOST_TEST((std::vector<BYTE>) Script(P2PKH_SCRIPT_BYTES) == P2PKH_SCRIPT_BYTES);
}

BOOST_AUTO_TEST_CASE(ScriptCastToStringVectorTest)
{
    BOOST_TEST((std::vector<std::string>) Script(P2PKH_SCRIPT_STRVEC) == P2PKH_SCRIPT_STRVEC);
}

BOOST_AUTO_TEST_CASE(ScriptCastToStringTest)
{
    BOOST_TEST((std::string) Script(P2PKH_SCRIPT_STR) == P2PKH_SCRIPT_STR);
}

BOOST_AUTO_TEST_CASE(ScriptCastToPtreeTest)
{
    BOOST_TEST((pt::ptree) Script(P2PKH_SCRIPT_PTREE) == P2PKH_SCRIPT_PTREE);
}

BOOST_AUTO_TEST_CASE(ScriptOperatorsTest)
{
    Script p2pkhScriptFromBytes(P2PKH_SCRIPT_BYTES);
    Script p2pkhScriptFromStrVec(P2PKH_SCRIPT_STRVEC);
    Script p2pkhScriptFromStr(P2PKH_SCRIPT_STR);
    Script p2pkhScriptFromCStr(P2PKH_SCRIPT_CSTR);
    Script p2pkhScriptFromPtree(P2PKH_SCRIPT_PTREE);
    Script p2shScriptFromBytes(P2SH_SCRIPT_BYTES);
    Script p2shScriptFromStrVec(P2SH_SCRIPT_STRVEC);
    Script p2shScriptFromStr(P2SH_SCRIPT_STR);
    Script p2shScriptFromCStr(P2SH_SCRIPT_CSTR);
    Script p2shScriptFromPtree(P2SH_SCRIPT_PTREE);
    BOOST_TEST(p2pkhScriptFromBytes == p2pkhScriptFromBytes);
    BOOST_TEST(p2pkhScriptFromBytes == p2pkhScriptFromStrVec);
    BOOST_TEST(p2pkhScriptFromBytes == p2pkhScriptFromStr);
    BOOST_TEST(p2pkhScriptFromBytes == p2pkhScriptFromCStr);
    BOOST_TEST(p2pkhScriptFromBytes == p2pkhScriptFromPtree);
    BOOST_TEST(p2pkhScriptFromBytes != p2shScriptFromBytes);
    BOOST_TEST(p2pkhScriptFromBytes != p2shScriptFromStrVec);
    BOOST_TEST(p2pkhScriptFromBytes != p2shScriptFromStr);
    BOOST_TEST(p2pkhScriptFromBytes != p2shScriptFromCStr);
    BOOST_TEST(p2pkhScriptFromBytes != p2shScriptFromPtree);
    BOOST_TEST(p2pkhScriptFromStrVec == p2pkhScriptFromBytes);
    BOOST_TEST(p2pkhScriptFromStrVec == p2pkhScriptFromStrVec);
    BOOST_TEST(p2pkhScriptFromStrVec == p2pkhScriptFromStr);
    BOOST_TEST(p2pkhScriptFromStrVec == p2pkhScriptFromCStr);
    BOOST_TEST(p2pkhScriptFromStrVec == p2pkhScriptFromPtree);
    BOOST_TEST(p2pkhScriptFromStrVec != p2shScriptFromBytes);
    BOOST_TEST(p2pkhScriptFromStrVec != p2shScriptFromStrVec);
    BOOST_TEST(p2pkhScriptFromStrVec != p2shScriptFromStr);
    BOOST_TEST(p2pkhScriptFromStrVec != p2shScriptFromCStr);
    BOOST_TEST(p2pkhScriptFromStrVec != p2shScriptFromPtree);
    BOOST_TEST(p2pkhScriptFromStr == p2pkhScriptFromBytes);
    BOOST_TEST(p2pkhScriptFromStr == p2pkhScriptFromStrVec);
    BOOST_TEST(p2pkhScriptFromStr == p2pkhScriptFromStr);
    BOOST_TEST(p2pkhScriptFromStr == p2pkhScriptFromCStr);
    BOOST_TEST(p2pkhScriptFromStr == p2pkhScriptFromPtree);
    BOOST_TEST(p2pkhScriptFromStr != p2shScriptFromBytes);
    BOOST_TEST(p2pkhScriptFromStr != p2shScriptFromStrVec);
    BOOST_TEST(p2pkhScriptFromStr != p2shScriptFromStr);
    BOOST_TEST(p2pkhScriptFromStr != p2shScriptFromCStr);
    BOOST_TEST(p2pkhScriptFromStr != p2shScriptFromPtree);
    BOOST_TEST(p2pkhScriptFromCStr == p2pkhScriptFromBytes);
    BOOST_TEST(p2pkhScriptFromCStr == p2pkhScriptFromStrVec);
    BOOST_TEST(p2pkhScriptFromCStr == p2pkhScriptFromStr);
    BOOST_TEST(p2pkhScriptFromCStr == p2pkhScriptFromCStr);
    BOOST_TEST(p2pkhScriptFromCStr == p2pkhScriptFromPtree);
    BOOST_TEST(p2pkhScriptFromCStr != p2shScriptFromBytes);
    BOOST_TEST(p2pkhScriptFromCStr != p2shScriptFromStrVec);
    BOOST_TEST(p2pkhScriptFromCStr != p2shScriptFromStr);
    BOOST_TEST(p2pkhScriptFromCStr != p2shScriptFromCStr);
    BOOST_TEST(p2pkhScriptFromCStr != p2shScriptFromPtree);
    BOOST_TEST(p2pkhScriptFromPtree == p2pkhScriptFromBytes);
    BOOST_TEST(p2pkhScriptFromPtree == p2pkhScriptFromStrVec);
    BOOST_TEST(p2pkhScriptFromPtree == p2pkhScriptFromStr);
    BOOST_TEST(p2pkhScriptFromPtree == p2pkhScriptFromCStr);
    BOOST_TEST(p2pkhScriptFromPtree == p2pkhScriptFromPtree);
    BOOST_TEST(p2pkhScriptFromPtree != p2shScriptFromBytes);
    BOOST_TEST(p2pkhScriptFromPtree != p2shScriptFromStrVec);
    BOOST_TEST(p2pkhScriptFromPtree != p2shScriptFromStr);
    BOOST_TEST(p2pkhScriptFromPtree != p2shScriptFromCStr);
    BOOST_TEST(p2pkhScriptFromPtree != p2shScriptFromPtree);
    BOOST_TEST(p2shScriptFromBytes != p2pkhScriptFromBytes);
    BOOST_TEST(p2shScriptFromBytes != p2pkhScriptFromStrVec);
    BOOST_TEST(p2shScriptFromBytes != p2pkhScriptFromStr);
    BOOST_TEST(p2shScriptFromBytes != p2pkhScriptFromCStr);
    BOOST_TEST(p2shScriptFromBytes != p2pkhScriptFromPtree);
    BOOST_TEST(p2shScriptFromBytes == p2shScriptFromBytes);
    BOOST_TEST(p2shScriptFromBytes == p2shScriptFromStrVec);
    BOOST_TEST(p2shScriptFromBytes == p2shScriptFromStr);
    BOOST_TEST(p2shScriptFromBytes == p2shScriptFromCStr);
    BOOST_TEST(p2shScriptFromBytes == p2shScriptFromPtree);
    BOOST_TEST(p2shScriptFromStrVec != p2pkhScriptFromBytes);
    BOOST_TEST(p2shScriptFromStrVec != p2pkhScriptFromStrVec);
    BOOST_TEST(p2shScriptFromStrVec != p2pkhScriptFromStr);
    BOOST_TEST(p2shScriptFromStrVec != p2pkhScriptFromCStr);
    BOOST_TEST(p2shScriptFromStrVec != p2pkhScriptFromPtree);
    BOOST_TEST(p2shScriptFromStrVec == p2shScriptFromBytes);
    BOOST_TEST(p2shScriptFromStrVec == p2shScriptFromStrVec);
    BOOST_TEST(p2shScriptFromStrVec == p2shScriptFromStr);
    BOOST_TEST(p2shScriptFromStrVec == p2shScriptFromCStr);
    BOOST_TEST(p2shScriptFromStrVec == p2shScriptFromPtree);
    BOOST_TEST(p2shScriptFromStr != p2pkhScriptFromBytes);
    BOOST_TEST(p2shScriptFromStr != p2pkhScriptFromStrVec);
    BOOST_TEST(p2shScriptFromStr != p2pkhScriptFromStr);
    BOOST_TEST(p2shScriptFromStr != p2pkhScriptFromCStr);
    BOOST_TEST(p2shScriptFromStr != p2pkhScriptFromPtree);
    BOOST_TEST(p2shScriptFromStr == p2shScriptFromBytes);
    BOOST_TEST(p2shScriptFromStr == p2shScriptFromStrVec);
    BOOST_TEST(p2shScriptFromStr == p2shScriptFromStr);
    BOOST_TEST(p2shScriptFromStr == p2shScriptFromCStr);
    BOOST_TEST(p2shScriptFromStr == p2shScriptFromPtree);
    BOOST_TEST(p2shScriptFromCStr != p2pkhScriptFromBytes);
    BOOST_TEST(p2shScriptFromCStr != p2pkhScriptFromStrVec);
    BOOST_TEST(p2shScriptFromCStr != p2pkhScriptFromStr);
    BOOST_TEST(p2shScriptFromCStr != p2pkhScriptFromCStr);
    BOOST_TEST(p2shScriptFromCStr != p2pkhScriptFromPtree);
    BOOST_TEST(p2shScriptFromCStr == p2shScriptFromBytes);
    BOOST_TEST(p2shScriptFromCStr == p2shScriptFromStrVec);
    BOOST_TEST(p2shScriptFromCStr == p2shScriptFromStr);
    BOOST_TEST(p2shScriptFromCStr == p2shScriptFromCStr);
    BOOST_TEST(p2shScriptFromCStr == p2shScriptFromPtree);
    BOOST_TEST(p2shScriptFromPtree != p2pkhScriptFromBytes);
    BOOST_TEST(p2shScriptFromPtree != p2pkhScriptFromStrVec);
    BOOST_TEST(p2shScriptFromPtree != p2pkhScriptFromStr);
    BOOST_TEST(p2shScriptFromPtree != p2pkhScriptFromCStr);
    BOOST_TEST(p2shScriptFromPtree != p2pkhScriptFromPtree);
    BOOST_TEST(p2shScriptFromPtree == p2shScriptFromBytes);
    BOOST_TEST(p2shScriptFromPtree == p2shScriptFromStrVec);
    BOOST_TEST(p2shScriptFromPtree == p2shScriptFromStr);
    BOOST_TEST(p2shScriptFromPtree == p2shScriptFromCStr);
    BOOST_TEST(p2shScriptFromPtree == p2shScriptFromPtree);
}

BOOST_AUTO_TEST_CASE(ScriptToHexStringTest)
{
    BOOST_TEST(Script(P2PKH_SCRIPT_BYTES).toHexString() == P2PKH_SCRIPT_HEXSTR);
}

BOOST_AUTO_TEST_CASE(ScriptGetHash160Test)
{
    BOOST_TEST(Script(P2PKH_SCRIPT_BYTES).getHash160() == P2PKH_SCRIPT_HASH160);
}

BOOST_AUTO_TEST_CASE(ScriptGetHash256Test)
{
    BOOST_TEST(Script(P2PKH_SCRIPT_BYTES).getHash256() == P2PKH_SCRIPT_HASH256);
}

BOOST_AUTO_TEST_CASE(ScriptGetSingleSHA256Test)
{
    BOOST_TEST(Script(P2PKH_SCRIPT_BYTES).getSingleSHA256() == P2PKH_SCRIPT_SHA256);
}
