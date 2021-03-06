//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef RIPPLE_APP_MISC_ACCOUNTSTATE_H_INCLUDED
#define RIPPLE_APP_MISC_ACCOUNTSTATE_H_INCLUDED

#include <ripple/basics/Blob.h>
#include <ripple/protocol/RippleAddress.h>
#include <ripple/protocol/STAmount.h>
#include <ripple/protocol/STLedgerEntry.h>

namespace ripple {

//
// Provide abstract access to an account's state, such that access to the serialized format is hidden.
//

class AccountState
{
public:
    using pointer = std::shared_ptr<AccountState>;

public:
    // For new accounts
    explicit AccountState (RippleAddress const& naAccountID);

    // For accounts in a ledger
    AccountState (SLE::ref ledgerEntry, RippleAddress const& naAccountI);

    bool haveAuthorizedKey ()
    {
        return mLedgerEntry->isFieldPresent (sfRegularKey);
    }

    RippleAddress getAuthorizedKey ()
    {
        return mLedgerEntry->getFieldAccount (sfRegularKey);
    }

    STAmount getBalance () const
    {
        return mLedgerEntry->getFieldAmount (sfBalance);
    }

    std::uint32_t getSeq () const
    {
        return mLedgerEntry->getFieldU32 (sfSequence);
    }

    STLedgerEntry::pointer getSLE ()
    {
        return mLedgerEntry;
    }

    STLedgerEntry const& peekSLE () const
    {
        return *mLedgerEntry;
    }

    STLedgerEntry& peekSLE ()
    {
        return *mLedgerEntry;
    }

    Blob getRaw () const;

    void addJson (Json::Value& value);

    void dump ();

    static std::string createGravatarUrl (uint128 uEmailHash);

private:
    RippleAddress const mAccountID;
    RippleAddress                  mAuthorizedKey;
    STLedgerEntry::pointer mLedgerEntry;

    bool                           mValid;
};

} // ripple

#endif
