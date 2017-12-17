/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eoslib/eos.hpp>
#include <eoslib/db.hpp>


namespace circles {
    struct account {
        uint64_t account;
    };

    struct last_claim {
        uint64_t account;
        time last_claim;
    };

    struct token_ownership {
        uint64_t owner;
        uint64_t token;
        uint64_t balance;
    };
    
    struct trust_relation {
        uint64_t trustor;
        uint64_t trustee;
    };

    struct exchange {
        uint64_t from;
        uint64_t from_currency;
        uint64_t to;
        uint64_t to_currency;
        uint64_t amount;
    };
    
    using last_claims = eosio::table<N(testacc), N(testacc), N(lastclaims), last_claim, uint64_t>;
    using token_owners = eosio::table<N(testacc), N(testacc), N(tokenowners), token_ownership, uint64_t, uint64_t>;
    using trust_relations = eosio::table<N(testacc), N(testacc), N(trusts), trust_relation, uint64_t, uint64_t>;
}