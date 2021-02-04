#include <eosio/eosio.hpp>

using namespace eosio;

// class [[eosio::conytract]] 
CONTRACT widgets : public contract {
  public:

    using contract::contract;

    ACTION welcome( name arrival) {
      check( has_auth( name ( "widgetsboss") ), "You're not my daddy.");
      check( arrival == name ("widgetsboss"), "You lied about your name!");
      print ("Welcome to Widgets Incorporated.");
    }

    ACTION onlyboss() {
      require_auth( name ( "widgetsboss") );
      print ("Only user widgetsboss is allowed here. Hello BOSS.");
    }

    ACTION goodbye( name leaving) { 
      print ("Goodbye...", leaving);
    }

};