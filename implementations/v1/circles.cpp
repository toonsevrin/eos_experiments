extern "C" {

   void init() {
      eosio::print( "Initializing Circles V1 contract\n" );
   }


   struct trust {
       uint64_t target;
   };

   struct untrust {
       uint64_t target;
   };

   struct exchange {
       uint64_t from;
       uint64_t to;
       uint64_t amount;
   };

   /// The apply method implements the dispatch of events to this contract
   void apply(uint64_t code, uint64_t action) {
        if(action == N(newaccount)){
            eosio::print("TODO: Create new account \n");
        }else if(action == N(claim)){
            eosio::print("TODO: CLaim currency \n");
        }else if(action == N(trust)){
            eosio::print("TODO: Trust account \n");
        }else if(action == N(untrust)){
            eosio::print("TODO: UNtrust account \n");
        }else if(action == N(exchange)){
            exchange message;
            eosio::print("TODO: Exchange currency \n");
 static_assert(sizeof(message) == 3*sizeof(uint64_t), "unexpected padding");
            auto read = read_message(&message, sizeof(message));
            assert(read == sizeof(message), "message too short" );
            eosio::print( "Transfer ", message.amount, " from ", eosio::name(message.from), " to ", eosio::name(message.to), "\n" );
        }
        eosio::print( "Received: ", eosio::name(code), "->", eosio::name(action), "\n" );
   }

} // extern "C"
