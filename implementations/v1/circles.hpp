#include <eoslib/eos.hpp>
#include <eoslib/db.hpp>
namespace circles {
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
}