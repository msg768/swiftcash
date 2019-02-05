// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 Bitcoin developers
// Copyright (c) 2014-2015 Dash developers
// Copyright (c) 2015-2018 PIVX developers
// Copyright (c) 2018-2019 SwiftCash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0,       uint256("0x000001211fb1c1d0cf722e8934ecc1d6dac522e0489657a8cd6b5ea288f8729b"))
    (10,      uint256("0x1d132334ba027555fec222c488583b58ece0e853e0275f0bea84103bb192bb20"))
    (20,      uint256("0x0c8cdb7d104416dbd1984ae69c3642b65abc8fa2714b9f7cdb692200d7ca2bfc"))
    (40,      uint256("0x7210057aaa88f17e4f841610d7eb8a9803533f52db55e2ee11ee425cb8411527"))
    (50,      uint256("0x30909eca3f3417cf3d5d7314472488a96332bca65b0fee8beb715fc15fa83098"))
    (80,      uint256("0x0f86f76252efe2c5d6c0c5111c941356d409a098dcb0e7800976603361cd12b3"))
    (100,     uint256("0x489777a0366d31276781e923946a3761d2d530b0a0fd9fb22d41e46efd96416f"))
    (110,     uint256("0x7451b12c35bea16f10c958ac95cfb1e84b929d8f76e8d08c7c074846418db0bb"))
    (120,     uint256("0x4bc3cabacb7e88fafe73c01aa8b406d28ebfc72a4df4012525acc0fc6b92ac5c"))
    (130,     uint256("0x329b8c02eead0e4b0a4db09fa33155d6b78401248b413c999b98800df2917c98"))
    (140,     uint256("0x72fc6ebac57f51555e3ee1c6c88bce23f969e5136181cdae208e741bae4a6bb9"))
    (150,     uint256("0x1840996ded1bece1f9acc722a63de32eecf34e100266ca513d11cd169bbaec4d"))
    (180,     uint256("0x4ef6e0069e6a2b8687b81e385576581697e29d04f1ce1285d490a3e5e3d3a118"))
    (200,     uint256("0x461b7eb382d7ba043a68df031681b0b3ee57dcb495e0f28f8d5206b0323fe312"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1540687441, // * UNIX timestamp of last checkpoint block
    0,     	// * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    250         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1540687444,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1540687443,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x42;
        pchMessageStart[1] = 0x1e;
        pchMessageStart[2] = 0x31;
        pchMessageStart[3] = 0xf5;
        vAlertPubKey = ParseHex("03001a39c631d98c9a674d1c855efd7f6cc2a893bf7e8f71f70f5ea4d06c679bc6");
        nDefaultPort = 8544;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 40 * 60; // SwiftCash: 40 minutes
        nTargetSpacing = 1 * 60;  // SwiftCash: 1 minute
        nRetargetInterval = 1; // SwiftCash: each block
        nMaturity = 20;
        nSwiftnodeCountDrift = 20;
        nMaxMoneyOut = 5000000000 * COIN; // 5B

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1; // we use the version 2 for SWIFT

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * node genesis.js -a keccak -t 1540687441 -v 0 -n 21256600 -z "Shooting at Tree of Life Congregation Synagogue in Pittsburgh"
         * ---------------
         * algorithm: keccak
         * pzTimestamp: Shooting at Tree of Life Congregation Synagogue in Pittsburgh
         * pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
         * bits: 504365040
         * time: 1540687441
         * merkle root hash: 28d9b3039993f5d90fda19141eaddc8b4459710bd752e41b6e23388ae5726c26
         * Searching for genesis hash...
         * nonce: 21766572
         * genesis hash: 000001211fb1c1d0cf722e8934ecc1d6dac522e0489657a8cd6b5ea288f8729b
         */
        const char* pszTimestamp = "Shooting at Tree of Life Congregation Synagogue in Pittsburgh";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1540687441;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 21766572;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001211fb1c1d0cf722e8934ecc1d6dac522e0489657a8cd6b5ea288f8729b"));
        assert(genesis.hashMerkleRoot == uint256("0x28d9b3039993f5d90fda19141eaddc8b4459710bd752e41b6e23388ae5726c26"));

        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("seed1.swiftcash.cc", "seed1.swiftcash.cc"));
        vSeeds.push_back(CDNSSeedData("seed2.swiftcash.cc", "seed2.swiftcash.cc"));
        vSeeds.push_back(CDNSSeedData("seed3.swiftcash.cc", "seed3.swiftcash.cc"));

        vSeeds.push_back(CDNSSeedData("seed1.swiftcash.me", "seed1.swiftcash.me"));
        vSeeds.push_back(CDNSSeedData("seed2.swiftcash.me", "seed2.swiftcash.me"));
        vSeeds.push_back(CDNSSeedData("seed3.swiftcash.me", "seed3.swiftcash.me"));

        vSeeds.push_back(CDNSSeedData("seed1.swiftcash.org", "seed1.swiftcash.org"));
        vSeeds.push_back(CDNSSeedData("seed2.swiftcash.org", "seed2.swiftcash.org"));
        vSeeds.push_back(CDNSSeedData("seed3.swiftcash.org", "seed3.swiftcash.org"));

        vSeeds.push_back(CDNSSeedData("seed1.swiftcash.space", "seed1.swiftcash.space"));
        vSeeds.push_back(CDNSSeedData("seed2.swiftcash.space", "seed2.swiftcash.space"));
        vSeeds.push_back(CDNSSeedData("seed3.swiftcash.space", "seed3.swiftcash.space"));

        // SwiftCash addresses start with 'S'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        // SwiftCash script addresses start with '8'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        // SwiftCash private keys start with 'V'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 191);
        // SwiftCash BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // SwiftCash BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // SwiftCash BIP44 coin type is '222' (0x800000de)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xde).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "03ae4c8038c50e10015d436f938237d66d7c8da21ee1a989658424cfe60379da78";
        strSwiftnodePoolDummyAddress = "Sh7nUAg9fWxqhCL2KiqWarsF6VfPBPvJz4";

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x42;
        pchMessageStart[1] = 0x51;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0x8a;
        vAlertPubKey = ParseHex("02c1d175e8a526d9ee25770b7b3d3a4f850f00b611130c2e07c1682aa3a74d5436");
        nDefaultPort = 28544;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 40 * 60; // SwiftCash: 40 minutes
        nTargetSpacing = 1 * 60; // SwiftCash: 1 minute
        nRetargetInterval = 1; // SwiftCash: each block
        nLastPOWBlock = 200;
        nMaturity = 10;
        nSwiftnodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 5000000000 * COIN; // 5B

        genesis.nTime = 1540687444;
        genesis.nNonce = 22026442;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000003f64020a3817b950ad5910917642faff02e3d5ec7cca9262db1bbb63038"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnetseed.swiftcash.cc", "testnetseed.swiftcash.cc"));
        vSeeds.push_back(CDNSSeedData("testnetseed.swiftcash.org", "testnetseed.swiftcash.org"));
        vSeeds.push_back(CDNSSeedData("testnetseed.swiftcash.space", "testnetseed.swiftcash.space"));
        vSeeds.push_back(CDNSSeedData("testnetseed.swiftcash.me", "testnetseed.swiftcash.me"));


        // Testnet SwiftCash addresses start with 'T'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65);
        // Testnet SwiftCash script addresses start with '5'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 11);
        // Testnet private keys start with 'U'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 188);
        // Testnet SwiftCash BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet SwiftCash BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet swiftcash BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "02c78ca70bcaea5468843854bebae65123b0e8ad99b0cbda98504160b71179d42b";
        strSwiftnodePoolDummyAddress = "THSwiJRv9UBw5pHVFxvzji5odtySjgyskh";
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x11;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0x43;
        pchMessageStart[3] = 0xff;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 40 * 60; // SwiftCash: 40 minutes
        nTargetSpacing = 1 * 60;  // SwiftCash: 1 minute
        nRetargetInterval = 1; // SwiftCash: each block
        bnProofOfWorkLimit = ~uint256(0) >> 1;

        genesis.nTime = 1540687443;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 21689207;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 48544;
        assert(hashGenesisBlock == uint256("0x00000928717cf50aacdb893a35686a88d33f912f60ff349ca90be0979301ce6e"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51488;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
