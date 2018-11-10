// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2015-2018 The Proelio developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
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
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
     (0, uint256("3090ce4cbba3c58b8e360d8588b66b82d43f53700948afaefccb128e64704fff")); //gen block
     /*(1, uint256("0000049ae9049f5c3a326f73470c8df7fa140c4b4944cd6ead20d0d8ef05af52"))
     (2, uint256("00000cbbae41ea4681910ab089578ae0d00d0b3ac64f4a04a093a3561e6240c2"))
     (3, uint256("00000acb4b623d299b6d399b915e399f4948c7619f36f5ac12312b304c93cbf4"))
    (20, uint256("000001e98b7c17304ecb6459b5e42dc59c471686f229e54cbdd5c278d6796dfc"))
    (32, uint256("0000027cb99e30ba168aaa08ab3d6e4d3cd2787b88e6db4aa43c1fd60a0b7e53"))
    (40, uint256("0000022948fea578947cb1b73893e5924e6d0e0faf7fd40c8435e18c94fb6827"))
    (45, uint256("0000008b0cf5d87ff9bf6ad5e1b64f874495934b085c414c53ef0489b1db4040"))
    (50, uint256("000000a5b756213648e74ef90cecbc21baf5deab79153506b54f1c498ef99028"));*/


static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1538139600, // * UNIX timestamp of last checkpoint block
    1,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    0,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        
        pchMessageStart[0] = 0x56;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0xae;
        pchMessageStart[3] = 0xd6;

        vAlertPubKey = ParseHex("042c64e450cb49740455f8da340ff2e973dbd855a84e8f2bb67d50fbcf0bf31fb1969e655936548b17d8aef755a7009deb5e46834851b58de582a25cda56286c1f");
        nDefaultPort = 5656;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Proelio starting difficulty is 1 / 2^12
        //nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Proelio: 1 minute
        nTargetSpacing = 1 * 60;  // Proelio: 1 minute
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 100000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 400;
        nModifierUpdateBlock = 999999999;
        nZerocoinStartHeight = 401;
        nZerocoinStartTime = 1538139600;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 1; // Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 268200*COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 99999999;
        nEnforceNewSporkKey = 1538140200;
        nRejectOldSporkKey = 1538139900;
        
        const char* pszTimestamp = "28/09/2018 - SAINT ETIENNE vs. AS MONACO";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);

        txNew.vin[0].scriptSig = CScript() << 504365040 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));

        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1538139600;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 511216;

        hashGenesisBlock = genesis.GetHash();

        /*printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        printf("hashGenesisBlock = %s\n", hashGenesisBlock.ToString().c_str());
        printf("genesis.nTime = %u\n", genesis.nTime);
        printf("genesis.nNonce = %u\n", genesis.nNonce);
        printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());*/

        assert(hashGenesisBlock == uint256("3090ce4cbba3c58b8e360d8588b66b82d43f53700948afaefccb128e64704fff"));
        assert(genesis.hashMerkleRoot == uint256("98a916dc950300b1d5930fd444d1fbbe8e94ab1f255a3b9576fdd731d4a14656"));
     
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 56); //P
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 33); //E
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 115); //o
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x38)(0x21)(0x73)(0x38).convert_to_container<std::vector<unsigned char>>();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x38)(0x21)(0x73)(0x3f).convert_to_container<std::vector<unsigned char>>();       
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x38)(0x21)(0x73).convert_to_container<std::vector<unsigned char>>();
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "048e22882754fe8a5d7bdf161de3f2600bb0f44026bc74b7d9df373729426a3f3d5d4677b4f09c3525a28785054e1fdc7da6f1fae5b620d2dd7f2ec17f423a334d";
        strSporkKeyOld = "0404acb6ae905bf812731aea7594fec55f7f6f7137ed70f3bee1eaebb709c463670b44c2e455d201249edf37d8c69e09e44cc321d07c4f6ed880cacaacf757a147";
        strObfuscationPoolDummyAddress = "PZ6FikG5KWoAYafvsXz7EGkqjXNPWDRCze";
        nStartMasternodePayments = 1538140500;

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zdev to be stakable

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

        pchMessageStart[0] = 0x56;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0x1e;
        pchMessageStart[3] = 0xd7;

        vAlertPubKey = ParseHex("04e266803c0a82bf3c75f06676c939e7bdbb6ee21e47b005785db3e435c5a3d5739e365e9be99c44889303106d3c39bcb77a1123d3aea8356f54872e45adaba0f7");
        nDefaultPort = 5658;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Proelio: 1 minute
        nTargetSpacing = 1 * 60;  // Proelio: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 1000000 * COIN;
        nZerocoinStartHeight = 201576;
        nZerocoinStartTime = 1533754167;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 444020; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1533754527; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1533754386; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1533754167;
        genesis.nNonce = 1254338;

        hashGenesisBlock = genesis.GetHash();

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 119);// p or q
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19); // 8 or 9
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 126);    // s or t
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x38)(0x21)(0x73)(0x39).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x38)(0x21)(0x73)(0x40).convert_to_container<std::vector<unsigned char> >();       
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x38)(0x21)(0x74).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04318049abd8fa67bd549bc55ef4db106859a532aa476e42489b9a801eadf3f52a05f9703868b9849fa7635e480b88c22564cc2802de355ee5d26a732b2b28db2a";
        strSporkKeyOld = "04671991be4d8f7dc636526e62f064f588fe8a9a0de07e5d89b43f594628bccf16471e5ca07821cca15b782a2f411ff300955b2b7a7cc8c92cb569c6463b47565d";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1533754612; //Fri, 09 Jan 2015 21:05:58 GMT
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
        pchMessageStart[0] = 0x56;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0x15;
        pchMessageStart[3] = 0x67;
        //nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Proelio: 1 day
        nTargetSpacing = 1 * 60;        // Proelio: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1533755665;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 155014;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 5660;

        vFixedSeeds.clear();
        vSeeds.clear();

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
        nDefaultPort = 5662;
        vFixedSeeds.clear();
        vSeeds.clear();

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
    //virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
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
