/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <circles.hpp>

/**
 *  The init() and apply() methods must have C calling convention so that the blockchain can lookup and
 *  call these methods.
 */

namespace circles {
    void createAccount(uint64_t account)
    {
        
    }
    void addTokens(uint64_t account, uint64_t token_name, uint64_t amount) {
        token query;
        query.token = token_name;
        bool getToken = tokenTable::get(query, account);
        query.balance = query.balance + amount;
        if(getToken == true) {
            tokenTable::update(query, account);
        } else {
            tokenTable::store(query, account);
        }
    }
    uint64_t getTokens(uint64_t account, uint64_t token_name){
	token query;
        query.token = token_name;
        tokenTable::get(query, account);
        return query.balance;
    }

    bool trust_exists(trust_relation relation){
        trust query;
        query.trustee = relation.trustee;
        return trustTable::get(query, relation.trustor);
    }

    void claimTokens(uint64_t account)
    {
        require_auth(account);
        last_claim query;
        query.account = account;
        bool exists = last_claims::get(query);
        if(!exists){      
            eosio::print("Created account at: ", now());
        }else{
            uint64_t diff = now() - query.last_claim;
            eosio::print("Granting tokens: ", diff);
            addTokens(account, account, diff);
        }

        last_claim lc { account, now() };
        last_claims::store(lc);
          
    }

    void trust_account(trust_relation relation)
    {       
          require_auth(relation.trustor);
          if(relation.trustor == relation.trustee){
               eosio::print("An account was prohibited in trusting itself");
               return;
          }
          trust query;
          query.trustee = relation.trustee;
          bool exists = trustTable::get(query, relation.trustor);
          if(!exists){
               trustTable::store(query, relation.trustor);
          eosio::print(eosio::name(relation.trustor),  " trusted account ", eosio::name(relation.trustee), " \n");
          } else {
              eosio::print(eosio::name(relation.trustor), " tried to trust ", eosio::name(relation.trustee), " but already did.");
          }
    }

    void untrust_account	(trust_relation relation)
    {       
          require_auth(relation.trustor);
          if(relation.trustor == relation.trustee){
               eosio::print("An account was prohibited in untrusting itself");
               return;
          }
          trust query;
          query.trustee = relation.trustee;
          bool exists = trustTable::get(query, relation.trustor);
          if(exists){
               trustTable::remove(query, relation.trustor);
          eosio::print(eosio::name(relation.trustor),  " untrusted account ", eosio::name(relation.trustee), " \n");
          } else {
              eosio::print(eosio::name(relation.trustor), " tried to untrust ", eosio::name(relation.trustee), " but already did.");
          }
    }
    void apply_exchange(exchange msg)
    {
        require_auth(msg.from);
        if(msg.from_currency != msg.to && !trust_exists({msg.to, msg.from_currency})){
            eosio::print("Exchange failed because ", eosio::name(msg.to), " does not trust ", eosio::name(msg.from_currency));
            return;
        }else if(!trust_exists({msg.to, msg.from})){
            eosio::print("Exchange failed because ", eosio::name(msg.to), " does not trust ", eosio::name(msg.from));
            return;
        }
        if(getTokens(msg.from, msg.from_currency) < msg.amount){
            eosio::print("Exchange failed because ", eosio::name(msg.from), "'s ", eosio::name(msg.from_currency), " balance is smaller then ", msg.amount);
            return;
        }
        if(getTokens(msg.to, msg.to_currency) < msg.amount){
            eosio::print("Exchange failed because ", eosio::name(msg.to), "'s ", eosio::name(msg.to_currency), " balance is smaller then ", msg.amount);
            return;
        }
	addTokens(msg.from, msg.from_currency, -msg.amount);
	addTokens(msg.from, msg.to_currency, msg.amount);
	addTokens(msg.to, msg.to_currency, -msg.amount);
	addTokens(msg.to, msg.from_currency, msg.amount);

        eosio::print( "Transfered ", msg.amount, " from ", eosio::name(msg.from),"(", eosio::name(msg.from_currency), ") to ", eosio::name(msg.to), "(", eosio::name(msg.to_currency),  ")\n" );
        
        
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
             account message;
	     static_assert(sizeof(message) == 1*sizeof(uint64_t), "unexpected padding");
	     auto read = read_message(&message, sizeof(message));
	     assert(read == sizeof(message), "message too short");
             circles::claimTokens(message.account);
         }
	 else if(action == N(trust))
	 {
             trust_relation message;
	     static_assert(sizeof(message) == 2*sizeof(uint64_t), "unexpected padding");
	     auto read = read_message(&message, sizeof(message));
	     assert(read == sizeof(message), "message too short");
             circles::trust_account(message);
         }
	 else if(action == N(untrust))
	 {
             trust_relation message;
	     static_assert(sizeof(message) == 2*sizeof(uint64_t), "unexpected padding");
	     auto read = read_message(&message, sizeof(message));
	     assert(read == sizeof(message), "message too short");
             circles::untrust_account(message);
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