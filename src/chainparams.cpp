// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x87;
        pchMessageStart[1] = 0x88;
        pchMessageStart[2] = 0x89;
        pchMessageStart[3] = 0x90;
        vAlertPubKey = ParseHex("04e120345923470dc15273cc4c0b9781f7ea7395da9f1f5ecdc0c51d2859ce2144afb25e3ce3158139cbf53abd7570e78759b09c6c77baf7a1284cc10bb5725fcc");
        nDefaultPort = 18714;
        nRPCPort = 18715;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 10);

        const char* pszTimestamp = "ForeverCoin 13 December 2014";
        CTransaction txNew;
        txNew.nTime = 1418428800;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1418428800;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 0xc76;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock ==	 uint256("0x003dad41f30dc95aea940d60de3d47ee4e2ba8e7807ba6c46ed4f0da2e45abde"));
        assert(genesis.hashMerkleRoot == uint256("0x087113a8f83c790a13220f4673ea2ae39d2f3fe10d85b6ffe66cfc33870ddf30"));

        vSeeds.push_back(CDNSSeedData("beijing.forevercoin.co", "beijing.forevercoin.co"));
        vSeeds.push_back(CDNSSeedData("guangzhou.forevercoin.co", "guangzhou.forevercoin.co"));
        vSeeds.push_back(CDNSSeedData("shanghai.forevercoin.co", "shanghai.forevercoin.co"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(36);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(25);
        base58Prefixes[SECRET_KEY] =     list_of(164);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x99;
        pchMessageStart[1] = 0x99;
        pchMessageStart[2] = 0x99;
        pchMessageStart[3] = 0x99;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04764d4d41b32693ebd2a03d7449a46f48d3f60dd183902003e4dd39adbee09c6233a0b2d0db75c8c9e0e8b2aba38c6d56557f0d03e7f148593d6cf89ed6c8ddd8");
        nDefaultPort = 17814;
        nRPCPort = 17815;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0x1325e;


	
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000072f40ee14ab78fde50f18d6fefb394301e6d671c4894612d58e66cffac4d"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x77;
        pchMessageStart[1] = 0x77;
        pchMessageStart[2] = 0x77;
        pchMessageStart[3] = 0x77;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1411111111;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 4;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
	
        assert(hashGenesisBlock == uint256("0x4b8cc393a13da4f8a4575119a4194873f094aba23766b48663ca3724ba0664cf"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
