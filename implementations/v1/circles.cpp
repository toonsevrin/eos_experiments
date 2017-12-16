#include <circles.hpp>

namespace circles {
    void createAccount(uint64_t account)
    {
        
    }
    void claimTokens(uint64_t account)
    {
          require_auth(account);
    }
    void trust(trust_relation relation)
    {       
          require_auth(relation.trustor);
          eosio::print("TODO: Let ", eosio::name(relation.trustor),  " trust account ", eosio::name(relation.trustee), " \n");
    }
    void untrust(trust_relation relation)
    {       
          require_auth(relation.trustor);
    }
    void apply_exchange(exchange exchange_msg)
    {
        require_auth(exchange_msg.from);
        eosio::print( "Transfer ", exchange_msg.amount, " from ", eosio::name(exchange_msg.from),"(", eosio::name(exchange_msg.from_currency), ") to ", eosio::name(exchange_msg.to), "(", eosio::name(exchange_msg.to_currency),  ")\n" );
    }

}

using namespace circles;

extern "C" {

    void init()  {
       eosio::print( "Initializing Circles V1 contract\n" );
    }

/// The apply method implements the dispatch of events to this contract
    void apply( uint64_t code, uint64_t action ) 
    {
         if(action == N(newaccount))
	 {
             eosio::print("TODO: Create new account \n");
         }
	 else if(action == N(claim))
	 {
	     eosio::print("TODO: CLaim currency \n");
         }
	 else if(action == N(trust))
	 {
             trust_relation message;
	     static_assert(sizeof(message) == 2*sizeof(uint64_t), "unexpected padding");
	     auto read = read_message(&message, sizeof(message));
	     assert(read == sizeof(message), "message too short");
             circles::trust(message);
         }
	 else if(action == N(untrust))
	 {
             eosio::print("TODO: UNtrust account \n");
         }
	 else if(action == N(exchange))
	 {
             exchange message;
             eosio::print("TODO: Exchange currency \n");
             static_assert(sizeof(message) == 5*sizeof(uint64_t), "unexpected padding");
	     auto read = read_message(&message, sizeof(message));
             assert(read == sizeof(message), "message too short");
	     circles::apply_exchange(message);
	 }
         eosio::print( "Received: ", eosio::name(code), "->", eosio::name(action), "\n" );
    }

} // extern "C"