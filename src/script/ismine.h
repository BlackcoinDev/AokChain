// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020 The AokChain Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AOKCHAIN_SCRIPT_ISMINE_H
#define AOKCHAIN_SCRIPT_ISMINE_H

#include "script/standard.h"
#include "chain.h"

#include <stdint.h>

class CKeyStore;
class CScript;

/** IsMine() return codes */
enum isminetype
{
    ISMINE_NO = 0,
    //! Indicates that we don't know how to create a scriptSig that would solve this if we were given the appropriate private keys
    ISMINE_WATCH_UNSOLVABLE = 1,
    //! Indicates that we know how to create a scriptSig that would solve this if we were given the appropriate private keys
    ISMINE_WATCH_SOLVABLE = 2,
    ISMINE_WATCH_ONLY = ISMINE_WATCH_SOLVABLE | ISMINE_WATCH_UNSOLVABLE,
    ISMINE_SPENDABLE = 4,
    ISMINE_STAKABLE = 8,
    ISMINE_SPENDABLE_STAKABLE = ISMINE_SPENDABLE | ISMINE_STAKABLE,
    ISMINE_ALL = ISMINE_WATCH_ONLY | ISMINE_SPENDABLE | ISMINE_STAKABLE
};
/** used for bitflags of isminetype */
typedef uint8_t isminefilter;

/* isInvalid becomes true when the script is found invalid by consensus or policy. This will terminate the recursion
 * and return a ISMINE_NO immediately, as an invalid script should never be considered as "mine". This is needed as
 * different SIGVERSION may have different network rules. Currently the only use of isInvalid is indicate uncompressed
 * keys in SIGVERSION_WITNESS_V0 script, but could also be used in similar cases in the future
 */
isminetype IsMine(const CKeyStore& keystore, const CScript& scriptPubKey, CBlockIndex* bestBlock, bool& isInvalid, SigVersion = SIGVERSION_BASE);
isminetype IsMine(const CKeyStore& keystore, const CScript& scriptPubKey, CBlockIndex* bestBlock, SigVersion = SIGVERSION_BASE);
isminetype IsMine(const CKeyStore& keystore, const CTxDestination& dest, CBlockIndex* bestBlock, bool& isInvalid, SigVersion = SIGVERSION_BASE);
isminetype IsMine(const CKeyStore& keystore, const CTxDestination& dest, CBlockIndex* bestBlock, SigVersion = SIGVERSION_BASE);

bool IsTimeLock(const CKeyStore &keystore, const CScript& scriptPubKey, CScriptNum& nLockTime);
bool IsTimeLock(const CScript& scriptPubKey, CScriptNum& nLockTime);

#endif // AOKCHAIN_SCRIPT_ISMINE_H
